/**************************************************************************/
/*!
  @file     RTClib.h

  Original library by JeeLabs http://news.jeelabs.org/code/, released to the
  public domain

  License: MIT (see LICENSE)

  This is a fork of JeeLab's fantastic real time clock library for Arduino.

  For details on using this library with an RTC module like the DS1307, PCF8523,
  or DS3231, see the guide at:
  https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/overview

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!
*/
/**************************************************************************/

#ifndef _RTCLIB_H_
#define _RTCLIB_H_

#include "main.h"
#include <stdlib.h>
/** Constants */
#define SECONDS_PER_DAY 86400L ///< 60 * 60 * 24
#define SECONDS_FROM_1970_TO_2000 946684800 ///< Unixtime for 2000-01-01 00:00:00, useful for initialization


/** PCF8523 INT/SQW pin mode settings */
typedef enum {
  PCF8523_OFF = 7,             /**< Off */
  PCF8523_SquareWave1HZ = 6,   /**< 1Hz square wave */
  PCF8523_SquareWave32HZ = 5,  /**< 32Hz square wave */
  PCF8523_SquareWave1kHz = 4,  /**< 1kHz square wave */
  PCF8523_SquareWave4kHz = 3,  /**< 4kHz square wave */
  PCF8523_SquareWave8kHz = 2,  /**< 8kHz square wave */
  PCF8523_SquareWave16kHz = 1, /**< 16kHz square wave */
  PCF8523_SquareWave32kHz = 0  /**< 32kHz square wave */
}Pcf8523SqwPinMode;

/** PCF8523 Timer Source Clock Frequencies for Timers A and B */
typedef enum {
  PCF8523_Frequency4kHz = 0,   /**< 1/4096th second = 244 microseconds,
                                    max 62.256 milliseconds */
  PCF8523_Frequency64Hz = 1,   /**< 1/64th second = 15.625 milliseconds,
                                    max 3.984375 seconds */
  PCF8523_FrequencySecond = 2, /**< 1 second, max 255 seconds = 4.25 minutes */
  PCF8523_FrequencyMinute = 3, /**< 1 minute, max 255 minutes = 4.25 hours */
  PCF8523_FrequencyHour = 4,   /**< 1 hour, max 255 hours = 10.625 days */
}PCF8523TimerClockFreq;

/** PCF8523 Timer Interrupt Low Pulse Width options for Timer B only */
typedef enum  {
  PCF8523_LowPulse3x64Hz = 0,  /**<  46.875 ms   3/64ths second */
  PCF8523_LowPulse4x64Hz = 1,  /**<  62.500 ms   4/64ths second */
  PCF8523_LowPulse5x64Hz = 2,  /**<  78.125 ms   5/64ths second */
  PCF8523_LowPulse6x64Hz = 3,  /**<  93.750 ms   6/64ths second */
  PCF8523_LowPulse8x64Hz = 4,  /**< 125.000 ms   8/64ths second */
  PCF8523_LowPulse10x64Hz = 5, /**< 156.250 ms  10/64ths second */
  PCF8523_LowPulse12x64Hz = 6, /**< 187.500 ms  12/64ths second */
  PCF8523_LowPulse14x64Hz = 7  /**< 218.750 ms  14/64ths second */
} PCF8523TimerIntPulse ;

/** PCF8523 Offset modes for making temperature/aging/accuracy adjustments */
typedef enum  {
  PCF8523_TwoHours = 0x00, /**< Offset made every two hours */
  PCF8523_OneMinute = 0x80 /**< Offset made every minute */
}Pcf8523OffsetMode;



/**************************************************************************/
/*!
    @brief  Simple general-purpose date/time class (no TZ / DST / leap
            seconds).

    This class stores date and time information in a broken-down form, as a
    tuple (year, month, day, hour, minute, second). The day of the week is
    not stored, but computed on request. The class has no notion of time
    zones, daylight saving time, or
    [leap seconds](http://en.wikipedia.org/wiki/Leap_second): time is stored
    in whatever time zone the user chooses to use.

    The class supports dates in the range from 1 Jan 2000 to 31 Dec 2099
    inclusive.
*/
/**************************************************************************/


typedef struct DateTime {
	  uint8_t year; ///< Year offset from 2000
	  uint8_t month;    ///< Month 1-12
	  uint8_t day;    ///< Day 1-31
	  uint8_t hour;   ///< Hours 0-23
	  uint8_t minute;   ///< Minutes 0-59
	  uint8_t second;   ///< Seconds 0-59
} DateTime;


/**************************************************************************/
/*!
    @brief  A generic I2C RTC base class. DO NOT USE DIRECTLY
*/
/**************************************************************************/


/*!
    @brief  Convert a binary coded decimal value to binary. RTC stores
  time/date values as BCD.
    @param val BCD value
    @return Binary value
*/
static uint8_t bcd2bin(uint8_t val);
/*!
    @brief  Convert a binary value to BCD format for the RTC registers
    @param val Binary value
    @return BCD value
*/
static uint8_t bin2bcd(uint8_t val);




uint8_t read_register(uint8_t reg);
void write_register(uint8_t reg, uint8_t val);



/**************************************************************/
/*!
    @brief  RTC based on the PCF8523 chip connected via I2C
*/
/**************************************************************/

uint8_t RTC_PCF8523_begin(I2C_HandleTypeDef *i2c);
void RTC_PCF8523_adjust(const DateTime *dt);
uint8_t RTC_PCF8523_lostPower(void);
uint8_t RTC_PCF8523_initialized(void);
DateTime RTC_PCF8523_now();
void RTC_PCF8523_start(void);
void RTC_PCF8523_stop(void);
uint8_t RTC_PCF8523_isrunning();
Pcf8523SqwPinMode readSqwPinMode();
void RTC_PCF8523_writeSqwPinMode(Pcf8523SqwPinMode mode);
void RTC_PCF8523_enableSecondTimer(void);
void RTC_PCF8523_disableSecondTimer(void);
void RTC_PCF8523_enableCountdownTimer(PCF8523TimerClockFreq clkFreq, uint8_t numPeriods, uint8_t lowPulseWidth);
void RTC_PCF8523_disableCountdownTimer(void);
void RTC_PCF8523_deconfigureAllTimers(void);
void RTC_PCF8523_calibrate(Pcf8523OffsetMode mode, int8_t offset);



#endif // _RTCLIB_H_
