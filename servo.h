#ifndef _SERVO_H_
#define _SERVO_H_
    #ifndef _C99VARSTAN_
    #define _C99VARSTAN_
        typedef  unsigned short   uint8_t;
        typedef  signed short     int8_t ;
        typedef  unsigned int     uint16_t;
        typedef  signed int       int16_t;
        typedef  unsigned long    uint32_t;
        typedef  signed long      int32_t;
    #endif
    //cpu frequency
    #ifndef FOSCMHZ
    #define FOSCMHZ 4      //16MHZ crystal dividded by cpu prescaller(4)
    #endif
typedef struct
{
    uint8_t pin;
    volatile uint8_t* serport;
    uint8_t angleTimeL;
    uint8_t angleTimeH;
    uint8_t serIndex;
}NEWSERVO;

extern void InitTimer1AndCompare(void) ;
extern void servoInterrupt(void);
extern void setServoAngle( NEWSERVO* servoptr , uint8_t angle );
extern void attachServo( NEWSERVO* servoptr , uint8_t* portptr ,uint8_t pinn);
extern void deattachServo( NEWSERVO* servoptr );

#endif