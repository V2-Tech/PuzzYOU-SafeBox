#include "gui.h"

void Gui::begin(void)
{
    //----------------------------------------
    //        INIT OLED
    //----------------------------------------
    Serial.println(F("OLED Initialization"));
    _oled.setBusClock(400000);
    if (!_oled.begin())
    {
        Serial.println(F("SSD1306 allocation failed"));
        for (;;)
            ; // Don't proceed, loop forever
    }
    Serial.println(F("OLED Initialization completed"));

    //----------------------------------------
    //        SHOW MAIN PAGE
    //----------------------------------------
    setPage(LOCK);
    redraw();
}

void Gui::update(void)
{
    _draw();
    _timersUpdate();
}

void Gui::setPage(state_e page)
{
    _actPage = page;
}

state_e Gui::getPage(void)
{
    return _actPage;
}

void Gui::setCodeNum(unsigned int position, unsigned int value)
{
    _codeActNum[position] = value;
    redraw();
}

void Gui::redraw(void)
{
    if (_redrawBusy == 0)
    {
        _redraw = 1;
    }
}

void Gui::drawLockPage(void)
{
    _renewCodePage = 1;

    _oled.setFont(u8g2_font_ncenB14_tr);
    _oled.drawXBMP(SCREEN_WIDTH / 2 - LOCK_ICO_WIDTH / 2, SCREEN_HEIGHT / 2 - LOCK_ICO_HEIGHT / 2,
                   LOCK_ICO_WIDTH, LOCK_ICO_HEIGHT, lock_ico);
}

void Gui::drawCodePage(void)
{
    _drawNum(0, _codeActNum[0]);
    _drawNum(1, _codeActNum[0]);
    _drawNum(2, _codeActNum[0]);
}

void Gui::drawFirstNum(void)
{
    if (_blinkStatus == 1)
    {
        _drawNum(0, -1);
        _drawNum(1, _codeActNum[0]);
        _drawNum(2, _codeActNum[0]);
        return;
    }

    _drawNum(0, _codeActNum[0]);
    _drawNum(1, _codeActNum[0]);
    _drawNum(2, _codeActNum[0]);
}

void Gui::drawSecondNum(void)
{
    if (_blinkStatus == 1)
    {
        _drawNum(1, 0);
        return;
    }

    _drawNum(1, _codeActNum[1]);
}

void Gui::drawThirdNum(void)
{
    if (_blinkStatus == 1)
    {
        _drawNum(2, 0);
        return;
    }

    _drawNum(2, _codeActNum[2]);
}

void Gui::_draw(void)
{
    if ((_redraw == 1 && _redrawBusy == 0))
    {
        _redrawBusy = 1;
        _oled.firstPage();
        do
        {
            switch (_actPage)
            {
            case LOCK:
                drawLockPage();
                break;

            case MAIN_PAGE:
                drawCodePage();
                break;

            case FIRST_NUM:
                drawFirstNum();
                break;

            default:
                break;
            }
        } while (_oled.nextPage());

        _redraw = 0;
        _redrawBusy = 0;
    }
}

void Gui::_drawNum(unsigned int pos, int value)
{
    char m_str[3] = {};
    int offsetX = -2;
    unsigned int startY = 20;
    unsigned int buttonW = 28;
    unsigned int buttonSpace = 8;

    _oled.setFont(u8g2_font_helvR10_tr);

    switch (pos)
    {
    case 0:
        // Draw first num
        if (value != -1)
        {
            strcpy(m_str, u8x8_u8toa(value, 2));
        }
        _oled.drawButtonUTF8(buttonW / 2 + buttonSpace + offsetX, startY, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, buttonW, 1, 2, m_str);
        break;
    case 1:
        // Draw second num
        strcpy(m_str, u8x8_u8toa(value, 2));
        _oled.drawButtonUTF8(3 * (buttonW / 2 + buttonSpace) + offsetX, startY, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, buttonW, 1, 2, m_str);

        break;
    case 2:
        // Draw third num
        strcpy(m_str, u8x8_u8toa(value, 2));
        _oled.drawButtonUTF8(5 * (buttonW / 2 + buttonSpace) + offsetX, startY, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, buttonW, 1, 2, m_str);
        break;

    default:
        break;
    }
}

void Gui::_timersUpdate(void)
{
    _timerBlinkUpdate();
}

void Gui::_timerBlinkUpdate(void)
{
    _timeBlinkNow = millis();
    if ((_timeBlinkNow - _timeBlinkOld) > BLINK_RATE_MS)
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
        redraw();
    }
}