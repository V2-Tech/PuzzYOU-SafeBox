#include "safebox.h"

void Safebox::begin(void)
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
                     { ((Safebox *)scope)->_singleClickEvent(); },
                     this);
    _but.attachDoubleClick([](void *scope)
                           { ((Safebox *)scope)->_doubleClickEvent(); },
                           this);
    Serial.println(F("Button Initialization completed"));

    Serial.println(F("Safeduino initialization completed"));

    //----------------------------------------
    //        FIRST ACTIONS
    //----------------------------------------
    _setStep(LOCK);
    _leds.animationON(led_animation_e::start_animation, 2);
}

void Safebox::run(void)
{
    _newEncPos = _enc.read();
    _but.tick();
    _stepManager();
    _display.update();
    _leds.run();
}

state_e Safebox::getStep(void)
{
    return this->_actStep;
}

void Safebox::_setStep(state_e step)
{
    _actStep = step;
    _newEvent = 1;
}

void Safebox::_nextStep(void)
{
    switch (_actStep)
    {
    case LOCK:
        _setStep(MAIN_PAGE);
        break;
    case MAIN_PAGE:
        _setStep(FIRST_NUM);
        break;
    case FIRST_NUM:
        _setStep(SECOND_NUM);
        break;
    case SECOND_NUM:
        _setStep(THIRD_NUM);
        break;
    case THIRD_NUM:
        _setStep(SELECTION_1);
        break;
    case SELECTION_1:
        _setStep(UNLOCKED);
        break;
    default:
        break;
    }
}

void Safebox::_prevStep(void)
{
    switch (_actStep)
    {
    case MAIN_PAGE:
        _setStep(LOCK);
        break;
    case FIRST_NUM:
        _setStep(MAIN_PAGE);
        break;
    case SECOND_NUM:
        _setStep(FIRST_NUM);
        break;
    case THIRD_NUM:
        _setStep(SECOND_NUM);
        break;
    case SELECTION_1:
        _setStep(THIRD_NUM);
        break;
    default:
        break;
    }
}

void Safebox::_stepManager(void)
{
    if (_newEvent == 1)
    {
        switch (_actStep)
        {
        case LOCK:
            _stepLock();
            break;
        case MAIN_PAGE:
            _stepMainPage();
            break;
        case FIRST_NUM:
            _stepFirstNum();
            break;
        case SECOND_NUM:
            _stepSecondNum();
            break;
        case THIRD_NUM:
            _stepThirdNum();
            break;
        case SELECTION_1:
            _stepSelection1();
            break;
        case UNLOCKED:
            _stepUnlocked();
            break;
        default:
            break;
        }

        _newEvent = 0;
    }
}

void Safebox::_stepLock(void)
{
    _display.setPage(LOCK);
}

void Safebox::_stepMainPage(void)
{
    _display.setPage(MAIN_PAGE);
}

void Safebox::_stepFirstNum(void)
{
    _display.setPage(FIRST_NUM);
}

void Safebox::_stepSecondNum(void)
{
    _display.setPage(SECOND_NUM);
}

void Safebox::_stepThirdNum(void)
{
    _display.setPage(THIRD_NUM);
}

void Safebox::_stepSelection1(void)
{
    _display.setPage(SELECTION_1);
}

void Safebox::_stepUnlocked(void)
{
    _display.setPage(UNLOCKED);
}

void Safebox::_lockDoor(void)
{
    _servo.write(8, H_SPEED, true);
}

void Safebox::_unlockDoor(void)
{
    _servo.write(90, L_SPEED, false);
}

void Safebox::_singleClickEvent(void)
{
    _nextStep();
}

void Safebox::_doubleClickEvent(void)
{
    //    static unsigned int status = 0;
    //    if (status == 0)
    //    {
    //        status = 1;
    //        _lockDoor();
    //        return;
    //    }
    //    _unlockDoor();
    //    status = 0;
    _prevStep();
}
