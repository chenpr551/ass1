#include <HCSR04.h>
#include "Arduino_LED_Matrix.h"  
#include "idle.h"
#include "animationTest.h"
#include "animation3.h"
#include "animation.h"
#include "coin.h"
#include "loading.h"
#include "plane.h"
#include "fail1.h"
#include "fail2.h"

byte triggerPin = 14; 
byte echoPin = 15;    


UltraSonicDistanceSensor distanceSensor(triggerPin, echoPin);



unsigned long lastRead = 0;
int rate = 30;             


float distanceMeasured;

float changeThreshold = 4;


int currentState = 0;
int previousState = 1;


ArduinoLEDMatrix ledScreen;  
boolean loopAnimation = true;


void setup () 
{
    Serial.begin(9600); 
    ledScreen.begin();
}

void loop () 
{
   readDistanceSensor();

  if((currentState==1)&&(previousState!=1))
  {
    ledScreen.loadSequence(loading);
        ledScreen.play(loopAnimation);
        
        
        delay(1500);
    int randomAnimation = random(1, 4);
    switch (randomAnimation) {
      case 1:
        ledScreen.loadSequence(fail1);
        break;
      case 2:
        ledScreen.loadSequence(plane);
        break;
      case 3:
        ledScreen.loadSequence(fail2);
        break;
      default:
      
        break;
    }
    ledScreen.play(loopAnimation);
  }
 
  if((currentState==0)&&(previousState!=0))
  {
    ledScreen.loadSequence(coin);
    ledScreen.play(loopAnimation);
  }

previousState = currentState;
}




void readDistanceSensor()
{
      unsigned long currentTime = millis(); 
 
  
    if((currentTime - lastRead) >= rate) 
    {
        lastRead = currentTime;
        distanceMeasured = distanceSensor.measureDistanceCm(); 
        Serial.println(distanceMeasured);
        if(distanceMeasured<=changeThreshold)
        {
          currentState = 1;
        }
        else
        {
          currentState = 0;
        }
      Serial.print(distanceMeasured); 
      Serial.print("\t");
      Serial.print("state : ");
      Serial.println(currentState);

    }
  
}

