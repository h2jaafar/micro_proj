/*
 * @Author: ELEGOO
 * @Date: 2019-10-22 11:59:09
 * @LastEditTime: 2020-06-28 14:55:26
 * @LastEditors: Changhua
 * @Description: SmartRobot robot tank
 * @FilePath: 
 */
#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "ApplicationFunctionSet_xxx0.h"

void setup()
{
  // put your setup code here, to run once:
  Application_FunctionSet.ApplicationFunctionSet_Init();
  float i;
  Serial.begin(9600);
  float left;
  float right;
  float middle;
}
  float left;
  float right;
  float middle;
  bool left_tripped;
  bool right_tripped;
  bool middle_tripped;
void loop()
{
  float i;
  i = 0;
  delay(10);
  i = Application_FunctionSet.ApplicationFunctionSet_Tracking(); 
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate();
  Serial.print("i= ");
  Serial.print(i);
  Serial.print('\t'); 
  left = Application_FunctionSet.Sensor_Left();
  right = Application_FunctionSet.Sensor_Right();
  middle = Application_FunctionSet.Sensor_Mid();

  left_tripped = Application_FunctionSet.Sensor_Left_Tripped();
  right_tripped = Application_FunctionSet.Sensor_Right_Tripped();
  middle_tripped = Application_FunctionSet.Sensor_Mid_Tripped();
  
  Serial.print("Left = ");
  Serial.print(left);
  Serial.print('\t');
  Serial.print("Middle = ");
  Serial.print(middle);
  Serial.print('\t');
  Serial.print("Right = ");
  Serial.print(right);
  Serial.print('\t');
  Serial.print(left_tripped);
  Serial.print('\t');
  Serial.print(middle_tripped);
  Serial.print('\t');
  Serial.print(right_tripped);


  
   
  

    Serial.print('\n');
  
  if (i=12.0)
  {
//    Serial.print("T-ju/nction \n ");//
    void;
  }
  else if (i=1)
  {
    Serial.print("Middle \n");
  }
  else if (i=2)
  {
    Serial.print("Left \n");
  }
  else if (i=3)
  {
    Serial.print("Right \n");
  }
  else if (i=0)
  {
  Serial.print("Other \n");
  }
  
  
}
