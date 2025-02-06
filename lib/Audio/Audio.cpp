#include "Audio.h"

TAudio::TAudio(int pin, const unsigned char *data, int length)
    : m_pin(pin),
      m_data(data),
      m_length(length)
{
}

void TAudio::setup()
{
    pinMode(m_pin, OUTPUT);
}

void TAudio::step()
{
    if (m_index < m_length)
    {
        digitalWrite(m_pin, m_data[m_index]);
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
    delete m_data;
}