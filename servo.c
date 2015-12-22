#include "servo.h"
//********************************* constants variables **************************
const uint16_t timerReloadValue=0xffff - 2500*FOSCMHZ;
const uint8_t hTimerReloadValue=timerReloadValue>>8;
const uint8_t lTimerReloadValue=timerReloadValue&255;
const uint16_t minServoTime=700;
const uint16_t maxServoTime=2400;
const double servoTimeSlope=(maxServoTime-minServoTime)/180.0;
//********************************* global variables **************************
volatile uint8_t* virtualport;
uint8_t servoCounter=0;
volatile uint8_t interruptServoCounter=0;
NEWSERVO* serviceServoArray [8];
//********************************* global function **************************
//Timer1
void InitTimer1AndCompare(void){
  CCP1CON = 0x0A;      //generate soft interrupt
  T1CON         = 0x00;
  TMR1IF_bit         = 0;
  TMR1H         = hTimerReloadValue;
  TMR1L         = lTimerReloadValue;
}
//interrupthandeller
void servoInterrupt(void)
{
   if (TMR1IF_bit)
  {
    TMR1IF_bit = 0;
    TMR1H         = hTimerReloadValue;
    TMR1L         = lTimerReloadValue;
    //Enter your code here
    if(interruptServoCounter < servoCounter)
    {
        virtualport=(serviceServoArray[interruptServoCounter] -> serport) ;
        *virtualport |= 1<<(serviceServoArray[interruptServoCounter] -> pin);
        CCP1IE_bit=1;
        CCP1IF_bit=0;
        CCPR1L = serviceServoArray[interruptServoCounter] -> angleTimeL;
        CCPR1H = serviceServoArray[interruptServoCounter] -> angleTimeH;
    }
    else
    {

        CCP1IE_bit=0;
        CCP1IF_bit=0;
        interruptServoCounter++;
        if (interruptServoCounter>7)interruptServoCounter=0;
    }

  }
  else if(CCP1IF_bit&&CCP1IE_bit)
  {
       CCP1IF_bit=0;
       if(interruptServoCounter <= servoCounter)*virtualport &= ~(1<<(serviceServoArray[interruptServoCounter] -> pin));
       interruptServoCounter++;
       if (interruptServoCounter>7)interruptServoCounter=0;
  }
}
//set servo angle
void setServoAngle( NEWSERVO* servoptr , uint8_t angle )
{
    uint16_t angleTime = 0;
    angleTime =  (servoTimeSlope * angle) ;
    angleTime +=minServoTime;
    angleTime *= FOSCMHZ;
    angleTime += timerReloadValue-25 ;

    servoptr -> angleTimeH = angleTime>>8;
    servoptr -> angleTimeL = angleTime&255;
}
//add NEWSERVO
void attachServo( NEWSERVO* servoptr , uint8_t* portptr ,uint8_t pinno)
{
    if (servoCounter<8)
    {
        serviceServoArray[servocounter]= servoptr;
        servoptr -> serport = portptr ;
        servoptr -> pin = pinno ;
        servoptr -> serIndex =servocounter;
        setServoAngle(servoptr,0);
        servoCounter++;
        if (servoCounter<2)
        {
            InitTimer1AndCompare(void);
            T1CON.TMR1ON = 1;
            PIE1.TMR1IE         = 1;
            PIE1.CCP1IE  =1;
            INTCON.PEIE=1;
            INTCON.GIE=1;
        }
    }
}
//deattach servo
void deattachServo( NEWSERVO* servoptr )
{
   if(servoCounter>0)
   {
     serviceServoArray[(servoptr -> serIndex)]= serviceServoArray[(servoCounter-1)];
     servoCounter--;
     if (servoCounter==0)
     {
         //disable Interrupt
         PIE1.TMR1IE  = 0;
         PIE1.CCP1IE  =0;
     }
   }
}