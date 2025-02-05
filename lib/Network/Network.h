#include "WiFi.h"
#include "Direction.h"

class TNetwork
{
public:
    TNetwork(const char *ssid, const char *password);
    void setup();
    Direction loop();
    WiFiServer get_server() const;

private:
    const char *m_ssid;
    const char *m_password;
    String m_header;
    int m_current_time;
    int m_previous_time;
    WiFiServer m_server;
    int m_timeout = 2000;
};