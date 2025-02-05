#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#include "WiFi.h"
#include "Motor.h"

const char *ssid = "ESP32-Access-Point";
const char *password = "123456789";

// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0;
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

WiFiServer server(80);

Motor leftMotor(12,14);
Motor rightMotor(32,33);

AnalogAudioStream out;
BluetoothA2DPSink a2dp_sink(out);

String header;

enum Direction : char
{
    NONE,
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};
Direction current_direction = NONE;

void data_recieved_callback(const uint8_t *data, uint32_t len)
{
    // generate your sound data
    // return the effective length (in frames) of the generated sound  (which usually is identical with the requested len)
    // 1 frame is 2 channels * 2 bytes = 4 bytes
    Serial.printf("Got %d bytes\n", len);
}

void bluetooth_setup()
{
    a2dp_sink.set_stream_reader(data_recieved_callback);
    a2dp_sink.start("Inselkaraoke");
}

void wifi_setup()
{
    // Connect to Wi-Fi network with SSID and password
    Serial.print("Setting AP (Access Point)…");
    // Remove the password parameter, if you want the AP (Access Point) to be open
    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    server.begin();
}

void setup()
{
    Serial.begin(115200);
    bluetooth_setup();
    wifi_setup();
    delay(2000);
}

void handle_client(WiFiClient client)
{
    if (!client)
        return;

    Serial.println("New Client.");
    // handle the client
    String currentLine = "";
    while (client.connected() && currentTime - previousTime <= timeoutTime)
    { // loop while the client's connected
        currentTime = millis();
        if (client.available())
        {
            char c = client.read();
            Serial.write(c);   
            header += c;
            if (c == '\n')
            {
                if (currentLine.length() == 0)
                {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();

                    if (header.indexOf("GET /none") >= 0)
                    {
                        current_direction = NONE;
                        Serial.println("NONE");
                    }
                    else if (header.indexOf("GET /forward") >= 0)
                    {
                        current_direction = FORWARD;
                        Serial.println("Forward");
                    }
                    else if (header.indexOf("GET /backward") >= 0)
                    {
                        current_direction = BACKWARD;
                    }
                    else if (header.indexOf("GET /left") >= 0)
                    {
                        current_direction = LEFT;
                    }
                    else if (header.indexOf("GET /right") >= 0)
                    {
                        current_direction = RIGHT;
                    }

                    client.println("<!DOCTYPE html><html>");
                    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
                    client.println("<body>");
                    client.printf("<p>%d</p>\n", current_direction);
                    client.println("</body></html>");

                    client.println();
                    break;
                }
                else
                {
                    currentLine = "";
                }
            }
            else if (c != '\r')
            {
                currentLine += c;
            }
        }
    }

    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");
}

void handle_state()
{
    switch (current_direction)
    {
    case NONE:
        rightMotor.stop();
        leftMotor.stop();
        break;
    case FORWARD:
        rightMotor.forward();
        leftMotor.forward();
        break;
    case BACKWARD:
        rightMotor.backwards();
        leftMotor.backwards();
        break;
    case LEFT:
        rightMotor.forward();
        leftMotor.backwards();
        break;
    case RIGHT:
        rightMotor.backwards();
        leftMotor.forward();
        break;
    }
}

void loop()
{
    handle_client(server.available());
    handle_state();
    previousTime = currentTime;
    currentTime = millis();
}