#pragma once
#include <Arduino.h>
#include <OneButton.h>
#include <Encoder.h>
#include "common_def.h"
#include "gui.h"
#include "VarSpeedServo.h"
#include "lights.h"

#define SERVO_PIN 6
#define L_SPEED 15
#define H_SPEED 100

#define KNOB_PIN 4

class Safeduino
{
public:
    Safeduino() : _enc(2, 3), _but(KNOB_PIN) {}

    void begin(void);
    void run(void);

    state_e getStep(void);

private:
    Gui _display;
    VarSpeedServo _servo;
    Lights _leds;
    Encoder _enc;
    OneButton _but;

    state_e _step;

    int servoPos = 0;

    volatile long _oldEncPos = -999;
    volatile long _newEncPos = 0;

    void _setStep(state_e step);

    void _lockDoor(void);
    void _unlockDoor(void);

    void _singleClickEvent(void);
    void _doubleClickEvent(void);
};