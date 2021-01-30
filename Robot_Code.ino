#define LT_Sides digitalRead(2) //IR sensor (left and right)
#define LT_M digitalRead(3) //IR Sensor (middle)

// lineStandard is the level to detect 
// if the sensor is on the line or not. If the sensor value is less than this
// the sensor it is above a white line.
//
//motor A
#define right_motor_1 4
#define right_motor_2 5
//motor b
#define left_motor_1 6
#define left_motor_2 5 // same pin, shared motor
//Belt motor
#define belt_motor_1 7
#define belt_motor_2 7
#define belt_motor_3 8
int Room;


//Ultrasonic sensor
#define echoPin 9 // attach pin D2 Arduino to pin Echo
#define trigPin 10 //attach pin D3 Arduino to pin Trig

// defines variables
long duration; // variable for the duration of sound wave travel
int distance; // variable for the distance measurement
int safe_distance = 5; // safe distance set to 5 cm

//======================
//Finite State Machine 
//======================
//Enumeration for States (Stop, Idle, And Run)
enum RobotState {stop, idle, run};
static RobotState current_state = stop;

void setup()
{ 
  pinMode(right_motor_1, OUTPUT);
  pinMode(right_motor_2, OUTPUT);
  pinMode(left_motor_1, OUTPUT);
  pinMode(left_motor_2, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

  // IR sensor readings for diagnostics
  Serial.begin(9600);
  Serial.println("IR Sensor Readings:: ");
  delay(1000);
  
}

void loop()
{

  
  //Creates State Object
  switch (current_state){
    case stop:
      //All the code the robot should be running when stopped

      break;
    case idle:
      //All the code the robot should run when idle

      break;
    case run:


      break;

  }

   // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  // Sets the trigPin HIGH (ACTIVE) for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculating the distance
  distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
  
Serial.println("Which room do you want it to be delivered to?"); //Prompt User for Input value for the room number
  while (Serial.available() == 0) {
    // Wait for User to Input Data
  }
  Room = Serial.parseInt(); //Read the data the user has inputted
  if (safe_distance < 5)
  {
    back(distance, safe_distance);
  }
  else
  {
    forward(Room);
  }
  Serial.print("The user has choosen the room number:");
  delay(0);  // add a delay to decrease sensitivity.
}

void delivery(int Room) {
  int counter = 0;
  counter = counter + 1;
  if (counter <= round(Room/2 + 0.1))
    forward(Room);
  else
  {
  digitalWrite(right_motor_1, LOW);
  digitalWrite(right_motor_2, LOW);
  digitalWrite(left_motor_1, LOW);
  digitalWrite(left_motor_2, LOW);
  digitalWrite(belt_motor_1, HIGH);
  digitalWrite(belt_motor_2, HIGH);
  analogWrite(10, 255);
  if ( (Room % 2) == 0) // Front horizontal conveyor engages to move right
  {
  digitalWrite(belt_motor_3, HIGH);
  analogWrite(11, 255); // PWM analog reading to have it run at max speed of 255
  }
  else // Front horizontal conveyor engages to move left
  {
  digitalWrite(belt_motor_3, LOW);
  analogWrite(11, 255); // PWM analog reading to have it run at max speed of 255
  }
  }
  }
  

void forward(int Room) { // Both Motor engages to move forward
  while ((LT_M))
  {
  digitalWrite(right_motor_1, HIGH);
  digitalWrite(right_motor_2, LOW);
  digitalWrite(left_motor_1, HIGH);
  digitalWrite(left_motor_2, LOW);
  analogWrite(11, 255); // PWM analog reading to have it run at max speed of 255
  if(LT_Sides)
  {
  delivery(Room);
  }
  }
}

void back(float distance, int safe_distance){
  while (distance < safe_distance)
  {
  digitalWrite(right_motor_1, LOW);
  digitalWrite(right_motor_2,HIGH); // Reversed Motor
  digitalWrite(left_motor_1, LOW);
  digitalWrite(left_motor_2, HIGH); // Reversed motor
    digitalWrite(belt_motor_1, HIGH); // Intake motor to collect items
  digitalWrite(belt_motor_2, HIGH); // Intake motor to collect items
  analogWrite(11, 255); // PWM analog reading to have it run at max speed of 255
  }
}

void moving_back(){
  if (distance > safe_distance)
  {
  digitalWrite(right_motor_1, LOW);
  digitalWrite(right_motor_2,HIGH);
  digitalWrite(left_motor_1, LOW);
  digitalWrite(left_motor_2, HIGH);
  analogWrite(11, 255); // PWM analog reading to have it run at max speed of 255
  }
  else if (distance < safe_distance)
  {
  digitalWrite(right_motor_1, LOW);
  digitalWrite(right_motor_2, LOW);
  digitalWrite(left_motor_1, LOW);
  digitalWrite(left_motor_2, LOW);  
  }
}
