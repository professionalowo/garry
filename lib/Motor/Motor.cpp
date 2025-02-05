#include "Motor.h"
#include "Arduino.h"

Motor::Motor(int forward_pin, int backwards_pin)
:m_backwardsPin(backwards_pin),m_forward_pin(forward_pin)
{
    pinMode(m_backwardsPin, OUTPUT);
    pinMode(m_forward_pin, OUTPUT);
}
Motor::~Motor()
{
    pinMode(m_backwardsPin, INPUT);
    pinMode(m_forward_pin, INPUT);
    stop();
}

void Motor::backwards(){
    digitalWrite(m_backwardsPin, HIGH);
    digitalWrite(m_forward_pin, LOW);
}

void Motor::forward(){
    digitalWrite(m_backwardsPin, LOW);
    digitalWrite(m_forward_pin, HIGH);
}

void Motor::stop(){
    digitalWrite(m_backwardsPin, LOW);
    digitalWrite(m_forward_pin, LOW);
}