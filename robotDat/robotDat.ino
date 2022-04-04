
/* DAT VERSION
 * @Author: ELEGOO
 * @Date: 2019-10-22 11:59:09
 * @LastEditTime: 2020-06-28 :55:26
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
  /*Initial Line Tracking Setup */

  Application_FunctionSet.ApplicationFunctionSet_Init(); // Init cpp application 
  float i;                                               // Declare i variable 
  Serial.begin(9600);                                    // Init serial baud rate
}

  /* Init variables for sensors */
  
  float left;
  float right;
  float middle;
  bool left_tripped;
  bool right_tripped;
  bool middle_tripped;
  float time_at_middle;
  
void loop() 
{
  /* This is the loop that initially spins to run linetracking */
  
  bool finished = false; //Define the finish flag as false
  float i;
  i = 0; 
  //delay(10);
  i = Application_FunctionSet.ApplicationFunctionSet_Tracking();
  // Pulls from ApplicationFunctionSet_xxx0.cpp, function ApplicationFunctionSet_Tracking () 
  // See comments  in ApplicationFunctionSet_xxx0.cpp... for more details 
  
  Application_FunctionSet.ApplicationFunctionSet_SensorDataUpdate(); // Update sensor values
  Serial.print("i= ");
  Serial.print(i);
  Serial.print('\t'); 

  // Raw sensor values
  left = Application_FunctionSet.Sensor_Left(); 
  right = Application_FunctionSet.Sensor_Right();
  middle = Application_FunctionSet.Sensor_Mid();

  // Sensor status (i.e if there is a line)
  left_tripped = Application_FunctionSet.Sensor_Left_Tripped();
  right_tripped = Application_FunctionSet.Sensor_Right_Tripped();
  middle_tripped = Application_FunctionSet.Sensor_Mid_Tripped();

  // Serial stuff for debugging 
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

  /* if i = 12 (i.e if it detects horizonital line) */ 
  if (i == 12.0) 
  {
    delay(2500); 
    maze(); // Run the maze function (seen below)
  }
}

bool sensorCheck(float sen)
{
  /* Simple function to return true if object is closer than 30cm
   */
  if (sen<=30&&sen>0){return true;}
  else {return false;}
}

int maze()
{

  /* Maze solving function
   *  Uses a Left Straight Right Back algorithm implementation
   *  (i.e hugs the left wall)
   */

  Serial.print("\n");
  Serial.print("\n");
  Serial.print("-----Beggining Maze Solver-----\n");
  
  bool Finished = false; // Finished flag false
  // define variables
  
  float left_sensor_raw, left_sensor, right_sensor_raw, right_sensor, forward_sensor, forward_sensor_raw;
  int wall_dist;
  unsigned long refreshInterval;
  unsigned long startMillis;

  wall_dist = 14; // This variable is used to determine how far away from a wall the robot should stop
                  // see below

  refreshInterval = 3.0;

  DeviceDriverSet_ULTRASONIC myUltrasonic; // Initilize ultarsonic object called myUltrasonic
                                           // This allows us to interact with it from robotDat
                                           
  myUltrasonic.DeviceDriverSet_ULTRASONIC_Init(); // init ultrasonic driver
  DeviceDriverSet_Servo myServo;           // Init servo objectr called myServo


 
  
  
  while(!Finished) // while finish flag is not tripped 
  {


   /* Timer to realize when end */

    
    // Turn left and get sensor data 
    myServo.DeviceDriverSet_Servo_control(180);  // rotate servo 180deg
    left_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //Function to get sensor data
    left_sensor = sensorCheck(left_sensor_raw); // Run sensorCheck function to see if object is there or not (closer than 30cm)
    Serial.print("Left = ");
    Serial.print(left_sensor);
    Serial.print(" ");
    //delay(250);

    // Turn straight (forward) and get sensor data
    myServo.DeviceDriverSet_Servo_control(90);
    forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
    forward_sensor = sensorCheck(forward_sensor_raw);//
    Serial.print("Forward = ");
    Serial.print(forward_sensor);
    Serial.print(" ");
    //delay(250);

    // Turn right and get sensor data
    myServo.DeviceDriverSet_Servo_control(0);
    right_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
    right_sensor = sensorCheck(right_sensor_raw);//
    Serial.print("Right = ");
    Serial.print(right_sensor);
    Serial.print("\n");
    myServo.DeviceDriverSet_Servo_control(90);

    // If there is an obstacle, x_sensor = true


    /* LSRB algorithm */ 

    startMillis = millis();

    
    if (left_sensor && right_sensor && !forward_sensor) // forward open, go forward, 
    {
      //move forward
      Serial.print("Forward\n");
      while(forward_sensor_raw !=wall_dist){ // keep moving forward until you are wall_distcm away from wall
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();
      Serial.print(forward_sensor_raw);
      Serial.print("\n");
      Application_FunctionSet.LinearControl(0);// 0 is command for forward

      if ((millis() - startMillis) > refreshInterval)
        {
          break; // this checks if it has been going for too long
        }
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
    }
    else if (!left_sensor && right_sensor && !forward_sensor) // left and forward open, go forward
    {
      //move forward
      Serial.print("Forward\n");
      while(forward_sensor_raw !=wall_dist){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();
      Serial.print(forward_sensor_raw);
      Serial.print("\n");
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
    }
    else if (left_sensor && !right_sensor && !forward_sensor) // right and forward open, go forward
    {
      //move forward
      Serial.print("Forward\n");
      while(forward_sensor_raw !=wall_dist){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();//
      Serial.print(forward_sensor_raw);
      Serial.print("\n");
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
    }


    else if (!left_sensor && right_sensor && forward_sensor) // left open, go left
    {
      // left turn: turn left then go forward until it is within 7cm of the forward wall
      Serial.print("Left Turn\n");
      Application_FunctionSet.LinearControl(2); // 2 is command for left
      delay(250);
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
      delay(250);
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();
      while(forward_sensor_raw !=wall_dist){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
    }

    
    else if (left_sensor && !right_sensor && forward_sensor)
    {
      // right turn: turn right then go forward until it is within 7cm of the forward wall
      Serial.print("Right Turn\n");
      Application_FunctionSet.LinearControl(1); // 1 is command for right
      delay(250);
      Application_FunctionSet.LinearControl(3);
      delay(250);
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();// 9 is command for stop
      while(forward_sensor_raw !=wall_dist){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
    }

    
    else if (!left_sensor && !right_sensor && forward_sensor) //left and right open, go left
    {
      if(left_sensor_raw>right_sensor_raw){
      // left turn: turn left then go forward until it is within 7cm of the forward wall
      Serial.print("Both open; Left Turn\n");
      Application_FunctionSet.LinearControl(2); // 2 is command for left
      delay(250);
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
      delay(250);
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();
      while(forward_sensor_raw !=wall_dist){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
      }
      
      else if(right_sensor_raw>left_sensor_raw){
      // right turn: turn right then go forward until it is within 7cm of the forward wall
      Serial.print("Both open; Right Turn\n");
      Application_FunctionSet.LinearControl(1); // 1 is command for right
      delay(250);
      Application_FunctionSet.LinearControl(3);
      delay(250);
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();// 9 is command for stop
      while(forward_sensor_raw !=wall_dist){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop 
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
      while(forward_sensor_raw !=wall_dist){
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
      delay(425);
      Application_FunctionSet.LinearControl(3); // 9 is command for stop
      delay(250);
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data();// 9 is command for stop
      while(forward_sensor_raw !=wall_dist){
      forward_sensor_raw = myUltrasonic.DeviceDriverSet_ULTRASONIC_Return_Sensor_Data(); //
      Application_FunctionSet.LinearControl(0);// 0 is command for forward
      }
      Application_FunctionSet.LinearControl(3); // 3 is command for stop
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
