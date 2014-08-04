/* Fishuino A. albifrons to Freq converter
 *
 * FreqMeasure - Example with serial output & display on 4-digit diyplay groove seeed studio
 * http://www.pjrc.com/teensy/td_libs_FreqMeasure.html
 *
 * This example code is in the public domain.
 *
 * modified by dusjagr 4.8.2014
 *
 */
 
#include <FreqMeasure.h>
#include "TM1637.h"
#define CLK 2            //pins definitions for TM1637 and can be changed to other ports       
#define DIO 3
TM1637 tm1637(CLK,DIO);

int8_t digits[4]= {0,0,0,0};
int8_t nulls[4]= {0,0,0,0};
uint8_t digit = 0;

void setup() {
  Serial.begin(57600);
  FreqMeasure.begin();
  tm1637.init();
  tm1637.set(7);         //BRIGHT_TYPICAL = 2,BRIGHT_DARKEST = 0,BRIGHTEST = 7;
}

double sum=0;
int count=0;

void loop() {
  
  if (FreqMeasure.available()) {
    // average several reading together
    sum = sum + FreqMeasure.read();
    count = count + 1;
    
    if (count > 30) {
      unsigned long frequency = FreqMeasure.countToFrequency(sum / count);
      
      //Serial.println(frequency);
      
      int i = 3; 
      tm1637.clearDisplay(); 
      
      while (frequency > 0) {
     
        digit = frequency % 10;
        tm1637.display(i,digit);      
        frequency /= 10;
        i--;
      }
  
      sum = 0;
      count = 0;
    }
  }
}

