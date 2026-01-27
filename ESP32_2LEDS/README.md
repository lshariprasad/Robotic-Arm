# 🌐 ESP32 Local Web Server – LED Control

Control two LEDs using an ESP32 through a local web server.
Access the web page from any device connected to the same Wi-Fi network and turn LEDs ON/OFF in real time.

---

## 🚀 Features

* ESP32 local web server (no internet required)
* Control **2 LEDs independently**
* Simple and clean web interface
* Works on **mobile & desktop browsers**
* Beginner-friendly Arduino code

---

## 🛠️ Hardware Requirements

* ESP32 Development Board
* 2 × LEDs
* 2 × 220Ω resistors
* Breadboard
* Jumper wires
* USB data cable

---

## 🔌 Circuit Connections

| Component | ESP32 GPIO |
| --------- | ---------- |
| LED 1     | GPIO 26    |
| LED 2     | GPIO 27    |

**Connections:**

* LED Anode (+) → Resistor → ESP32 GPIO pin
* LED Cathode (–) → GND

> ⚠️ Always use a resistor to protect the LED from overcurrent.

---

## 💻 Software Requirements

* Arduino IDE
* ESP32 Board Package (by Espressif Systems)
* CP2102 / CH340 USB Driver (depending on your ESP32 board)

---

## ⚙️ Installation & Setup

### 1️⃣ Install ESP32 Board in Arduino IDE

1. Open **Arduino IDE**
2. Go to **File → Preferences**
3. Add this URL in *Additional Boards Manager URLs*:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

4. Go to **Tools → Board → Boards Manager**
5. Search for **ESP32** and install the package by *Espressif Systems*

---

### 2️⃣ Upload the Code

1. Open the project `.ino` file
2. Update your Wi-Fi credentials:

```cpp
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";
```

3. Select:

* **Tools → Board → ESP32 Dev Module**
* **Tools → Port → COMx**

4. Click **Upload**
5. If required, **hold the BOOT button** while uploading

---

## 🌍 How It Works

1. ESP32 connects to your Wi-Fi network
2. A local web server runs on **port 80**
3. A web page displays LED ON/OFF buttons
4. Button clicks send HTTP requests
5. ESP32 toggles the corresponding GPIO pins

---

## 📱 Usage

1. Open **Serial Monitor** (9600 baud or as set in code)
2. Copy the IP address printed by the ESP32
3. Open a browser and visit:

```
http://<ESP32-IP-ADDRESS>
```

4. Control the LEDs instantly ⚡

---
## Pictures 🖼️

![WhatsApp Image 2026-01-26 at 7 14 36 AM](https://github.com/user-attachments/assets/e6a07368-a829-4c07-8f78-67d2a281427b)

![WhatsApp Image 2026-01-27 at 11 19 07 PM (1)](https://github.com/user-attachments/assets/70829c3c-ecc0-4915-aefa-b78c0e839bcb)

![WhatsApp Image 2026-01-27 at 11 19 07 PM (2)](https://github.com/user-attachments/assets/5377bcfe-4263-419b-b950-98b9666703f0)

![WhatsApp Image 2026-01-27 at 11 19 07 PM (1)](https://github.com/user-attachments/assets/61cdd869-574b-4735-a04d-256affa5d34f)

![WhatsApp Image 2026-01-27 at 11 51 01 PM](https://github.com/user-attachments/assets/33892174-e6f1-4d41-afd7-854214709ef6)

![WhatsApp Image 2026-01-26 at 7 10 13 AM](https://github.com/user-attachments/assets/aba0b713-8361-4029-bf8d-06233ef6e26f)


## Finally Updated Version : 

![WhatsApp Image 2026-01-27 at 11 48 35 PM](https://github.com/user-attachments/assets/6eaac656-f630-4ffa-83cc-7d563d82538f)





---

## 📂 Project Structure

```
ESP32-LED-WebServer/
│── esp32_led_webserver.ino
│── README.md
```

---

## 🔮 Future Improvements

* Toggle switch based UI
* WebSocket-based real-time updates
* Password-protected access
* Relay module control
* Sensor data display (DHT11, LDR, etc.)

---

## 🧑‍💻 Author

**Hari Prasad**
ESP32 | IoT | Embedded Systems

---

## 📜 License

This project is licensed under the **MIT License**.
Feel free to use, modify, and share 🚀
