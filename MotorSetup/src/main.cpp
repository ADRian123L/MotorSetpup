#include <Arduino.h>
#include <math.h>

// Struct:
struct MotorAction {
  int motor1,
      motor2,
      motor3,
      motor4;
};

// Struct:
struct MotorAction Motor;

// PWD pins constants:
const int PWD1 = 3, PWD2 = 5, PWD3 = 6 , PWD4 = 9;
const int MAX = 255, MIN = 0;

// Functions:
int main(void);
int degree(void);
double converter(int degree_arg);
int x_components(double radian_x);
int y_components(double radian_y);
void motors(int xcomp, int ycomp);

// Direction pins:
const int PIN1R = 2, PIN1L = 4,
          PIN2R = 7, PIN2L = 8,
          PIN3R = 10, PIN3L = 11,
          PIN4R = 12, PIN4L = 13;

// String Constants:
const String prompt;

void setup() {
  // put your setup code here, to run once:
  pinMode(PWD1, OUTPUT);
  pinMode(PWD2, OUTPUT);
  pinMode(PWD3, OUTPUT);
  pinMode(PWD4, OUTPUT);
  pinMode(PIN1R, OUTPUT);
  pinMode(PIN2R, OUTPUT);
  pinMode(PIN3R, OUTPUT);
  pinMode(PIN4R, OUTPUT);
  pinMode(PIN1L, OUTPUT);
  pinMode(PIN2L, OUTPUT);
  pinMode(PIN3L, OUTPUT);
  pinMode(PIN4L, OUTPUT);

  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("It works");
}

// Read the input in degrees:
int degree(void) {
  // Empty variable:
  int get_degree;
  //Prints the prompt:
  Serial.println(prompt);
  // Waits until a message is sent:
  while (Serial.available() == 0) {
    // Delays.
  }
  // Saves the message:
  get_degree = Serial.parseInt();
   return get_degree;
}

// Convert to radians: 
double converter(int degree_arg) {
  double radians;
  // Converts to radians:
  radians = degree_arg / (PI / 180);
  return radians;
}

// Converts the radians into its x-component:
int x_components(double radian_x) {

    // Empty variables:
    int sign_x;
    double value_x;

    // Finds the component:
    value_x = round(cos(radian_x));
    
    if (value_x > 0) {
        sign_x = 1;
    }
    else if (value_x == 0) {
        sign_x = 0;
    }
    else {
        sign_x = -1;
    }

    return sign_x;
}

// Converts the radians into its y-component:
int y_components(double radian_y) {

    // Empty variables:
    int sign_y;
    double value_y;

    // Finds the component:
    value_y = round(sin(radian_y));
    
    if (value_y > 0) {
        sign_y = 1;
    }
    else if (value_y == 0) {
        sign_y = 0;
    }
    else {
        sign_y = -1;
    }

    return sign_y;
}

// Control the motors:
void motors(int xcomp, int ycomp) {
  // Empty int variable:
  int m[4];

  // Determines the motor power and direction:
  if (xcomp == 1 && ycomp == 1){
      m[0] = 1;
      m[1] = 0;
      m[2] = -1;
      m[3] = 0;
  }
  else if (xcomp == 0 && ycomp == 1){
     m[0] = 1;
     m[1] = 1;
     m[2] = -1;
     m[3] = -1;
  }
  else if (xcomp == 1 && ycomp == 0) {
    m[0] = 1;
    m[1] = -1;
    m[2] = -1;
    m[3] = 1;
    }
  else if (xcomp == -1 && ycomp == 0){
      /* code */
      m[0] = -1;
      m[1] = 1;
      m[2] = 1;
      m[3] = -1;
    }
  else if (xcomp == -1 && ycomp == -1){
      /* code */
      m[0] = -1;
      m[1] = 0;
      m[2] = 1;
      m[3] = 0;  
    }
  else if (xcomp == -1 && ycomp == 1){
      /* code */
      m[0] = 0;
      m[1] = 1;
      m[2] = 0;
      m[3] = -1;
    }
  else if (xcomp == 1 && ycomp == -1){
      /* code */
      m[0] = 0;
      m[1] = -1;
      m[2] = 0;
      m[3] = 1;
    }
  else if (xcomp == 0 && ycomp == -1){
    /* code */
    m[0] = -1;
    m[1] = -1;
    m[2] = 1;
    m[3] = 1;  
  }

  // Assign the attributes:
  Motor.motor1 = m[0];
  Motor.motor2 = m[1];
  Motor.motor3 = m[2];
  Motor.motor4 = m[3];
}

int main(void) {
  int input;
  double radian_value, Xcomp, Ycomp;
  input = degree();
  radian_value = radians(input);
  Xcomp = x_components(radian_value);
  Ycomp = y_components(radian_value);
  motors(Xcomp, Ycomp);
  Serial.println(Motor.motor1);
  Serial.println(Motor.motor2);
  Serial.println(Motor.motor3);
  Serial.println(Motor.motor4);
  return 0;
}