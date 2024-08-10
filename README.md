# ESP32 Web-Based IR Remote Control Interface: Capture, Store, and Send IR Signals

## Overview
This project uses an ESP32 to create a web server that allows you to capture, store, and send IR (infrared) signals using a remote control. The web interface is designed to be responsive and professional, fitting well on any device. You can capture new IR signals, view and manage saved signals, and send commands directly from the web interface.

## Features
- **Capture IR Signals**: Use the web interface to capture IR signals from your remote control.
- **Store IR Signals**: Save captured IR signals with a custom name. The data is preserved even if the ESP32 is restarted.
- **Manage Signals**: View a list of saved IR signals, and delete or send commands as needed.
- **Responsive Design**: The web interface is designed to be responsive, making it suitable for any device, including smartphones and desktops.
- **Persistent Storage**: Uses SPIFFS to store IR signals, ensuring data is preserved across power cycles.
- **User-Friendly Interface**: Includes on-screen instructions and intuitive controls.

## Capabilities and Usage

### Capabilities
- **Capture IR Signals**: The system can capture IR signals from standard remote controls and store them in the ESP32's file system using SPIFFS.
- **Manage IR Signals**: Users can view, name, delete, and manage captured IR signals through a web-based interface.
- **Send IR Signals**: The ESP32 can re-transmit stored IR signals, allowing it to function as a programmable IR remote.
- **Web Interface**: The project includes a user-friendly web interface that can be accessed through any device connected to the ESP32's Wi-Fi network. The interface allows users to interact with the system without the need for additional software.

### Ethical Reminders
While this project offers powerful capabilities, it is crucial to use them responsibly. Here are some ethical considerations to keep in mind:

- **Respect Privacy**: Only capture and retransmit IR signals from devices you own or have explicit permission to control. Unauthorized use of this project to interfere with or control devices owned by others is unethical and potentially illegal.
- **Fair Use**: Do not use this project to interfere with other people's IR-controlled devices in public or shared spaces. Always respect the boundaries and personal space of others.
- **Compliance with Local Laws**: Ensure that your usage of this project complies with local laws and regulations, especially in contexts where IR signals might interfere with public or commercial devices.

### Non-Ethical Usage Warnings
- **Avoid Malicious Intent**: The project should not be used to disrupt or control devices in unauthorized settings, such as public displays, security systems, or other sensitive equipment.
- **Signal Jamming**: Be cautious not to inadvertently cause signal interference in environments where multiple IR-controlled devices are in operation. Misuse of this capability can lead to unintended consequences, including device malfunctions.

## Components
- **ESP32 Development Board**: Used for handling IR signals and hosting the web server.
- **IR Receiver Module or TSOP38238 IR receiver**: Captures IR signals from remote controls.
- **IR TRANSMITTER LED**: Sends IR commands to devices.
- **Resistor**: Used with the IR TRANSMITTER LED.
- **Breadboard and Jumper Wires**: For connecting the components.

## Installation

### Hardware Setup
1. **Connect the IR Receiver**:
   - Signal pin to GPIO 15 (or your chosen pin).
   - VCC to 3.3V.
   - GND to GND.

2. **Connect the IR Emitter**:
   - Signal pin to GPIO 4 (or your chosen pin).
   - VCC to 3.3V.
   - GND to GND.
   - **Note**: If you are using only an IR transmitter LED, connect a resistor to the positive end of the LED, and then connect the other end of the resistor to the signal pin. Connect the other end of the LED directly to GND.

### Software Setup
1. **Install Libraries**:
   - The following libraries are included with the ESP32 board package:
     - `WiFi.h`
     - `WebServer.h`
     - `SPIFFS.h`
   - Install the following libraries:
     - `IRremote` library: Install from the Arduino Library Manager or download from [GitHub](https://github.com/Arduino-IRremote/Arduino-IRremote).
     - `ArduinoJson` library: Install from the Arduino Library Manager or download from [Arduino](https://www.arduino.cc/reference/en/libraries/arduinojson/).

2. **Upload the Code**:
   - Open the Arduino IDE.
   - Select your ESP32 board and the correct port.
   - Copy and paste the code from `ESP32_IR_Remote_Web_Interface.ino` into a new sketch.
   - Upload the sketch to your ESP32.

## Usage
1. **Connect to the ESP32**:
   - After uploading the code, the ESP32 will create a Wi-Fi network named `ESP32_IR_Remote` with password `12345678`.
   - Connect your device to this Wi-Fi network.

2. **Access the Web Interface**:
   - Open a web browser and navigate to `http://192.168.4.1` to access the web interface.

3. **Capture IR Signals**:
   - Use the "Capture a New Signal" form to capture IR signals from your remote control.

4. **Manage IR Signals**:
   - View captured IR signals in the list.
   - Use the "Send" button to send a signal.
   - Use the "Delete" button to remove a signal from the list.

## Customization
- You can change the Wi-Fi SSID and password in the code.
- Modify the CSS in the `handleStyleCSS()` function to customize the look and feel of the web interface.

## Troubleshooting
- **ESP32 Not Connecting**: Ensure that the ESP32 is properly connected to your computer and the correct board and port are selected in the Arduino IDE.
- **Web Interface Not Loading**: Verify that you are connected to the ESP32 Wi-Fi network and that the IP address (`http://192.168.4.1`) is correctly entered in your browser.
- **IR Signal Capture Issues**: Ensure your IR receiver is properly connected and try adjusting the distance and angle to the remote control.
- **IR Signal Sending Issues**: Check the connection to your IR LED and ensure it's not obstructed.

## Contributing
Contributions to this project are welcome! Please feel free to submit a Pull Request.

## License
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Creator
Created by Kent Carlo Amante.

## Acknowledgments
- Thanks to the creators and maintainers of the libraries used in this project.
- Inspired by various IR remote projects in the maker community.

## Contact
For questions or support, please open an issue on the [GitHub repository](https://github.com/Skca01/ESP32-IR-Remote-Web-Interface).
