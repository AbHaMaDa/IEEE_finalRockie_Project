#include <PID_v1.h>
#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library

/* Create an instance of the LCD display */
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MOTOR_L_IN1       13
#define MOTOR_L_IN2       12
#define MOTOR_R_IN3       11
#define MOTOR_R_IN4       8 
#define speedControlerR   10 
#define speedControlerL   9

#define sensor_1st A0
#define sensor_2nd A1
#define sensor_3th A2
#define sensor_4th A3
#define sensor_5th A4



// variables that are used in the code
int speedValue = 255 ;
char mode = 'M';   // M || L || F
char order;

// fun for lcd
void lcdSpeed();
void lcdMessage(const char* message);

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
  //sensors pins
  pinMode(sensor_1st,INPUT);
  pinMode(sensor_2nd,INPUT);
  pinMode(sensor_3th,INPUT);
  pinMode(sensor_4th,INPUT);
  pinMode(sensor_5th,INPUT);


  Serial.begin(9600); // Use the default Serial
  Serial.println("Motor Control Program Initialized");
  Serial.println("ROBOT is Ready!");
  Serial.println(" You Now Are In Manual Mode");

    // Initialize LCD
  lcd.init();
  lcd.backlight();   // Turn on the LCD backlight
  lcd.setCursor(0, 0);
  lcd.print("You Now Are In Manual Mode");


}

void loop() {
  // check if the serial port is available
    if (Serial.available()) {
      char input = Serial.read(); // read the incoming byte:
      Serial.print("Received: ");
      Serial.println(input);

      if(input == 'M' || input == 'L' || input == 'F'){ // check if the input is one of the modes
          mode = input;
          lcd.clear();  // Clear the previous message
          switch (mode){
          case 'M':lcd.print("You Now Are In Manual Mode");break;
          case 'L':lcd.print("You Now Are In Line Following Mode");break;
          case 'F':lcd.print("You Now Are In Fire Fighting Mode");break;
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
  }
  order = ' ';
}


void LineFollowing(){ //2nd mode
  speedValue = 180;
  // code of line following
  if((digitalRead(sensor_2nd) == 0)  && (digitalRead(sensor_4th) == 0)){
    movingForward();
  }else if ((digitalRead(sensor_2nd) == 1)  && (digitalRead(sensor_4th) == 0)){
    turningLeft();
  }else if ((digitalRead(sensor_2nd) == 0)  && (digitalRead(sensor_4th) == 1)){
    turningRight();
  }else if ((digitalRead(sensor_2nd) == 1)  && (digitalRead(sensor_4th) == 1)){
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
  lcdMessage("MOVING FORWARD");
}

void movingBackward(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("Moving Backward");

}

void turningRight(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("Turning Right");

  

}

void turningLeft(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("Turning Left");



}
void stopMoving(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, 0);
  analogWrite(speedControlerL, 0);
  lcdMessage("Stop Moving");

}
void movingForwardLeft(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue-40);
  lcdMessage("Moving Forward Left");

}
void movingForwardRight(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue-40);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("Moving Forward Right");

}
void movingBackwardLeft(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue-40);
  lcdMessage("Moving Backward Left");

}

void movingBackwardRight(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue-40);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("Moving Backward Right");

}
void speedUp(){
  speedValue += 20;
  speedValue = constrain(speedValue, 0, 255);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("updated speed: ");
  lcdSpeed();
}

void speedDown(){
  speedValue -= 20;
  speedValue = constrain(speedValue, 0, 255);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("updated speed: ");
  lcdSpeed();

}

void lcdSpeed() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Speed: ");
  lcd.print(speedValue);
}

// Helper function to print messages on LCD
void lcdMessage(const char* message) {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(message);
}

