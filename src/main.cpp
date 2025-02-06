#include "WiFi.h"
#include "Motor.h"
#include "Direction.h"
#include "Network.h"
#include "Pressure.h"
#include "Light.h"

TNetwork network("Garry-Net", "123456789");

TLight light(32);

TMotor leftMotor(12, 14);
TMotor rightMotor(32, 33);

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
    case Direction::LEFT:
        rightMotor.backward();
        leftMotor.forward();
        break;
    case Direction::RIGHT:
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
}