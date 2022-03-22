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
}
  float left;
  float right;
  float middle;
  bool left_tripped;
  bool right_tripped;
  bool middle_tripped;
  float time_at_middle;
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

  delay(1000);
  if (i = 12.0)
  {
    maze();
  }
  
}

int maze()
{
  /* Left Straight Right Back Algorithm*/
  
  Serial.print("-----Beggining Maze Solver-----");
  bool Finished = false;
  while(!Finished)
  {
    left_sensor_raw = //
    left_sensor = // 

    right_sensor_raw = //
    right_sensor = //

    forward_sensor_raw = //
    forward_sensor = //

    // If there is an obstacle, x_sensor = true
    
    if (left_sensor && right_sensor && !forward_sensor)
    {
      //move forward
    }

    else if (!left_sensor && right_sensor && forward_sensor)
    {
      // left turn 
    }

    
    else if (left_sensor && !right_sensor && forward_sensor)
    {
      // right turn
    }

    
    else if (!left_sensor && !right_sensor && forward_sensor)
    {
      // when both left and right are possible, go left
    }

//    else if (!left_sensor && right_sensor && forward_sensor)
//    {
//      // all are possible, go straight
//    }

    
    else if (!left_sensor && !right_sensor && !forward_sensor)
    {
      // U-turn
    }

    
    else if (!left_sensor && !right_sensor && !forward_sensor)
    {
      // completed maze
    }

    
  }
  
}
