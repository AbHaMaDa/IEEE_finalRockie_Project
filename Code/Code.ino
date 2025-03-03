
#define MOTOR_L_IN1       13
#define MOTOR_L_IN2       12
#define MOTOR_R_IN3       11
#define MOTOR_R_IN4       8 
#define speedControlerR   10 
#define speedControlerL   9



// variables that are used in the code
int speedValue ;
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

  speedValue = 200;
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
  }
  order = ' ';
}


void LineFollowing(){ //2nd mode
  // code of line following
  Serial.println(" You Now Are In Line Following Mode");

  
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
  analogWrite(speedControlerL, speedValue-40);
  Serial.println("Moving Forward Left");
}
void movingForwardRight(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue-40);
  analogWrite(speedControlerL, speedValue);
  Serial.println("Moving Forward Right");
}
void movingBackwardLeft(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue-40);
  Serial.println("Moving Backward Left");
}

void movingBackwardRight(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue-40);
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

