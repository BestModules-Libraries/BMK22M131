/*************************************************
File:             geyCascadeButtonStatus.ino
Description:      The three key modules are cascaded, and then connected with the development board.
                  The development board obtains the key trigger status with I2C when receiving the interrupt signal.
Note:               
**************************************************/
#include <BMK22M131.h>

BMK22M131 myButton(2,&Wire);
uint8_t retVal = 0;
uint8_t moduleNumber = 0;
uint8_t int_flag = 0;
uint8_t buttonStatus[10] = {0};

void setup() {
  Serial.begin(9600);   //Serial debug output
  attachInterrupt(digitalPinToInterrupt(2), ButtonInt, FALLING);
  myButton.begin();
  moduleNumber= myButton.getNumber();
  Serial.print("The modules number is: ");
  Serial.println(moduleNumber);
}

void loop() {
  byte index;
  if(int_flag)
  {
    int_flag = 0;
    retVal = myButton.getButtonStatus(buttonStatus);
    if(retVal == 0)
    {
      Serial.println("The buttons status are:");
      for(index = 1; index <= moduleNumber; index++)
      {
        Serial.print(buttonStatus[index]);
        Serial.print(" ");
      }
      Serial.println(" ");
    }
  }
}

void ButtonInt(){
  int_flag = 1;
}
