#include <LiquidCrystal_I2C.h>  // Include the LiquidCrystal_I2C library
#include <Servo.h>  // Include the Servo library

/* Create an instance of the LCD display */
LiquidCrystal_I2C lcd(0x27, 16, 2);

#define MOTOR_L_IN1       12
#define MOTOR_L_IN2       11
#define MOTOR_R_IN3       8
#define MOTOR_R_IN4       7 
#define speedControlerR   10 
#define speedControlerL   9

#define relayPin  13 // Connect relay module to digital pin 13
#define SERVO_PIN 6  // Define the pin for the servo motor


#define sensor_1st A0
#define sensor_2nd A1
#define sensor_3th A2
#define sensor_4th A3
#define sensor_5th A4


Servo fireServo; // Create a servo object



// variables that are used in the code
int speedValue = 255 ;
char mode = 'M';   // M || L || F
char order ='k';

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
void activateFireExtinguisher();
void stopFireExtinguisher();



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

  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
  digitalWrite(relayPin, LOW); // Ensure the relay is off at startup

  fireServo.attach(SERVO_PIN); // Attach servo to pin 6
  fireServo.write(90); // Set servo to start position


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
 // Step 1: Check if a new command is available
  if (Serial.available()) {
    char input = Serial.read();
    Serial.print("Received: ");
    Serial.println(input);

    if (input == 'M' || input == 'L' || input == 'F') {
      mode = input;  // Update the mode immediately
      lcd.clear();
      switch (mode) {
        case 'M': lcd.print("Manual Mode"); Serial.println("Mode: Manual"); break;
        case 'L': lcd.print("Line Following Mode"); Serial.println("Mode: Line Following"); break;
        case 'F': lcd.print("Fire Fighting Mode"); Serial.println("Mode: Fire Fighting"); break;
      }
    } else {
      order = input;  // Store order if it's not a mode change
    }
  }

  // Step 2: Run the correct mode function (Each function runs only once per cycle)
  if (mode == 'M') {
    Manual();
  } else if (mode == 'L') {
    LineFollowing();
  } else if (mode == 'F') {
    FireFighting();
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
    default: stopMoving(); break;  // <-- ADD THIS TO STOP WHEN NO VALID COMMAND

  }
  order = ' ';
}


void LineFollowing(){ //2nd mode
  if (mode != 'L') return;  // Stop immediately if mode has changed

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
  if (mode != 'L') return;  // Check again before taking action

  
}

void FireFighting() { 

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
  analogWrite(speedControlerL, speedValue-120);
  lcdMessage("Moving Forward Left");

}
void movingForwardRight(){
  digitalWrite(MOTOR_L_IN1, HIGH);
  digitalWrite(MOTOR_L_IN2, LOW);
  digitalWrite(MOTOR_R_IN3, HIGH);
  digitalWrite(MOTOR_R_IN4, LOW);
  analogWrite(speedControlerR, speedValue-120);
  analogWrite(speedControlerL, speedValue);
  lcdMessage("Moving Forward Right");

}
void movingBackwardLeft(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue);
  analogWrite(speedControlerL, speedValue-120);
  lcdMessage("Moving Backward Left");

}

void movingBackwardRight(){
  digitalWrite(MOTOR_L_IN1, LOW);
  digitalWrite(MOTOR_L_IN2, HIGH);
  digitalWrite(MOTOR_R_IN3, LOW);
  digitalWrite(MOTOR_R_IN4, HIGH);
  analogWrite(speedControlerR, speedValue-120);
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
            if (servoAngle >= 180) movingForward = false;
        } else {
            servoAngle -= 10;
            if (servoAngle <= 0) movingForward = true;
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








