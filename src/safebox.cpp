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
    _encoderManager();
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
        _setStep(FOURTH_NUM);
        break;
    case FOURTH_NUM:
        _setStep(UNLOCKED);
        break;
    case UNLOCKED:
        _setStep(MAIN_PAGE);
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
    case FOURTH_NUM:
        _setStep(THIRD_NUM);
        break;
    case UNLOCKED:
        _setStep(FOURTH_NUM);
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
        case FOURTH_NUM:
            _stepFourthNum();
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
    _codeActNum[0] = _display.getCodeNum(0);
    _checkCodeNum(1);
    _display.setPage(SECOND_NUM);
}

void Safebox::_stepThirdNum(void)
{
    _codeActNum[1] = _display.getCodeNum(1);
    _checkCodeNum(2);
    _display.setPage(THIRD_NUM);
}

void Safebox::_stepFourthNum(void)
{
    _codeActNum[2] = _display.getCodeNum(2);
    _checkCodeNum(3);
    _display.setPage(FOURTH_NUM);
}

void Safebox::_stepUnlocked(void)
{
    _codeActNum[3] = _display.getCodeNum(3);
    _checkCodeNum(4);
    _checkCode();
}

void Safebox::_encoderManager(void)
{
    _newEncPos = _enc.read();
    if ((_newEncPos >= _oldEncPos + 2 * KNOB_MULTIPLIER) || (_newEncPos <= _oldEncPos - 2 * KNOB_MULTIPLIER))
    {
        _newEncoderEvent();
    }
}

void Safebox::_newEncoderEvent(void)
{
    if (_newEncPos >= _oldEncPos)
    {
        _encoderEventSub();
    }
    if (_newEncPos < _oldEncPos)
    {
        _encoderEventAdd();
    }

    _oldEncPos = _newEncPos;
}

void Safebox::_encoderEventAdd(void)
{
    unsigned int tempVal;

    switch (_actStep)
    {
    case FIRST_NUM:
        tempVal = _display.getCodeNum(0);
        if (tempVal == 99)
        {
            break;
        }
        _display.setCodeNum(0, ++tempVal);
        break;
    case SECOND_NUM:
        tempVal = _display.getCodeNum(1);
        if (tempVal == 99)
        {
            break;
        }
        _display.setCodeNum(1, ++tempVal);
        break;
    case THIRD_NUM:
        tempVal = _display.getCodeNum(2);
        if (tempVal == 99)
        {
            break;
        }
        _display.setCodeNum(2, ++tempVal);
        break;
    case FOURTH_NUM:
        tempVal = _display.getCodeNum(3);
        if (tempVal == 99)
        {
            break;
        }
        _display.setCodeNum(3, ++tempVal);
        break;
    default:
        break;
    }
}

void Safebox::_encoderEventSub(void)
{
    unsigned int tempVal;

    switch (_actStep)
    {
    case FIRST_NUM:
        tempVal = _display.getCodeNum(0);
        if (tempVal == 0)
        {
            break;
        }
        _display.setCodeNum(0, --tempVal);
        break;
    case SECOND_NUM:
        tempVal = _display.getCodeNum(1);
        if (tempVal == 0)
        {
            break;
        }
        _display.setCodeNum(1, --tempVal);
        break;
    case THIRD_NUM:
        tempVal = _display.getCodeNum(2);
        if (tempVal == 0)
        {
            break;
        }
        _display.setCodeNum(2, --tempVal);
        break;
    case FOURTH_NUM:
        tempVal = _display.getCodeNum(3);
        if (tempVal == 0)
        {
            break;
        }
        _display.setCodeNum(3, --tempVal);
        break;
    default:
        break;
    }
}

void Safebox::_checkCode(void)
{
    if ((_codeActNum[0] == CODE_NUM_1) && (_codeActNum[1] == CODE_NUM_2) &&
        (_codeActNum[2] == CODE_NUM_3) && (_codeActNum[3] == CODE_NUM_4))
    {
        _codeOKProcedure();
        return;
    }

    _wrongCodeProcedure();
}

void Safebox::_checkCodeNum(unsigned int pos)
{
    switch (pos)
    {
    case 1:
        _checkCodeNum1();
        break;
    case 2:
        _checkCodeNum2();
        break;
    case 3:
        _checkCodeNum3();
        break;
    case 4:
        _checkCodeNum4();
        break;
    default:
        break;
    }
}

void Safebox::_checkCodeNum1(void)
{
    if (_codeActNum[0] == CODE_NUM_1)
    {
        _leds.ledON(led_e::led_left_up_gn);
        return;
    }
    _leds.ledOFF(led_e::led_left_up_gn);
}

void Safebox::_checkCodeNum2(void)
{
    if (_codeActNum[1] == CODE_NUM_2)
    {
        _leds.ledON(led_e::led_left_down_gn);
        return;
    }
    _leds.ledOFF(led_e::led_left_down_gn);
}

void Safebox::_checkCodeNum3(void)
{
    if (_codeActNum[2] == CODE_NUM_3)
    {
        _leds.ledON(led_e::led_right_down_gn);
        return;
    }
    _leds.ledOFF(led_e::led_right_down_gn);
}

void Safebox::_checkCodeNum4(void)
{
    if (_codeActNum[3] == CODE_NUM_4)
    {
        _leds.ledON(led_e::led_right_up_gn);
        return;
    }
    _leds.ledOFF(led_e::led_right_up_gn);
}

void Safebox::_wrongCodeProcedure(void)
{
    _setStep(MAIN_PAGE);
    _display.resetCodeGuiNum();
    _display.setPage(MAIN_PAGE);
    _leds.animationON(led_animation_e::error_animation, 2);
    //_display.setPage(UNLOCKED);

    _leds.ledOFF(led_left_up_gn);
    _leds.ledOFF(led_left_down_gn);
    _leds.ledOFF(led_right_up_gn);
    _leds.ledOFF(led_right_down_gn);

    _lockDoor();
}

void Safebox::_codeOKProcedure(void)
{
    _display.setPage(UNLOCKED);
    _unlockDoor();
}

void Safebox::_lockDoor(void)
{
    //_servo.write(8, H_SPEED, true);
    _servo.write(9);
}

void Safebox::_unlockDoor(void)
{
    //_servo.write(90, L_SPEED, false);
    _servo.write(90);
}

void Safebox::_singleClickEvent(void)
{
    _nextStep();
}

void Safebox::_doubleClickEvent(void)
{
    // static unsigned int status = 0;
    // if (status == 0)
    //{
    //     status = 1;
    //     _lockDoor();
    //     return;
    // }
    //_unlockDoor();
    // status = 0;
    _prevStep();
}
