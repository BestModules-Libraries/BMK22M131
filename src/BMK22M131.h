/*****************************************************************
File:             BMK22M131.h
Author:           BESTMODULES
Description:      Define classes and required variables
History：         
V1.0.1-- initial version；2023-04-04；Arduino IDE : ≥v1.8.13
******************************************************************/
#ifndef _BMK22M131_
#define _BMK22M131_

#include <Arduino.h>
#include <Wire.h>

#define CHECK_OK        0
#define CHECK_ERROR     1

#define MODULE_TPYE                       (0x77)

#define COMMUNICATION_OK                  (0x00)
#define COMMUNICATION_ERROR               (0x01)

#define BROADCAST_ID                      (0x00)        

#define CMD_LED_CONTROL                   (0x01)
#define CMD_LED_FOLLOW_BUTTON             (0x02)
#define CMD_GET_BUTTON_STATUS             (0x03)        
#define CMD_SET_BUTTON_LONG_ON_TIME       (0x05)               
#define CMD_READ_BUTTON_LONG_ON_TIME      (0x07)        
#define CMD_GET_MODULE_NUMBER             (0x12)
#define CMD_IS_MODULE_READY               (0x13)        
        

#define CONTROL_A_MODULE_TIMEOUT  (2)          //Read the communication timeout of a module（ms）
#define READ_ALL_MODULE_TIMEOUT   (6)          //Read the communication timeout of all modules（ms）

class BMK22M131
{
  public:
    BMK22M131(uint16_t intPin,TwoWire *theWire); 
	  void begin();                                                 //Initialize
    uint8_t isConnected(); 
    uint8_t getNumber();
    uint8_t ledButtonMode(uint8_t id);                  //
    uint8_t setBrightness(uint8_t id, uint8_t brightness);        
    
    uint8_t getButtonStatus(uint8_t id);                         //
    uint8_t getButtonStatus(uint8_t ButtonStatus[]);        //
    
    uint8_t setButtonLongOnTime(uint8_t id, uint16_t timeVal);    //
    uint16_t getButtonLongOnTime(uint8_t id);                     //
    
  private:
	  TwoWire *_wire = NULL;
    uint16_t _intPin;
    const uint8_t MODULE_ADDR =(0x77);
    uint8_t _moduleNumber = 0;
    uint8_t dataTxBbuf[16] = {0};                                 //Array of data frames sent
    uint8_t dataRxBbuf[32] = {0};                                 //Array of data frames receive  
	  void writeBytes(uint8_t wbuf[], uint8_t wlen);
    uint8_t readBytes(uint8_t rbuf[], uint8_t rlen);
	  uint8_t wireCommunication(uint8_t dataSend[], uint8_t sendDataLen, uint8_t dataRec[], uint8_t recDataLen);
};

#endif
