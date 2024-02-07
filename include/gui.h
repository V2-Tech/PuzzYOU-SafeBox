#include <Arduino.h>
#include <U8g2lib.h>
#include <OneButton.h>
#include <Encoder.h>
#include "icons.h"
#include "shared.h"

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels
#define KNOB_PIN 4

class Gui
{
private:
    // Private constructor to prevent instantiation from outside
    Gui() : oled(U8G2_R0, U8X8_PIN_NONE), enc(2, 3), button(KNOB_PIN) {}

    // Private instance of the class
    static Gui *instance;

public:
    // Public method to access the singleton instance
    static Gui *getInstance();

    void begin(void);
    void update(void);

private:
    U8G2_SSD1306_128X64_ALT0_F_HW_I2C oled;
    Encoder enc;
    OneButton button;

    volatile long _oldEncPos = -999;
    volatile long _newEncPos = 0;

    void _checkButton(void);
    void _singleClick(void);
    void _doubleClick(void);
    static void _singleClickEvent(void)
    {
        Gui *gui = Gui::getInstance();
        gui->_singleClick();
    }
    static void _doubleClickEvent(void)
    {
        Gui *gui = Gui::getInstance();
        gui->_doubleClick();
    }
};