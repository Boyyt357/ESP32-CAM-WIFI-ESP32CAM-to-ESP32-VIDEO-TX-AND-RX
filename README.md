Under Construction
# **📸 ESP32-CAM FPV Video Transmitter (VTX)**

**Low-latency, cost-effective digital video transmission using the popular ESP32-CAM module.**

This project transforms the versatile **ESP32-CAM** development board into a functional **Video Transmitter (VTX)**, perfect for use in RC vehicles, small drones, or general remote monitoring applications where a light, affordable digital video link is needed.

Leveraging the power of the ESP32 chip, this firmware streams live video over **Wi-Fi**, providing a modern alternative to traditional analog VTX systems.

## **✨ Key Features**

* **Wireless Video Streaming:** Utilizes the ESP32's built-in Wi-Fi for video transmission.  
* **Web-Based Viewer:** Includes a simple built-in web server for easy viewing from any Wi-Fi-enabled device (phone, tablet, PC).  
* **Low Latency Focus:** Optimized configuration for maximum frame rate and minimum delay, crucial for FPV.  
* **Lightweight & Compact:** Ideal for small-scale projects where size and weight are critical.  
* **Configuration:** Easy-to-edit configuration file for adjusting Wi-Fi settings and camera parameters (e.g., resolution, brightness).

## **🛠️ Hardware Requirements**

To get this project running, you will need the following core components:

| Component | Description |
| :---- | :---- |
| **ESP32-CAM Module** | AI-Thinker or similar module with the OV2640 camera. |
| **FTDI / USB-to-TTL Adapter** | Required for flashing the firmware to the ESP32. |
| **Power Supply** | A stable 5V DC supply (a BEC on an RC system works well). |

## **🚀 Getting Started**

Follow these steps to flash the firmware onto your ESP32-CAM and begin streaming video.

### **1\. Software Prerequisites**

Make sure you have the following software installed:

* **Arduino IDE** or **VS Code with PlatformIO**  
* The **ESP32 Boards Manager** installed in your IDE.

### **2\. Flashing the Code**

1. Clone this repository to your local machine:  
   git clone \[https://github.com/Boyyt357/Esp-32-cam-VTX.git\](https://github.com/Boyyt357/Esp-32-cam-VTX.git)

2. Open the project in your chosen IDE.  
3. **Configure Wi-Fi:** Before compiling, open the main sketch file and update the following lines with your network credentials:  
   const char\* ssid \= "YOUR\_WIFI\_SSID";  
   const char\* password \= "YOUR\_WIFI\_PASSWORD";

   *(Note: For field use, you may want to configure it to create its own Access Point (AP).)*  
4. Connect your ESP32-CAM to your FTDI adapter (ensure correct wiring for programming mode, usually grounding **GPIO 0**).  
5. Select the correct board (AI-Thinker ESP32-CAM) and COM port.  
6. Upload the code. Once the upload is complete, disconnect the **GPIO 0** wire to return the board to running mode.

### **3\. Usage**

1. Connect the ESP32-CAM to a stable 5V power source.  
2. The module will connect to your specified Wi-Fi network.  
3. Check your router's client list or use a network scanning app to find the IP address assigned to the ESP32 (it will likely appear as esp32-cam).  
4. Open any web browser on a device connected to the same network and navigate to the IP address:  
   http://\<ESP32\_IP\_ADDRESS\>

5. You should now see the live video feed\!

## **🤝 Contribution**

Contributions, issues, and feature requests are welcome\! Feel free to check the [issues page](https://www.google.com/search?q=https://github.com/Boyyt357/Esp-32-cam-VTX/issues) and submit a pull request if you have improvements or bug fixes.

## **📄 License**

This project is released under the **MIT License**. See the LICENSE file for details.
