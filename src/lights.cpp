#include "lights.h"

void Lights::begin(void)
{
    Serial.println(F("Lights Initialization"));

    pinMode(L1_GN_PIN, OUTPUT);
    pinMode(L1_YL_PIN, OUTPUT);
    pinMode(L2_GN_PIN, OUTPUT);
    pinMode(L2_YL_PIN, OUTPUT);
    pinMode(L3_GN_PIN, OUTPUT);
    pinMode(L3_YL_PIN, OUTPUT);
    pinMode(L4_GN_PIN, OUTPUT);
    pinMode(L4_YL_PIN, OUTPUT);

    Serial.println(F("Lights Initialization completed"));

    renew();
}

void Lights::run(void)
{
    _ledsManager();
    _timersUpdate();
}

void Lights::ledON(led_e led)
{
    if (_actMode == led_mode_e::blinking)
    {
        ledOFF(led_left_up_yl);
        ledOFF(led_left_up_gn);
        ledOFF(led_left_down_yl);
        ledOFF(led_left_down_gn);
        ledOFF(led_right_up_yl);
        ledOFF(led_right_up_gn);
        ledOFF(led_right_down_yl);
        ledOFF(led_right_down_gn);
    }

    switch (led)
    {
    case led_left_up_yl:
        digitalWrite(L1_YL_PIN, HIGH);
        break;
    case led_left_up_gn:
        digitalWrite(L1_GN_PIN, HIGH);
        break;
    case led_left_down_yl:
        digitalWrite(L2_YL_PIN, HIGH);
        break;
    case led_left_down_gn:
        digitalWrite(L2_GN_PIN, HIGH);
        break;
    case led_right_up_yl:
        digitalWrite(L3_YL_PIN, HIGH);
        break;
    case led_right_up_gn:
        digitalWrite(L3_GN_PIN, HIGH);
        break;
    case led_right_down_yl:
        digitalWrite(L4_YL_PIN, HIGH);
        break;
    case led_right_down_gn:
        digitalWrite(L4_GN_PIN, HIGH);
        break;
    default:
        break;
    }
}

void Lights::ledOFF(led_e led)
{
    switch (led)
    {
    case led_left_up_yl:
        digitalWrite(L1_YL_PIN, LOW);
        break;
    case led_left_up_gn:
        digitalWrite(L1_GN_PIN, LOW);
        break;
    case led_left_down_yl:
        digitalWrite(L2_YL_PIN, LOW);
        break;
    case led_left_down_gn:
        digitalWrite(L2_GN_PIN, LOW);
        break;
    case led_right_up_yl:
        digitalWrite(L3_YL_PIN, LOW);
        break;
    case led_right_up_gn:
        digitalWrite(L3_GN_PIN, LOW);
        break;
    case led_right_down_yl:
        digitalWrite(L4_YL_PIN, LOW);
        break;
    case led_right_down_gn:
        digitalWrite(L4_GN_PIN, LOW);
        break;
    default:
        break;
    }
}

void Lights::renew(void)
{
    _renew = 1;
}

void Lights::allLedsBlinkON(unsigned long rate_ms)
{
    if (rate_ms != _rate_ms)
    {
        _setBlinkRate(rate_ms);
    }

    _actLedsActive.leds_array = 0b11111111;

    _setMode(led_mode_e::blinking);
}

void Lights::allLedsBlinkOFF(void)
{
    _actLedsActive.leds_array = 0;

    _setMode(led_mode_e::blinking);
}

void Lights::ledBlinkON(led_e led, unsigned long rate_ms)
{
    if (rate_ms != _rate_ms)
    {
        _setBlinkRate(rate_ms);
    }

    _actLedsActive.leds_array = _actLedsActive.leds_array || (1U << led);

    _setMode(led_mode_e::blinking);
}

void Lights::ledBlinkOFF(led_e led)
{
    switch (led)
    {
    case led_left_up_yl:
        _actLedsActive.leds.led_left_up_yl = 0;
        break;
    case led_left_up_gn:
        _actLedsActive.leds.led_left_up_gn = 0;
        break;
    case led_left_down_yl:
        _actLedsActive.leds.led_left_down_yl = 0;
        break;
    case led_left_down_gn:
        _actLedsActive.leds.led_left_down_gn = 0;
        break;
    case led_right_up_yl:
        _actLedsActive.leds.led_right_up_yl = 0;
        break;
    case led_right_up_gn:
        _actLedsActive.leds.led_right_up_gn = 0;
        break;
    case led_right_down_yl:
        _actLedsActive.leds.led_right_down_yl = 0;
        break;
    case led_right_down_gn:
        _actLedsActive.leds.led_right_down_gn = 0;
        break;
    default:
        break;
    }

    _setMode(led_mode_e::blinking);
}

void Lights::animationON(led_animation_e animation_num, unsigned long duration_s)
{
    _setMode(led_mode_e::animation);

    _actAnimation = animation_num;
    _actAnimationDur_ms = duration_s * 1000;

    _resetAnim();
}

void Lights::_ledsManager(void)
{
    switch (_actMode)
    {
    case led_mode_e::fixed:
        _fixedMode();
        break;
    case led_mode_e::blinking:
        _blinkingMode();
        break;
    case led_mode_e::animation:
        _animationMode();
        break;
    default:
        break;
    }
}

void Lights::_setMode(led_mode_e mode)
{
    _actMode = mode;
}

void Lights::_blinkingMode(void)
{
    if (_renew == 1)
    {
        if (_actLedsActive.leds.led_left_up_yl)
        {
            if (_blinkStatus)
            {
                ledON(led_left_up_yl);
            }
            else
            {
                ledOFF(led_left_up_yl);
            }
        }
        else
        {
            ledOFF(led_left_up_yl);
        }
        if (_actLedsActive.leds.led_left_up_gn)
        {
            if (_blinkStatus)
            {
                ledON(led_left_up_gn);
            }
            else
            {
                ledOFF(led_left_up_gn);
            }
        }
        else
        {
            ledOFF(led_left_up_gn);
        }
        if (_actLedsActive.leds.led_left_down_yl)
        {
            if (_blinkStatus)
            {
                ledON(led_left_down_yl);
            }
            else
            {
                ledOFF(led_left_down_yl);
            }
        }
        else
        {
            ledOFF(led_left_down_yl);
        }
        if (_actLedsActive.leds.led_left_down_gn)
        {
            if (_blinkStatus)
            {
                ledON(led_left_down_gn);
            }
            else
            {
                ledOFF(led_left_down_gn);
            }
        }
        else
        {
            ledOFF(led_left_down_gn);
        }
        if (_actLedsActive.leds.led_right_up_yl)
        {
            if (_blinkStatus)
            {
                ledON(led_right_up_yl);
            }
            else
            {
                ledOFF(led_right_up_yl);
            }
        }
        else
        {
            ledOFF(led_right_up_yl);
        }
        if (_actLedsActive.leds.led_right_up_gn)
        {
            if (_blinkStatus)
            {
                ledON(led_right_up_gn);
            }
            else
            {
                ledOFF(led_right_up_gn);
            }
        }
        else
        {
            ledOFF(led_right_up_gn);
        }
        if (_actLedsActive.leds.led_right_down_yl)
        {
            if (_blinkStatus)
            {
                ledON(led_right_down_yl);
            }
            else
            {
                ledOFF(led_right_down_yl);
            }
        }
        else
        {
            ledOFF(led_right_down_yl);
        }
        if (_actLedsActive.leds.led_right_down_gn)
        {
            if (_blinkStatus)
            {
                ledON(led_right_down_gn);
            }
            else
            {
                ledOFF(led_right_down_gn);
            }
        }
        else
        {
            ledOFF(led_right_down_gn);
        }
        _renew = 0;
    }
}

void Lights::_fixedMode(void)
{
    return;
}

void Lights::_animationMode(void)
{
    switch (_actAnimation)
    {
    case led_animation_e::start_animation:
        _animationStart();
        break;
    case led_animation_e::unlock_animaiton:
        _animationUnlock();
        break;
    case led_animation_e::error_animation:
        _animationError();
        break;
    default:
        break;
    }
}

void Lights::_reset(void)
{
    _actLedsActive.leds_array = 0;
    _newAnim = 1;

    ledOFF(led_left_up_yl);
    ledOFF(led_left_up_gn);
    ledOFF(led_left_down_yl);
    ledOFF(led_left_down_gn);
    ledOFF(led_right_up_yl);
    ledOFF(led_right_up_gn);
    ledOFF(led_right_down_yl);
    ledOFF(led_right_down_gn);

    _setMode(led_mode_e::fixed);
}

void Lights::_resetAnim(void)
{
    _newAnim = 1;
}

void Lights::_timersUpdate(void)
{
    _timerBlinkUpdate(BLINK_RATE_1_MS);
}

void Lights::_setBlinkRate(unsigned long rate_ms)
{
    _rate_ms = rate_ms;
    _blinkStatus = 0;
}

void Lights::_timerBlinkUpdate(unsigned long rate_ms)
{
    _timeBlinkNow = millis();
    if ((_timeBlinkNow - _timeBlinkOld) > rate_ms)
    {
        _timeBlinkOld = _timeBlinkNow;
        switch (_blinkStatus)
        {
        case 0:
            _blinkStatus = 1;
            break;

        case 1:
            _blinkStatus = 0;
            break;

        default:
            _blinkStatus = 1;
            break;
        }

        renew();
    }
}

void Lights::_animationStart(void)
{
    unsigned long _timeAnimNow = millis();
    static unsigned long _timeAnimOld;
    static leds_array_u oldLedArrayStatus;

    if (_newAnim == 1)
    {
        oldLedArrayStatus = _actLedsActive;
        _timeAnimOld = millis();
        _newAnim = 0;
        _setBlinkRate(BLINK_RATE_1_MS);
        _actLedsActive.leds_array = 0b11111111;
    }

    if ((_timeAnimNow - _timeAnimOld) < START_ANIM_DUR_MS)
    {
        _blinkingMode();
        return;
    }

    _actLedsActive = oldLedArrayStatus;
    _animationCompleted();
}

void Lights::_animationUnlock(void)
{
}

void Lights::_animationError(void)
{
    unsigned long _timeAnimNow = millis();
    static unsigned long _timeAnimOld;
    static leds_array_u oldLedArrayStatus;

    if (_newAnim == 1)
    {
        oldLedArrayStatus = _actLedsActive;
        _timeAnimOld = millis();
        _newAnim = 0;
        _setBlinkRate(BLINK_RATE_1_MS / 2);

        _actLedsActive.leds.led_left_down_yl = 1;
        _actLedsActive.leds.led_left_down_gn = 0;
        _actLedsActive.leds.led_left_up_yl = 1;
        _actLedsActive.leds.led_left_up_gn = 0;
        _actLedsActive.leds.led_right_down_yl = 1;
        _actLedsActive.leds.led_right_down_gn = 0;
        _actLedsActive.leds.led_right_up_yl = 1;
        _actLedsActive.leds.led_right_up_gn = 0;
    }

    if ((_timeAnimNow - _timeAnimOld) < _actAnimationDur_ms)
    {
        _blinkingMode();
        return;
    }

    _actLedsActive = oldLedArrayStatus;
    _animationCompleted();
}

void Lights::_animationCompleted(void)
{
    _actAnimationDur_ms = 0;
    
    ledOFF(led_left_up_yl);
    ledOFF(led_left_up_gn);
    ledOFF(led_left_down_yl);
    ledOFF(led_left_down_gn);
    ledOFF(led_right_up_yl);
    ledOFF(led_right_up_gn);
    ledOFF(led_right_down_yl);
    ledOFF(led_right_down_gn);

    _setMode(led_mode_e::fixed);
}