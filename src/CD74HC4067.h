/*
  Multiplexer.h - Library for using the CD74HC4067 multiplexer.
  April 18, 2016.
  LGPL 3.0
*/

#ifndef CD74HC4067_h
#define CD74HC4067_h

#ifndef anRdRes
    #define anRdRes 12
#endif // anRdRes

#ifndef anWrRes
    #define anWrRes 8
#endif // anWrRes


#define muxON LOW
#define muxOFF HIGH

#include "Arduino.h"
#include <inttypes.h>

extern uint32_t _g_channel_truth_table[16][4];

namespace CD74HC4067_Module
{
    enum ModuleState
    {
        MULTIPLEXER = 0,
        DEMULTIPLEXER = 1
    };
}

using namespace CD74HC4067_Module;

class CD74HC4067
{
  public:
    CD74HC4067(uint32_t s0, uint32_t s1, uint32_t s2, uint32_t s3, uint32_t en, uint32_t com, ModuleState state);
    void channel(uint32_t channel);

    bool init();
    void enable();
    void disable();
    void changeState(ModuleState state);
    uint32_t read(uint32_t ch);
    void write(uint32_t ch, uint32_t val);


  private:
  	uint32_t _s0;
  	uint32_t _s1;
  	uint32_t _s2;
  	uint32_t _s3;
  	uint32_t _en;
    uint32_t _com;
    uint32_t _value;
  	uint32_t _channel;
	ModuleState _state;
	uint32_t bytes;
};

#endif
