//@quiquegurdiel - 2025

#include <Stepper.h>

/*----- Variables, Pins -----*/
const int steps = 2048;   // Number of steps per revolution of Internal shaft
int button = 7;

/*-----( Declare objects )-----*/
// Setup of proper sequencing for Motor Driver Pins
// In1, In2, In3, In4 in the sequence 1-3-2-4
Stepper small_stepper(steps, 8, 10, 9, 11);

void setup()
{
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.print('\n');
  Serial.print("*****************************");
  Serial.print("*****************************");
  Serial.print('\n');
  Serial.print("*****************************");
  Serial.print("***********PoDA-M0***********");
  Serial.print('\n');
  Serial.print('\n');
  Serial.print("Step equivalent: ");
  Serial.print(0.1723);
  Serial.print('\n');
  Serial.print('\n');
  Serial.print("Input speed equivalent: ");
  Serial.print(5.954);
  Serial.print('\n');
  Serial.print('\n');
  Serial.print("*****************************");
  Serial.print("********up and running*******");
  Serial.print('\n');
  Serial.print("*****************************");
  Serial.print("*****************************");
  Serial.print('\n');
  Serial.print('\n');
}

void loop()
{
  if (digitalRead(button) == LOW)
  {
    Serial.print('\n');
    Serial.print("start of instructions");
    //************************************************************
    //************************************************************
    
          //Steps calibration
          delay(50);
          small_stepper.setSpeed(4);
          small_stepper.step(1800);
          small_stepper.step(-1800);
          small_stepper.step(1800);
          small_stepper.step(-1800);
          small_stepper.step(1800);
          small_stepper.step(-1800);
          small_stepper.step(1800);
          small_stepper.step(-1800);
          small_stepper.step(1800);
          small_stepper.step(-1800);

    //************************************************************
    //************************************************************
    Serial.print('\n');
    Serial.print("end of instructions");
  }

    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW); 
}
