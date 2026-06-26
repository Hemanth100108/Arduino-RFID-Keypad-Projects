# Arduino_Access_Control_Projects

Arduino Uno projects using RFID Readers, Keypads, OLED/LCD Displays, Servo Motors, and Buzzers for authentication, access control, attendance management, and smart security applications.

## 1. Objective

The objective of this repository is to develop practical Arduino-based access control and security applications using RFID technology, keypad authentication, OLED/LCD displays, servo motors, and buzzers. These projects demonstrate RFID-based authentication, password verification, attendance management, two-factor authentication, and smart door lock systems using embedded system technologies.

---

## 2. Components Used

### Hardware Components

* Arduino Uno R3
* MFRC522 RFID Reader
* RFID Cards/Tags
* 4×4 Matrix Keypad
* OLED Display (SSD1306 I2C)
* 16×2 LCD Display (I2C)
* SG90 Servo Motor
* Active Buzzer Module
* Breadboard
* Jumper Wires

### Software Components

* Arduino IDE
* MFRC522 Library
* Keypad Library
* Adafruit SSD1306 Library
* Adafruit GFX Library
* LiquidCrystal_I2C Library
* Servo Library
* SPI Library
* Wire Library

---

## 3. Circuit Diagram

The projects use different combinations of the following modules.

### MFRC522 RFID Reader

| RFID Pin | Arduino Uno |
| -------- | ----------- |
| SDA      | D10         |
| SCK      | D13         |
| MOSI     | D11         |
| MISO     | D12         |
| RST      | D9          |
| VCC      | 3.3V        |
| GND      | GND         |

### OLED Display (SSD1306)

| OLED Pin | Arduino Uno |
| -------- | ----------- |
| VCC      | 5V          |
| GND      | GND         |
| SDA      | A4          |
| SCL      | A5          |

### 16×2 I2C LCD

| LCD Pin | Arduino Uno |
| ------- | ----------- |
| VCC     | 5V          |
| GND     | GND         |
| SDA     | A4          |
| SCL     | A5          |

### 4×4 Matrix Keypad

| Keypad Pin | Arduino Uno |
| ---------- | ----------- |
| R1         | D8          |
| R2         | D7          |
| R3         | D6          |
| R4         | D5          |
| C1         | D4          |
| C2         | D3          |
| C3         | D2          |
| C4         | A0          |

### Servo Motor

| Servo Pin | Arduino Uno                  |
| --------- | ---------------------------- |
| Signal    | D6/D10 *(Project Dependent)* |
| VCC       | 5V (External Recommended)    |
| GND       | GND                          |

### Active Buzzer

| Buzzer Pin | Arduino Uno                 |
| ---------- | --------------------------- |
| Signal     | D7/A1 *(Project Dependent)* |
| VCC        | 5V                          |
| GND        | GND                         |

---

## 4. Code Explanation

This repository contains the following Arduino projects:

### RFID Servo Door Lock

Uses RFID authentication to unlock a smart door. Authorized RFID cards are verified before access is granted. The servo motor rotates to simulate door unlocking and automatically returns to the locked position after a short delay.

### RFID Attendance System

Registers attendance using RFID cards assigned to students. Student names are displayed on the OLED/LCD, attendance is logged in the Serial Monitor, and duplicate attendance is prevented within a specified time interval.

### RFID + Keypad LCD Smart Lock

Implements two-factor authentication using both an RFID card and a 4-digit PIN entered through a keypad. Only when both credentials are verified does the system display "Door Unlocked". Invalid cards or incorrect PINs trigger a buzzer alert.

### Keypad Servo Door Lock

A password-protected smart door lock that allows users to unlock the door using a 4-digit PIN entered through a keypad. The OLED displays authentication messages while the servo motor simulates the locking and unlocking mechanism.

---

## 5. Output Images

### RFID Servo Door Lock

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 16 PM (1)" src="https://github.com/user-attachments/assets/f727b252-3a7b-427b-9071-05dd24b23036" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 16 PM" src="https://github.com/user-attachments/assets/7f532ce3-b1d9-4ac7-81e6-30c0960156e5" />

### RFID Attendance System

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 17 PM" src="https://github.com/user-attachments/assets/2a3151fd-1da0-4af4-8efc-bc8e6e9db9b2" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 16 PM" src="https://github.com/user-attachments/assets/5407a9d8-934b-42e5-9229-0e24052e9b43" />

### RFID + Keypad LCD Smart Lock

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 17 PM (1)" src="https://github.com/user-attachments/assets/3df7c292-6a55-40c2-91ed-141920058a7a" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 17 PM" src="https://github.com/user-attachments/assets/76c476be-178c-4bb9-aa1f-c410e3d1d854" />

### Keypad Servo Door Lock

<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 15 PM (1)" src="https://github.com/user-attachments/assets/bd5c6f8f-2ad1-4c43-a8ab-44a864674902" />
<img width="1600" height="1200" alt="WhatsApp Image 2026-06-26 at 6 22 15 PM" src="https://github.com/user-attachments/assets/b070fc7f-8939-4d51-8134-88fb6ee893bd" />

---

## 6. Learning Outcome

After completing these projects, learners will be able to:

* Interface the MFRC522 RFID reader with Arduino Uno using SPI communication.
* Read and verify RFID card UIDs.
* Develop RFID-based authentication systems.
* Interface 4×4 matrix keypads for password entry.
* Implement secure PIN verification algorithms.
* Create OLED and LCD user interfaces for embedded applications.
* Control servo motors for smart locking mechanisms.
* Develop RFID-based attendance management systems.
* Implement two-factor authentication using RFID and keypad.
* Design practical smart access control and security systems using Arduino.

---

**Hemanth A S**
