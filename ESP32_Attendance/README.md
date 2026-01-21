# 📌 IoT Based RFID Attendance System using ESP32

This project implements an **IoT-based Smart Attendance System** using **ESP32**, **RFID**, and a **Python Flask server** to automatically store attendance records in an **Excel file** with real-time date and time.

It is designed for academic demonstration and college project submission.

---

## 🚀 Features

- RFID based attendance marking  
- ESP32 with WiFi communication  
- Automatic name mapping using UID  
- Real-time Date & Time logging  
- Attendance stored directly in Excel  
- LCD display for status messages  
- Buzzer for confirmation sound  

---

## 🧰 Hardware Components Used

- ESP32 Development Board  
- RFID Module (RC522)  
- RFID Cards/Tags  
- 16x2 I2C LCD Display  
- Buzzer  
- Breadboard & Jumper Wires  

---

## 💻 Software & Tools Used

- Arduino IDE  
- Python 3.x  
- Flask (Python Web Framework)  
- OpenPyXL (Excel Library)  

---

RFID Card
    ↓
RFID Reader (RC522)
    ↓
ESP32  ──── WiFi ────> PC / Server (Python Script)
    ↓                      ↓
 LCD Display            Excel File (.xlsx)
    ↓
 Buzzer

---

## 🖼️ Picture :
![WhatsApp Image 2026-01-21 at 8 53 46 AM](https://github.com/user-attachments/assets/af1baa00-2d59-44d7-9fcd-2309c6d7923a)

![WhatsApp Image 2026-01-21 at 9 17 19 AM](https://github.com/user-attachments/assets/2c31c6eb-ad11-4e8e-98d2-f0b127c159d7)

![WhatsApp Image 2026-01-21 at 9 19 22 AM](https://github.com/user-attachments/assets/a204457c-8a16-4cf1-87e6-86438a3c3973)

![WhatsApp Image 2026-01-21 at 9 24 52 AM](https://github.com/user-attachments/assets/80fd92e0-fd23-4d62-899a-da9c874a0686)

---

## 🔧 Working Principle

1. Student scans RFID card on RC522 module.  
2. ESP32 reads the UID of the card.  
3. ESP32 sends the UID to the Python Flask server over WiFi.  
4. Flask server maps UID to student details (SNO, Name, Department).  
5. Current Date and Time are automatically generated.  
6. Attendance is stored in `attendance.xlsx`.  
7. LCD shows "Attendance Marked" and buzzer beeps for confirmation.

---

## 📂 Project Structure

ESP32_Attendance/
│
├── attendance_in_esp32.ino # ESP32 Arduino Code
├── attendance_server.py # Python Flask Server
├── attendance.xlsx # Generated Excel File (after running)
└── README.md # Project Documentation


---

## 🧪 How to Run the Project

### 1️⃣ Install Required Python Libraries

bash
```
pip install flask openpyxl
```
You Should be the safe the file in the order or a folder.
```
cd C:\Users
```
You should see:
```
Running on http://<PC_IP>:5000
```

3️⃣ Upload ESP32 Code
Open attendance_in_esp32.ino in Arduino IDE

Select Board: ESP32 Dev Module

Select correct COM Port

Update this line with your PC IP: 
```
const char* serverIP = "YOUR_PC_IP";
```
Upload the code

Open Serial Monitor at 115200 baud # In Arduino IDE

👨‍🎓 Student Mapping (Example)

| SNO | NAME        | DEPARTMENT |
| --- | ----------- | ---------- |
| 1   | VIJAY ANAND | EEE        |
| 2   | SATHISH     | EEE        |
| 3   | GURU PRASAD | EEE        |
| 4   | HARI PRASAD | EEE        |

📊 Sample Output (Excel)
| SNO | NAME        | DEPARTMENT | DATE       | TIME     |
| --- | ----------- | ---------- | ---------- | -------- |
| 1   | VIJAY ANAND | EEE        | 2026-01-21 | 08:30:12 |
| 2   | SATHISH     | EEE        | 2026-01-21 | 08:31:05 |

🧑‍💻 Author
Hari Prasad
Department of Electrical and Electronics Engineering (EEE)
RFID Attendance System Project

⭐ If you like this project
Give a ⭐ star on GitHub and feel free to fork and improve it!




## 🏗️ System Architecture

