/*
   DS1307.h - Arduino library support for the DS1307 I2C Real-Time Clock
   Copyright (C)2010 Henning Karlsen. All right reserved

   You can find the latest version of the library at
   http://www.henningkarlsen.com/electronics

   This library has been made to easily interface and use the DS1307 RTC with
   the Arduino without needing the Wire library.

   If you make any modifications or improvements to the code, I would appreciate
   that you share the code with me so that I might include it in the next release.
   I can be contacted through http://www.henningkarlsen.com/electronics/contact.php

   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA

   Version:   1.0  - Oct   4 2010  - initial release

 */

  // Modified by Fernando Garcia to support Wire library only.

#ifndef DS1307_h
#define DS1307_h

#if ARDUINO >= 100
 #include "Arduino.h"      // for delayMicroseconds, digitalPinToBitMask, etc
#else
 #include "WProgram.h"     // for delayMicroseconds
 #include "pins_arduino.h" // for digitalPinToBitMask, etc
#endif

// Uncomment only the line corresponding to your language.
// #define ENGLISH_L
// #define FRENCH_L
// #define GERMAN_L
// #define ITALIAN_L
#define PORTUGUESE_L
// #define SPANISH_L

#define DS_ADDR_W 0x68

#define FORMAT_SHORT  1
#define FORMAT_LONG   2

#define FORMAT_LITTLEENDIAN 1
#define FORMAT_BIGENDIAN  2
#define FORMAT_MIDDLEENDIAN 3

#define SQW_RATE_1    0
#define SQW_RATE_4K   1
#define SQW_RATE_8K   2
#define SQW_RATE_32K  3

class Time
{
public:
uint8_t hour;
uint8_t min;
uint8_t sec;
uint8_t date;
uint8_t mon;
uint16_t year;
uint8_t dow;

Time();
};

class RTC_DS_RAM
{
public:
byte cell[56];

RTC_DS_RAM();
};

class RTC_DS
{
public:
RTC_DS();
uint8_t isRunning(void);
uint8_t isPresent(void);

Time  getTime();
uint8_t validateDateForMonth(byte d, byte m, word y);
uint8_t validateDate(byte d, byte m, word y);
void  setTime(uint8_t hour, uint8_t min, uint8_t sec);
void  setDate(uint8_t date, uint8_t mon, uint16_t year);
char  *getTimeStr(uint8_t format = FORMAT_LONG);
char  *getDateStr(uint8_t slformat = FORMAT_LONG, uint8_t eformat = FORMAT_LITTLEENDIAN, char divider = '.');
char  *getDOWStr(uint8_t format = FORMAT_LONG);
char  *getMonthStr(uint8_t format = FORMAT_LONG);
void  halt(bool value);
void  setOutput(bool enable);
void  enableSQW(bool enable);
void  setSQWRate(int rate);
void    writeBuffer(RTC_DS_RAM r);
RTC_DS_RAM  readBuffer();
uint8_t    poke(uint8_t addr, uint8_t value);
uint8_t   peek(uint8_t addr);
unsigned long getTimeStamp();

private:
uint8_t _burstArray[8];
uint8_t _decode(uint8_t value);
uint8_t _decodeH(uint8_t value);
uint8_t _decodeY(uint8_t value);
uint8_t _encode(uint8_t vaule);
uint8_t _calcDOW(byte d, byte m, int y);
};
#endif
