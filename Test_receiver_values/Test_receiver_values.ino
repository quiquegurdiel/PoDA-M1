#include "IRremote.h"
#include <math.h>    // (no semicolon)

int receiver = 12; // Signal Pin of IR receiver to Arduino Digital Pin 6

IRrecv irrecv(receiver);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup()
{ 
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
  Serial.print("**********PoDA-M**********");
  Serial.print('\n');
  Serial.print('\n');
  Serial.print("test receiver values");
  Serial.print('\n');
  Serial.print('\n');
  Serial.print("*****************************");
  Serial.print('\n');
}

void loop()
{
if (irrecv.decode(&results)) // have we received an IR signal?
  { 
    Serial.print(results.value,HEX);
    Serial.print('\n');
    switch(results.value)
    {
      case 0x511DBB:
          Serial.print("VOL +");
          Serial.print('\n');
          
          break;
          
          case 0xF076C13B:
          Serial.print("DOWN");
          Serial.print('\n');
          
          break;
          
      case 0x5E19BBC7:
          Serial.print("UP");
          Serial.print('\n');
          
          break;

      case 0xFA19A1C1:
          Serial.print("1");
          Serial.print('\n');
          
          break;

      case 0x6182021B:
          Serial.print("3");
          Serial.print('\n');
          
          break;
          
    }
    irrecv.resume(); // receive the next value
  }
}
