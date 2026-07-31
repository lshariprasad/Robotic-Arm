# 🔐 Smart Door Lock System using Arduino UNO

A simple Arduino-based Smart Door Lock System that unlocks a servo-controlled door using either a password entered through a 4×4 keypad or by bending a flex sensor. The system displays all actions on a 16×2 I2C LCD.

## 📌 Features

- 🔑 Password-based door unlocking
- ✋ Flex sensor-based door unlocking
- 🔒 Automatic door locking after 5 seconds
- 📺 16×2 I2C LCD status display
- 🔄 Smooth servo motor movement (0° → 180° → 0°)
- ❌ Wrong password detection
- ⭐ Beginner-friendly Arduino project

## 🛠 Hardware Used

| Component | Quantity |
|---|---|
| Arduino UNO | 1 |
| 16×2 LCD with I2C Module | 1 |
| 4×4 Matrix Keypad | 1 |
| SG90 Servo Motor | 1 |
| 2.2-inch Flex Sensor | 1 |
| 4.7kΩ Resistor | 1 |
| Breadboard | 1 |
| Jumper Wires | As Required |
| USB Cable | 1 |

## 📷 Project Overview

```
          +-----------------------+
          |    Arduino UNO        |
          +-----------------------+
              |      |      |
              |      |      |
          LCD(I2C)  Keypad  Servo
              |
         Flex Sensor
              |
         Smart Door Lock
```

## ⚙️ Working Principle

### Method 1 – Password Authentication
1. LCD displays "Enter Password"
2. User enters the password using the keypad
3. Press `#` to verify
4. If the password is correct:
   - LCD displays "Access Granted"
   - Servo rotates from 0° to 180°
   - Door remains open for 5 seconds
   - Servo returns from 180° to 0°
   - Door locks automatically
5. If the password is incorrect:
   - LCD displays "Wrong Password"
   - User is prompted to enter the password again

### Method 2 – Flex Sensor Authentication
1. Arduino continuously monitors the flex sensor
2. When the flex sensor is bent beyond the threshold:
   - LCD displays "Flex Detected"
   - Servo opens the door
3. After 5 seconds, the door closes automatically

## 🔌 Circuit Connections

### LCD (I2C)
| LCD Pin | Arduino UNO |
|---|---|
| VCC | 5V |
| GND | GND |
| SDA | A4 |
| SCL | A5 |

### Servo Motor
| Servo Wire | Arduino UNO |
|---|---|
| VCC | 5V |
| GND | GND |
| Signal | D9 |

### Flex Sensor
```
5V
 │
Flex Sensor
 │
 ├──────── A0
 │
4.7kΩ
 │
GND
```

### Keypad
| Keypad Pin | Arduino UNO |
|---|---|
| R1 | D2 |
| R2 | D3 |
| R3 | D4 |
| R4 | D5 |
| C1 | D6 |
| C2 | D7 |
| C3 | D8 |
| C4 | D10 |

## 🔑 Default Password
`1234`

### Key Functions
| Key | Function |
|---|---|
| 0–9 | Enter Password |
| # | Verify Password |
| * | Clear Password |

## 📂 Arduino Libraries

Install the following libraries via Arduino IDE Library Manager:
- Servo
- Keypad
- LiquidCrystal_I2C
- Wire

## 📁 Folder Structure

```
Smart-Door-Lock-System/
│
├── Smart_Door_Lock.ino
├── README.md
├── Images/
│   ├── Circuit_Diagram.png
│   ├── Hardware_Setup.jpg
│   └── Working.jpg
└── LICENSE
```

## 🚀 How to Run

1. Install Arduino IDE
2. Install the required libraries
3. Connect all components according to the wiring table
4. Upload the code to the Arduino UNO
5. Open the Serial Monitor (9600 baud) to view flex sensor values
6. Enter the password (`1234`) and press `#`, or bend the flex sensor to unlock the door

## 📸 Output

```
SMART DOOR
LOCK SYSTEM
     ↓
Enter Pass:
     ↓
Access Granted
     ↓
Door Opening
     ↓
Door Open
     ↓
Door Closing
     ↓
Door Locked
```

## 💡 Future Improvements

- Fingerprint authentication
- RFID card access
- Face recognition using ESP32-CAM
- Bluetooth control
- Wi-Fi remote unlocking
- Mobile application
- OTP-based authentication
- Buzzer alarm
- EEPROM password storage
- Firebase cloud integration

## 📖 Applications

- Smart Home Security
- Office Door Access
- Laboratory Entry System
- College Mini Project
- IoT Learning Project
- Educational Demonstration

## 👨‍💻 Developed By

**Hari Prasad L S**
Department: Electrical and Electronics Engineering (EEE)
Institution: Saveetha School of Engineering, SIMATS
GitHub: https://github.com/lshariprasad

⭐ If you found this project useful, please consider giving it a Star on GitHub!
