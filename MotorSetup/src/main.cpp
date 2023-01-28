/*
    Purpose: This program is used to control the motor speed and direction of
             a vehicle.
    Author: Adrian Lozada & Jiahui Dang
        
*/

#include <Arduino.h>
#include <math.h>
#include <stdio.h>

// Macros:
#define MAX 255;
#define MIN 0;
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

void setup()
{
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

    // Communication:
    Serial.begin(9600);
}

void loop()
{
    float input = (PI / 2);
    direction(input);
    movement(0.5f);
}

void direction(float radian)
{   
    // Set the direction of the motors:
    MotorOne.direction = (-cos(radian + ADDER));
    MotorTwo.direction = (sin(radian + ADDER));
    MotorThree.direction = (-cos(radian + ADDER));
    MotorFour.direction = (sin(radian + ADDER));
}

void movement(float speed)
{
    // Set the speed of the motors:
    MotorOne.speed = speed * MAX;
    MotorTwo.speed = speed * MAX;
    MotorThree.speed = speed * MAX;
    MotorFour.speed = speed * MAX;
    
    // Set the pins to the correct direction:
    if (MotorOne.direction > 0)
    {
        analogWrite(MotorOne.forwardPin, MotorOne.speed);
        analogWrite(MotorOne.backwardPin, LOW);
    }
    else if (MotorTwo.direction > 0) 
    {
        analogWrite(MotorTwo.forwardPin, MotorTwo.speed);
        analogWrite(MotorTwo.backwardPin, LOW);
    }
    else if (MotorThree.direction > 0)
    {
        analogWrite(MotorThree.forwardPin, MotorThree.speed);
        analogWrite(MotorThree.backwardPin, LOW);
    }
    else if (MotorFour.direction > 0)
    {
        analogWrite(MotorFour.forwardPin, MotorFour.speed);
        analogWrite(MotorFour.backwardPin, LOW);
    }
    else if (MotorOne.direction < 0)
    {
        analogWrite(MotorOne.forwardPin, LOW);
        analogWrite(MotorOne.backwardPin, MotorOne.speed);
    }
    else if (MotorTwo.direction < 0)
    {
        analogWrite(MotorTwo.forwardPin, LOW);
        analogWrite(MotorTwo.backwardPin, MotorTwo.speed);
    }
    else if (MotorThree.direction < 0)
    {
        analogWrite(MotorThree.forwardPin, LOW);
        analogWrite(MotorThree.backwardPin, MotorThree.speed);
    }
    else if (MotorFour.direction < 0)
    {
        analogWrite(MotorFour.forwardPin, LOW);
        analogWrite(MotorFour.backwardPin, MotorFour.speed);
    }
    else if (MotorOne.direction == 0)
    {
        analogWrite(MotorOne.forwardPin, LOW);
        analogWrite(MotorOne.backwardPin, LOW);
    }
    else if (MotorTwo.direction == 0)
    {
        analogWrite(MotorTwo.forwardPin, LOW);
        analogWrite(MotorTwo.backwardPin, LOW);
    }
    else if (MotorThree.direction == 0)
    {
        analogWrite(MotorFour.forwardPin, LOW);
        analogWrite(MotorFour.backwardPin, LOW);
    }
    else if (MotorFour.direction == 0)
    {
        analogWrite(MotorFour.forwardPin, LOW);
        analogWrite(MotorFour.backwardPin, LOW);
    }
    else 
        // Why is there an error with Serial.println?

        Serial.println("Error: No direction for motors.\n");
}