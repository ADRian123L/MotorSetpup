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
#define MOTOR1_F 3
#define MOTOR1_R 2
#define MOTOR2_F 5
#define MOTOR2_R 4
#define Motor3_F 7
#define Motor3_B 6
#define Motor4_F 9
#define Motor4_B 8
#define ADDER (float) (PI/4)

// Structs:
struct Motor
{
    /// @brief This struct is used to store the pins and direction of the motors.

    unsigned short forwardPin,
                   backwardPin,
                   speed;
    float direction;
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
    Serial.begin(9600);
}

void loop(void)
{
    float input = (PI / 2);
    direction(input);
    movement(1.0f);

    delay(1000);
}

void direction(float radian)
{   
    /// @brief This function sets the direction of the motors.
    /// @param radian The angle of the motors.

    // Set the direction of the motors:
    MotorOne.direction = (-cos(radian + ADDER));
    MotorTwo.direction = (sin(radian + ADDER));
    MotorThree.direction = (-cos(radian + ADDER));
    MotorFour.direction = (sin(radian + ADDER));
}

void movement(float speed)
{
    /// @brief This function sets the speed and direction of the motors.
    /// @param speed The speed of the motors.

    // Set the speed of the motors:
    MotorOne.speed = speed * MAX;
    MotorTwo.speed = speed * MAX;
    MotorThree.speed = speed * MAX;
    MotorFour.speed = speed * MAX;
    
    // Set the pins to the correct direction:
    if (MotorOne.direction > 0)
    {
        analogWrite(MotorOne.forwardPin, (int) MotorOne.speed);
        analogWrite(MotorOne.backwardPin, MIN);
    }
    else if (MotorTwo.direction > 0) 
    {
        analogWrite(MotorTwo.forwardPin, (int) MotorTwo.speed);
        analogWrite(MotorTwo.backwardPin, MIN);
    }
    else if (MotorThree.direction > 0)
    {
        analogWrite(MotorThree.forwardPin, (int) MotorThree.speed);
        analogWrite(MotorThree.backwardPin, MIN);
    }
    else if (MotorFour.direction > 0)
    {
        analogWrite(MotorFour.forwardPin, (int) MotorFour.speed);
        analogWrite(MotorFour.backwardPin, MIN);
    }
    else if (MotorOne.direction < 0)
    {
        analogWrite(MotorOne.forwardPin, MIN);
        analogWrite(MotorOne.backwardPin, (int) MotorOne.speed);
    }
    else if (MotorTwo.direction < 0)
    {
        analogWrite(MotorTwo.forwardPin, MIN);
        analogWrite(MotorTwo.backwardPin, (int) MotorTwo.speed);
    }
    else if (MotorThree.direction < 0)
    {
        analogWrite(MotorThree.forwardPin,  MIN);
        analogWrite(MotorThree.backwardPin, (int) MotorThree.speed);
    }
    else if (MotorFour.direction < 0)
    {
        analogWrite(MotorFour.forwardPin, MIN);
        analogWrite(MotorFour.backwardPin, (int) MotorFour.speed);
    }
    else if (MotorOne.direction == 0)
    {
        analogWrite(MotorOne.forwardPin, MIN);
        analogWrite(MotorOne.backwardPin, MIN);
    }
    else if (MotorTwo.direction == 0)
    {
        analogWrite(MotorTwo.forwardPin, MIN);
        analogWrite(MotorTwo.backwardPin, MIN);
    }
    else if (MotorThree.direction == 0)
    {
        analogWrite(MotorFour.forwardPin, MIN);
        analogWrite(MotorFour.backwardPin, MIN);
    }
    else if (MotorFour.direction == 0)
    {
        analogWrite(MotorFour.forwardPin, MIN);
        analogWrite(MotorFour.backwardPin, MIN);
    }
    else 
        Serial.println("Error: No direction for motors.\n");
}