/*************************************************
File:             setBrightness.ino
Description:      Control a LED switch of the key module and display it as a breathing lamp
Note:               
**************************************************/
#include <BMK22M131.h>
#include <Wire.h>

BMK22M131 myButton(2,&Wire);

void setup() {
  Serial.begin(9600);   //Serial debug output
  myButton.begin();
  Serial.println("Check whether the module is connected,waiting...");
  if(myButton.isConnected() == true)
  {Serial.println("The module is connecting");} 
}

void loop() {
  uint8_t led_Brightness = 0;
  
  for(int i = 0; i < 3; i++)
  {
    myButton.setBrightness(1,255);
    delay(500);
    myButton.setBrightness(1,0);
    delay(500);
  }

  while(led_Brightness < 255)
  {
    led_Brightness++;
    myButton.setBrightness(1,led_Brightness);
    delay(1);
  }
  
  while(led_Brightness > 0)
  {
    led_Brightness--;
    myButton.setBrightness(1,led_Brightness);
    delay(1);
  }

  delay(500);
}
