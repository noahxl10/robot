/**
 * @file LEDControl.h
 * @brief 
 * @version 0.1
 * @date 2021-03-31
 * 
 * @copyright Copyright (c) 2021
 * 
 */

long _blink = 0;
bool _BlinkONS =false;

void LEDControl(int _pin, bool _on, bool _flash, int _frequency)
{
    if (_on && !_flash)
    {
        digitalWrite(_pin,HIGH);
    }
    else if (_on && _flash)
    {
        if ((_blink + _frequency) < millis() && !_BlinkONS){
            digitalWrite(_pin,LOW);
            _BlinkONS =true;
        }
        if ((_blink + _frequency * 2) < millis()){
            digitalWrite(_pin,HIGH);
            _blink = millis();
            _BlinkONS =false;
        }
    }
    else
    {
        digitalWrite(_pin,LOW);
    }
}
