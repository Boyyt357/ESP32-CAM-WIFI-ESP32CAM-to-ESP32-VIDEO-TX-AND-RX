# **🛰️ ESP32-CAM WIFi FPV Digital Video Link**

## ***Tutorial and Testing👇***
## **https://youtu.be/i73PIZorhhw**
<img width="1450" height="967" alt="3bb64f09-70f4-411a-84ec-98a55a553816" src="https://github.com/user-attachments/assets/3f4c891e-3cf7-48c4-8c82-1b1fbeec757f" />


**A dual-device digital FPV system leveraging two ESP32 modules for low-latency video transmission and link quality monitoring.**

This project transforms the **ESP32-CAM** into a high-performance **Video Transmitter (VTX)** and uses a second standard **ESP32** module as a dedicated **Ground Station Client**. This configuration ensures maximum link performance by disabling Wi-Fi sleep and maximizing transmission power on both ends.

The video stream is available directly on any mobile device (phone, tablet, computer) connected to the VTX's dedicated Wi-Fi network.

## **✨ System Architecture & Key Features**

### **1\. Vehicle/VTX (ESP32-CAM)**

* **Access Point (AP) Mode:** Creates its own dedicated Wi-Fi network (Esp32Cam / 12345678).  
* **High-Power TX:** Sets Wi-Fi transmit power to maximum (**19.5dBm**) for maximum range and penetration.  
* **Low-Latency Optimized:** Uses **QVGA resolution** and a **JPEG Quality of 35** to prioritize high frame rates over image size.  
* **MJPEG Video Stream:** Serves a raw MJPEG video stream accessible via a standard web browser.

### **2\. Ground Station Client (ESP32)**

* **Link Quality Monitoring:** Connects to the VTX network and reports the real-time **RSSI (Signal Strength)** via Serial Monitor.  
* **Max Performance Mode:** Disables Wi-Fi sleep (WiFi.setSleep(false)) to maintain the fastest possible connection and communication.

## **🛠️ Hardware Components**

| Component | Role | Description |
| :---- | :---- | :---- |
| **ESP32-CAM Module** | Vehicle VTX & Server | Camera module (e.g., AI-Thinker) running the AP firmware. |
| **Standard ESP32 Module** | Ground Client & Monitor | Any standard ESP32 development board (e.g., ESP32 DevKit) running the client firmware. |
| **FTDI / USB-to-TTL Adapters** | Programming | Required for flashing both ESP32 modules. |
| **Viewer Device** | Monitor Screen | Smartphone, tablet, or laptop to connect to the Esp32Cam network and view the stream. |

## **⚙️ Setup and Flashing Instructions**

### **1\. Prepare Environment**

* Install **Arduino IDE** or **VS Code with PlatformIO**.  
* Ensure the ESP32 Boards Manager is installed.

### **2\. Flash the VTX Firmware (ESP32-CAM)**

1. Open the Esp32\_cam\_VTX code.  
2. Verify the AP credentials (currently Esp32Cam / 12345678).  
3. Select the AI-Thinker ESP32-CAM board.  
4. Connect the ESP32-CAM and set it to **programming mode** (usually by grounding **GPIO 0**).  
5. Upload the code.  
6. After upload, disconnect **GPIO 0**.

### **3\. Flash the Ground Station Client Firmware (Standard ESP32)**

1. Open the esp32\_client code.  
2. Verify the SSID/Password match the VTX firmware.  
3. Select your standard ESP32 board model.  
4. Upload the code.

## **🚀 Operation and Viewing**

1. **Power On:** Supply stable 5V power to both the ESP32-CAM (VTX) and the ESP32 Client (Ground).  
2. **Monitor Link:** Open the Serial Monitor for the **Ground Station Client** to see the **RSSI** (signal strength) reports. This lets you confirm the connection quality.  
3. **Connect Viewer:** On your phone, tablet, or laptop, connect to the new Wi-Fi network:  
   * **SSID:** Esp32Cam  
   * **Password:** 12345678  
4. **View Stream:** Open a web browser and navigate to the default IP address of the ESP32-CAM server:  
   (http://192.168.10.2/)
