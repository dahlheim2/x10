/************************************************************/
/* X10 IR receiver library.                                 */
/* This library is free software; you can redistribute it   */
/* and/or modify it under the terms of the GNU License.     */
/*                                                          */
/* Written by Thomas Mittet thomas@mittet.nu June 2010.     */
/************************************************************/

#ifndef X10ir_h
#define X10ir_h

#include <inttypes.h>

#define X10_IR_SB_MIN            3800
#define X10_IR_SB_MAX            4400
#define X10_IR_EB_MIN           11000
#define X10_IR_EB_MAX           12000
#define X10_IR_BIT0_MIN          1050
#define X10_IR_BIT0_MAX          1300
#define X10_IR_BIT1_MIN          3550
#define X10_IR_BIT1_MAX          4000
#define X10_IR_REPEAT_THRESHOLD   200

#define X10_IR_NIB_HOUSE    B0001
#define X10_IR_NIB_UNIT     B0000
#define X10_IR_NIB_COMMAND  B1000
#define X10_IR_NIB_ERROR    B1111

#define DATA_UNKNOWN        0xF0

#define CMD_ADDRESS         0x10

#define CMD_ALL_UNITS_OFF   B0000
#define CMD_ALL_LIGHTS_ON   B0001
#define CMD_ON              B0010
#define CMD_OFF             B0011
#define CMD_DIM             B0100
#define CMD_BRIGHT          B0101

class X10ir
{

public:
  typedef void (*irReceiveCallback_t)(char, uint8_t, uint8_t, bool);
  X10ir(uint8_t receiveInt, uint8_t receivePin, char defaultHouse, irReceiveCallback_t irReceiveCallback);
  // Public methods
  void begin();
  void receive();
  
private:
  static const uint8_t HOUSE_CODE[16];
  static const uint8_t UNIT_CODE[16];
  // Set in constructor
  uint8_t receiveInt, receivePin, receivePort, receiveBitMask;
  irReceiveCallback_t irReceiveCallback;
  // Used by interrupt triggered methods
  uint32_t lowUs, receiveStarted;
  char house;
  uint8_t unit, command;
  // Private methods
  void triggerCallback(bool isRepeat);
  uint8_t getNibble();
  bool validateNibble(uint16_t data, uint8_t bits);
  int8_t findCodeIndex(const uint8_t codeList[16], uint8_t code);
};

#endif
