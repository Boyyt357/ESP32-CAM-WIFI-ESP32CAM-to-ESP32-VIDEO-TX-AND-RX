# **Long-Range ESP32-CAM Video Relay (TX/RX)**

## **Tutorial and Testing👇**
## **https://youtu.be/i73PIZorhhw**
<img width="1450" height="967" alt="3bb64f09-70f4-411a-84ec-98a55a553816" src="https://github.com/user-attachments/assets/3f4c891e-3cf7-48c4-8c82-1b1fbeec757f" />

This project provides a robust, two-ESP32 solution for creating a **long-range, high-power wireless video link** between an **ESP32-CAM (Transmitter/TX)** and a **Viewing Device (Client)**, using a second **ESP32 (Receiver/RX)** as a dedicated, high-gain Access Point (AP) relay.

## **🚀 Concept Overview**

Instead of relying on a standard home router or a single ESP32 acting as both AP and server (which limits range and performance), this setup dedicates each device to a specific task for maximum efficiency:

1. **RX Unit (AP Relay):** Creates a dedicated, high-power Wi-Fi network with optimized settings for range (Max TX Power, 20MHz bandwidth).  
2. **TX Unit (Camera):** Connects to the RX unit's AP, captures MJPEG video, and hosts the web stream.  
3. **Viewer (Phone/PC):** Connects to the RX unit's AP and accesses the stream URL hosted by the TX unit.

## **✨ Features**

* **High-Power AP Mode:** RX unit is configured with esp\_wifi\_set\_max\_tx\_power(84) (21 dBm) for maximum possible Wi-Fi range.  
* **MJPEG Video Stream:** The TX unit captures and streams high-speed video frames (up to 15 FPS at VGA).  
* **Dedicated Bandwidth:** The system operates on its own dedicated network, reducing interference and maximizing link stability.  
* **Simple Web Interface:** Minimalist dark-themed web interface for viewing the stream.  
* **Optimized Camera Settings:** Allows easy configuration of resolution and JPEG quality.

## **📋 Hardware Requirements**

| Component | Quantity | Description |
| :---- | :---- | :---- |
| **TX Unit (Transmitter)** | 1 | ESP32-CAM (AI-Thinker model assumed) |
| **RX Unit (Access Point)** | 1 | Standard ESP32 Development Board (e.g., ESP32-WROOM-32) |
| **Viewing Device** | 1 | Smartphone, Tablet, or PC with Wi-Fi and Web Browser |
| **Power Supply** | 2 | Stable 5V supply for both units |

## **🛠️ Software & Libraries**

* **Arduino IDE** or **VS Code (PlatformIO)**  
* **ESP32 Board Support Package**  
* **Libraries:**  
  * WiFi.h (Built-in)  
  * WebServer.h (Install using Library Manager: **"WebServer by ESP32"**)  
  * esp\_camera.h (Built-in with ESP32-CAM support)

## **⚙️ Configuration & Setup**

### **1\. Common Settings (Verify in both files)**

The network credentials must match exactly in both the TX.ino and RX.ino files:

| Setting | Value | File to Check |
| :---- | :---- | :---- |
| **SSID** | ESP32\_CAM\_RELAY | Both |
| **Password** | camera123 | Both |
| **Access IP** | 192.168.10.1 | RX.ino (Gateway/AP) |
| **Camera IP (Expected)** | 192.168.10.2 | TX.ino connects to AP, this is the expected address. |

### **2\. RX Unit (Access Point / Relay) Setup (RX.ino)**

The RX.ino sketch configures the second ESP32 as the dedicated Access Point:

* **Purpose:** Creates the high-power network (ESP32\_CAM\_RELAY).  
* **Power Optimization:** Sets the TX power to maximum (84/21dBm) and disables power save.  
* **Upload the RX.ino sketch to your standard ESP32 board.**  
* **Monitor Serial Output:** Once started, the RX unit will print its network info and begin monitoring for connected clients.

### **3\. TX Unit (Camera Streamer) Setup (TX.ino)**

The TX.ino sketch configures the ESP32-CAM to capture video and join the network:

* **Pinout:** The included pin definitions are for the standard **AI-THINKER ESP32-CAM** board. If you are using a different model, you must verify and adjust the \#define pin numbers at the top of the file.  
* **Resolution/Quality:** Adjust the following lines in TX.ino to balance quality and speed:  
  \#define DEFAULT\_FRAME\_SIZE FRAMESIZE\_VGA // FRAMESIZE\_QVGA (320x240) for faster stream  
  \#define DEFAULT\_JPEG\_QUALITY 20         // Lower number (e.g., 10\) for better quality, higher (e.g., 40\) for faster transmission

* **Upload the TX.ino sketch to your ESP32-CAM board.**  
* **Monitor Serial Output:** The TX unit will attempt to connect to the ESP32\_CAM\_RELAY network and report its assigned IP address.

## **📺 Usage Guide**

Once both the **RX Unit** and the **TX Unit** are powered on and running:

1. **Connect Your Device:** Use your mobile phone, tablet, or PC to connect to the Wi-Fi network named **ESP32\_CAM\_RELAY** using the password **camera123**.  
2. **Access the Stream:** Open a web browser on your connected viewing device.  
3. **Enter the TX IP:** Navigate to the expected IP address of the camera unit:  
   \[http://192.168.10.2\](http://192.168.10.2)

4. **View:** The browser will load the web page, and the live MJPEG stream will begin displaying automatically.

**Note:** The stream address is hosted by the **TX Unit** (the camera), but you must be connected to the network created by the **RX Unit** (the AP Relay) to reach it.
