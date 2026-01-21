# ESP32 Smart Voice & Web Controlled Motor and Light System

## 📌 Project Overview

This project demonstrates a **Smart IoT Control System** using **ESP32** to control:

* 💡 A Light (LED)
* ⚙️ A DC Motor (via Relay)
* 📟 OLED Display for status
* 🌐 Web Control (buttons)
* 🎤 Voice Control (using mobile keyboard voice typing)

The system hosts a **local web server** on ESP32. From any mobile connected to the same Wi-Fi network, the user can:

* Click buttons to control devices
* Type commands
* Speak commands using the mobile keyboard microphone

All actions are displayed in real-time on the OLED screen.
---

# 🖼️ Picture :

![WhatsApp Image 2026-01-21 at 10 32 45 AM](https://github.com/user-attachments/assets/351ef9ac-2e80-4f2a-b249-b92187413192)

![WhatsApp Image 2026-01-21 at 10 32 45 AM](https://github.com/user-attachments/assets/50956882-6293-43cb-ab29-c5d0969af4d6)

![WhatsApp Image 2026-01-21 at 10 32 45 AM](https://github.com/user-attachments/assets/3698bd33-4e41-4288-a3af-64eabffa2364)

![WhatsApp Image 2026-01-21 at 10 32 46 AM (1)](https://github.com/user-attachments/assets/a612c2a0-2eb6-4da4-82a9-fd96cb856c7e)

![WhatsApp Image 2026-01-21 at 10 32 46 AM](https://github.com/user-attachments/assets/f0d6cd70-d05b-4c3b-919b-3684ab3ae0eb)


---

## 🧰 Components Used

| Component                 | Quantity    |
| ------------------------- | ----------- |
| ESP32 Dev Board           | 1           |
| 0.96" OLED Display (I2C)  | 1           |
| 1-Channel 5V Relay Module | 1           |
| Yellow DC Motor           | 1           |
| 9V Battery / 6V Supply    | 1           |
| LED                       | 1           |
| 220Ω Resistor             | 1           |
| Breadboard & Jumper Wires | As required |

---

## 🔌 Pin Connections

### Power

* ESP32 **3V3** → Breadboard +
* ESP32 **GND** → Breadboard –

### LED

* ESP32 **GPIO 2** → 220Ω Resistor → LED +
* LED – → GND

### Relay (Control Side)

* Relay **IN**  → ESP32 **GPIO 26**
* Relay **VCC** → **5V**
* Relay **GND** → **GND**

### Relay (Power Side, NO Mode)

Relay terminal order:

```
[ NO ] [ COM ] [ NC ]
```

Connections:

* Battery + → **COM** (middle)
* **NO** (left) → Motor +
* Motor – → Battery –
* **NC** → Not used

### OLED (I2C)

* OLED **VCC** → ESP32 **3V3**
* OLED **GND** → ESP32 **GND**
* OLED **SDA** → ESP32 **GPIO 21**
* OLED **SCL** → ESP32 **GPIO 22**

---

## 💻 Software Requirements

* Arduino IDE
* ESP32 Board Package installed
* Libraries:

  * Adafruit GFX Library
  * Adafruit SSD1306 Library

---

## 🌐 How the System Works

1. ESP32 connects to your Wi-Fi network.
2. ESP32 starts a **local web server**.
3. User opens the ESP32 IP address in a mobile browser.
4. User controls devices by:

   * Clicking buttons (Web control)
   * Typing commands
   * Speaking commands using mobile keyboard voice typing
5. ESP32 processes commands and:

   * Turns LED ON/OFF
   * Turns Motor ON/OFF using relay
   * Updates status on OLED display

---

## 🎛️ Supported Commands

### Button Control

* LIGHT ON
* LIGHT OFF
* MOTOR ON
* MOTOR OFF

### Text / Voice Commands (Type or Speak)

* `light on`
* `light off`
* `motor on`
* `motor off`
* `fan on`
* `fan off`

---

## 📱 How to Use

1. Upload the provided code to ESP32.
2. Open **Serial Monitor** (115200 baud).
3. Note the IP address shown, for example:

   ```
   http://192.168.1.25
   ```
4. Open this URL in your mobile browser.
5. Use:

   * Buttons for control
   * Text box for typing commands
   * Mobile keyboard 🎤 for voice input

---

## 🧠 Voice Control Method

Due to browser security, direct microphone access is blocked on HTTP pages.

So voice control is implemented using:

> **Mobile keyboard voice typing**

Flow:

```
Your Voice → Mobile Keyboard → Text → ESP32 → Device Control
```

This method is reliable and works on all phones.

---

## 🛡️ Safety Notes

* Do NOT connect AC mains directly without proper isolation.
* Always use a relay module with optocoupler.
* Do not power the motor from ESP32.
* Use separate battery or adapter for motor.

---

## 📄 Example Project Description (For Report)

> "This project implements a Smart IoT Control System using ESP32. The system allows users to control a light and a DC motor through a web interface and voice commands. The ESP32 hosts a local web server, and users send commands using a mobile browser. Voice commands are converted into text using the mobile keyboard and processed by the ESP32. An OLED display shows real-time device status. This project demonstrates IoT, embedded systems, and human-machine interaction."

---

## 🏁 Conclusion

This project demonstrates:

* Embedded systems
* IoT web server
* Relay-based motor control
* OLED interfacing
* Voice-based human interaction

It is suitable for:

* Mini projects
* Final year projects
* Hackathons
* IoT demonstrations

---

## ✨ Author

L. S. HARI PRASAD :
Developed using ESP32 by following step-by-step IoT design methodology.

---

## 🔜 Future Enhancements

* Google Assistant integration
* Cloud control
* Multiple appliance control
* Android app interface
* User authentication

---

**End of README**
