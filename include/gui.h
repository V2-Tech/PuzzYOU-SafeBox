#include <Arduino.h>
#include <U8g2lib.h>
#include "common_def.h"
#include "icons.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

#define BLINK_RATE_MS 250

class Gui
{
public:
    Gui() : _oled(U8G2_R0, U8X8_PIN_NONE) {}

    void begin(void);
    void update(void);

    void setPage(state_e page);
    state_e getPage(void);

    void setCodeNum(unsigned int position, unsigned int value);

    void redraw(void);
    void drawLockPage(void);
    void drawCodePage(void);
    void drawFirstNum(void);
    void drawSecondNum(void);
    void drawThirdNum(void);
    void drawSelection1(void);
    void drawUnlocked(void);

private:
    U8G2_SSD1306_128X64_ALT0_1_HW_I2C _oled;

    state_e _actPage = state_e::LOCK;
    unsigned int _codeActNum[3] = {0 ,0 ,0};

    unsigned int _redraw;
    unsigned int _redrawBusy = 0;
    unsigned int _renewCodePage = 0;

    unsigned long _timeBlinkNow = 0;
    unsigned long _timeBlinkOld = 0;
    unsigned int _blinkStatus = 0;

    
    void _draw(void);
    void _drawNum(unsigned int pos, int value);

    void _timersUpdate(void);
    void _timerBlinkUpdate(void);
};