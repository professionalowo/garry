#include "AudioTools.h"
#include "BluetoothA2DPSink.h"
#include "WiFi.h"
#include "Motor.h"
#include "Direction.h"
#include "Network.h"
#include "Pressure.h"
#include "Light.h"

TNetwork network("ESP32-Access-Point", "123456789");

TPressure pressure(17);

TLight light(4, 32);

TMotor leftMotor(14, 12);
TMotor rightMotor(33, 32);

AnalogAudioStream out;
BluetoothA2DPSink a2dp_sink(out);

void data_recieved_callback(const uint8_t *data, uint32_t len)
{
    // generate your sound data
    // return the effective length (in frames) of the generated sound  (which usually is identical with the requested len)
    // 1 frame is 2 channels * 2 bytes = 4 bytes
    Serial.printf("Got %d bytes\n", len);
}

void bluetooth_setup()
{
    a2dp_sink.set_stream_reader(data_recieved_callback);
    a2dp_sink.start("Inselkaraoke");
}

void setup()
{
    Serial.begin(115200);
    bluetooth_setup();
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
    light.loop(pressure);
}