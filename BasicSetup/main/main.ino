/*
    Purpose: This program is used to control the motor speed and direction of
             a vehicle.
    Author: Adrian Lozada & Jiahui Dang
        
*/
    /// @file main.cpp
#include <Arduino.h>
#include <math.h>
#include <stdio.h>

// Macros:
#define MAX 255
#define MIN 0
#define H_POWER 22
#define MOTOR1_F 2
#define MOTOR1_R 3
#define MOTOR2_F 4
#define MOTOR2_R 5
#define Motor3_F 6
#define Motor3_B 7
#define Motor4_F 8
#define Motor4_B 9
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

void loop(void)
{   /*
    i++;
    k = (float) i / 100.0;
    float input = (k * PI * 2);
    // Call the functions:
    direction(input);
    movement(.05f);
    if (i == 100)
        i = 0;
    delay(500);
    */

    // Print the input and direction:
    // Serial.print("Input: ");
    // Serial.println(input);
    // Direction for each motor:
    Serial.print("Motor One Direction: ");
    Serial.println(MotorOne.angle);
    Serial.print("Motor Two Direction: ");
    Serial.println(MotorTwo.angle);
    Serial.print("Motor Three Direction: ");
    Serial.println(MotorThree.angle);
    Serial.print("Motor Four Direction: ");
    Serial.println(MotorFour.angle);
    Serial.print("Speed of Motor 1: ");
    Serial.println(MotorOne.speed);
    Serial.print("Speed of Motor 2: ");
    Serial.println(MotorTwo.speed);
    Serial.print("Speed of Motor 3: ");
    Serial.println(MotorThree.speed);
    Serial.print("Speed of Motor 4: ");
    Serial.println(MotorFour.speed);


    //Square movement
    if (car_direction >= 2 * PI)
        car_direction = 0;
    direction (car_direction);
    car_direction += (PI / 2.0);
    movement(100);
    delay(500);

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
    {   for (int i; i < MotorOne.speed; i++)
        {
            analogWrite(MotorOne.forwardPin, (int) i);
            analogWrite(MotorOne.backwardPin, MIN);
            delay(100);
        }
        analogWrite(MotorOne.forwardPin, (int) MotorOne.speed);
        analogWrite(MotorOne.backwardPin, MIN);
        
    }

    if (MotorTwo.angle > 0) 
    {
        analogWrite(MotorTwo.forwardPin, (int) MotorTwo.speed);
        analogWrite(MotorTwo.backwardPin, MIN);
        
    }
    if (MotorThree.angle > 0)
    {
        analogWrite(MotorThree.forwardPin, (int) MotorThree.speed);
        analogWrite(MotorThree.backwardPin, MIN);
        
    }
    if (MotorFour.angle > 0)
    {
        analogWrite(MotorFour.forwardPin, (int) MotorFour.speed);
        analogWrite(MotorFour.backwardPin, MIN);
    }
    if (MotorOne.angle < 0)
    {
        analogWrite(MotorOne.forwardPin, MIN);
        analogWrite(MotorOne.backwardPin, (int) MotorOne.speed);
    }
    if (MotorTwo.angle < 0)
    {
        analogWrite(MotorTwo.forwardPin, MIN);
        analogWrite(MotorTwo.backwardPin, (int) MotorTwo.speed);
    }
    if (MotorThree.angle < 0)
    {
        analogWrite(MotorThree.forwardPin,  MIN);
        analogWrite(MotorThree.backwardPin, (int) MotorThree.speed);
    }
    if (MotorFour.angle < 0)
    {
        analogWrite(MotorFour.forwardPin, MIN);
        analogWrite(MotorFour.backwardPin, (int) MotorFour.speed);
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