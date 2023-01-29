#include <Arduino.h>

#define MOTOR1_F 3
#define MOTOR1_R 2
#define MOTOR2_F 5
#define MOTOR2_R 4
#define Motor3_F 7
#define Motor3_B 6
#define Motor4_F 9
#define Motor4_B 8

void setup(void)
{
    pinMode(MOTOR1_F, OUTPUT);
    pinMode(MOTOR1_R, OUTPUT);
    pinMode(MOTOR2_F, OUTPUT);
    pinMode(MOTOR2_R, OUTPUT);
    pinMode(Motor3_F, OUTPUT);
    pinMode(Motor3_B, OUTPUT);
    pinMode(Motor4_F, OUTPUT);
    pinMode(Motor4_B, OUTPUT);

    // Turn on pn 22 and set it to output:
    pinMode(22, OUTPUT);
    

    Serial.begin(9600);

}

void loop(void)
{
    digitalWrite(22, HIGH);
    
    // Set the motors to forward at full speed:
    digitalWrite(MOTOR1_F, HIGH);
    digitalWrite(MOTOR1_R, LOW);
    digitalWrite(MOTOR2_F, HIGH);
    digitalWrite(MOTOR2_R, LOW);
    digitalWrite(Motor3_F, HIGH);
    digitalWrite(Motor3_B, LOW);
    digitalWrite(Motor4_F, HIGH);
    digitalWrite(Motor4_B, LOW);

    delay(99999);

    // Reverse the motors:
    digitalWrite(MOTOR1_F, LOW);
    digitalWrite(MOTOR1_R, HIGH);
    digitalWrite(MOTOR2_F, LOW);
    digitalWrite(MOTOR2_R, HIGH);
    digitalWrite(Motor3_F, LOW);
    digitalWrite(Motor3_B, HIGH);
    digitalWrite(Motor4_F, LOW);
    digitalWrite(Motor4_B, HIGH);

    delay(99999);

}