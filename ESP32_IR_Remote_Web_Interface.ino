#include <WiFi.h>
#include <WebServer.h>
#include <IRremote.hpp>
#include <SPIFFS.h>
#include <ArduinoJson.h>

const char* ssid = "ESP32_IR_Remote";
const char* password = "12345678";

WebServer server(80);

#define IR_RECEIVE_PIN 15
#define IR_SEND_PIN 4

struct IRSignal {
  String name;
  uint16_t address;
  uint8_t command;
};

std::vector<IRSignal> irSignals;

void setup() {
  Serial.begin(115200);
  WiFi.softAP(ssid, password);
  IPAddress IP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(IP);
  
  if(!SPIFFS.begin(true)) {
    Serial.println("SPIFFS Mount Failed");
    return;
  }
  
  loadIRSignals();
  
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
  IrSender.begin(IR_SEND_PIN);
  
  server.on("/", handleRoot);
  server.on("/capture", handleCaptureIR);
  server.on("/delete", handleDeleteIR);
  server.on("/send", handleSendIR);
  server.on("/style.css", handleStyleCSS);
  
  server.begin();
  Serial.println("Web server started");
}

void loop() {
  server.handleClient();
  
  if (IrReceiver.decode()) {
    IRSignal signal = {
      "New Signal",
      IrReceiver.decodedIRData.address,
      IrReceiver.decodedIRData.command
    };
    
    irSignals.push_back(signal);
    saveIRSignals();
    
    IrReceiver.resume();
  }
}

void handleRoot() {
  String page = R"(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP32 Web-Based IR Remote Control Interface: Capture, Store, and Send IR Signals</title>
    <link rel="stylesheet" href="/style.css">
</head>
<body>
    <div class="container">
        <header>
            <h1>ESP32 Web-Based IR Remote Control Interface: Capture, Store, and Send IR Signals</h1>
        </header>
        <main>
            <section class="instructions">
                <h2>How to Use</h2>
                <ol>
                    <li>Point your IR remote at the ESP32 and press a button.</li>
                    <li>Enter a name and click "Capture".</li>
                    <li>The captured signal will appear in the list below.</li>
                    <li>To send a signal, click the "Send" button next to it.</li>
                    <li>To delete a signal, click the "Delete" button.</li>
                </ol>
            </section>
            <section class="capture-form">
                <h2>Capture New Signal</h2>
                <form action="/capture" method="post">
                    <input type="text" name="name" placeholder="Enter signal name" required>
                    <button type="submit" class="btn btn-primary">Capture</button>
                </form>
            </section>
            <section class="signal-list">
                <h2>Captured IR Signals</h2>
                <ul>
)";

  for (size_t i = 0; i < irSignals.size(); i++) {
    page += "<li class='signal-item'>";
    page += "<div class='signal-info'>";
    page += "<h3>" + irSignals[i].name + "</h3>";
    page += "<span>Address: 0x" + String(irSignals[i].address, HEX) + "</span>";
    page += "<span>Command: 0x" + String(irSignals[i].command, HEX) + "</span>";
    page += "</div>";
    page += "<div class='signal-actions'>";
    page += "<a href='/send?id=" + String(i) + "' class='btn btn-send'>Send</a>";
    page += "<a href='/delete?id=" + String(i) + "' class='btn btn-delete'>Delete</a>";
    page += "</div></li>";
  }

  page += R"(
                </ul>
            </section>
        </main>
        <footer>
            <p>&copy; 2024 ESP32 Web-Based IR Remote Control Interface: Capture, Store, and Send IR Signals. Created by Kent Carlo Amante</p>
        </footer>
    </div>
</body>
</html>
  )";
  
  server.send(200, "text/html", page);
}

void handleCaptureIR() {
  String name = server.arg("name");
  
  if (name.length() > 0) {
    irSignals.back().name = name;
    saveIRSignals();
  }
  
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleDeleteIR() {
  size_t id = server.arg("id").toInt();
  
  if (id < irSignals.size()) {
    irSignals.erase(irSignals.begin() + id);
    saveIRSignals();
  }
  
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleSendIR() {
  size_t id = server.arg("id").toInt();
  
  if (id < irSignals.size()) {
    IrSender.sendNEC(irSignals[id].address, irSignals[id].command, 2);
  }
  
  server.sendHeader("Location", "/");
  server.send(303);
}

void handleStyleCSS() {
  String css = R"(
:root {
  --primary-color: #007bff;
  --secondary-color: #6c757d;
  --success-color: #28a745;
  --danger-color: #dc3545;
  --light-color: #f8f9fa;
  --dark-color: #343a40;
}

* {
  box-sizing: border-box;
  margin: 0;
  padding: 0;
}

body {
  font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
  line-height: 1.6;
  color: var(--dark-color);
  background-color: var(--light-color);
}

.container {
  max-width: 800px;
  margin: 0 auto;
  padding: 20px;
}

header {
  text-align: center;
  margin-bottom: 2rem;
}

h1 {
  color: var(--primary-color);
}

h2 {
  color: var(--secondary-color);
  margin-bottom: 1rem;
}

.instructions {
  background-color: #fff;
  border-radius: 8px;
  padding: 20px;
  margin-bottom: 2rem;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

.instructions ol {
  padding-left: 20px;
}

.capture-form {
  background-color: #fff;
  border-radius: 8px;
  padding: 20px;
  margin-bottom: 2rem;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

form {
  display: flex;
  gap: 10px;
}

input[type="text"] {
  flex-grow: 1;
  padding: 10px;
  border: 1px solid #ddd;
  border-radius: 4px;
}

.btn {
  padding: 10px 20px;
  border: none;
  border-radius: 4px;
  cursor: pointer;
  transition: background-color 0.3s ease;
}

.btn-primary {
  background-color: var(--primary-color);
  color: white;
}

.btn-primary:hover {
  background-color: #0056b3;
}

.signal-list {
  background-color: #fff;
  border-radius: 8px;
  padding: 20px;
  box-shadow: 0 2px 4px rgba(0,0,0,0.1);
}

.signal-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 15px;
  border-bottom: 1px solid #eee;
}

.signal-item:last-child {
  border-bottom: none;
}

.signal-info h3 {
  margin-bottom: 5px;
}

.signal-info span {
  display: block;
  font-size: 0.9em;
  color: var(--secondary-color);
}

.signal-actions {
  display: flex;
  gap: 10px;
}

.btn-send {
  background-color: var(--success-color);
  color: white;
}

.btn-send:hover {
  background-color: #218838;
}

.btn-delete {
  background-color: var(--danger-color);
  color: white;
}

.btn-delete:hover {
  background-color: #c82333;
}

footer {
  text-align: center;
  margin-top: 2rem;
  color: var(--secondary-color);
}

@media (max-width: 600px) {
  .container {
    padding: 10px;
  }
  
  form {
    flex-direction: column;
  }
  
  .signal-item {
    flex-direction: column;
    align-items: flex-start;
  }
  
  .signal-actions {
    margin-top: 10px;
  }
}
  )";
  
  server.send(200, "text/css", css);
}

void loadIRSignals() {
  File file = SPIFFS.open("/irsignals.json", "r");
  
  if (!file) {
    Serial.println("Failed to open file for reading");
    return;
  }
  
  DynamicJsonDocument doc(1024);
  
  DeserializationError error = deserializeJson(doc, file);
  if (error) {
    Serial.print(F("Failed to read file, using default configuration"));
    return;
  }
  
  for (JsonVariant v : doc["signals"].as<JsonArray>()) {
    IRSignal signal = {
      v["name"].as<String>(),
      v["address"].as<uint16_t>(),
      v["command"].as<uint8_t>()
    };
    
    irSignals.push_back(signal);
  }
  
  file.close();
}

void saveIRSignals() {
  DynamicJsonDocument doc(1024);
  
  JsonArray array = doc.createNestedArray("signals");
  for (IRSignal &signal : irSignals) {
    JsonObject obj = array.createNestedObject();
    obj["name"] = signal.name;
    obj["address"] = signal.address;
    obj["command"] = signal.command;
  }
  
  File file = SPIFFS.open("/irsignals.json", "w");
  
  if (!file) {
    Serial.println("Failed to open file for writing");
    return;
  }
  
  if (serializeJson(doc, file) == 0) {
    Serial.println(F("Failed to write to file"));
  }
  
  file.close();
}
