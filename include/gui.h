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
    unsigned int getCodeNum(unsigned int position);
    void resetCodeGuiNum(void);

    void redraw(void);
    void drawLockPage(void);
    void drawCodePage(void);
    void drawFirstNum(void);
    void drawSecondNum(void);
    void drawThirdNum(void);
    void drawFourthNum(void);
    void drawUnlocked(void);

private:
    U8G2_SSD1306_128X64_ALT0_1_HW_I2C _oled;

    state_e _actPage = state_e::LOCK;
    unsigned int _codeGuiActNum[4] = {0, 0, 0, 0};

    unsigned int _redraw = 0;
    unsigned int _redrawBusy = 0;
    unsigned int _drawGIFFrame = 0;
    unsigned int _drawGIFFrameBusy = 0;
    unsigned int _renewCodePage = 0;

    unsigned long _timeBlinkNow = 0;
    unsigned long _timeBlinkOld = 0;
    unsigned int _blinkStatus = 0;

    unsigned long _timeGIFNow = 0;
    unsigned long _timeGIFOld = 0;
    unsigned long _gifFrameRate = 200; // 40ms = 25fps
    unsigned int _actGIFFrame = 0;

    void _draw(void);
    void _drawNum(unsigned int pos, int value);

    void _timersUpdate(void);
    void _timerBlinkUpdate(void);
    void _timerGIFUpdate(void);

    void _gifNextFrame(void);
    void _gifAnimationUnlock(void);
    void _gifAnimationUnlockCompleted(void);
};