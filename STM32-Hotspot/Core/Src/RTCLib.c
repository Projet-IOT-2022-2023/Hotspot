/**************************************************************************/
/*!
  @file     RTClib.cpp

  @mainpage Adafruit RTClib

  @section intro Introduction

  This is a fork of JeeLab's fantastic real time clock library for Arduino.

  For details on using this library with an RTC module like the DS1307, PCF8523,
  or DS3231, see the guide at:
  https://learn.adafruit.com/ds1307-real-time-clock-breakout-board-kit/overview

  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  @section classes Available classes

  This library provides the following classes:

  - Classes for manipulating dates, times and durations:
    - DateTime represents a specific point in time; this is the data
      type used for setting and reading the supported RTCs
    - TimeSpan represents the length of a time interval
  - Interfacing specific RTC chips:
    - RTC_DS1307
    - RTC_DS3231
    - RTC_PCF8523
    - RTC_PCF8563
  - RTC emulated in software; do not expect much accuracy out of these:
    - RTC_Millis is based on `millis()`
    - RTC_Micros is based on `micros()`; its drift rate can be tuned by
      the user

  @section license License

  Original library by JeeLabs https://jeelabs.org/pub/docs/rtclib/, released to
  the public domain.

  This version: MIT (see LICENSE)
*/
/**************************************************************************/

#include "RTCLib.h"

#define PCF8523_pgm_read_byte(addr) (*(const unsigned char *)(addr))

#define PCF8523_ADDRESS 0x68       ///< I2C address for PCF8523
#define PCF8523_CLKOUTCONTROL 0x0F ///< Timer and CLKOUT control register
#define PCF8523_CONTROL_1 0x00     ///< Control and status register 1
#define PCF8523_CONTROL_2 0x01     ///< Control and status register 2
#define PCF8523_CONTROL_3 0x02     ///< Control and status register 3
#define PCF8523_TIMER_B_FRCTL 0x12 ///< Timer B source clock frequency control
#define PCF8523_TIMER_B_VALUE 0x13 ///< Timer B value (number clock periods)
#define PCF8523_OFFSET 0x0E        ///< Offset register
#define PCF8523_STATUSREG 0x03     ///< Status register


I2C_HandleTypeDef *hi2crtc;



/*!
  @brief  Convert a binary coded decimal value to binary. RTC stores
time/date values as BCD.
  @param val BCD value
  @return Binary value
*/
static uint8_t bcd2bin(uint8_t val) { return val - 6 * (val >> 4); }
/*!
  @brief  Convert a binary value to BCD format for the RTC registers
  @param val Binary value
  @return BCD value
*/
static uint8_t bin2bcd(uint8_t val) { return val + 6 * (val / 10); }


/**************************************************************************/
/*!
    @brief Write value to register.
    @param reg register address
    @param val value to write
*/
/**************************************************************************/
void RTC_PCF8523_write_register(uint8_t reg, uint8_t val) {
	uint8_t buffer[2] = {reg, val};

	while(HAL_I2C_GetState(hi2crtc) != HAL_I2C_STATE_READY);
	HAL_I2C_Master_Transmit(hi2crtc,PCF8523_ADDRESS, (uint8_t*) &buffer, 2, HAL_MAX_DELAY);


}

/**************************************************************************/
/*!
    @brief Read value from register.
    @param reg register address
    @return value of register
*/
/**************************************************************************/
uint8_t RTC_PCF8523_read_register(uint8_t reg) {
	uint8_t *buffer = (uint8_t*) malloc(1*sizeof(uint8_t));

	while(HAL_I2C_GetState(hi2crtc) != HAL_I2C_STATE_READY);

	if (HAL_I2C_Master_Transmit(hi2crtc, PCF8523_ADDRESS, &reg, 1, HAL_MAX_DELAY) != HAL_OK) {
	  return 0;
	}

	while(HAL_I2C_GetState(hi2crtc) != HAL_I2C_STATE_READY);

	if (HAL_I2C_Master_Receive (hi2crtc, PCF8523_ADDRESS, buffer, 1, HAL_MAX_DELAY) != HAL_OK) {
	  return 0;
	}

	return buffer[0];

}

/**************************************************************************/
/*!
    @brief Write value.
    @param buffer address of the value
    @param size size in bytes of the value
*/
/**************************************************************************/
void RTC_PCF8523_write(uint8_t* buffer, uint8_t size) {

	while(HAL_I2C_GetState(hi2crtc) != HAL_I2C_STATE_READY);

	HAL_I2C_Master_Transmit(hi2crtc,PCF8523_ADDRESS , buffer, size, HAL_MAX_DELAY);
}

/**************************************************************************/
/*!
    @brief Read value .
    @param size of reading buffer
    @return value
*/
/**************************************************************************/
void RTC_PCF8523_read(uint8_t* buffer, uint8_t size) {

  while(HAL_I2C_GetState(hi2crtc) != HAL_I2C_STATE_READY);

  HAL_I2C_Master_Receive (hi2crtc, PCF8523_ADDRESS, buffer, size, HAL_MAX_DELAY);
}


/**************************************************************************/
/*!
    @brief Write a value then read value through the i2c device.
    @param size of reading buffer
    @return value
*/
/**************************************************************************/
void RTC_PCF8523_write_then_read(uint8_t* bufferWrite, uint8_t sizeWrite, uint8_t* bufferRead, uint8_t sizeRead) {

	while(HAL_I2C_GetState(hi2crtc) != HAL_I2C_STATE_READY);

	HAL_I2C_Master_Transmit(hi2crtc, PCF8523_ADDRESS, bufferWrite, sizeWrite, HAL_MAX_DELAY);

	while(HAL_I2C_GetState(hi2crtc) != HAL_I2C_STATE_READY);

	HAL_I2C_Master_Receive (hi2crtc, PCF8523_ADDRESS, bufferRead, sizeRead, HAL_MAX_DELAY);
}

/**************************************************************************/
// utility code, some of this could be exposed in the DateTime API if needed
/**************************************************************************/

/**
  Number of days in each month, from January to November. December is not
  needed. Omitting it avoids an incompatibility with Paul Stoffregen's Time
  library. C.f. https://github.com/adafruit/RTClib/issues/114
*/
const uint8_t daysInMonth[]= {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30};

/**************************************************************************/
/*!
    @brief  Given a date, return number of days since 2000/01/01,
            valid for 2000--2099
    @param y Year
    @param m Month
    @param d Day
    @return Number of days
*/
/**************************************************************************/
/*static uint16_t date2days(uint16_t y, uint8_t m, uint8_t d) {
  if (y >= 2000U)
    y -= 2000U;
  uint16_t days = d;
  for (uint8_t i = 1; i < m; ++i)
    days += PCF8523_pgm_read_byte(daysInMonth + i - 1);
  if (m > 2 && y % 4 == 0)
    ++days;
  return days + 365 * y + (y + 3) / 4 - 1;
}*/

/**************************************************************************/
/*!
    @brief  Given a number of days, hours, minutes, and seconds, return the
   total seconds
    @param days Days
    @param h Hours
    @param m Minutes
    @param s Seconds
    @return Number of seconds total
*/
/**************************************************************************/
/*static uint32_t time2ulong(uint16_t days, uint8_t h, uint8_t m, uint8_t s) {
  return ((days * 24UL + h) * 60 + m) * 60 + s;
}*/

/**************************************************************************/
/*!
    @brief  Start I2C for the PCF8523 and test succesful connection
    @param  wireInstance pointer to the I2C bus
    @return True if Wire can find PCF8523 or false otherwise.
*/
/**************************************************************************/
uint8_t RTC_PCF8523_begin(I2C_HandleTypeDef *i2c) {
  /*
  if (i2c_dev)
    delete i2c_dev;
  i2c_dev = new Adafruit_I2CDevice(PCF8523_ADDRESS, wireInstance);
  if (!i2c_dev->begin())
    return false;
  return true;
  */

  return 1;
}

/**************************************************************************/
/*!
    @brief  Check the status register Oscillator Stop flag to see if the PCF8523
   stopped due to power loss
    @details When battery or external power is first applied, the PCF8523's
   crystal oscillator takes up to 2s to stabilize. During this time adjust()
   cannot clear the 'OS' flag. See datasheet OS flag section for details.
    @return True if the bit is set (oscillator is or has stopped) and false only
   after the bit is cleared, for instance with adjust()
*/
/**************************************************************************/
uint8_t RTC_PCF8523_lostPower(void) {
  return RTC_PCF8523_read_register(PCF8523_STATUSREG) >> 7;
}

/**************************************************************************/
/*!
    @brief  Check control register 3 to see if we've run adjust() yet (setting
   the date/time and battery switchover mode)
    @return True if the PCF8523 has been set up, false if not
*/
/**************************************************************************/
uint8_t RTC_PCF8523_initialized(void) {
  return (RTC_PCF8523_read_register(PCF8523_CONTROL_3) & 0xE0) != 0xE0;
}

/**************************************************************************/
/*!
    @brief  Set the date and time, set battery switchover mode
    @param dt DateTime to set
*/
/**************************************************************************/
void RTC_PCF8523_adjust(const DateTime *dt) {
  uint8_t buffer[8] = {3, // start at location 3
                       bin2bcd(dt->second),
                       bin2bcd(dt->minute),
                       bin2bcd(dt->hour),
                       bin2bcd(dt->day),
                       bin2bcd(0), // skip weekdays
                       bin2bcd(dt->month),
                       bin2bcd(dt->year - 2000U)};

  RTC_PCF8523_write(buffer, 8);

  // set to battery switchover mode
  RTC_PCF8523_write_register(PCF8523_CONTROL_3, 0x00);
}

/**************************************************************************/
/*!
    @brief  Get the current date/time
    @return DateTime object containing the current date/time
*/
/**************************************************************************/
DateTime RTC_PCF8523_now() {
  uint8_t buffer[7];
  buffer[0] = 3;
  RTC_PCF8523_write_then_read(buffer, 1, buffer, 7);

  DateTime dt;

  dt.year = bcd2bin(buffer[6]) + 2000U;
  dt.month = bcd2bin(buffer[5]);
  dt.day = bcd2bin(buffer[3]);
  dt.hour = bcd2bin(buffer[2]);
  dt.minute = bcd2bin(buffer[1]);
  dt.second = bcd2bin(buffer[0] & 0x7F);

  return dt;
}

/**************************************************************************/
/*!
    @brief  Resets the STOP bit in register Control_1
*/
/**************************************************************************/
void RTC_PCF8523_start(void) {
  uint8_t ctlreg = RTC_PCF8523_read_register(PCF8523_CONTROL_1);
  if (ctlreg & (1 << 5))
    RTC_PCF8523_write_register(PCF8523_CONTROL_1, ctlreg & ~(1 << 5));
}

/**************************************************************************/
/*!
    @brief  Sets the STOP bit in register Control_1
*/
/**************************************************************************/
void RTC_PCF8523_stop(void) {
  RTC_PCF8523_write_register(PCF8523_CONTROL_1,
                 RTC_PCF8523_read_register(PCF8523_CONTROL_1) | (1 << 5));
}

/**************************************************************************/
/*!
    @brief  Is the PCF8523 running? Check the STOP bit in register Control_1
    @return 1 if the RTC is running, 0 if not
*/
/**************************************************************************/
uint8_t RTC_PCF8523_isrunning() {
  return !((RTC_PCF8523_read_register(PCF8523_CONTROL_1) >> 5) & 1);
}

/**************************************************************************/
/*!
    @brief  Read the mode of the INT/SQW pin on the PCF8523
    @return SQW pin mode as a #Pcf8523SqwPinMode enum
*/
/**************************************************************************/
Pcf8523SqwPinMode RTC_PCF8523_readSqwPinMode() {
  int mode = RTC_PCF8523_read_register(PCF8523_CLKOUTCONTROL);
  mode >>= 3;
  mode &= 0x7;
  return (Pcf8523SqwPinMode)(mode);
}

/**************************************************************************/
/*!
    @brief  Set the INT/SQW pin mode on the PCF8523
    @param mode The mode to set, see the #Pcf8523SqwPinMode enum for options
*/
/**************************************************************************/
void RTC_PCF8523_writeSqwPinMode(Pcf8523SqwPinMode mode) {
  RTC_PCF8523_write_register(PCF8523_CLKOUTCONTROL, mode << 3);
}

/**************************************************************************/
/*!
    @brief  Enable the Second Timer (1Hz) Interrupt on the PCF8523.
    @details The INT/SQW pin will pull low for a brief pulse once per second.
*/
/**************************************************************************/
void RTC_PCF8523_enableSecondTimer() {
  uint8_t ctlreg = RTC_PCF8523_read_register(PCF8523_CONTROL_1);
  uint8_t clkreg = RTC_PCF8523_read_register(PCF8523_CLKOUTCONTROL);
  // TAM pulse int. mode (shared with Timer A), CLKOUT (aka SQW) disabled
  RTC_PCF8523_write_register(PCF8523_CLKOUTCONTROL, clkreg | 0xB8);
  // SIE Second timer int. enable
  RTC_PCF8523_write_register(PCF8523_CONTROL_1, ctlreg | (1 << 2));
}

/**************************************************************************/
/*!
    @brief  Disable the Second Timer (1Hz) Interrupt on the PCF8523.
*/
/**************************************************************************/
void RTC_PCF8523_disableSecondTimer() {
  RTC_PCF8523_write_register(PCF8523_CONTROL_1,
                 RTC_PCF8523_read_register(PCF8523_CONTROL_1) & ~(1 << 2));
}

/**************************************************************************/
/*!
    @brief  Enable the Countdown Timer Interrupt on the PCF8523.
    @details The INT/SQW pin will be pulled low at the end of a specified
   countdown period ranging from 244 microseconds to 10.625 days.
    Uses PCF8523 Timer B. Any existing CLKOUT square wave, configured with
   writeSqwPinMode(), will halt. The interrupt low pulse width is adjustable
   from 3/64ths (default) to 14/64ths of a second.
    @param clkFreq One of the PCF8523's Timer Source Clock Frequencies.
   See the #PCF8523TimerClockFreq enum for options and associated time ranges.
    @param numPeriods The number of clkFreq periods (1-255) to count down.
    @param lowPulseWidth Optional: the length of time for the interrupt pin
   low pulse. See the #PCF8523TimerIntPulse enum for options.
*/
/**************************************************************************/
void RTC_PCF8523_enableCountdownTimer(PCF8523TimerClockFreq clkFreq,
                                       uint8_t numPeriods,
                                       uint8_t lowPulseWidth) {
  // Datasheet cautions against updating countdown value while it's running,
  // so disabling allows repeated calls with new values to set new countdowns
  RTC_PCF8523_disableCountdownTimer();

  // Leave compatible settings intact
  uint8_t ctlreg = RTC_PCF8523_read_register(PCF8523_CONTROL_2);
  uint8_t clkreg = RTC_PCF8523_read_register(PCF8523_CLKOUTCONTROL);

  // CTBIE Countdown Timer B Interrupt Enabled
  RTC_PCF8523_write_register(PCF8523_CONTROL_2, ctlreg |= 0x01);

  // Timer B source clock frequency, optionally int. low pulse width
  RTC_PCF8523_write_register(PCF8523_TIMER_B_FRCTL, lowPulseWidth << 4 | clkFreq);

  // Timer B value (number of source clock periods)
  RTC_PCF8523_write_register(PCF8523_TIMER_B_VALUE, numPeriods);

  // TBM Timer B pulse int. mode, CLKOUT (aka SQW) disabled, TBC start Timer B
  RTC_PCF8523_write_register(PCF8523_CLKOUTCONTROL, clkreg | 0x79);
}


/**************************************************************************/
/*!
    @brief  Disable the Countdown Timer Interrupt on the PCF8523.
    @details For simplicity, this function strictly disables Timer B by setting
   TBC to 0. The datasheet describes TBC as the Timer B on/off switch.
   Timer B is the only countdown timer implemented at this time.
   The following flags have no effect while TBC is off, they are *not* cleared:
      - TBM: Timer B will still be set to pulsed mode.
      - CTBIE: Timer B interrupt would be triggered if TBC were on.
      - CTBF: Timer B flag indicates that interrupt was triggered. Though
        typically used for non-pulsed mode, user may wish to query this later.
*/
/**************************************************************************/
void RTC_PCF8523_disableCountdownTimer() {
  // TBC disable to stop Timer B clock
  RTC_PCF8523_write_register(PCF8523_CLKOUTCONTROL,
                 ~1 & RTC_PCF8523_read_register(PCF8523_CLKOUTCONTROL));
}

/**************************************************************************/
/*!
    @brief  Stop all timers, clear their flags and settings on the PCF8523.
    @details This includes the Countdown Timer, Second Timer, and any CLKOUT
   square wave configured with writeSqwPinMode().
*/
/**************************************************************************/
void RTC_PCF8523_deconfigureAllTimers() {
  RTC_PCF8523_disableSecondTimer(); // Surgically clears CONTROL_1
  RTC_PCF8523_write_register(PCF8523_CONTROL_2, 0);
  RTC_PCF8523_write_register(PCF8523_CLKOUTCONTROL, 0);
  RTC_PCF8523_write_register(PCF8523_TIMER_B_FRCTL, 0);
  RTC_PCF8523_write_register(PCF8523_TIMER_B_VALUE, 0);
}

/**************************************************************************/
/*!
    @brief Compensate the drift of the RTC.
    @details This method sets the "offset" register of the PCF8523,
      which can be used to correct a previously measured drift rate.
      Two correction modes are available:

      - **PCF8523\_TwoHours**: Clock adjustments are performed on
        `offset` consecutive minutes every two hours. This is the most
        energy-efficient mode.

      - **PCF8523\_OneMinute**: Clock adjustments are performed on
        `offset` consecutive seconds every minute. Extra adjustments are
        performed on the last second of the minute is `abs(offset)>60`.

      The `offset` parameter sets the correction amount in units of
      roughly 4&nbsp;ppm. The exact unit depends on the selected mode:

      |  mode               | offset unit                            |
      |---------------------|----------------------------------------|
      | `PCF8523_TwoHours`  | 4.340 ppm = 0.375 s/day = 2.625 s/week |
      | `PCF8523_OneMinute` | 4.069 ppm = 0.352 s/day = 2.461 s/week |

      See the accompanying sketch pcf8523.ino for an example on how to
      use this method.

    @param mode Correction mode, either `PCF8523_TwoHours` or
      `PCF8523_OneMinute`.
    @param offset Correction amount, from -64 to +63. A positive offset
      makes the clock slower.
*/
/**************************************************************************/
void RTC_PCF8523_calibrate(Pcf8523OffsetMode mode, int8_t offset) {
  RTC_PCF8523_write_register(PCF8523_OFFSET, ((uint8_t)offset & 0x7F) | mode);
}
