#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "username";
const char* password = "password";

ESP8266WebServer server(80); // Create a web server on port 80
const int LED_PIN = 15;  // GPIO2 (D4 on most NodeMCU boards)

void handleLED() {
    Serial.println(WiFi.localIP());
    String state = server.arg("state");
    if (state == "on") {
        Serial.println("SWITCHING ON");
        digitalWrite(LED_PIN, LOW);  // Turn LED ON (ESP8266 uses inverted logic)
        server.send(200, "text/plain", "LED is ON");
    } else if (state == "off") {
        Serial.println("SWITCHING OFF");
        digitalWrite(LED_PIN, HIGH); // Turn LED OFF
        server.send(200, "text/plain", "LED is OFF");
    } else {
        Serial.println("INVALID INPUT");
        server.send(400, "text/plain", "Invalid state");
    }
}

void setup() {
    Serial.begin(115200);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi");

    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }

    Serial.println("\nWiFi Connected!");
    Serial.print("ESP8266 IP Address: ");
    Serial.println(WiFi.localIP());

    pinMode(LED_PIN, OUTPUT);
    digitalWrite(LED_PIN, HIGH); // LED OFF by default

    server.on("/led", handleLED); // Define the LED control endpoint
    server.begin();
    Serial.println("HTTP Server started...");
}

void loop() {
    server.handleClient(); // Handle client requests
}
