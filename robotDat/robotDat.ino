
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
  maze();
  bool finished = false;
  float i;
  i = 0;
  //delay(10);
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
  //delay(1000);
  if (i == 12.0)
  {
    delay(3000);
    maze();
  }
}

bool sensorCheck(float sen)
{

  if (sen<=15&&sen>0){return true;}
  else {return false;}
}

int forward_with_detection()
{
  int cursed_timer = 0;
  float forward_sensor_raw;
  float middle;
  DeviceDriverSet_ULTRASONIC myUltrasonic;
  myUltrasonic.DeviceDriverSet_ULTRASONIC_Init();
  DeviceDriverSet_Servo myServo;
  int wall_dist = 3;
  myServo.DeviceDriverSet_Servo_control(90);
  //move forward
  Serial.print("Forward\n");
  while(forward_sensor_raw !=wall_dist){  
  forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();
  //Serial.print(forward_sensor_raw);
  //Serial.print("\n");
  Application_FunctionSet.LinearControl(0);// 0 is command for forward
  cursed_timer++;
  if(cursed_timer == 50000){break;}
  middle = Application_FunctionSet.Sensor_Mid();
  //if(middle<1000){break;}
  }
  Application_FunctionSet.LinearControl(3); // 3 is command for stop
}

int maze()
{
  /* Left Straight Right Back Algorithm*/
  Serial.print("\n");
  Serial.print("\n");
  Serial.print("-----Beggining Maze Solver-----\n");
  bool Finished = false;
  float left_sensor_raw, left_sensor, right_sensor_raw, right_sensor, forward_sensor, forward_sensor_raw;
  int turn_time = 1215;
  int u_turn_time = 2450;

  DeviceDriverSet_ULTRASONIC myUltrasonic;
  myUltrasonic.DeviceDriverSet_ULTRASONIC_Init();
  DeviceDriverSet_Servo myServo;

forward_with_detection();
  
  while(!Finished)
  {
    myServo.DeviceDriverSet_Servo_control(180);
    left_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //Function to get sensor data
    left_sensor = sensorCheck(left_sensor_raw); // 
    Serial.print("Left = ");
    Serial.print(left_sensor);
    Serial.print(" ");
    //delay(250);
    
    myServo.DeviceDriverSet_Servo_control(90);
    forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
    forward_sensor = sensorCheck(forward_sensor_raw);//
    Serial.print("Forward = ");
    Serial.print(forward_sensor);
    Serial.print(" ");
    //delay(250);

    myServo.DeviceDriverSet_Servo_control(0);
    right_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
    right_sensor = sensorCheck(right_sensor_raw);//
    Serial.print("Right = ");
    Serial.print(right_sensor);
    Serial.print("\n");

    // If there is an obstacle, x_sensor = true
    
    if (left_sensor && right_sensor && !forward_sensor) // forward open, go forward, 
    {
      forward_with_detection();
    }
    else if (!left_sensor && right_sensor && !forward_sensor) // left and forward open, go forward
    {
      forward_with_detection();
    }
    else if (left_sensor && !right_sensor && !forward_sensor) // right and forward open, go forward
    {
forward_with_detection();
    }

    else if (!left_sensor && right_sensor && forward_sensor) // left open, go left
    {
      // left turn: turn left then go forward until it is within 7cm of the forward wall
      Serial.print("Left Turn\n");
      Application_FunctionSet.LinearControl(2); // 2 is command for left
      delay(turn_time);
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
      delay(100);
forward_with_detection();
    }

    
    else if (left_sensor && !right_sensor && forward_sensor)
    {
      // right turn: turn right then go forward until it is within 7cm of the forward wall
      Serial.print("Right Turn\n");
      Application_FunctionSet.LinearControl(1); // 1 is command for right
      delay(turn_time);
      Application_FunctionSet.LinearControl(3);
      delay(100);
forward_with_detection();
    }

    
    else if (!left_sensor && !right_sensor && forward_sensor) //left and right open, go left
    {
      if(left_sensor_raw>right_sensor_raw){
      // left turn: turn left then go forward until it is within 7cm of the forward wall
      Serial.print("Both open; Left Turn\n");
      Application_FunctionSet.LinearControl(2); // 2 is command for left
      delay(turn_time);
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
      delay(100);
forward_with_detection();
      }
      else if(right_sensor_raw>left_sensor_raw){
      // right turn: turn right then go forward until it is within 7cm of the forward wall
      Serial.print("Both open; Right Turn\n");
      Application_FunctionSet.LinearControl(1); // 1 is command for right
      delay(turn_time);
      Application_FunctionSet.LinearControl(3);
      delay(100);
forward_with_detection();
      }
    }
    /*{
      // when both left and right are possible, go left
      Serial.print("Both options: Left\n");
      Application_FunctionSet.LinearControl(2); // 2 is command for left
      delay(250);
      Application_FunctionSet.LinearControl(3); // 9 is command for stop
          delay(250);
            forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();
      while(forward_sensor_raw !=14){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 9 is command for stop
    }*/

//    else if (!left_sensor && right_sensor && forward_sensor)
//    {
//      // all are possible, go straight
//    }

    
    else if (left_sensor && right_sensor && forward_sensor)
    {
      // U-turn: rotate in place for 180 degrees. 
      Serial.print("U-turn\n");
      Application_FunctionSet.LinearControl(1); 
      delay(u_turn_time);
      Application_FunctionSet.LinearControl(3); // 9 is command for stop
      delay(100);
      
      forward_with_detection();
    }

    
    else if (!left_sensor && !right_sensor && !forward_sensor)
    {
      // completed maze
      Serial.print("Finish\n");
      Finished = true;
      Application_FunctionSet.LinearControl(0); // 0 is command for forward
      delay(1000);
      Application_FunctionSet.LinearControl(3); // 9 is command for stop
      break;
    }

    
  }
}
