/*
OmniSol Solar Tracker
OMNi Technologies
Designed and fabricated by Om Anavekar
Made in the USA
9/12/18
*/

#include <Servo.h> // Servo library

// Fully Qualified Board Name


//Servos
Servo trackerLR;  // Create servo object for left/right movement servo 
Servo trackerTB;  // Create servo object for top/bottom movement servo 

//Photoresistor Pins
int photo_top_left = A0;  //Analog pins for photoresistors
int photo_top_right = A1;
int photo_bottom_left = A2;
int photo_bottom_right = A3;


//Photoresistors
int ldr_top_left = 0;  //Variables for the sensor values
int ldr_top_right = 0;
int ldr_bottom_left = 0;
int ldr_bottom_right = 0;    //Not a real sensor. This will be the average of right and left photoresistors.

int ldr_top = 0;
int ldr_bottom = 0;

//Differences between right/left and top/bottom photoresistors
int horizontalError = 0;
int verticalError = 0;

int trackerLRPos = 90;    //Create a variable to store the servo position
int trackerTBPos = 90;

void setup() 
{ 
 //Servo pins
 trackerLR.attach(9);  
 trackerTB.attach(10);

}
 
void loop() 
{ 
  //Values of the right and left sensors
  ldr_top_right = analogRead(ldr_top_right);    
  ldr_top_left = analogRead(ldr_top_left);
  
  horizontalError = ldr_top_right - ldr_top_left;  //Difference between the two sensors.
  
  if(horizontalError>20)  //If the error is greater than 20 then move the tracker to the right
  {
      trackerLRPos--;
      trackerLRPos = constrain (trackerLRPos, 0,179);
      trackerLR.write(trackerLRPos);  
  }
  
  else if(horizontalError<-20)  //If the error is less than -20 then move the tracker to the left
  {
      trackerLRPos++;
      trackerLRPos = constrain (trackerLRPos, 0,179 );
      trackerLR.write(trackerLRPos);  
  }

  //Values of the bottom and top sensors 
  ldr_top = (ldr_top_left + ldr_top_right)/2; //Average value of TOP- right and left sensors
  ldr_bottom = (ldr_bottom_left + ldr_bottom_right)/2;//Average value of BOTTOM- right and left sensors

  verticalError = ldr_top - ldr_bottom; //Difference between top and bottom readings
  
  if(verticalError>50)  //If the error is greater than 50 then move the tracker up
  {
      trackerTBPos++;
      trackerTBPos = constrain (trackerTBPos, 10,120);
      trackerTB.write(trackerTBPos);  
  }
  
  else if(verticalError<-50)  //If the error is less than -50 then move the tracker down
  {
      trackerTBPos--;
      trackerTBPos = constrain (trackerTBPos, 10,120);
      trackerTB.write(trackerTBPos); 
  }
  delay(25);
}
