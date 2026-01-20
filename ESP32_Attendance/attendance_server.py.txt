from flask import Flask, request
from openpyxl import Workbook, load_workbook
from datetime import datetime
import os

app = Flask(__name__)

FILE = "attendance.xlsx"

# Create or open Excel file
if os.path.exists(FILE):
    wb = load_workbook(FILE)
    ws = wb.active
else:
    wb = Workbook()
    ws = wb.active
    ws.append(["UID", "Date", "Time"])
    wb.save(FILE)

@app.route('/mark', methods=['GET'])
def mark():
    uid = request.args.get('uid')

    now = datetime.now()
    date = now.strftime("%Y-%m-%d")
    time = now.strftime("%H:%M:%S")

    ws.append([uid, date, time])
    wb.save(FILE)

    print("Attendance Marked:", uid, date, time)
    return "OK"

if __name__ == "__main__":
    print("Attendance Server Running on Port 5000")
    app.run(host="0.0.0.0", port=5000)
