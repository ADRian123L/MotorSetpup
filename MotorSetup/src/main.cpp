#include <Arduino.h>

// Struct:
struct MotorAttribute {
  int pin_1,
      pin_2,
      pin_pbw,
      velocity,
      power_supply;

};

// Struct:
struct MotorAttribute Motor1, 
                      Motor2,
                      Motor3,
                      Motor4;



// PWD pins constants:
const int PWD1 = 3, PWD2 = 5, 
          PWD4 = 11, PWD3 = 6;
const int MAX = 255, MIN = 0;

// Direction pins:
const int PIN1R = 4, PIN1L = 7,
          PIN2R = 13, PIN2L = 12,
          PIN3R = 8, PIN3L = 9,
          PIN4R = 10, PIN4L = 2;

// Functions:
int degree(void);
double converter(int degree_arg);
int x_components(double radian_x);
int y_components(double radian_y);
void motors(int xcomp, int ycomp);
void set_power(MotorAttribute wheel_name);
int motor_control(MotorAttribute motor_name);

// String Constants:
const String prompt = "Add the angle: ";

void setup() {
  
  //Assign each object its pins:
  Motor1.pin_1 = PIN1L;
  Motor1.pin_2 = PIN1R;
  Motor1.pin_pbw = PWD1;

  Motor2.pin_1 = PIN2L;
  Motor2.pin_2 = PIN2R;
  Motor2.pin_pbw = PWD2;

  Motor3.pin_1 = PIN3L;
  Motor3.pin_2 = PIN3R;
  Motor3.pin_pbw = PWD3;

  Motor4.pin_1 = PIN4L;
  Motor4.pin_2 = PIN4R;
  Motor4.pin_pbw = PWD4;

 // Pins type:
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

  // Start communication:
  Serial.begin(9600);

}



  
  
void loop() {

  Serial.println("it works");
  // Empty var:
  int input, return1, return2, return3, return4;
  double radian_value, Xcomp, Ycomp;

  // Prompts for degrees:
  input = 90;

  // Converts to radians:
  radian_value = radians(input);

  // Converts into (x - y) components:
  Xcomp = x_components(radian_value);
  Ycomp = y_components(radian_value);

  // Calculates the power and direction:
  motors(Xcomp, Ycomp);

  // Set motors' output:
  return1 = motor_control(Motor1);
  return2 = motor_control(Motor2);
  return3 = motor_control(Motor3);
  return4  = motor_control(Motor4);

  // Prints:
  Serial.println(return1);
  Serial.println(return2);
  Serial.println(return3);
  Serial.println(return4);
  
  delay(9000000);
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
  // Converts to radians:asdaa
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
  if (xcomp == 1 && ycomp == 0) {
      m[0] = -1;
      m[1] = 1;
      m[2] = -1;
      m[3] = 1;
  }
  else if (xcomp == 1 && ycomp == 1) {
     m[0] = 0;
     m[1] = 1;
     m[2] = 0;
     m[3] = 1;
  }
  else if (xcomp == 0 && ycomp == 1) {
    m[0] = 1;
    m[1] = 1;
    m[2] = 1;
    m[3] = 1;
    }
  else if (xcomp == -1 && ycomp == 1) {
      /* code */
      m[0] = 1;
      m[1] = 0;
      m[2] = 1;
      m[3] = 0;
    }
  else if (xcomp == -1 && ycomp == 0) {
      /* code */
      m[0] = 1;
      m[1] = -1;
      m[2] = 1;
      m[3] = -1;  
    }
  else if (xcomp == -1 && ycomp == -1) {
      /* code */
      m[0] = -1;
      m[1] = 0;
      m[2] = -1;
      m[3] = 0;
    }
  else if (xcomp == 0 && ycomp == -1) {
      /* code */
      m[0] = -1;
      m[1] = -1;
      m[2] = -1;
      m[3] = -1;
    }
  else if (xcomp == 1 && ycomp == -1) {
    /* code */
    m[0] = -1;
    m[1] = 0;
    m[2] = -1;
    m[3] = 0;  
  }

  // Assign the attributes:
  Motor1.velocity = m[0];
  Motor2.velocity = m[1];
  Motor3.velocity= m[2];
  Motor4.velocity = m[3];
}

void set_power(MotorAttribute wheel_name) {
  
  wheel_name.power_supply = abs(wheel_name.velocity * 255);

}

int motor_control(MotorAttribute motor_name) {

    set_power(motor_name);
    
    switch (motor_name.velocity) {

    case 1:
      digitalWrite(motor_name.pin_1, HIGH);
      digitalWrite(motor_name.pin_2, LOW);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
      return 0;
    
    case 0:
      digitalWrite(motor_name.pin_1, LOW);
      digitalWrite(motor_name.pin_2, LOW);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
      return 0; 

    case -1:
      digitalWrite(motor_name.pin_1, LOW);
      digitalWrite(motor_name.pin_2, HIGH);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
      return 0;

    }

    return -1;

  }
