/*
 * @Author: ELEGOO
 * @Date: 2019-10-22 11:59:09
 * @LastEditTime: 2020-06-28 14:55:26
 * @LastEditors: Me
 * @Description: SmartRobot robot tank
 * @FilePath: 
 */
#include <avr/wdt.h>
#include "DeviceDriverSet_xxx0.h"
#include "DeviceDriverSet_xxx0_US.h"
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
  Serial.print("\t");
  Serial.print(left_tripped);
  Serial.print('\t');
  Serial.print(middle_tripped);
  Serial.print('\t');
  Serial.print(right_tripped);

  Serial.print("\n");
  delay(1000);
  if (i == 12.0)
  {
    maze();
  }
  
}

bool sensorCheck(float sen)
{

  if (sen<=20){return true;} // check if 20cm close 
  else {return false;}
}

int maze()
{
  /* Left Straight Right Back Algorithm*/
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("-----Beggining Maze Solver-----");
  bool Finished = false;
  float left_sensor_raw, left_sensor, right_sensor_raw, right_sensor, forward_sensor, forward_sensor_raw;

  DeviceDriverSet_ULTRASONIC myUltrasonic;
  myUltrasonic.DeviceDriverSet_ULTRASONIC_Init();
  DeviceDriverSet_Servo myServo;
 

  
  while(!Finished)
  {
    myServo.DeviceDriverSet_Servo_control(180);
    left_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //Function to get sensor data
    left_sensor = sensorCheck(left_sensor_raw); // 
    
    delay(2000);
    myServo.DeviceDriverSet_Servo_control(90);
    forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
    forward_sensor = sensorCheck(forward_sensor_raw);//

    delay(2000);

    myServo.DeviceDriverSet_Servo_control(0);
    right_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
    right_sensor = sensorCheck(right_sensor_raw);//

    // If there is an obstacle, x_sensor = true
    
    if (left_sensor && right_sensor && !forward_sensor)
    {
      //move forward
      Serial.print("Motion Chosen: Forward");
      Application_FunctionSet.LinearControl(0); // 0 is command for forward 
    }

    else if (!left_sensor && right_sensor && forward_sensor)
    {
      // left turn 
      Serial.print("Motion Chosen: Left Turn");
      Application_FunctionSet.LinearControl(2); // 2 is command for left
    }

    
    else if (left_sensor && !right_sensor && forward_sensor)
    {
      // right turn
      Serial.print("Motion Chosen: Right Turn");
      Application_FunctionSet.LinearControl(1); // 1 is command for right
    }

    
    else if (!left_sensor && !right_sensor && forward_sensor)
    {
      // when both left and right are possible, go left
      Serial.print("Motion Chosen: Both options: Left");
      Application_FunctionSet.LinearControl(2); // 2 is command for left
    }

//    else if (!left_sensor && right_sensor && forward_sensor)
//    {
//      // all are possible, go straight
//    }

    
    else if (!left_sensor && !right_sensor && !forward_sensor)
    {
      // U-turn
      Serial.print("Motion Chosen: U-turn");
      Application_FunctionSet.LinearControl(4); // 4 is command for backward 
    }

    
    else if (!left_sensor && !right_sensor && !forward_sensor)
    {
      // completed maze
      Serial.print("Finish");
      Finished = true;
    }

  }
  
}
