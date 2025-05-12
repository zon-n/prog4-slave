#include <Arduino.h>
#include <CrcLib.h>
#include <Wire.h>

#define MIN_FORCE 10

int8_t posX;
int8_t posY;
int8_t angleInput;
;
int8_t speedInput;

byte forceOutput;
float angleOutput;
byte index;
volatile bool flag = true;

int8_t powerWheelFrontLeft = 0;
int8_t powerWheelFrontRight = 0;
int8_t powerWheelBackLeft = 0;
int8_t powerWheelBackRight = 0;

void requestEvent()
{
    Wire.write(speedInput);
    Wire.write(angleInput);
}

void receiveEvent(int quantity)
{
    forceOutput = Wire.read();
    angleOutput = Wire.read() * PI / 180;
    flag = true;
}

void setup()
{
    Serial.begin(115200);
    CrcLib::Initialize();
    CrcLib::InitializePwmOutput(CRC_PWM_1);
    CrcLib::InitializePwmOutput(CRC_PWM_2, true);
    CrcLib::InitializePwmOutput(CRC_PWM_3);
    CrcLib::InitializePwmOutput(CRC_PWM_4, true);
    Wire.begin(0x02);
    Wire.onRequest(requestEvent);
    Wire.onReceive(receiveEvent);
}

void loop()
{
    CrcLib::Update();

    // Read Joysticks returns values from -128, 127
    posX = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_X);
    posY = CrcLib::ReadAnalogChannel(ANALOG::JOYSTICK2_Y);

    speedInput = (CrcLib::ReadAnalogChannel(ANALOG::GACHETTE_L) + 128) / 2;
    if (posY > 0)
    {
        speedInput = -speedInput;
    }

    if (abs(posX) < MIN_FORCE && abs(posY) < MIN_FORCE)
    {
        angleInput = 0;
    }
    else
    {
        angleInput = atan((float)posX / (float)posY) * 180 / PI;
    }

    Serial.println("angleInput: " + String(angleInput));
    Serial.println("speedInput: " + String(speedInput));
    Serial.println("forceOutput: " + String(forceOutput));
    Serial.println("angleOutput: " + String(angleOutput));
    Serial.println("------------------");

    if (flag)
    {
        flag = false;
        if (forceOutput < MIN_FORCE)
        {
            forceOutput = 0;
        }

        int8_t x = forceOutput * sin(angleInput * PI / 180);
        int8_t y = forceOutput * cos(angleOutput * PI / 180);

        powerWheelFrontLeft = y - x;
        powerWheelFrontRight = y + x;
        powerWheelBackLeft = y + x;
        powerWheelBackRight = y - x;

        Serial.println("powerWheelFrontLeft: " + String(powerWheelFrontLeft));
        Serial.println("powerWheelFrontRight: " + String(powerWheelFrontRight));
        Serial.println("powerWheelBackLeft: " + String(powerWheelBackLeft));
        Serial.println("powerWheelBackRight: " + String(powerWheelBackRight));

        CrcLib::SetPwmOutput(CRC_PWM_1, powerWheelFrontLeft);
        CrcLib::SetPwmOutput(CRC_PWM_2, powerWheelFrontRight);
        CrcLib::SetPwmOutput(CRC_PWM_3, powerWheelBackLeft);
        CrcLib::SetPwmOutput(CRC_PWM_4, powerWheelBackRight);
    }
}