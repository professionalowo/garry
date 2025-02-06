#include "Audio.h"

#define DEBUG_AUDIO 1

TAudio::TAudio(int pin, std::vector<std::pair<int,int>> &&data)
    : m_pin(pin),
      m_data(data),
      m_tone(new ToneESP32(pin, 0))
{
}

void TAudio::loop(bool start_audio)
{
    if (start_audio)
    {
        step();
    }
}

void TAudio::step()
{
    if (m_index < m_data.size())
    {
        auto val = m_data[m_index];
        m_tone.get()->tone(val.first, val.second);
        m_index++;
    }
    else
    {
        m_index = 0;
    }
}
