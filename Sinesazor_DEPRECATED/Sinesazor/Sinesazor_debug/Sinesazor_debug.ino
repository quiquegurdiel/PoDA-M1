//www.elegoo.com
//2016.12.12

#include "Stepper.h"
#include "IRremote.h"
#include <math.h>    // (no semicolon)

/*----- Variables, Pins -----*/
double stepsRatio = 1.137 * 3.2;   // Correction (ojo 1.32) * Diameter objective (58mm) / diameter motor (1.8mm) 

#define STEPS  round(2048*stepsRatio)   // Number of steps per revolution of Internal shaft
int  Steps2Take;  // STEPS -> 1 Revolution
int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 6
double mySpeed = 15/stepsRatio; //Maximum safe speed
int n = 30; //Number of divisions of the 90º boundaries

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4

Stepper small_stepper(STEPS, 8, 10, 9, 11);
IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
  Serial.print("**********SINESAZOR**********");
  Serial.print('\n');
  Serial.print('\n');
  Serial.print("RUNNING");
  Serial.print('\n');
  Serial.print("EFFECTIVE STEPS: ");
  Serial.print(STEPS);
  Serial.print('\n');
  Serial.print("*****************************");
  Serial.print('\n');
}

void loop()
{
if (irrecv.decode(&results)) // have we received an IR signal?
  Serial.print(results.value);
  {
    switch(results.value)

    {

      case 0xFFA857: // VOL- button pressed
                      Serial.print("BUTTON: -");
                      Serial.print('\n');                      
                      
                      break;

      case 0xFF629D: // VOL+ button pressed
                      Serial.print("BUTTON: +");
                      Serial.print('\n');

                      small_stepper.setSpeed(mySpeed);
                      Steps2Take  =  -STEPS;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      delay(20); 
                      break;

      case 0xFF906F: // UP button pressed
                      Serial.print("BUTTON: up");
                      Serial.print('\n');

                      small_stepper.setSpeed(mySpeed);
                      Steps2Take  =  -20;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      delay(2); 
                      break;
                      
      case 0xFFE01F: // DOWN button pressed
                      Serial.print("BUTTON: down");
                      Serial.print('\n');

                      small_stepper.setSpeed(mySpeed);
                      Steps2Take  =  20;  // Rotate CCW
                      small_stepper.step(Steps2Take);
                      delay(2); 
                      break;

       case 0xFF9867: // EQ button pressed
                      Serial.print("BUTTON: EQ");
                      Serial.print('\n');
                      //**************************************************************
                      Serial.print("...calculating trajectory...");
                      Serial.print('\n');
                      double x[n+1];
                      double ang[n+1];
                      double v[n];
                      for (int i=1; i<n+2; i++){
                          x[i]=1/double(n)*(i-1);
                                                Serial.print(i);
                          ang[i]=acos(pow(x[i],3))/acos(double(0)); // angle normalised in the interval
                          if (i>1){
                            v[i-1]=ang[i-1]-ang[i];
                          }
                      }
                                                Serial.print('\n');                                                 
                                                Serial.print(x[n+1]);
                                                Serial.print("*****");                                                                      
                                                Serial.print(ang[n+1]);
                                                Serial.print("*****");
                                                Serial.print(v[n]);                                                                      
                      Serial.print("...starting movement...");
                      Serial.print('\n');
                      
                      //**************************************************************
                      Serial.print("  ...position to zero...");
                      Serial.print('\n');
                      small_stepper.setSpeed(mySpeed); //RPM
                      Steps2Take  =  round(-STEPS/4);  // Rotate CW
                      small_stepper.step(Steps2Take);
                      delay(200); 
                      
                      Serial.print("  ...0 to 90...");
                      double thisSpeed;
                      Serial.print('\n');
                      for(int i=1; i<n+1; i++){
                        //small_stepper.setSpeed(mySpeed);
                          thisSpeed=2*mySpeed*v[i]/v[n];
                          if (thisSpeed<1){
                            thisSpeed= 1;
                          }
                          small_stepper.setSpeed(thisSpeed); //RPM
                          Steps2Take  =  round((STEPS/4)*v[i]);  // Rotate CW
                                                 Serial.print('\n');
                                                 Serial.print(thisSpeed);
                                                 Serial.print('\n');                                                 
                                                 Serial.print(i);
                                                 Serial.print("*****");
                                                 Serial.print(STEPS/4);
                                                 Serial.print("*****");
                                                 Serial.print(v[i]);
                                                 Serial.print("*****");
                                                 Serial.print(Steps2Take);   
                          small_stepper.step(Steps2Take);
                      }
                                            
                      //**************************************************************
                      Serial.print("  ...90 to 180...");
                      Serial.print('\n');
                      for(int i=n; i>0; i--){
                          thisSpeed=2*mySpeed*v[i]/v[n];
                          if (thisSpeed<1){
                            thisSpeed= 1;
                          }
                          small_stepper.setSpeed(thisSpeed); //RPM
                          Steps2Take  =  round(STEPS/4*v[i]);  // Rotate CW
                          small_stepper.step(Steps2Take);
                      }

                      //**************************************************************
                      Serial.print("  ...180 to 270...");
                      Serial.print('\n');
                      for(int i=1; i<n+1; i++){
                          thisSpeed=2*mySpeed*v[i]/v[n];
                          if (thisSpeed<1){
                            thisSpeed= 1;
                          }
                          small_stepper.setSpeed(thisSpeed); //RPM
                          Steps2Take  =  round(STEPS/4*v[i]);  // Rotate CW
                          small_stepper.step(Steps2Take);
                      }

                      //**************************************************************
                      Serial.print("  ...270 to 0...");
                      Serial.print('\n');
                      for(int i=n; i>0; i--){
                          thisSpeed=2*mySpeed*v[i]/v[n];
                          if (thisSpeed<1){
                            thisSpeed= 1;
                          }
                          small_stepper.setSpeed(thisSpeed); //RPM
                          Steps2Take  =  round(STEPS/4*v[i]);  // Rotate CW
                          small_stepper.step(Steps2Take);
                      }
                      break;
    }
    
      irrecv.resume(); // receive the next value
                 digitalWrite(8, LOW);
                 digitalWrite(9, LOW);
                 digitalWrite(10, LOW);
                 digitalWrite(11, LOW);       
  }  


}/* --end main loop -- */
