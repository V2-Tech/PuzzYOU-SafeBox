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
private:
    // Private constructor to prevent instantiation from outside
    Safeduino() {}

    // Private instance of the class
    static Safeduino *instance;

public:
    // Public method to access the singleton instance
    static Safeduino *getInstance();

    void begin(void);
    void run(void);

private:
    Gui *display = Gui::getInstance();
    VarSpeedServo servo;

    int servoPos = 0;
};