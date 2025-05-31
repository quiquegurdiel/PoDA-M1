#include "IRremote.h"
int RECV_PIN = 12; // Signal Pin of IR receiver to Arduino Digital Pin 6
IRrecv irrecv(RECV_PIN);    // create instance of 'irrecv'
decode_results results;     // create instance of 'decode_results'

void setup() {
  // put your setup code here, to run once:
  irrecv.enableIRIn(); // Start the receiver
  Serial.begin(9600);
  Serial.print("*****************GET RECEIVER CODING*****************");

}

void loop()
{
  // put your main code here, to run repeatedly:
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    Serial.print("Button");
    Serial.print('\n');
    Serial.println(results.value, HEX);
    Serial.print('\n');
    irrecv.resume(); // receive the next value
  }
}
