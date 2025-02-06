#include "WiFi.h"
#include "Motor.h"
#include "Direction.h"
#include "Network.h"
#include "Pressure.h"
#include "Light.h"
#include "Audio.h"

TNetwork network("Müllabfuhr-Point", "123456789");

TLight light(32);

TMotor leftMotor(14, 12);
TMotor rightMotor(33, 32);

TPressure pressure(26);

std::vector<unsigned char> audio_data = {HIGH, LOW, HIGH, LOW, HIGH};

TAudio audio(25, std::move(audio_data));

void setup()
{
    Serial.begin(115200);
    network.setup();
    light.setup();
    audio.setup();
}

void handle_state(Direction current_direction)
{
    switch (current_direction)
    {
    case Direction::NONE:
        rightMotor.stop();
        leftMotor.stop();
        break;
    case Direction::FORWARD:
        rightMotor.forward();
        leftMotor.forward();
        break;
    case Direction::BACKWARD:
        rightMotor.backward();
        leftMotor.backward();
        break;
    case Direction::LEFT:
        rightMotor.stop();
        leftMotor.forward();
        break;
    case Direction::RIGHT:
        rightMotor.forward();
        leftMotor.stop();
        break;
    }
}

void loop()
{
    handle_state(network.loop());
    auto is_hit = pressure.loop();
    light.loop(is_hit);
    audio.loop(is_hit);
}