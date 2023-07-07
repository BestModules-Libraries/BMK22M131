/*************************************************
File:               BMK22M131.cpp
Author:             BESTMODULES
Description:        I2C communication with the BMK22M131 and obtain the corresponding value
History：            
  V1.00.1   -- initial version；2023-04-04；Arduino IDE :  ≥v1.8.13
**************************************************/
#include "BMK22M131.h"
/*************************************************
Description:        Constructed function
Parameters:              *theWire：Wire Port  
Output:             None
Return:             None
Others:             
*************************************************/
BMK22M131::BMK22M131(uint16_t intPin,TwoWire *theWire)
{
   _intPin=intPin;
   _wire = theWire;
   pinMode(_intPin,INPUT_PULLUP);
}

/*************************************************
Description:        initialize
Parameters:         None  
Return:             None
Others:             
*************************************************/
void BMK22M131::begin()
{
  _wire->begin();
  dataTxBbuf[0] = MODULE_TPYE;  
}

/*************************************************
Description:        Is the modules ready
Parameters:         None  
Return:             Connected - 0x01; Disconnect - 0x00;
Others:             
*************************************************/
uint8_t BMK22M131::isConnected()
{
  uint8_t dataIndex;
  uint8_t retVal;
  dataTxBbuf[1] = 0x00;
  dataTxBbuf[2] = 0x02;
  dataTxBbuf[3] = CMD_IS_MODULE_READY;
  dataTxBbuf[4] = 0;
  for (dataIndex = 0; dataIndex < 4; dataIndex++)
  {
    dataTxBbuf[4] += dataTxBbuf[dataIndex];
  }

  retVal = wireCommunication(dataTxBbuf, 5, dataRxBbuf, 5);
  if (retVal==0)
  {
      return true;
  }
  else
  {      return false;}
}
/*************************************************
Description:        Is the modules ready
Parameters:         None  
Return:             Connected - 0x01; Disconnect - 0x00;
Others:             
*************************************************/
uint8_t BMK22M131::getNumber()
{
  uint8_t dataIndex;
  uint8_t retVal;
  uint8_t moduleNumber;
  dataTxBbuf[1] = 0x00;
  dataTxBbuf[2] = 0x02;
  dataTxBbuf[3] = CMD_GET_MODULE_NUMBER;
  dataTxBbuf[4] = 0;
  for (dataIndex = 0; dataIndex < 4; dataIndex++)
  {
    dataTxBbuf[4] += dataTxBbuf[dataIndex];
  }

  retVal = wireCommunication(dataTxBbuf, 5, dataRxBbuf, 6);
  if (retVal==0)
  {
    moduleNumber = dataRxBbuf[4];
  }
  else
  {moduleNumber=0;}
  return moduleNumber;
}
/*************************************************
Description:        Enable the led follow button
Parameters:         id：button module id; 
Return:             Communication status: COMMUNICATION_OK(0x00) or COMMUNICATION_ERROR(0x01)
Others:             
*************************************************/
uint8_t BMK22M131::ledButtonMode(uint8_t id)
{
  uint8_t dataIndex;
  uint8_t retVal;
  dataTxBbuf[1] = id;
  dataTxBbuf[2] = 0x02;
  dataTxBbuf[3] = CMD_LED_FOLLOW_BUTTON;
  dataTxBbuf[4] = 0;
  for (dataIndex = 0; dataIndex < 4; dataIndex++)
  {
    dataTxBbuf[4] += dataTxBbuf[dataIndex];
  }

  retVal = wireCommunication(dataTxBbuf, 5, dataRxBbuf, 5);

  return retVal;
} 


/*************************************************
Description:        Turn on the LED and adjust the LED brightness
Parameters:         id：button module id; 
                    brightness：LED brightness 0~255
Return:             Communication status: COMMUNICATION_OK(0x00) or COMMUNICATION_ERROR(0x01)
Others:             
*************************************************/
uint8_t BMK22M131::setBrightness(uint8_t id, uint8_t brightness)
{
  uint8_t dataIndex;
  uint8_t retVal;
  dataTxBbuf[1] = id;
  dataTxBbuf[2] = 0x03;
  dataTxBbuf[3] = CMD_LED_CONTROL;
  dataTxBbuf[4] = brightness;
  dataTxBbuf[5] = 0;
  for (dataIndex = 0; dataIndex < 5; dataIndex++)
  {
    dataTxBbuf[5] += dataTxBbuf[dataIndex];
  }

  retVal = wireCommunication(dataTxBbuf, 6, dataRxBbuf, 5);

  return retVal;
}
/*************************************************
Description:        Read a button status
Parameters:         id：button module id; 
                    buttonStatus：Variables for storing the button status 
Return:             Communication status: COMMUNICATION_OK(0x00) or COMMUNICATION_ERROR(0x01)
Others:             
*************************************************/
uint8_t BMK22M131::getButtonStatus(uint8_t id)
{
  uint8_t dataIndex;
  uint8_t retVal;
  uint8_t buttonStatus;
  dataTxBbuf[1] = id;
  dataTxBbuf[2] = 0x02;
  dataTxBbuf[3] = CMD_GET_BUTTON_STATUS;
  dataTxBbuf[4] = 0;
  for (dataIndex = 0; dataIndex < 4; dataIndex++)
  {
    dataTxBbuf[4] += dataTxBbuf[dataIndex];
  }

  retVal = wireCommunication(dataTxBbuf, 5, dataRxBbuf, 6);
  if(retVal == COMMUNICATION_OK)
  {
    buttonStatus = dataRxBbuf[4];
    return buttonStatus;
  }
  else
  {
    return COMMUNICATION_ERROR;
  }
}


/*************************************************
Description:        Get all button status
Parameters:         allButtonStatus：The array that stores all button states  
Return:             Communication status: COMMUNICATION_OK(0x00) or COMMUNICATION_ERROR(0x01) 
Others:             
*************************************************/
uint8_t BMK22M131::getButtonStatus(uint8_t ButtonStatus[])
{
  uint8_t dataIndex;
  uint8_t retVal;
  uint8_t moduleNumber;
  dataTxBbuf[1] = 0x00;
  dataTxBbuf[2] = 0x02;
  dataTxBbuf[3] = CMD_GET_BUTTON_STATUS;
  dataTxBbuf[4] = 0;
  for (dataIndex = 0; dataIndex < 4; dataIndex++)
  {
    dataTxBbuf[4] += dataTxBbuf[dataIndex];
  }
  retVal = wireCommunication(dataTxBbuf, 5, dataRxBbuf,22);

  for (dataIndex = 0; dataIndex <= dataRxBbuf[4]; dataIndex++)
  {
    *ButtonStatus = dataRxBbuf[4 + dataIndex];
    ButtonStatus++;
  }
  return retVal;
}

/*************************************************
Description:        Set the time of button long on 
Parameters:         id：button module id; 
                    timeVal：time of button long on 
Return:             Communication status: COMMUNICATION_OK(0x00) or COMMUNICATION_ERROR(0x01)
Others:             
*************************************************/
uint8_t BMK22M131::setButtonLongOnTime(uint8_t id, uint16_t timeVal)
{
  uint8_t dataIndex;
  uint8_t retVal;
  dataTxBbuf[1] = id;
  dataTxBbuf[2] = 0x04;
  dataTxBbuf[3] = CMD_SET_BUTTON_LONG_ON_TIME;
  dataTxBbuf[4] = timeVal >> 8;
  dataTxBbuf[5] = timeVal & 0xff;
  dataTxBbuf[6] = 0;
  for (dataIndex = 0; dataIndex < 6; dataIndex++)
  {
    dataTxBbuf[6] += dataTxBbuf[dataIndex];
  }

  retVal = wireCommunication(dataTxBbuf, 7, dataRxBbuf, 5);

  return retVal;
}
/*************************************************
Description:        Get a button long on time
Parameters:         id：button module id; 
                    timeVal：Variables for storing the button long on time 
Return:             Communication status: COMMUNICATION_OK(0x00) or COMMUNICATION_ERROR(0x01)
Others:             
*************************************************/
uint16_t BMK22M131::getButtonLongOnTime(uint8_t id)
{
  uint8_t dataIndex;
  uint8_t retVal;
  uint16_t timeVal;
  dataTxBbuf[1] = id;
  dataTxBbuf[2] = 0x02;
  dataTxBbuf[3] = CMD_READ_BUTTON_LONG_ON_TIME;
  dataTxBbuf[4] = 0;
  for (dataIndex = 0; dataIndex < 4; dataIndex++)
  {
    dataTxBbuf[4] += dataTxBbuf[dataIndex];
  }

  retVal = wireCommunication(dataTxBbuf, 5, dataRxBbuf, 7);

  timeVal = dataRxBbuf[4];
  timeVal = (timeVal << 8) + dataRxBbuf[5];

  if(retVal == COMMUNICATION_OK)
  {
    return timeVal;
  }
  else
  {
    return COMMUNICATION_ERROR;
  }
  
}
/*************************************************
Description:        Sending Command frame and receiving response data frame
Parameters:         dataSend：Send data frame
                    sendDataLen：Transmission data frame length
                    dataRec：Array for storing response frame
                    recDataLen：Received data frame length
Return:             0x00: Success
                    0x40: Check code error
                    0x80: Command not supported
                    0x01: CHECK_ERROR
Others:           
*************************************************/
uint8_t BMK22M131::wireCommunication(uint8_t dataSend[], uint8_t sendDataLen, uint8_t dataRec[], uint8_t recDataLen)
{
  writeBytes(dataSend,sendDataLen);//Send data
  delay(7);  //delay 7ms，Receive response
  //Waiting for response
  readBytes(dataRec,recDataLen);  
  if((dataRec[3]==0x00)||(dataRec[3]==0x40)||(dataRec[3]==0x80))
  {return dataRec[3];}
  else
  {return CHECK_ERROR;}
}
/**********************************************************
Description: Write data through IIC
Parameters: wbuf:The array for storing Data to be sent
            wlen:Length of data sent
Return: None
Others: None
**********************************************************/
void BMK22M131::writeBytes(uint8_t wbuf[], uint8_t wlen)
{
  if (_wire != NULL)
  {
    while (_wire->available() > 0)
    {
      _wire->read();
    }
    _wire->beginTransmission(MODULE_ADDR);
    _wire->write(wbuf, wlen);
    _wire->endTransmission();
  }
}
/**********************************************************
Description: Read data through IIC
Parameters: rbuf: Used to store received data
            rlen: Length of data to be read
Return: 0: check ok
        1: check error
Others: None
**********************************************************/
uint8_t BMK22M131::readBytes(uint8_t rbuf[], uint8_t rlen)
{
  uint8_t i = 0, checkSum = 0;
  _wire->requestFrom(MODULE_ADDR,rlen);
  for (i = 0; i < rlen; i++)
  {
    rbuf[i] = _wire->read();
    delay(1);
  }
  /* Check Sum */
  for (i = 0; i < (rlen - 1); i++)
  {
    checkSum += rbuf[i];
  }
  if (checkSum == rbuf[rlen - 1])
  {
    return CHECK_OK; // Check correct
  }
  else
  {
    return CHECK_ERROR; // Check error
  }
}
