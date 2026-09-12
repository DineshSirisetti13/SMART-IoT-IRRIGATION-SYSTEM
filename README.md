# 🌱 SMART-IOT-IRRIGATION-SYSTEM

## 📖 Project Overview

The **Smart IoT Irrigation System** is an embedded IoT-based automation project designed to monitor environmental conditions and control irrigation automatically. The system reads **temperature**, **humidity**, and **soil moisture** values, displays them locally on an LCD, and uploads the data to the **ThingSpeak cloud platform** for remote monitoring. Based on the soil moisture level, the system automatically controls a water pump (represented by an LED for testing).

This project helps automate agricultural irrigation, reduce water wastage, and improve farming efficiency.

---
## 🎯 Aim of the Project

The main aim of this project is to monitor the irrigation system over IoT by reading environmental parameters such as:

- Temperature
- Relative Humidity
- Soil Moisture
The collected data is sent to **ThingSpeak Cloud**, and the irrigation motor is automatically controlled based on **soil moisture conditions and user-defined irrigation settings**.

---

## ✨ Features

- Real-time **temperature monitoring**
- Real-time **humidity monitoring**
- **Soil moisture detection**
- Automatic **water pump control**
- LCD display for local monitoring
- IoT cloud data upload using **ESP01 Wi-Fi**
- RTC-based timed data transmission
- **Menu-driven user interface**
- **User-configurable irrigation settings**
- Different water supply modes for different crop/field requirements
- Custom irrigation duration selection
---

## 🔧 Hardware Requirements

The following components are used in this project:

- **LPC2148 Microcontroller**
- **DHT11 Sensor**
- **LCD Display**
- **ESP01 Wi-Fi Module**
- **Soil Moisture Sensor**
- **Keypad**
- **Push Button**
- **Relay**
- **12V Power Supply**
- **Water Motor**
- **DB9 Cable / USB-UART Converter**

---

## 💻 Software Requirements

- **Keil C Compiler**
- **Embedded C Programming**
- **Flash Magic** 

---

## 🏗️ System Architecture

<img width="1181" height="1331" alt="image" src="https://github.com/user-attachments/assets/950194c3-8ad0-4c4b-8955-120cc4629773" />



---

## ⚙️ Working Principle

The Smart IoT Irrigation System continuously monitors environmental conditions and automatically controls irrigation based on sensor data and user-defined settings.

### Step 1: System Initialization
When the system is powered ON, the LPC2148 microcontroller initializes all required peripherals:

- LCD display
- DHT11 (temperature and humidity sensor)
- Soil moisture sensor
- ESP01 Wi-Fi module
- RTC (Real Time Clock)
- Keypad
- External interrupt
- UART communication

---

### Step 2: Sensor Monitoring
The system continuously reads:

- **Temperature** from DHT11
- **Relative Humidity** from DHT11
- **Soil Moisture Level** from soil moisture sensor

The measured values are displayed on the LCD in real time.

---

### Step 3: Interrupt-Based User Configuration through Menu-Driven Interface
Whenever the user presses the **external interrupt switch**, the system enters **menu configuration mode**.

A menu is displayed on the LCD, and the user can select options using the **keypad**.

#### Menu Option 1:  Motor Timing Selection
The user can manually set the irrigation motor ON duration based on field requirements.

Example:
- 1 minute
- 2 minutes
- 3 minutes

This allows different crops or fields to receive different amounts of water.

---

#### Menu Option 2:  Temperature and Humidity Threshold Settings
The user can configure automatic motor timing based on environmental conditions.

Examples:

- **High Temperature + Low Humidity → Motor ON for 3 minutes**
- **Moderate Temperature + Moderate Humidity → Motor ON for 2 minutes**
- **Low Temperature + High Humidity → Motor ON for 1 minute**


These settings allow different crops or fields to receive different amounts of water based on user requirements.

---

### Step 4: Automatic Irrigation Control
The **soil moisture sensor** acts as the primary decision parameter.

- If the soil moisture is **low (dry soil)**, the system checks the **user-selected irrigation settings**.
- Based on the selected **motor timing** or **temperature-humidity mode**, the motor is turned **ON**.
- The motor runs for the configured duration.
- If the soil becomes **wet (sufficient moisture)**, the motor is turned **OFF**.

This ensures irrigation occurs according to the **user’s field requirements**.
---

### Step 5: UART Communication with ESP01 using Interrupts

The system uses the **UART protocol** for communication between the **LPC2148 microcontroller** and the **ESP01 Wi-Fi module**.

#### UART Transmission
The LPC2148 sends **AT commands** to the ESP01 through the **UART transmitter** to configure the Wi-Fi module and establish communication with the ThingSpeak cloud.

Examples of transmitted AT commands:

- `AT` → Check ESP01 response
- `AT+CWMODE` → Set Wi-Fi mode
- `AT+CWJAP` → Connect to Wi-Fi network
- `AT+CIPSTART` → Open TCP connection
- `AT+CIPSEND` → Send data
- HTTP request to update ThingSpeak fields

---

#### UART Reception using Interrupts
The ESP01 sends back response messages such as:

- `OK`
- `ERROR`
- `SEND OK`
- Wi-Fi connection status

These responses are received using the **UART receiver interrupt**.

Whenever data is received from the ESP01:

- UART receive interrupt is triggered.
- The received characters are stored in a buffer.
- The response is processed by the microcontroller.
- Important status messages are displayed on the **LCD** for user monitoring.

---

#### Benefits of UART Interrupt Communication

- Efficient real-time communication
- No continuous polling required
- Faster response handling
- Reliable transmission and reception
- Easy debugging through LCD display

---

### Step 6: Cloud Data Upload to ThingSpeak

After successful UART communication with ESP01, the system uploads the following data to **ThingSpeak Cloud**:

- Temperature
- Humidity
- Motor ON/OFF status

This allows remote monitoring of the irrigation system over the internet.

## 🖼️ Project Images

### 📊 1. System Block Diagram

This block diagram illustrates the detailed hardware modules and their interconnections, including DHT11, soil moisture sensor, RTC, LCD, keypad, ESP01, relay, and motor.

<img width="608" height="346" alt="Screenshot 2026-05-18 153309" src="https://github.com/user-attachments/assets/5b0164cf-9dc1-40ea-9cea-2340c369b3e4" />


---

### 🔌 2. Hardware Setup

This image shows the actual hardware implementation of the Smart IoT Irrigation System with all connected peripherals and modules.

<img width="1280" height="960" alt="image" src="https://github.com/user-attachments/assets/2f26a454-bf60-4503-8c78-696bbf2c0dba" />



---

### 📟 3. LCD Output

This image shows the LCD displaying real-time humidity, temperature, and checksum values read from the DHT11 sensor.

<img width="1536" height="1024" alt="image" src="https://github.com/user-attachments/assets/f38f6ac9-c0d7-48f3-aed3-93199be6ba3c" />


---

### 📟 4. LCD Menu Navigation (Interrupt-Based)

This image shows the LCD returning to the **main menu** after pressing the external interrupt button.  
The interrupt allows the user to switch between **Irrigation Time Setting** and **Temperature & Humidity Monitoring** without restarting the system.

**LCD Menu Options:**
- **1. Set Irrigation Time**
- **2.  Temp & Humidity**

<img width="1448" height="1086" alt="image" src="https://github.com/user-attachments/assets/cc91d2a1-ecf2-4683-9775-a48913385269" />


---

### ☁️ 5. ThingSpeak Cloud Output

#### 🌡️ Temperature Monitoring Chart

This chart shows the real-time **temperature data** uploaded from the DHT11 sensor to the ThingSpeak cloud platform.

<img width="593" height="410" alt="Screenshot 2026-05-18 163848" src="https://github.com/user-attachments/assets/608ad6a2-44ae-4251-b718-31c0727b9c64" />

---

#### 💧 Humidity Monitoring Chart

This chart shows the real-time **humidity data** uploaded from the DHT11 sensor to the ThingSpeak cloud platform.

<img width="590" height="406" alt="Screenshot 2026-05-18 163903" src="https://github.com/user-attachments/assets/69dc44f4-6baf-4c13-9904-13bb0948cd8b" />


---

#### 🔄 Motor ON/OFF Status Chart

This chart shows the irrigation motor operating status uploaded to the ThingSpeak cloud platform.

- **1** → Motor **ON**
- **0** → Motor **OFF**

The motor status changes based on **soil moisture conditions** and **user-defined irrigation settings**, allowing remote monitoring of irrigation activity.

<img width="602" height="415" alt="Screenshot 2026-05-18 163914" src="https://github.com/user-attachments/assets/47a6979e-9fe1-4c6d-8a9a-1f56a425012a" />


---
## 🚀 How to Run the Project

### 1. Create Project Folder
Create a folder and save all project source files inside.

---

### 2. Verify LCD Module
Check LCD display for:

- Character constants
- String constants
- Integer display

---

### 3. Verify UART Communication
Transmit a test string on serial terminal.

---

### 4. Connect DHT11 Sensor
Develop and test the DHT11 driver for:

- Temperature reading
- Humidity reading

Display output on LCD.

---

### 5. Configure ESP01
Test ESP01 using Flash Magic terminal and AT commands.

---

### 6. Connect ESP01 to LPC2148
Develop Wi-Fi driver and send sample data to ThingSpeak.

---

### 7. Connect Soil Moisture Sensor
Read soil moisture output and verify motor/LED control.

---

### 8. Implement Main Logic
Initialize all peripherals and combine:

- Sensor reading
- LCD display
- Cloud updates
- Motor automation

---

### 9. Build and Flash
Compile using **Keil**, generate HEX file, and flash using **Flash Magic**.

---

## 🌍 Applications

- Smart Agriculture
- Automated Irrigation
- Remote Environmental Monitoring
- IoT-based Farming Systems
- Water Conservation Solutions

---

## 🔮 Future Improvements

- Add mobile app control
- Soil moisture percentage using ADC
- Automatic pump hardware
- Cloud analytics dashboard
- SMS/Email alerts
- Solar-powered operation

---

## 👨‍💻 Author

**Name:** Ankamma Vallepu  


---
