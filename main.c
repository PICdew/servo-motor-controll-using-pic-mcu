/*
pro name : servo libarary for mcu
target device :  pic18f452(or compatible devices) ,16 MHZ fre
description : this program use ccp1 module and timer1 to control servo motors with precise angles from 0 to 180
developed by : mohamed yehia (thedesertm@gmail.com)

*/
#define FOSCMHZ 4    //fosc/4
#include "servo.h"
void main(void)
{
    NEWSERVO ser1,ser2,ser3,ser4,ser5,ser6,ser7,ser8;
    TRISD=0;
    attachServo(&ser1 ,&PORTD , 0);
    attachServo(&ser2 ,&PORTD , 1);
    attachServo(&ser3 ,&PORTD , 2);
    attachServo(&ser4 ,&PORTD , 3);
    attachServo(&ser5 ,&PORTD , 4);
    attachServo(&ser6 ,&PORTD , 5);
    attachServo(&ser7 ,&PORTD , 6);
    attachServo(&ser8 ,&PORTD , 7);
    setServoAngle(&ser1,30);
    setServoAngle(&ser2,63);
    setServoAngle(&ser3,108);
    setServoAngle(&ser4,173);
    setServoAngle(&ser5,0);
    setServoAngle(&ser6,15);
    setServoAngle(&ser7,80);
    setServoAngle(&ser8,135);
}
void Interrupt()
{
     servoInterrupt();
}
