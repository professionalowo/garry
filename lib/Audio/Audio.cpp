#include "Audio.h"

#define DEBUG_AUDIO 0

TAudio::TAudio(int pin, std::vector<unsigned char> &&data)
    : m_pin(pin),
      m_data(data)
{
}

void TAudio::setup()
{
    pinMode(m_pin, OUTPUT);
}

void TAudio::step()
{
    if (m_index < m_data.size())
    {
        digitalWrite(m_pin, m_data[m_index]);
        if (DEBUG_AUDIO)
        {
            Serial.println(m_data[m_index]);
        }
        m_index++;
    }
    else
    {
        stop();
    }
}

void TAudio::loop(bool start_audio)
{
    if (start_audio)
    {
        step();
    }
    else
    {
        stop();
    }
}

void TAudio::stop()
{
    m_index = 0;
    digitalWrite(m_pin, LOW);
}

TAudio::~TAudio()
{
    stop();
}