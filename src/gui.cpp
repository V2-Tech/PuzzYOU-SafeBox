#include "gui.h"

void Gui::begin(void)
{
    //----------------------------------------
    //        INIT OLED
    //----------------------------------------
    Serial.println(F("OLED Initialization"));
    oled.setBusClock(400000);
    if (!oled.begin(KNOB_PIN, U8X8_PIN_NONE, U8X8_PIN_NONE))
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    Serial.println(F("OLED Initialization completed"));

    // Draw a single pixel in white
    oled.drawXBMP(SCREEN_WIDTH / 2 - LOCK_ICO_WIDTH / 2, SCREEN_HEIGHT / 2 - LOCK_ICO_HEIGHT / 2,
                  LOCK_ICO_WIDTH, LOCK_ICO_HEIGHT, lock_ico);
    oled.sendBuffer();

    //----------------------------------------
    //        INIT KNOB BUTTON
    //----------------------------------------
    Serial.println(F("Button Initialization"));
    //button.attachClick(_singleClickEvent, this);
    //button.attachDoubleClick(_doubleClickEvent);
    button.attachClick([](void *scope) { _singleClick;}, this);
    Serial.println(F("Button Initialization completed"));
}

void Gui::update(void)
{
    _newEncPos = enc.read();
    button.tick();
}

void Gui::_checkButton(void)
{
    switch (oled.getMenuEvent())
    {
    case U8X8_MSG_GPIO_MENU_SELECT:
        /* code */
        break;
    case U8X8_MSG_GPIO_MENU_NEXT:
    case U8X8_MSG_GPIO_MENU_PREV:
    case U8X8_MSG_GPIO_MENU_HOME:
    case U8X8_MSG_GPIO_MENU_UP:
    case U8X8_MSG_GPIO_MENU_DOWN:
        break;

    default:
        break;
    }
}

void Gui::_singleClick(void)
{
    Serial.println(F("Hello from single click"));
}


void Gui::_doubleClick(void)
{
    Serial.println(F("Hello from double click"));
}
