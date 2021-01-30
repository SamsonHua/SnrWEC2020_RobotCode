//===================================================================
//===================================================================
//  Masonville Dynamics (Warman) - Snr Design WEC 2021 Source Code
//  Developed by Mason K., Samson H., Adrian K, Owen K.,
//  Jan 30th, 2021
//===================================================================
//===================================================================

//===================================================================
// Library
//===================================================================
#include <Servo.h>
//===================================================================
// Pin Declarations
//===================================================================

//Motors
int leftMotor = 11;
int hMotor = 12;
int rightMotor = 10;
int revolverMotor = 6;
int extenderMotor = 5;
Servo servo_5;
Servo servo_6;
Servo servo_10;
Servo servo_11;
Servo servo_12;

//Sensors
#define leftEcho A0
#define leftTrig 4
#define rightEcho A1
#define rightTrig 3
#define forwardEcho A2
#define forwardTrig 2
#define backwardEcho A3
#define backwardTrig 7



//Initialized Values
int Room;
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int safe_distance = 5; // safe distance set to 5 cm
bool safe = true; //Safety declaration
bool lefty = true; //Safety declaration left
bool righty = true; //Safety declaration right
bool delivery = true; //Delivery declaration
int pos = 0;
//=========================================================
//Object Detection Variables
//=========================================================

#define LT_Sides digitalRead(2) //IR sensor (left and right)
#define LT_M digitalRead(3) //IR Sensor (middle)

//=========================================================
//Finite State Machine
//=========================================================
//Enumeration for States (Stop, Idle, And Run)

enum RobotState {stop, idle, left, right, run};
enum RobotState current_state = stop;

//=========================================================
//Functions
//=========================================================

//checkObstacle() - This code determines whether there is any obstacles and returns true or false
bool checkObstacle(){

  //State to detect obstacle interference
  bool rightDetect = false;
  bool leftDetect = false;
  bool forwardDetect = false;
  bool backwardDetect = false;

  //Check each of the four sensors to determine whether there is any obstacle interference
  
  //Uses a helper function to ping
  rightDetect = ping(rightEcho, rightTrig);
  leftDetect = ping(leftEcho, leftTrig);
  forwardDetect = ping(forwardEcho, forwardTrig);
  backwardDetect = ping(backwardEcho, backwardTrig);

  //I am bad at bitshifting, so I will use two nested OR loops
  if((rightDetect||leftDetect)||(forwardDetect || backwardDetect)){
    return false;
  }else{
    return true;
  }
}

//checkObstacleleft() - This code determines whether there is any obstacles right and returns true or false
bool checkObstacleleft(){

  //State to detect obstacle interference
  bool rightDetect = true;
  bool leftDetect = false;
  bool forwardDetect = true;
  bool backwardDetect = false;

  //Check each of the four sensors to determine whether there is any obstacle interference
  
  //Uses a helper function to ping
  rightDetect = ping(rightEcho, rightTrig);
  leftDetect = ping(leftEcho, leftTrig);
  forwardDetect = ping(forwardEcho, forwardTrig);
  backwardDetect = ping(backwardEcho, backwardTrig);

  //I am bad at bitshifting, so I will use two nested OR loops
  if((rightDetect||leftDetect)||(forwardDetect || backwardDetect)){
    return false;
  }else{
    return true;
  }
}

//checkObstacleright() - This code determines whether there is any obstacles left and returns true or false
bool checkObstacleright(){

  //State to detect obstacle interference
  bool rightDetect = false;
  bool leftDetect = true;
  bool forwardDetect = true;
  bool backwardDetect = false;

  //Check each of the four sensors to determine whether there is any obstacle interference
  
  //Uses a helper function to ping
  rightDetect = ping(rightEcho, rightTrig);
  leftDetect = ping(leftEcho, leftTrig);
  forwardDetect = ping(forwardEcho, forwardTrig);
  backwardDetect = ping(backwardEcho, backwardTrig);

  //I am bad at bitshifting, so I will use two nested OR loops
  if((rightDetect||leftDetect)||(forwardDetect || backwardDetect)){
    return false;
  }else{
    return true;
  }
}

//checkObstacleright() - This code determines whether there is any obstacles and returns true or false
bool checkObstacledelivery(){

  //State to detect obstacle interference
  bool rightDetect = false;
  bool leftDetect = false;
  bool forwardDetect = true;
  bool backwardDetect = false;

  //Check each of the four sensors to determine whether there is any obstacle interference
  
  //Uses a helper function to ping
  rightDetect = ping(rightEcho, rightTrig);
  leftDetect = ping(leftEcho, leftTrig);
  forwardDetect = ping(forwardEcho, forwardTrig);
  backwardDetect = ping(backwardEcho, backwardTrig);

  //I am bad at bitshifting, so I will use two nested OR loops
  if((rightDetect||leftDetect)||(forwardDetect || backwardDetect)){
    return false;
  }else{
    return true;
  }
}

//ping() is a helper function for checkObstacle(), it takes in a trigger and echo and returns whether there is an obstacle interference
bool ping(int echo, int trigger){
  int duration = 0;
  
  //Ping ultrasonic signal
  digitalWrite(trigger, LOW);
  delayMicroseconds(5);
  digitalWrite(trigger, HIGH);
  delay(10);
  digitalWrite(trigger, LOW);

  //Determine the time for bounce
  pinMode(echo, INPUT);
  duration = pulseIn(echo, HIGH);

  //Divide by duration by 58 to get cm
  duration = duration/58;

  //If distance is less than 25cm, stop the robot to be safe
  if(duration < 50){
    return true;
  }
  else{
    return false;
  }

}

//forward() is a movement function, it allows the robot to move forward
void Forward(){
  // sweep the servo from 0 to precise forward rotations in steps
  // of 1 degrees
  for (pos = 0; pos <= 720; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_10.write(pos);
    servo_11.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
}

void stopper(){
 servo_10.write(pos);
 servo_11.write(pos);
}

//backward() is a movement function, it allows the robot to move backward
void backward(){
  // sweep the servo from 0 to precise backward rotations degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= -720; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_10.write(pos);
    servo_11.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
}

//left() is a movement function, it allows the robot to move left
void Left(){
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= 720; pos += 1) {
    // tell servo to go to position in variable 'pos'
    servo_11.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
}

//right() is a movement function, it allows the robot to move right
void Right(){
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= -720; pos -= 1) {
    // tell servo to go to position in variable 'pos'
    servo_11.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
}

//revolver() is a movement function, it allows the robot to move revolver
void revolver(){
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= 720; pos += 0.5) {
    // tell servo to go to position in variable 'pos'
    servo_6.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
}

//Extender() is a movement function, it allows the robot to move extender
void ExtenderMotor(){
  // sweep the servo from 0 to 180 degrees in steps
  // of 1 degrees
  for (pos = 0; pos <= 360; pos += 5) {
    // tell servo to go to position in variable 'pos'
    servo_5.write(pos);
    // wait 15 ms for servo to reach the position
    delay(15); // Wait for 15 millisecond(s)
  }
}
//=========================================================
//=========================================================
//                        Setup
//=========================================================
//=========================================================

void setup()
{ 

//Chooses a 9600 baud rate
Serial.begin(9600);

//Motor Pin Declarations
servo_11.attach(leftMotor);
servo_12.attach(hMotor);
servo_10.attach(rightMotor);
servo_6.attach(revolverMotor);
servo_5.attach(extenderMotor);

//Sensor Pin Declarations
pinMode(leftEcho, INPUT);
pinMode(rightEcho, INPUT);
pinMode(forwardEcho, INPUT);
pinMode(backwardEcho, INPUT);
pinMode(leftTrig, OUTPUT);
pinMode(rightTrig, OUTPUT);
pinMode(forwardTrig, OUTPUT);
pinMode(backwardTrig, OUTPUT);

}

//=========================================================
//=========================================================
//                        Loop
//=========================================================
//=========================================================

void loop()
{
  //=========================================================
  //Safety Check - Checks to see if there is any interference
  //=========================================================
  safe = checkObstacle();
  lefty = checkObstacleleft();
  righty = checkObstacleright();
  delivery = checkObstacledelivery();
  
  //Enums are buggy in arduino so we had to use a boolean lol
  if(safe){
    current_state = run;
  }
  else if(lefty){
    current_state = left;
  }
  else if(righty){
    current_state = right;
  }
  else if(delivery){
    current_state = idle;
  }
  else{
    current_state = stop;
  }
  

  //===============================================================================
  //Command Check - Checks to see if there is any instructions from the transmitter
  //===============================================================================
  // TODO: Implement reciever and transmitter code in here

  //Changes state based on the two checks
  switch (current_state){
    case stop:
      //All the code the robot should be running when stopped
      Serial.println("Robot is currently stopped");
      stopper();
      break;
    case idle:
      //All the code the robot should run when idle
      Serial.println("Robot await instructions");
      
      revolver();
      //timed revolve and then initiate extender arm
      delay(300);
      ExtenderMotor();
      
      break;
    case left:
    //All the code the robot should run when left
      Left();
    case right:
    //All the code the robot should run when right
      Right();
    case run:
      //All the code the robot should run forward
      Forward();
      break;

  }

}
