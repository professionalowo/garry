#include "Network.h"

TNetwork::TNetwork(const char *ssid, const char *password)
    : m_ssid(ssid),
      m_password(password),
      m_current_time(0),
      m_previous_time(0),
      m_server(WiFiServer(80)),
      m_current_direction(Direction::NONE)
{
}

void TNetwork::setup()
{
    WiFi.softAP(m_ssid, m_password);

    IPAddress IP = WiFi.softAPIP();
    Serial.print("AP IP address: ");
    Serial.println(IP);

    m_server.begin();
}

Direction TNetwork::loop()
{
    WiFiClient client = m_server.available();
    if (!client)
        return m_current_direction;

    Serial.println("New Client.");
    // handle the client
    String currentLine = "";
    while (client.connected())
    { // loop while the client's connected
        m_previous_time = m_current_time;
        m_current_time = millis();
        if (client.available())
        {
            char c = client.read();
            Serial.write(c);
            m_header += c;
            if (c == '\n')
            {
                if (currentLine.length() == 0)
                {
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-type:text/html");
                    client.println("Connection: close");
                    client.println();

                    if (m_header.indexOf("GET /none") >= 0)
                    {
                        m_current_direction = NONE;
                        Serial.println("None");
                    }
                    else if (m_header.indexOf("GET /forward") >= 0)
                    {
                        m_current_direction = FORWARD;
                        Serial.println("Forward");
                    }
                    else if (m_header.indexOf("GET /backward") >= 0)
                    {
                        m_current_direction = BACKWARD;
                        Serial.println("Backward");
                    }
                    else if (m_header.indexOf("GET /left") >= 0)
                    {
                        m_current_direction = LEFT;
                        Serial.println("Left");
                    }
                    else if (m_header.indexOf("GET /right") >= 0)
                    {
                        m_current_direction = RIGHT;
                        Serial.println("Right");
                    }

                    client.println("<!DOCTYPE html><html>");
                    client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
                    client.println("<body>");
                    client.printf("<p>%d</p>\n", m_current_direction);
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

    m_header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

    Serial.printf("Current Direction: %d\n",m_current_direction);

    return m_current_direction;
};

WiFiServer TNetwork::get_server() const
{
    return m_server;
};