#include <Servo.h>  // Include the Servo library


#define MOTOR_L_IN1       12
#define MOTOR_L_IN2       11
#define MOTOR_R_IN3       8
#define MOTOR_R_IN4       7 
#define speedControlerR   5 
#define speedControlerL   6


#define sensor_1st A0
#define sensor_2nd A1
#define sensor_3th A2
#define sensor_4th A3
#define sensor_5th A4

#define relayPin  13 // Connect relay module to digital pin 13
#define SERVO_PIN 10  // Define the pin for the servo motor

Servo fireServo; // Create a servo object


// variables that are used in the code
int speedValue=255;
char mode = 'M';   // M || L || F
char order;
// function prototypes that are used in the code
void Manual();
void LineFollowing();
void FireFighting();
void movingForward();
void movingBackward();
void turningRight();  
void turningLeft();
void stopMoving();
void movingForwardLeft();
void movingForwardRight();
void movingBackwardLeft();
void movingBackwardRight();
void speedUp();
void speedDown();
// the setup function runs once when you press reset or power the board
void setup() {
  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
  digitalWrite(relayPin, LOW); // Ensure the relay is off at startup

  fireServo.attach(SERVO_PIN); // Attach servo to pin 6
  fireServo.write(90); // Set servo to start position
  // set the pins to be output or input
  pinMode(MOTOR_L_IN1, OUTPUT);
  pinMode(MOTOR_L_IN2, OUTPUT);
  pinMode(MOTOR_R_IN3, OUTPUT);
  pinMode(MOTOR_R_IN4, OUTPUT);
  pinMode(speedControlerR, OUTPUT);
  pinMode(speedControlerL, OUTPUT);




  Serial.begin(9600);
  Serial.println("ROBOT is Ready!");
  Serial.println(" You Now Are In Manual Mode");
}
void loop() {
  // check if the serial port is available
    if (Serial.available()) {
      Serial.println("Motor Control Program Initialized");
      char input = Serial.read(); // read the incoming byte:
      Serial.print("Received: ");
      Serial.println(input);
      if(input == 'M' || input == 'L' || input == 'F'){ // check if the input is one of the modes
          mode = input;
          switch (mode){
          case 'M':Serial.println(" You Now Are In Manual Mode");break;
          case 'L':Serial.println(" You Now Are In Line Following Mode");break;
          case 'F':Serial.println(" You Now Are In Fire Fighting Mode");break;
          }
      }else{
        order = input;
        Serial.print("Received: ");
        Serial.println(order);
      }
  }
  switch (mode){
    case 'M':Manual();break;
    case 'L':LineFollowing();break;
    case 'F':FireFighting();break;
  }
  
}
// function definitions
void Manual(){ //1st mode
  // set the speed value to be between 0 and 255
  speedValue = constrain(speedValue, 0, 255);
  // check the order and execute the corresponding function
  switch (order){
    case 'W':movingForward();break;
    case 'S':movingBackward();break;
    case 'D':turningRight();break;
    case 'A':turningLeft();break;
    case 'K':stopMoving();break;
    case 'Q':movingForwardLeft();break;
    case 'E':movingForwardRight();break;
    case 'Z':movingBackwardLeft();break;
    case 'C':movingBackwardRight();break;
    case 'U':speedUp();break;
    case 'X':speedDown();break;
    case 'R':activateFireExtinguisher();break;
    case 'O':stopFireExtinguisher();break;
  }
  order = ' ';
}
void LineFollowing(){ //2nd mode
  // code of line following
  // code of line following
  if((digitalRead(sensor_2nd) == 1)  && (digitalRead(sensor_4th) == 1)){
    movingForward();
  }else if ((digitalRead(sensor_2nd) == 0)  && (digitalRead(sensor_4th) == 1)){
    turningLeft();
  }else if ((digitalRead(sensor_2nd) == 1)  && (digitalRead(sensor_4th) == 0)){
    turningRight();
  }else if ((digitalRead(sensor_2nd) == 0)  && (digitalRead(sensor_4th) == 0)){
    stopMoving();
  }  
}
void FireFighting(){ //3th
// code of fire fighting
  Serial.println(" You Now Are In Fire Fighting Mode");
}
void movingForward(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  Serial.println("Moving Forward");
}
void movingBackward(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  Serial.println("Moving Backward");
}
void turningRight(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  Serial.println("Turning Right");
}
void turningLeft(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  Serial.println("Turning Left");
}
void stopMoving(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, 0);
  analogWrite(speedControlerL, 0);
  Serial.println("Stop Moving");
}
void movingForwardLeft(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue-80);
  Serial.println("Moving Forward Left");
}
void movingForwardRight(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue-80);
  analogWrite(speedControlerL, speedValue);
  Serial.println("Moving Forward Right");
}
void movingBackwardLeft(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue-80);
  Serial.println("Moving Backward Left");
}
void movingBackwardRight(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue-80);
  analogWrite(speedControlerL, speedValue);
  Serial.println("Moving Backward Right");
}
void speedUp(){
  speedValue += 20;
  speedValue = constrain(speedValue, 0, 255);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
    Serial.print("updated speed: ");
    Serial.println(speedValue);
  
}
void speedDown(){
  speedValue -= 20;
  speedValue = constrain(speedValue, 0, 255);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  Serial.print("updated speed: ");
  Serial.println(speedValue);
}


void activateFireExtinguisher() {
    static bool pumpState = false;
    static int servoAngle = 90;
    static bool movingForward = true;
    static unsigned long lastServoMove = 0;

    if (!pumpState) {
        digitalWrite(relayPin, HIGH);  // Turn pump ON
        Serial.println("Fire Extinguisher ON");
        pumpState = true;
    }

    // Move the servo back and forth
    if (millis() - lastServoMove >= 140) {  // Move every 140ms
        if (movingForward) {
            servoAngle += 10;
            if (servoAngle >= 150) movingForward = false;
        } else {
            servoAngle -= 10;
            if (servoAngle <= 30) movingForward = true;
        }
        fireServo.write(servoAngle);
        lastServoMove = millis();
    }
}

void stopFireExtinguisher() {
    digitalWrite(relayPin, LOW);  // Turn pump OFF
    Serial.println("Fire Extinguisher OFF");
    fireServo.write(90);  // Reset servo position
}