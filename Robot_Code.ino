//===================================================================
//===================================================================
//  Masonville Dynamics (Warman) - Snr Design WEC 2021 Source Code
//  Developed by Mason K., Samson H., Adrian K, Owen K.,
//  Jan 30th, 2021
//===================================================================
//===================================================================

//===================================================================
// Pin Declarations
//===================================================================

//Motors
#define leftMotor 11
#define hMotor 12
#define rightMotor 13
#define revolverMotor 6
#define extenderMotor 5

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

//=========================================================
//Object Detection Variables
//=========================================================

#define LT_Sides digitalRead(2) //IR sensor (left and right)
#define LT_M digitalRead(3) //IR Sensor (middle)

//=========================================================
//Finite State Machine
//=========================================================
//Enumeration for States (Stop, Idle, And Run)

enum RobotState {stop, idle, run};
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
pinMode(leftMotor, OUTPUT);
pinMode(hMotor, OUTPUT);
pinMode(rightMotor, OUTPUT);
pinMode(revolverMotor, OUTPUT);
pinMode(extenderMotor, OUTPUT);

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

  //Enums are buggy in arduino so we had to use a boolean lol
  if(safe){
    current_state = idle;
  }else{
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
      break;
    case idle:
      //All the code the robot should run when idle
      Serial.println("Robot await instructions");
      break;
    case run:
      //

      break;

  }

}

