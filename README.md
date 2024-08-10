# ESP32 IR Remote Web Interface

## Overview

This project uses an ESP32 to create a web server that allows you to capture, store, and send IR (infrared) signals using a remote control. The web interface is designed to be responsive and professional, fitting well on any device. You can capture new IR signals, view and manage saved signals, and send commands directly from the web interface.

## Features

- **Capture IR Signals**: Use the web interface to capture IR signals from your remote control.
- **Store IR Signals**: Save captured IR signals with a custom name. The data is preserved even if the ESP32 is restarted.
- **Manage Signals**: View a list of saved IR signals, and delete or send commands as needed.
- **Responsive Design**: The web interface is designed to be responsive, making it suitable for any device, including smartphones and desktops.

## Components

- **ESP32**: Microcontroller used for handling IR signals and hosting the web server.
- **IR Receiver**: Captures IR signals from remote controls.
- **IR Emitter**: Sends IR commands to devices.

## Installation

### Hardware

1. **Connect the IR Receiver**:
   - Signal pin to GPIO 15 (or your chosen pin).
   - VCC to 3.3V.
   - GND to GND.

2. **Connect the IR Emitter**:
   - Signal pin to GPIO 4 (or your chosen pin).
   - VCC to 3.3V.
   - GND to GND.

### Software

1. **Install Libraries**:
   - Install the `IRremote` library from the Arduino Library Manager.
   - Install the `ArduinoJson` library from the Arduino Library Manager.

2. **Upload the Code**:
   - Open the Arduino IDE.
   - Select your ESP32 board and the correct port.
   - Copy and paste the code from `esp32_ir_remote.ino` into a new sketch.
   - Upload the sketch to your ESP32.

3. **Upload Filesystem Data**:
   - Create a `data` folder in the Arduino sketch directory.
   - Place `index.html`, `style.css`, and `script.js` files into the `data` folder.
   - Use the "ESP32 Sketch Data Upload" tool in the Arduino IDE to upload the files to the ESP32 filesystem.

## Usage

1. **Connect to the ESP32**:
   - After uploading the code, the ESP32 will create a Wi-Fi network named `ESP32_IR_Remote`.
   - Connect your device to this Wi-Fi network.

2. **Access the Web Interface**:
   - Open a web browser and navigate to `http://192.168.4.1` to access the web interface.

3. **Capture IR Signals**:
   - Use the "Capture a New Signal" form to capture IR signals from your remote control.

4. **Manage IR Signals**:
   - View captured IR signals in the list.
   - Use the "Send" button to send a signal.
   - Use the "Delete" button to remove a signal from the list.

## Files

- `esp32_ir_remote.ino`: Main Arduino sketch for the ESP32.
- `index.html`: HTML file for the web interface.
- `style.css`: CSS file for styling the web interface.
- `script.js`: JavaScript file for handling interactions on the web interface.

## Troubleshooting

- **ESP32 Not Connecting**: Ensure that the ESP32 is properly connected to your computer and the correct board and port are selected in the Arduino IDE.
- **Web Interface Not Loading**: Verify that you are connected to the ESP32 Wi-Fi network and that the IP address (`http://192.168.4.1`) is correctly entered in your browser.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

## Creator

Created by Kent Carlo Amante.

## Contact

For questions or support, please open an issue on the [GitHub repository]([https://github.com/yourusername/esp32-ir-remote](https://github.com/Skca01/ESP32-IR-Remote-Web-Interface)).
