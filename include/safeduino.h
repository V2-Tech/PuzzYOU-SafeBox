#pragma once
#include <Arduino.h>
#include "gui.h"
#include "VarSpeedServo.h"
#include "shared.h"

#define L_SPEED 20
#define H_SPEED 100
#define SERVO_PIN 6

class Safeduino
{
public:
    Safeduino() {}

    void begin(void);
    void run(void);

private:
    VarSpeedServo servo;

    int servoPos = 0;
};