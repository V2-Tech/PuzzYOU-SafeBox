#include "safeduino.h"

void Safeduino::begin(void)
{
    Serial.println(F("Safeduino initialization"));
    //----------------------------------------
    //        INIT SCREEN
    //----------------------------------------
    _display.begin();

    //----------------------------------------
    //        INIT DOOR LOCK
    //----------------------------------------
    _servo.attach(SERVO_PIN);
    _lockDoor();

    //----------------------------------------
    //        INIT DOOR LEDS
    //----------------------------------------
    _leds.begin();

    //----------------------------------------
    //        INIT KNOB BUTTON
    //----------------------------------------
    Serial.println(F("Button Initialization"));
    _but.attachClick([](void *scope)
                     { ((Safeduino *)scope)->_singleClickEvent(); },
                     this);
    _but.attachDoubleClick([](void *scope)
                           { ((Safeduino *)scope)->_doubleClickEvent(); },
                           this);
    Serial.println(F("Button Initialization completed"));

    Serial.println(F("Safeduino initialization completed"));

    _setStep(LOCK);
}

void Safeduino::run(void)
{
    _newEncPos = _enc.read();
    _but.tick();
    _display.update();
}

state_e Safeduino::getStep(void)
{
    return this->_step;
}

void Safeduino::_setStep(state_e step)
{
    _step = step;
}

void Safeduino::_lockDoor(void)
{
    _servo.write(8, H_SPEED, true);
}

void Safeduino::_unlockDoor(void)
{
    _servo.write(90, L_SPEED, false);
}

void Safeduino::_singleClickEvent(void)
{
    Serial.println(F("Hello from single click"));
    switch (_step)
    {
    case LOCK:
        _setStep(MAIN_PAGE);
        _display.setPage(MAIN_PAGE);
        break;

    case MAIN_PAGE:
        _setStep(FIRST_NUM);
        _display.setPage(FIRST_NUM);
        break;

    case FIRST_NUM:
        break;

    default:
        break;
    }
}

void Safeduino::_doubleClickEvent(void)
{
    static unsigned int status = 0;
    if (status == 0)
    {
        status = 1;
        _lockDoor();
        return;
    }
    _unlockDoor();
    status = 0;

    Serial.println(F("Hello from double click"));
}
