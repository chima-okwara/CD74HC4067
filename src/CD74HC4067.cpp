/*
  Multiplexer.cpp - Library for using the CD74HC4067 multiplexer.
  April 18, 2016.
  LGPL 3.0
*/

#include "Arduino.h"
#include "CD74HC4067.h"

uint32_t _g_channel_truth_table[16][4] = {
  // s0, s1, s2, s3     channel
    {0,  0,  0,  0}, // 0
    {1,  0,  0,  0}, // 1
    {0,  1,  0,  0}, // 2
    {1,  1,  0,  0}, // 3
    {0,  0,  1,  0}, // 4
    {1,  0,  1,  0}, // 5
    {0,  1,  1,  0}, // 6
    {1,  1,  1,  0}, // 7
    {0,  0,  0,  1}, // 8
    {1,  0,  0,  1}, // 9
    {0,  1,  0,  1}, // 10
    {1,  1,  0,  1}, // 11
    {0,  0,  1,  1}, // 12
    {1,  0,  1,  1}, // 13
    {0,  1,  1,  1}, // 14
    {1,  1,  1,  1}  // 15
};

CD74HC4067::CD74HC4067(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3, uint32_t en, uint32_t com, ModuleState state):_s0(s0), _s1(s1), _s2(s2), _s3(s3), _en(en), _com(com), _state(state)
{
  bytes = 0;
  _value = 0;
}

bool CD74HC4067::init()
{

    //Set number of channels:
    if(_s0 == -1)
        return false;

    if(_s1 == -1)
    {
        pinMode(_s0, OUTPUT); bytes++;
        return true;
    }

    if(_s2 == -1)
    {
        pinMode(_s0, OUTPUT); bytes++;
        pinMode(_s1, OUTPUT); bytes++;
        return true;
    }

    if(_s3 == -1)
    {
        pinMode(_s0, OUTPUT); bytes++;
        pinMode(_s1, OUTPUT); bytes++;
        pinMode(_s2, OUTPUT); bytes++;
        return true;
    }

    pinMode(_s0, OUTPUT); bytes++;
    pinMode(_s1, OUTPUT); bytes++;
    pinMode(_s2, OUTPUT); bytes++;
    pinMode(_s3, OUTPUT); bytes++;
    return true;


    //Set module operation mode:
    if(_state == MULTIPLEXER)
    {
        analogReadResolution(anRdRes);
        pinMode(_com, INPUT_ANALOG);
    }

    else if(_state == DEMULTIPLEXER)
    {
        analogWriteResolution(anWrRes);
        pinMode(_com, OUTPUT);
    }
}

void CD74HC4067::channel(uint32_t channel)
{
  if(bytes > 0) digitalWrite(_s0, _g_channel_truth_table[channel][0]);
  if(bytes > 1) digitalWrite(_s1, _g_channel_truth_table[channel][1]);
  if(bytes > 2) digitalWrite(_s2, _g_channel_truth_table[channel][2]);
  if(bytes > 3) digitalWrite(_s3, _g_channel_truth_table[channel][3]);
}

void CD74HC4067::enable()
{
    digitalWrite(_en, muxON);
}

void CD74HC4067::disable()
{
    digitalWrite(_en, muxOFF);
}

void CD74HC4067::changeState(ModuleState state)
{
    this->disable();

    if(state == MULTIPLEXER)
    {
        analogReadResolution(anRdRes);
        pinMode(this->_com, INPUT_ANALOG);
        this->_state = MULTIPLEXER;
    }

    if(state == DEMULTIPLEXER)
    {
        analogWriteResolution(anWrRes);
        pinMode(this->_com, OUTPUT);
        this->_state = DEMULTIPLEXER;
    }

    this->enable();
}

uint32_t CD74HC4067::read(uint32_t ch)
{
    if(_state != MULTIPLEXER)
    {
        this->disable();
        this->changeState(MULTIPLEXER);
        this->enable();
    }
    this->channel(ch);
    this->_value = digitalRead(this->_com);
    return (this->_value);
}

void CD74HC4067::write(uint32_t ch, uint32_t val)
{
    if(_state != DEMULTIPLEXER)
    {
        this->disable();
        this->changeState(DEMULTIPLEXER);
        this->enable();
    }
    this->channel(ch);
    this->_value = val;
    analogWrite(this->_com, this->_value);
}
