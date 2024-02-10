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
    redraw();
}

state_e Gui::getPage(void)
{
    return _actPage;
}

void Gui::setCodeNum(unsigned int position, unsigned int value)
{
    _codeGuiActNum[position] = value;
    redraw();
}

unsigned int Gui::getCodeNum(unsigned int position)
{
    return _codeGuiActNum[position];
}

void Gui::resetCodeGuiNum(void)
{
    for (size_t i = 0; i <= 3; i++)
    {
        _codeGuiActNum[i] = 0;
    }
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
    _drawNum(0, _codeGuiActNum[0]);
    _drawNum(1, _codeGuiActNum[0]);
    _drawNum(2, _codeGuiActNum[0]);
    _drawNum(3, _codeGuiActNum[0]);
}

void Gui::drawFirstNum(void)
{
    if (_blinkStatus == 1)
    {
        _drawNum(0, -1);
        _drawNum(1, _codeGuiActNum[1]);
        _drawNum(2, _codeGuiActNum[2]);
        _drawNum(3, _codeGuiActNum[3]);
        return;
    }

    _drawNum(0, _codeGuiActNum[0]);
    _drawNum(1, _codeGuiActNum[1]);
    _drawNum(2, _codeGuiActNum[2]);
    _drawNum(3, _codeGuiActNum[3]);
}

void Gui::drawSecondNum(void)
{
    if (_blinkStatus == 1)
    {
        _drawNum(0, _codeGuiActNum[0]);
        _drawNum(1, -1);
        _drawNum(2, _codeGuiActNum[2]);
        _drawNum(3, _codeGuiActNum[3]);
        return;
    }

    _drawNum(0, _codeGuiActNum[0]);
    _drawNum(1, _codeGuiActNum[1]);
    _drawNum(2, _codeGuiActNum[2]);
    _drawNum(3, _codeGuiActNum[3]);
}

void Gui::drawThirdNum(void)
{
    if (_blinkStatus == 1)
    {
        _drawNum(0, _codeGuiActNum[0]);
        _drawNum(1, _codeGuiActNum[1]);
        _drawNum(2, -1);
        _drawNum(3, _codeGuiActNum[3]);
        return;
    }

    _drawNum(0, _codeGuiActNum[0]);
    _drawNum(1, _codeGuiActNum[1]);
    _drawNum(2, _codeGuiActNum[2]);
    _drawNum(3, _codeGuiActNum[3]);
}

void Gui::drawFourthNum(void)
{
    if (_blinkStatus == 1)
    {
        _drawNum(0, _codeGuiActNum[0]);
        _drawNum(1, _codeGuiActNum[1]);
        _drawNum(2, _codeGuiActNum[2]);
        _drawNum(3, -1);
        return;
    }

    _drawNum(0, _codeGuiActNum[0]);
    _drawNum(1, _codeGuiActNum[1]);
    _drawNum(2, _codeGuiActNum[2]);
    _drawNum(3, _codeGuiActNum[3]);
}

void Gui::drawUnlocked(void)
{
    _gifAnimationUnlock();
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
            case SECOND_NUM:
                drawSecondNum();
                break;
            case THIRD_NUM:
                drawThirdNum();
                break;
            case FOURTH_NUM:
                drawFourthNum();
                break;
            default:
                break;
            }
        } while (_oled.nextPage());

        _redraw = 0;
        _redrawBusy = 0;
    }
    if ((_drawGIFFrame == 1 && _drawGIFFrameBusy == 0))
    {
        _drawGIFFrameBusy = 1;
        _oled.firstPage();
        do
        {
            switch (_actPage)
            {
            case UNLOCKED:
                drawUnlocked();
                break;
            default:
                break;
            }
        } while (_oled.nextPage());

        _drawGIFFrame = 0;
        _drawGIFFrameBusy = 0;
    }
}

void Gui::_drawNum(unsigned int pos, int value)
{
    char m_str[3] = {};
    int offsetX = 1;
    unsigned int startY = 17;
    unsigned int buttonW = 18;
    unsigned int buttonSpace = 7;

    _oled.setFont(u8g2_font_ncenB08_tn);

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
        if (value != -1)
        {
            strcpy(m_str, u8x8_u8toa(value, 2));
        }
        _oled.drawButtonUTF8(3 * (buttonW / 2 + buttonSpace) + offsetX, startY, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, buttonW, 1, 2, m_str);
        break;
    case 2:
        // Draw third num
        if (value != -1)
        {
            strcpy(m_str, u8x8_u8toa(value, 2));
        }
        _oled.drawButtonUTF8(5 * (buttonW / 2 + buttonSpace) + offsetX, startY, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, buttonW, 1, 2, m_str);
        break;
    case 3:
        // Draw third num
        if (value != -1)
        {
            strcpy(m_str, u8x8_u8toa(value, 2));
        }
        _oled.drawButtonUTF8(7 * (buttonW / 2 + buttonSpace) + offsetX, startY, U8G2_BTN_SHADOW1 | U8G2_BTN_HCENTER | U8G2_BTN_BW2, buttonW, 1, 2, m_str);
        break;
    default:
        break;
    }
}

void Gui::_timersUpdate(void)
{
    _timerBlinkUpdate();
    _timerGIFUpdate();
}

void Gui::_timerBlinkUpdate(void)
{
    _timeBlinkNow = millis();
    if (((_timeBlinkNow - _timeBlinkOld) > BLINK_RATE_MS) &&
        ((_actPage == FIRST_NUM) || (_actPage == SECOND_NUM) || (_actPage == THIRD_NUM) || (_actPage == FOURTH_NUM)))
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

void Gui::_timerGIFUpdate(void)
{
    _timeGIFNow = millis();
    if (((_timeGIFNow - _timeGIFOld) > _gifFrameRate) &&
        ((_actPage == UNLOCKED)))
    {
        _timeGIFOld = _timeGIFNow;
        _gifNextFrame();
    }
}

void Gui::_gifNextFrame(void)
{
    if (_drawGIFFrameBusy == 0)
    {
        if (_actGIFFrame > unlock_gif_frames_LEN)
        {
            _gifAnimationUnlockCompleted();
            return;
        }
        _actGIFFrame++;
        _drawGIFFrame = 1;
    }
}

void Gui::_gifAnimationUnlock(void)
{
    _oled.drawXBMP(SCREEN_WIDTH / 2 - UNLOCK_GIF_WIDTH / 2, SCREEN_HEIGHT / 2 - UNLOCK_GIF_HEIGHT / 2,
                   UNLOCK_GIF_WIDTH, UNLOCK_GIF_HEIGHT, unlock_gif_frames[_actGIFFrame-1]);
}

void Gui::_gifAnimationUnlockCompleted(void)
{
    _oled.drawXBMP(SCREEN_WIDTH / 2 - UNLOCK_GIF_WIDTH / 2, SCREEN_HEIGHT / 2 - UNLOCK_GIF_HEIGHT / 2,
                   UNLOCK_GIF_WIDTH, UNLOCK_GIF_HEIGHT, unlock_gif_frames[unlock_gif_frames_LEN-1]);
}
