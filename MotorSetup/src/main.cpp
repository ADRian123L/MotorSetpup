#include <Arduino.h>
// Struct:
struct MotorAttribute {
  int pin_1,
      pin_2,
      pin_pbw;
      
  
   double   velocity,
            power_supply;

};

// Struct:
struct MotorAttribute Motor1, 
                      Motor2,
                      Motor3,
                      Motor4;



// PWD pins constants:
const int PWD1 = 2, PWD2 = 3, 
          PWD4 = 4, PWD3 = 5;
const int MAX = 255, MIN = 0;

// Direction pins:
const int PIN1R = 30, PIN1L = 31,
          PIN2R = 32, PIN2L = 33,
          PIN3R = 34, PIN3L = 35,
          PIN4R = 36, PIN4L = 37;

// Functions:
int degree(void);
double converter(int degree_arg);
double x_components(double radian_x);
double y_components(double radian_y);
void motors(int xcomp, int ycomp);
void set_power(MotorAttribute wheel_name);
double motor_control(MotorAttribute motor_name);

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

  // Empty var:
  int input, return1, return2, return3, return4;
  float radian_value;
  double Xcomp, Ycomp;

  // Prompts for degrees:
  input = 30;

  // Converts to radians:
  radian_value = converter(input);

  // Converts into (x - y) components:
  Xcomp = x_components(radian_value);
  Ycomp = y_components(radian_value);
  

  // Calculates the power and direction:
  motors(Xcomp, Ycomp);

  // Set motors' output:
  return1 = motor_control(Motor1);
  return2 = motor_control(Motor2);
  return3 = motor_control(Motor3);
  return4 = motor_control(Motor4);

  // Prints:
  Serial.println(radian_value);
  Serial.println(Xcomp);
  Serial.println(Ycomp);
  Serial.println(return1);
  Serial.println(return2);
  Serial.println(return3);
  Serial.println(return4);
  
  Serial.println(Motor1.velocity);
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
  int new_degree = degree_arg + 45;
  // Converts to radians:
  radians =  new_degree * (PI / 180);
  return radians;
}

// Converts the radians into its x-component:
double x_components(double radian_x) {

    // Empty variables:
    
    double value_x = cos(radian_x);

    // Finds the component:
    
    Serial.print("it is");
    Serial.println(value_x);
    

    return value_x;
}

// Converts the radians into its y-component:
double y_components(double radian_y) {

    // Empty variables:
    
    double value_y;

    // Finds the component:
    value_y = sin(radian_y);
    

    return value_y;
}

// Control the motors:
void motors(double xcomp, double ycomp) {
  // Empty int variable:
 
  // Assign the attributes:
  Motor1.velocity = 0 - xcomp;
  Motor2.velocity = ycomp;
  Motor3.velocity= 0 - xcomp;
  Motor4.velocity = ycomp;
}

void set_power(MotorAttribute wheel_name) {
  
  wheel_name.power_supply = abs(wheel_name.velocity * 255);

}

double motor_control(MotorAttribute motor_name) {

    motor_name.power_supply = abs(motor_name.velocity * 255);
    
    if (motor_name.velocity > 0) {

    
      digitalWrite(motor_name.pin_1, HIGH);
      digitalWrite(motor_name.pin_2, LOW);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
      return motor_name.power_supply;
    }
    else if (motor_name.velocity == 0) {
      digitalWrite(motor_name.pin_1, LOW);
      digitalWrite(motor_name.pin_2, LOW);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
      return motor_name.power_supply; 
    }
    else {
      digitalWrite(motor_name.pin_1, LOW);
      digitalWrite(motor_name.pin_2, HIGH);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
      return motor_name.power_supply;

    }

    return -1;

  }
