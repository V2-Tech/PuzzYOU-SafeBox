#include "safeduino.h"

// Initialize the static instance to nullptr
Safeduino *Safeduino::instance = nullptr;

// Implementation of getInstance method
Safeduino *Safeduino::getInstance()
{
    if (!instance)
    {
        instance = new Safeduino();
    }
    return instance;
}

void Safeduino::begin(void)
{
    //----------------------------------------
    //        INIT SCREEN
    //----------------------------------------
    //display->begin();

    //----------------------------------------
    //        INIT DOOR LOCK
    //----------------------------------------
    servo.attach(SERVO_PIN);
}

void Safeduino::run(void)
{
    //display->update();
}
