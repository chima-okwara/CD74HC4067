/*
 * Controlling and looping through a CD74HC4067's channel outputs
 *
 *
 * Connect the four control pins to any unused digital or analog pins.
 * This example has been modified to use an STM32 BluePill or Blackpill.
 * It should. however, work for any generic Arduino board.
 * Change the pin definitions below as per your own hardware connections.
 *
 * Connect the common pin to any other available pin. This is the pin that will be
 * shared between the 16 channels of the CD74HC4067. The 16 channels will inherit the
 * capabilities of the common pin. For example, if it's connected to an analog pin,
 * you will be able to use analogRead on each of the 16 channels.
 *
*/

//Multiplexer pins:
#define muxPin PA1
#define muxEn PA2
#define S0  PB9
#define S1  PC14
#define S2  PC15
#define S3  PA0

#include <CD74HC4067.h>

               // s0 s1 s2 s3
CD74HC4067 mux (S0, S1, S2, S3, muxEn, muxPin, CD74HC4067_Module::MULTIPLEXER);
Serial.begin(9600);
uint32_t channel { }, voltage { };
void setup()
{
    if(mux.init())
    {
        Serial.print("Init successful.");
    }

    else
    {
        Serial.print("Init failed.");
    }

    mux.enable();
    channel = 0;

    Serial.println("Start test\n.");
}

void loop()
{
    Serial.print("Channel: ");
    Serial.println(channel);
    Serial.print("Value: ");
    Serial.println(voltage);

    mux.write(channel, voltage);
    delay(2000);
    channel++;
    if(channel > 15)
        channel = 0;
}
