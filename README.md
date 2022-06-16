# Arduino Based Line Tracking Car

Follow the line until the sensor detects a "3" wide line, and then stops, initiates maze. 
Maze follows common LSRB algorithm.

## Installation
1. Copy libararies to Arduino src library folder 
2. Open, verify and upload robiotDat to the car (ensure you are in upload mode)

## Common Problems
There are a few unresolved bugs, namely, sometimes the robot detects false walls. Due to time constraints, we were unable to resolve the problem.

## Acknowledgments
This project was written for a microprocessor course at Toronto Metropolitan University. However, much of the code provided here includes snippets and driver files from the manufactuer tutorials (ELEGOO Smart car). 

Also, if you are looking at this repository and are taking the microprocessor course, I would not advise trying to copy this. A better approach would be to build one from scratch, as our method was fairly bulky and not optimized. There are dozens of unused functions that use up a lot of overhead. Communicate directly with the motor shield, instead of using i2c and driver files like we did here.  
