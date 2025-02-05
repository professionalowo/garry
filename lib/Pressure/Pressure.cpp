#include "Pressure.h"

TPressure::TPressure(int pin)
    : m_pin(pin),
      m_previous_time(0)
{
    pinMode(m_pin, INPUT);
}

// check if preassure plate has been pressed for 1 second through m_pin
bool TPressure::loop() {
        int pinState = digitalRead(m_pin);
        unsigned long current_time = millis();

        if (pinState == HIGH) {
            if (m_previous_time == 0) {
                // Start timing when pin first goes HIGH
                m_previous_time = current_time;
            }
            // Check if the pin has been HIGH for at least m_timeout
            if ((current_time - m_previous_time) >= m_timeout) {
                return true;
            }
        } else {
            // Reset timing when pin goes LOW
            m_previous_time = 0;
        }

        return false;
    }
