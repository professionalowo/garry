#include "Network.h"

TNetwork::TNetwork(const char *ssid, const char *password)
    : m_ssid(ssid),
      m_password(password),
      m_current_time(millis()),
      m_previous_time(0),
      m_server(WiFiServer(80))
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
        return Direction::NONE;

    Serial.println("New Client.");
    // handle the client
    String currentLine = "";
    Direction current_direction = NONE;
    while (client.connected() && m_current_time - m_previous_time <= m_timeout)
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
                        current_direction = NONE;
                    }
                    else if (m_header.indexOf("GET /forward") >= 0)
                    {
                        current_direction = FORWARD;
                        Serial.println("Forward");
                    }
                    else if (m_header.indexOf("GET /backward") >= 0)
                    {
                        current_direction = BACKWARD;
                    }
                    else if (m_header.indexOf("GET /left") >= 0)
                    {
                        current_direction = LEFT;
                    }
                    else if (m_header.indexOf("GET /right") >= 0)
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

    m_header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

    return current_direction;
};

WiFiServer TNetwork::get_server() const
{
    return m_server;
};