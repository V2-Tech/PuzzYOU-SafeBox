#pragma once

#include <Arduino.h>

#define L1_YL_PIN 10 // led left up yellow
#define L1_GN_PIN 9  // led left up green
#define L2_YL_PIN 14 // led left down yellow
#define L2_GN_PIN 15 // led left down green
#define L3_YL_PIN 16 // led right up yellow
#define L3_GN_PIN 17 // led right up green
#define L4_YL_PIN 12 // led right down yellow
#define L4_GN_PIN 11 // led right down green

#define BLINK_RATE_1_MS 250 // Slow blink
#define BLINK_RATE_2_MS 500 // Fast blink

#define START_ANIM_DUR_MS 2500 // Fast blink

enum led_e
{
    led_left_up_yl = 0,
    led_left_up_gn = 1,
    led_left_down_yl = 2,
    led_left_down_gn = 3,
    led_right_up_yl = 4,
    led_right_up_gn = 5,
    led_right_down_yl = 6,
    led_right_down_gn = 7,
};

enum led_mode_e
{
    fixed = 0,
    blinking = 1,
    animation = 2,
};

enum led_animation_e
{
    start_animation = 0,
    unlock_animaiton = 1,
    error_animation = 2,
};

typedef union
{
    struct
    {
        uint8_t led_left_up_yl : 1;
        uint8_t led_left_up_gn : 1;
        uint8_t led_left_down_yl : 1;
        uint8_t led_left_down_gn : 1;
        uint8_t led_right_up_yl : 1;
        uint8_t led_right_up_gn : 1;
        uint8_t led_right_down_yl : 1;
        uint8_t led_right_down_gn : 1;
    } leds;
    uint8_t leds_array;
} leds_array_u;

class Lights
{
public:
    Lights(){};
    ~Lights(){};

    void begin(void);
    void run(void);

    void allLedsBlinkON(unsigned long rate_ms);
    void allLedsBlinkOFF(void);
    void ledBlinkON(led_e led, unsigned long rate_ms);
    void ledBlinkOFF(led_e led);
    void animationON(led_animation_e animation_num, unsigned long duration_s);

    void ledON(led_e led);
    void ledOFF(led_e led);

    void renew(void);

private:
    led_mode_e _actMode = led_mode_e::fixed;

    leds_array_u _actLedsActive;

    led_animation_e _actAnimation;
    unsigned long _actAnimationDur_ms = 0;

    unsigned long _timeBlinkNow = 0;
    unsigned long _timeBlinkOld = 0;
    int _blinkStatus = 0;

    unsigned long _rate_ms = 0;

    unsigned int _renew = 0;
    unsigned int _newAnim = 0;

    void _ledON(led_e led);
    void _ledOFF(led_e led);

    void _ledsManager(void);
    void _setMode(led_mode_e mode);
    void _blinkingMode(void);
    void _fixedMode(void);
    void _animationMode(void);

    void _reset(void);
    void _resetAnim(void);

    void _timersUpdate(void);
    void _setBlinkRate(unsigned long rate_ms);
    void _timerBlinkUpdate(unsigned long rate_ms);

    void _animationStart(void);
    void _animationUnlock(void);
    void _animationError(void);

    void _animationCompleted(void);
};