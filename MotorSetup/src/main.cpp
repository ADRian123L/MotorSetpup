#include <Arduino.h>

// Struct:
struct MotorAttribute {
  // Pins attribute:
  int pin_1,
      pin_2,
      pin_pbw;
  // Speed attribute:
   double  velocity,
          power_supply;
  // the motor's number
  int number;

};

// Initialize four objects:
struct MotorAttribute Motor1, 
                      Motor2,
                      Motor3,
                      Motor4;

// PWD pins constants:
const int PWD1 = 3, PWD2 = 5, 
          PWD3 = 6, PWD4 = 11;
// Max speed:
const int MAX = 255;
// Varying speed:
int current_speed;


// Direction pins:
const int PIN1R = 7, PIN1L = 4,
          PIN2R = 12, PIN2L = 13,
          PIN3R = 9, PIN3L = 8,
          PIN4R = 2, PIN4L = 10;

// Count variable:
int count = 0;

// Functions:
int input_degree(void);
double input_speed(void);
double converter(int degree_arg);
double x_components(double radian_x);
double y_components(double radian_y);
void motors(double xcomp, double ycomp);
void motor_control(MotorAttribute motor_name);
void speed(double percentage);

// String Constants:
const String prompt = "Add the angle: ",
             prompt2 = "Add speed level: ";

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

 // the motor's number
 Motor1.number = 1;
 Motor2.number = 2;
 Motor3.number = 3;
 Motor4.number = 4;

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
  int degree_input, speed_percent;
  float radian_value;
  double X_comp, Y_comp;

  // Prompts for degrees:
  degree_input = 90;
  speed_percent = 50;

  // Prints the motors' properties:
  Serial.print("Angle: ");
  Serial.println(count);

  // Sets the speed:
  speed(speed_percent);

  // Converts to radians:
  radian_value = converter(degree_input);

  // Converts into (x - y) components:
  X_comp = x_components(radian_value);
  Y_comp = y_components(radian_value);
  
  // Calculates the power and direction:
  motors(X_comp, Y_comp);
  motor_control(Motor1);
  motor_control(Motor2);
  motor_control(Motor3);
  motor_control(Motor4);

  Serial.println(count);
  //count = count + 2;

  delay(9000000);
}

// Read the degree_input in degrees:
int input_degree(void) {
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

// Read the degree_input in speed:
double input_speed(void) {
  // Empty variable:
  double get_speed;
  //Prints the prompt:
  Serial.println(prompt2);
  // Waits until a message is sent:
  while (Serial.available() == 0) {
    // Delays.
  }
  // Saves the message:
  get_speed = Serial.parseInt();
  return get_speed;
}

// Convert to radians: 
double converter(int degree_arg) {
  double radians;
  double new_degree = degree_arg + 45;
  // Converts to radians:
  radians =  new_degree * (PI / 180);
  return radians;
}

// Converts the radians into its x-component:
double x_components(double radian_x) {
    // Finds the component:
    double value_x = cos(radian_x);
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
  // Assign the attributes:
  Motor1.velocity = 0 - xcomp;
  Motor2.velocity = ycomp;
  Motor3.velocity= 0 - xcomp;
  Motor4.velocity = ycomp;
}

// Drives the motors:
void motor_control(MotorAttribute motor_name) {
    // Assigns the power to the object:
    motor_name.power_supply = abs(motor_name.velocity * current_speed);
    // looking for the specific motor
    if (motor_name.number == 3) {
     motor_name.power_supply =  motor_name.power_supply * 2;
    }
    // Runs the motors:
    if (motor_name.velocity > 0) {
      digitalWrite(motor_name.pin_1, HIGH);
      digitalWrite(motor_name.pin_2, LOW);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
    }
    else if (motor_name.velocity == 0) {
      digitalWrite(motor_name.pin_1, LOW);
      digitalWrite(motor_name.pin_2, LOW);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply); 
    }
    else {
      digitalWrite(motor_name.pin_1, LOW);
      digitalWrite(motor_name.pin_2, HIGH);
      analogWrite(motor_name.pin_pbw, motor_name.power_supply);
    }
    Serial.println(motor_name.velocity);
  }
  
void speed(double percentage) {
  // Empty var:
  double decimal;
  // Converts to percentage:
  decimal = percentage / 100;
  // Assigns the value:
  current_speed = round(decimal * MAX);
}