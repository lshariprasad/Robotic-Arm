RFID Attendance Marking System
A Python and Arduino-based system that automates attendance tracking using MFRC522 RFID technology. This project scans RFID tags, identifies the user, and logs the attendance with a timestamp into a CSV file or database.

🚀 Features
Real-time Scanning: Instantly reads RFID tags and validates IDs.

Automated Logging: Saves attendance data (Name, Date, Time) automatically.

User-Friendly: Simple Python interface to monitor scans.

Hardware Integration: Uses Arduino Uno for reliable sensor data collection.

🛠 Hardware Required
Arduino Uno

MFRC522 RFID Module

RFID Tags/Cards

Jumper Wires

USB Cable (for connecting Arduino to PC)

💻 Software Setup
1. Arduino Environment
Open the Arduino IDE.

Install the MFRC522 Library (Sketch -> Include Library -> Manage Libraries).

Upload your .ino sketch to the Arduino Uno.

2. Python Environment
Make sure you have Python 3.x installed. You will need the pyserial library to communicate with the Arduino.

Bash
```
pip install pyserial
```

📁 Project Structure

<img width="300" height="800" alt="image" src="https://github.com/user-attachments/assets/4325a8cf-683d-4e11-9564-14d2b4f68790" />
<img width="300" height="800" alt="image" src="https://github.com/user-attachments/assets/eaf7f287-435e-4f07-85b0-003ef82afd06" />
<img width="300" height="800" alt="image" src="https://github.com/user-attachments/assets/62e016bf-0f2a-4715-bea8-367bd3dc323f" />


arduino_code/: Contains the .ino file for the Arduino Uno.

python_script/: Contains the Python script to read serial data and save to CSV.

attendance.csv: The file where attendance records are stored.

📝 How to Use
Connect your Arduino Uno to your computer via USB.

Upload the Arduino code using the Arduino IDE.

Note the COM Port (e.g., COM3 on Windows or /dev/ttyACM0 on Linux).

Update the Python Script with your specific COM port.

Run the Python script:

Bash
```
python main.py
```

Scan an RFID tag; the system will display the user info and save it to the log.

📊 Sample Data Output
The attendance is saved in the following format:

   Name	            ID	             Date	         Time
 John Doe	      83:A1:D2:1A	      2026-01-20	    10:30:05
Jane Smith	    12:B4:C5:6D	      2026-01-20	    10:32:14



🤝 Contributing
Feel free to fork this project, submit issues, or pull requests to improve the system!







