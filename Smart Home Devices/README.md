# 🏠 ESP32 Smart Relay Control with Web Interface

A simple ESP32-based smart home automation demo project that allows controlling a relay (AC bulb/load) using a **web browser**.  
It supports **manual ON/OFF control** and an **AUTO CONTROL mode** using time-based logic.

This project is designed for **college submission, demos, and beginners**.

---

## 🚀 Features

- 🌐 Web-based relay control (mobile & PC)
- 🔘 Manual ON / OFF buttons
- ⏱️ Auto Control mode (time-based automation)
- 📱 No mobile app required (browser only)
- ⚡ Local ESP32 Web Server (no cloud)
- 🧠 Simple and reliable logic

---

## 🧠 Working Logic

### 🔹 Manual Control
- **ON button** → Relay ON  
- **OFF button** → Relay OFF  

### 🔹 Auto Control
When **AUTO CONTROL** button is pressed:

| Time | Relay State |
|----|------------|
| 0 – 10 seconds | OFF |
| 10 – 23 seconds | ON |
| After 23 seconds | Auto stops |

> This auto mode simulates intelligent automation.  
> Sensor-based logic can be added later.

---

## 🛠️ Components Used

- ESP32 Dev Module
- 5V Relay Module (Active LOW)
- AC Bulb / Load
- Breadboard
- Jumper Wires
- WiFi Network

---

## 🔌 Pin Configuration

🔌 ESP32 Pin Connections – Table Format
🔹 ESP32 ↔ Relay Module

| ESP32 Pin | Relay Pin | Description                |
| --------- | --------- | -------------------------- |
| 5V        | VCC       | Power supply to relay      |
| GND       | GND       | Common ground              |
| GPIO26    | IN        | Relay control (Active LOW) |

🔹 Relay ↔ AC Bulb (Load Side)

| Relay Terminal   | Connection           |
| ---------------- | -------------------- |
| COM              | AC Live (Phase)      |
| NO               | One terminal of bulb |
| Bulb (other end) | AC Neutral           |

🔹 ESP32 ↔ PIR Motion Sensor

| ESP32 Pin | PIR Pin | Description             |
| --------- | ------- | ----------------------- |
| 5V        | VCC     | Power supply            |
| GND       | GND     | Common ground           |
| GPIO13    | OUT     | Motion detection output |

🔹 ESP32 ↔ Gas Sensor (MQ-2 / MQ-135)

| ESP32 Pin | Gas Sensor Pin | Description                    |
| --------- | -------------- | ------------------------------ |
| 5V        | VCC            | Power supply                   |
| GND       | GND            | Common ground                  |
| GPIO14    | DO             | Gas detection (Digital Output) |

🔹 ESP32 ↔ Fire (Flame) Sensor

| ESP32 Pin | Fire Sensor Pin | Description           |
| --------- | --------------- | --------------------- |
| 5V        | VCC             | Power supply          |
| GND       | GND             | Common ground         |
| GPIO27    | DO              | Fire detection output |

🔹 ESP32 ↔ Humidity Sensor (DHT11 / DHT22)

| ESP32 Pin | DHT Pin | Description          |
| --------- | ------- | -------------------- |
| 3.3V / 5V | VCC     | Power supply         |
| GND       | GND     | Common ground        |
| GPIO4     | DATA    | Humidity data signal |

📌 If bare DHT sensor is used, connect a 10kΩ resistor between DATA and VCC.

🔹 Power Distribution (Common Connection)

| ESP32 Pin | Connected To        |
| --------- | ------------------- |
| 5V        | All sensor VCC pins |
| GND       | All sensor GND pins |

🔹 Final GPIO Summary Table

| Component     | ESP32 GPIO |
| ------------- | ---------- |
| Relay Control | GPIO26     |
| PIR Sensor    | GPIO13     |
| Gas Sensor    | GPIO14     |
| Fire Sensor   | GPIO27     |
| DHT Sensor    | GPIO4      |


---

## 📐 Pin Diagram (ESP32 ↔ Relay)

ESP32 Relay Module
5V ----------------> VCC
GND ----------------> GND
GPIO26 ----------------> IN


---

## 🔌 AC Bulb Connection (Relay Output Side)

Relay Terminals: **COM**, **NO**, **NC**

Use **COM and NO only**.

AC LIVE -----> COM (Relay)
NO (Relay) -----> Bulb
Bulb ----------> AC NEUTRAL


⚠️ Be careful while handling AC voltage.

---

## 🌐 How to Use

1. Upload the code to ESP32
2. Open **Serial Monitor (115200 baud)**
3. Note the IP address displayed
4. Connect your mobile/PC to the same WiFi
5. Open browser and type:

http://<ESP32_IP_ADDRESS> // Give in ( serial monitor ) in ( ARDUINO IDE )

6. Use buttons:
- ON
- OFF
- AUTO CONTROL

---

## 📂 Code Behavior Summary

- ESP32 runs a local web server
- Web page contains 3 buttons
- Relay controlled using GPIO26
- Auto control uses `millis()` timing
- No blocking delay for smooth operation

---

## 🖼️ Picture : 

![WhatsApp Image 2026-01-27 at 7 38 29 PM](https://github.com/user-attachments/assets/90f476d3-d00c-403d-9a1e-af7ab925cd91)


![WhatsApp Image 2026-01-27 at 7 42 34 PM](https://github.com/user-attachments/assets/28c52eeb-e5c6-4eaf-8a9b-980b3dc4e2af)


![WhatsApp Image 2026-01-28 at 2 01 27 AM](https://github.com/user-attachments/assets/2565cf34-1315-40ff-ba68-505338a3d99a)




---

## 🎓 Use Cases

- College mini project
- Smart home demo
- IoT learning project
- Embedded systems demonstration

---

## 🔮 Future Enhancements

- Add sensors (Gas, Fire, Motion, Humidity)
- Add real-time web page refresh
- Add buzzer or LED alert
- Cloud integration (Firebase / MQTT)
- AI-based automation logic

---

## 👨‍💻 Author

**HARI PRASAD L S**  
ESP32 Smart Home Automation Project

---

## 📜 License

This project is open-source and free to use for **educational purposes**.
