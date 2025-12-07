# Updated script with Excel outputs

#!/usr/bin/env python3
import os
import pandas as pd
import traceback
from collections import defaultdict
from io import BytesIO

from reportlab.platypus import SimpleDocTemplate, Table, TableStyle, Paragraph, Image, Spacer, Flowable
from reportlab.lib.pagesizes import A4
from reportlab.lib.styles import getSampleStyleSheet, ParagraphStyle
from reportlab.lib import colors

import logging
from logging.handlers import RotatingFileHandler
import argparse
from datetime import datetime

LOG_FILENAME = "app.log"
logger = logging.getLogger("ExamSeatingLogger")
logger.setLevel(logging.DEBUG)
handler = RotatingFileHandler(LOG_FILENAME, maxBytes=500000, backupCount=3)
handler.setFormatter(logging.Formatter('%(asctime)s - %(levelname)s - %(message)s'))
if not logger.hasHandlers():
    logger.addHandler(handler)

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
NO_IMAGE_PATH = os.path.join(BASE_DIR, "no_image_available.png")

if not os.path.exists(NO_IMAGE_PATH):
    raise FileNotFoundError(f"'no_image_available.png' missing at {NO_IMAGE_PATH}")

def safe_strip(x):
    if pd.isna(x):
        return ""
    return str(x).strip()

def check_clashes(subject_rolls):
    clashes = []
    subs = list(subject_rolls.keys())
    for i in range(len(subs)):
        for j in range(i + 1, len(subs)):
            inter = subject_rolls[subs[i]].intersection(subject_rolls[subs[j]])
            for r in inter:
                clashes.append((subs[i], subs[j], r))
    return clashes

def allocate_for_slot(date, day, slot, subjects, students_by_subject, rooms_df, buffer, density, roll_name_map):
    subject_rolls = {}
    subject_counts = {}
    for s in subjects:
        rolls = set(safe_strip(r) for r in students_by_subject.get(s, []) if safe_strip(r))
        subject_rolls[s] = rolls
        subject_counts[s] = len(rolls)

    rooms_info = {}
    rooms_by_block = defaultdict(list)

    for _, row in rooms_df.iterrows():
        room = safe_strip(row.get("Room No.", ""))
        block = safe_strip(row.get("Block", "")) or "Block"
        try:
            cap = int(float(safe_strip(row.get("Exam Capacity", "0"))))
        except:
            cap = 0
        rooms_info[room] = {"block": block, "capacity": cap, "remaining": 0}
        rooms_by_block[block].append(room)

    def eff_cap_room(r):
        return max(0, rooms_info[r]["capacity"] - buffer)

    def eff_cap_per_sub(r):
        base = eff_cap_room(r)
        return base // 2 if density == "sparse" else base

    for r in rooms_info:
        rooms_info[r]["remaining"] = eff_cap_per_sub(r)

    clashes = check_clashes(subject_rolls)

    assignments = {s: [] for s in subjects}

    for s in sorted(subjects, key=lambda x: -subject_counts[x]):
        needed = subject_counts[s]
        assigned = 0

        for block, room_list in rooms_by_block.items():
            for r in room_list:
                if assigned >= needed:
                    break
                take = min(rooms_info[r]["remaining"], needed - assigned)
                if take > 0:
                    rolls = list(subject_rolls[s])[assigned:assigned + take]
                    assignments[s].append({"room": r, "rolls": rolls})
                    rooms_info[r]["remaining"] -= take
                    assigned += take
            if assigned >= needed:
                break

    overall_rows = []
    seats_left_rows = []

    for s in subjects:
        for item in assignments[s]:
            overall_rows.append({
                "Date": date,
                "Day": day,
                "course_code": s,
                "Room": item["room"],
                "Allocated_students_count": len(item["rolls"]),
                "Roll_list(semicolon separated)": ";".join(item["rolls"])
            })

    for r, info in rooms_info.items():
        used = info["capacity"] - info["remaining"]
        seats_left_rows.append({
            "Date": date,
            "Room No.": r,
            "Exam Capacity": info["capacity"],
            "Block": info["block"],
            "Alloted": used,
            "Vacant": info["remaining"]
        })

    return assignments, overall_rows, seats_left_rows, clashes

styles = getSampleStyleSheet()
student_style = ParagraphStyle("student_style", parent=styles["Normal"], fontSize=9, leading=11, alignment=1)
card_name_style = ParagraphStyle("card_name_style", parent=styles["Normal"], fontSize=10, leading=12, alignment=1)
meta_style = ParagraphStyle("meta_style", parent=styles["Normal"], fontSize=9, leading=11, alignment=0)

PAGE_WIDTH = A4[0] - 20
CARD_WIDTH = PAGE_WIDTH / 3

class DashedLine(Flowable):
    def __init__(self, width, height=10):
        Flowable.__init__(self)
        self.width = width
        self.height = height
    def draw(self):
        c = self.canv
        x = 0
        y = self.height / 2.0
        dash_len, space = 3, 2
        pos = x
        while pos < self.width:
            c.line(pos, y, min(pos + dash_len, self.width), y)
            pos += dash_len + space

def make_card(name, roll, seat_no):
    img = Image(NO_IMAGE_PATH, width=42, height=42)
    name_para = Paragraph(f"<b>{name}</b>", card_name_style)
    roll_para = Paragraph(f"Roll: {roll}", student_style)
    seat_para = Paragraph(f"Seat: {seat_no}", student_style)
    sign_para = Paragraph("Signature:", student_style)

    card_table = Table(
        [[img], [seat_para], [name_para], [roll_para], [sign_para], [DashedLine(CARD_WIDTH * 0.9, 12)]],
        colWidths=[CARD_WIDTH * 0.95]
    )
    card_table.setStyle(TableStyle([
        ("BOX", (0,0), (-1,-1), 0.8, colors.HexColor("#2E4053")),
        ("ALIGN", (0,0), (-1,-1), "CENTER"),
        ("VALIGN", (0,0), (-1,-1), "MIDDLE"),
        ("TOPPADDING", (0,0), (-1,-1), 6),
        ("BOTTOMPADDING", (0,0), (-1,-1), 6),
        ("BACKGROUND", (0,0), (0,0), colors.HexColor("#F1F4F8")),
    ]))
    return card_table

def build_attendance_pdf(pdf_path, date, day, slot, room, subject, rolls, roll_name_map):
    pdf_buffer = BytesIO()
    pdf = SimpleDocTemplate(pdf_buffer, pagesize=A4, leftMargin=10, rightMargin=10, topMargin=18, bottomMargin=18)
    elements = []

    elements.append(Paragraph("<b>IITP Attendance System</b>", ParagraphStyle("title", parent=styles["Title"], alignment=1)))
    elements.append(Spacer(1, 6))

    meta_line = Paragraph(f"<b>Date:</b> {date} &nbsp;&nbsp; <b>Day:</b> {day} &nbsp;&nbsp; <b>Shift:</b> {slot} &nbsp;&nbsp; <b>Room:</b> {room} &nbsp;&nbsp; <b>Subject:</b> {subject}", meta_style)
    elements.append(meta_line)
    elements.append(Spacer(1, 10))

    rows = []
    row = []
    seat_no = 1
    for roll in rolls:
        name = roll_name_map.get(roll, "(name not found)")
        card = make_card(name, roll, seat_no)
        seat_no += 1
        row.append(card)
        if len(row) == 3:
            rows.append(row)
            row = []
    if row:
        while len(row) < 3:
            row.append("")
        rows.append(row)

    if rows:
        table = Table(rows, colWidths=[CARD_WIDTH]*3, hAlign='CENTER')
        table.setStyle(TableStyle([
            ('VALIGN', (0,0), (-1,-1), 'TOP'),
            ('LEFTPADDING', (0,0), (-1,-1), 6),
            ('RIGHTPADDING', (0,0), (-1,-1), 6),
            ('BOTTOMPADDING', (0,0), (-1,-1), 8),
            ('TOPPADDING', (0,0), (-1,-1), 8),
        ]))
        elements.append(table)
    else:
        elements.append(Paragraph("No students allocated.", styles["Normal"]))

    elements.append(Spacer(1, 18))
    elements.append(Paragraph("<b>Invigilator Name & Signature</b>", styles["Heading4"]))

    inv = [["Sl No.", "Name", "Signature"]] + [[str(i+1), "", ""] for i in range(8)]
    inv_table = Table(inv, colWidths=[50, PAGE_WIDTH - 260, 200])
    inv_table.setStyle(TableStyle([
        ("GRID", (0,0), (-1,-1), 0.6, colors.black),
        ("BACKGROUND", (0,0), (-1,0), colors.whitesmoke),
        ("ALIGN", (0,0), (-1,0), "CENTER"),
        ("BOTTOMPADDING", (0,0), (-1,0), 6),
    ]))

    elements.append(Spacer(1, 8))
    elements.append(inv_table)

    gen_time = datetime.now().strftime("%Y-%m-%d %H:%M:%S")
    elements.append(Spacer(1, 12))
    elements.append(Paragraph(f"Generated: {gen_time}", ParagraphStyle("footer", parent=styles["Normal"], fontSize=8, alignment=2)))

    pdf.build(elements)

    with open(pdf_path, "wb") as f:
        f.write(pdf_buffer.getvalue())

# === FIXED & REGENERATED FULL CODE BELOW ===

def run(input_path, buffer_val=5, density="dense", output_root=None):
    if output_root is None:
        output_root = os.path.join(BASE_DIR, "output")
    os.makedirs(output_root, exist_ok=True)
    print(f"Output will be saved in: {output_root}")

    try:
        if not os.path.exists(input_path):
            print(f"ERROR: Input file not found: {input_path}")
            return

        xls = pd.ExcelFile(input_path)
        timetable = pd.read_excel(xls, "in_timetable", dtype=str)
        students_df = pd.read_excel(xls, "in_course_roll_mapping", dtype=str)
        rooms_df = pd.read_excel(xls, "in_room_capacity", dtype=str)
        mapping_df = pd.read_excel(xls, "in_roll_name_mapping", dtype=str)

        students_by_subject = defaultdict(list)
        for _, r in students_df.iterrows():
            s = safe_strip(r.get("course_code", ""))
            roll = safe_strip(r.get("rollno", ""))
            if s and roll:
                students_by_subject[s].append(roll)

        roll_name_map = {safe_strip(r.get("Roll", "")): safe_strip(r.get("Name", "")) for _, r in mapping_df.iterrows()}

        total_generated = 0
        all_overall = []
        all_seats_left = []

        for _, row in timetable.iterrows():
            date_val = row.get("Date", "")
            date = date_val.strftime("%Y-%m-%d") if isinstance(date_val, pd.Timestamp) else safe_strip(date_val).split(" ")[0]
            day = safe_strip(row.get("Day", ""))

            for slot in ["Morning", "Evening"]:
                subjects = [safe_strip(s) for s in safe_strip(row.get(slot, "")).split(";") if safe_strip(s)]
                if not subjects:
                    continue

                assignments, overall_rows, seats_left_rows, clashes = allocate_for_slot(
                    date, day, slot, subjects, students_by_subject, rooms_df, buffer_val, density, roll_name_map
                )

                all_overall.extend(overall_rows)
                all_seats_left.extend(seats_left_rows)

                for course, allocs in assignments.items():
                    for alloc in allocs:
                        room = alloc["room"]
                        rolls = alloc["rolls"]

                        folder = os.path.join(output_root, date, slot)
                        os.makedirs(folder, exist_ok=True)

                        safe_course = "".join(c if c.isalnum() or c in ("-", "_") else "_" for c in course)
                        safe_room = "".join(c if c.isalnum() or c in ("-", "_") else "_" for c in room)

                        filename = f"{date}_{safe_course}_{safe_room}_{slot}.pdf"
                        pdf_path = os.path.join(folder, filename)

                        build_attendance_pdf(pdf_path, date, day, slot, room, course, rolls, roll_name_map)
                        total_generated += 1
                        print(f"Saved: {pdf_path}")

        # ===== NEW EXCEL OUTPUTS (FIXED: one sheet per day with Date included) =====
        overall_output_path = os.path.join(output_root, "op_overall_seating_arrangement.xlsx")
        seats_left_output_path = os.path.join(output_root, "op_seats_left.xlsx")

        # overall seating
        pd.DataFrame(all_overall).to_excel(overall_output_path, index=False)
        print(f"Saved: {overall_output_path}")

        # vacancy grouped by date
        df_vac = pd.DataFrame(all_seats_left)
        if "Date" not in df_vac.columns:
            df_vac["Date"] = "UNKNOWN"

        with pd.ExcelWriter(seats_left_output_path) as writer:
            for date_value, df_day in df_vac.groupby("Date"):
                sheet = str(date_value).replace("-", "_").replace("/", "_")
                df_day.to_excel(writer, sheet_name=sheet[:31], index=False)

        print(f"Saved: {seats_left_output_path}")

    except Exception as e:
        logger.error("Error generating seating PDFs", exc_info=True)
        print("ERROR:", e)
        print(traceback.format_exc())

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Generate exam seating PDFs and Excel reports.")
    parser.add_argument("--input", "-i", default="input_data.xlsx")
    parser.add_argument("--buffer", "-b", type=int, default=5)
    parser.add_argument("--density", "-d", choices=["dense", "sparse"], default="dense")
    parser.add_argument("--output", "-o", default=None)
    args = parser.parse_args()
    run(args.input, args.buffer, args.density, args.output)
