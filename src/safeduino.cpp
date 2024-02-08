#include "safeduino.h"

static Gui display;

void Safeduino::begin(void)
{
    Serial.println(F("Safeduino initialization"));
    //----------------------------------------
    //        INIT SCREEN
    //----------------------------------------
    display.begin();

    //----------------------------------------
    //        INIT DOOR LOCK
    //----------------------------------------
    servo.attach(SERVO_PIN);
    Serial.println(F("Safeduino initialization completed"));
}

void Safeduino::run(void)
{
    display.update();
}
