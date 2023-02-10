/*
    Purpose: This program is used to control the motor speed and direction of
             a vehicle.
    Author: Adrian Lozada & Jiahui Dang
        
*/
    /// @file main.cpp
    /// @brief This file contains the main function of the program.
    /// @author Adrian Lozada & Jiahui Dang

#include <Arduino.h>
#include <math.h>
#include <stdio.h>

// Macros:
#define MAX 255
#define MIN 0
#define H_POWER 22
#define MOTOR1_F 2
#define MOTOR1_R 3
#define MOTOR2_F 5
#define MOTOR2_R 4
#define Motor3_F 6
#define Motor3_B 7
#define Motor4_F 9
#define Motor4_B 8
#define ADDER (float) (PI/4)

// Structs:
struct Motor
{
    /// @brief This struct is used to store the pins and direction of the motors.

    unsigned short forwardPin,
                   backwardPin;
                   
    float angle, speed;

    bool direction;
};

//Initialize the motors:
struct Motor MotorOne,
             MotorTwo,
             MotorThree,
             MotorFour;

// Functions:
void direction(float radian);
void movement(float speed);
void info(void);
void speed_check(void);

void setup(void)
{
    /// @brief This function sets up the pins and the motors.

    // Assign the pins to the motors:
    MotorOne.forwardPin = MOTOR1_F;
    MotorOne.backwardPin = MOTOR1_R;
    MotorTwo.forwardPin = MOTOR2_F;
    MotorTwo.backwardPin = MOTOR2_R;
    MotorThree.forwardPin = Motor3_F;
    MotorThree.backwardPin = Motor3_B;
    MotorFour.forwardPin = Motor4_F;
    MotorFour.backwardPin = Motor4_B;

    // Set the pins to output:
    pinMode(10, OUTPUT);
    pinMode(MotorOne.forwardPin, OUTPUT);
    pinMode(MotorOne.backwardPin, OUTPUT);
    pinMode(MotorTwo.forwardPin, OUTPUT);
    pinMode(MotorTwo.backwardPin, OUTPUT);
    pinMode(MotorThree.forwardPin, OUTPUT);
    pinMode(MotorThree.backwardPin, OUTPUT);
    pinMode(MotorFour.forwardPin, OUTPUT);
    pinMode(MotorFour.backwardPin, OUTPUT);

    // Turn on the power to H-bridge:
    pinMode(H_POWER, OUTPUT);
    digitalWrite(H_POWER, HIGH);

    // Communication:
    Serial.begin(115200);
}
float car_direction = 0;
int i = 0;
float k = 0;
int counter = 0;
int number_sides = 20;
double delay_var = 8000.0;

void loop(void)
{ 
    /// @brief This function controls the speed and direction of the motors.

   // Check if the car has completed a full rotation:
    if (car_direction >= 2 * PI)
        {
        car_direction = 0;
        // Beep the beeper:
        
       
        
        
        }
    // Set the direction of the motors:
    direction (car_direction);
    // Set the speed and direction of the motors:
    car_direction += (float) (2.0 * PI) / number_sides;
    // Check if the motors are at 0 speed:
    speed_check();
    // Output the direction and speed of the motors:
    movement(10 / 100.0); 
    // Delay:
 
 
    delay(delay_var / number_sides);
  

    // Print the direction and speed of the motors:
    info();
}

void speed_check(void)
{
    /// @brief This function checks if the motors are at 0 speed.

    if (MotorOne.speed <= 10 && MotorOne.speed >= -10)
        delay_var *= 1;
    if (MotorTwo.speed <= 10 && MotorTwo.speed >= -10)
        delay_var *= 1;
    if (MotorThree.speed <= 10 && MotorThree.speed >= -10)
        delay_var *= 1;
    if (MotorFour.speed <= 10 && MotorFour.speed >= -10)
        delay_var *= 1;
}

void info(void)
{
    /// @brief This function outputs the direction and speed of the motors.

     // Output the direction of the motors:
    Serial.print("MotorOne.angle: ");
    Serial.println(MotorOne.angle);
    Serial.print("MotorTwo.angle: ");
    Serial.println(MotorTwo.angle);
    Serial.print("MotorThree.angle: ");
    Serial.println(MotorThree.angle);
    Serial.print("MotorFour.angle: ");
    Serial.println(MotorFour.angle);
    Serial.println();
    // Output the speed of the motors:
    Serial.print("MotorOne.speed: ");
    Serial.println(MotorOne.speed);
    Serial.print("MotorTwo.speed: ");
    Serial.println(MotorTwo.speed);
    Serial.print("MotorThree.speed: ");
    Serial.println(MotorThree.speed);
    Serial.print("MotorFour.speed: ");
    Serial.println(MotorFour.speed);
}

void direction(float radian)
{   
    /// @brief This function sets the direction of the motors.
    /// @param radian The angle of the motors.

    // Set the direction of the motors:
    MotorOne.angle = (float) (-cos(radian + ADDER));
    MotorTwo.angle = (float) (sin(radian + ADDER));
    MotorThree.angle = (float) (-cos(radian + ADDER));
    MotorFour.angle = (float) (sin(radian + ADDER));
}

void movement(float speed)
{
    /// @brief This function sets the speed and direction of the motors.
    /// @param speed The speed of the motors.

    // Set the speed of the motors:
    MotorOne.speed = speed * MAX * MotorOne.angle;
    MotorTwo.speed = speed * MAX * MotorTwo.angle;
    MotorThree.speed = speed * MAX * MotorThree.angle;
    MotorFour.speed = speed * MAX * MotorFour.angle;
    
    // Set the pins to the correct direction:
    if (MotorOne.angle > 0)
    {  
        analogWrite(MotorOne.forwardPin, (int) abs(MotorOne.speed));
        analogWrite(MotorOne.backwardPin, MIN);
    }
    if (MotorTwo.angle > 0) 
    {
        analogWrite(MotorTwo.forwardPin, (int) abs(MotorTwo.speed));
        analogWrite(MotorTwo.backwardPin, MIN);
        
    }
    if (MotorThree.angle > 0)
    {
        analogWrite(MotorThree.forwardPin, (int) abs(MotorThree.speed));
        analogWrite(MotorThree.backwardPin, MIN);
        
    }
    if (MotorFour.angle > 0)
    {
        analogWrite(MotorFour.forwardPin, (int) abs(MotorFour.speed));
        analogWrite(MotorFour.backwardPin, MIN);
    }
    if (MotorOne.angle < 0)
    {
        analogWrite(MotorOne.forwardPin, MIN);
        analogWrite(MotorOne.backwardPin, (int) abs(MotorOne.speed));
    }
    if (MotorTwo.angle < 0)
    {
        analogWrite(MotorTwo.forwardPin, MIN);
        analogWrite(MotorTwo.backwardPin, (int) abs(MotorTwo.speed));
    }
    if (MotorThree.angle < 0)
    {
        analogWrite(MotorThree.forwardPin,  MIN);
        analogWrite(MotorThree.backwardPin, (int) abs(MotorThree.speed));
    }
    if (MotorFour.angle < 0)
    {
        analogWrite(MotorFour.forwardPin, MIN);
        analogWrite(MotorFour.backwardPin, (int) abs(MotorFour.speed));
    }
    if (MotorOne.angle == 0)
    {
        analogWrite(MotorOne.forwardPin, MIN);
        analogWrite(MotorOne.backwardPin, MIN);
    }
    if (MotorTwo.angle == 0)
    {
        analogWrite(MotorTwo.forwardPin, MIN);
        analogWrite(MotorTwo.backwardPin, MIN);
    }
    if (MotorThree.angle == 0)
    {
        analogWrite(MotorFour.forwardPin, MIN);
        analogWrite(MotorFour.backwardPin, MIN);
    }
    if (MotorFour.angle == 0)
    {
        analogWrite(MotorFour.forwardPin, MIN);
        analogWrite(MotorFour.backwardPin, MIN);       
    }
}