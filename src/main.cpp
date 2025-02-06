#include "WiFi.h"
#include "Motor.h"
#include "Direction.h"
#include "Network.h"
#include "Pressure.h"
#include "Light.h"
#include "Audio.h"

TNetwork network("Garry-Net", "123456789");

TLight light(32);

TMotor leftMotor(14, 12);
TMotor rightMotor(33, 32);

TAudio audio(23, {});

TPressure pressure(26);

void setup()
{
    Serial.begin(115200);
    network.setup();
    light.setup();
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
    case Direction::RIGHT:
        rightMotor.backward();
        leftMotor.forward();
        break;
    case Direction::LEFT:
        rightMotor.forward();
        leftMotor.backward();
        break;
    }
}

void loop()
{
    auto state = network.loop();
    handle_state(state);
    auto is_hit = pressure.loop();
    light.loop(is_hit);
    audio.loop(is_hit);
}