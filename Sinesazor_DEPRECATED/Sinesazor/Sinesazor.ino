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
  { 
    switch(results.value)
    {

      case 0xFFA857: // VOL- button pressed
                      Serial.print("BUTTON: -");
                      Serial.print('\n');                      

                      Serial.print("4");
                      Serial.print('\n');
                      small_stepper.setSpeed(4); //RPM
                      Steps2Take  =  3910;  // Rotate CW
                      small_stepper.step(Steps2Take);
                      delay(2);
                      
                      break;

      case 0xFF629D: // VOL+ button pressed
                      Serial.print("BUTTON: +");
                      Serial.print('\n');

                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(2000);
                      small_stepper.setSpeed(1.2305);
                      small_stepper.step(302);
                      small_stepper.setSpeed(1.9634);
                      small_stepper.step(482);
                      small_stepper.setSpeed(1.5934);
                      small_stepper.step(391);
                      small_stepper.setSpeed(1.7798);
                      small_stepper.step(437);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-171);
                      delay(603);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(5);
                      delay(1962);
                      small_stepper.setSpeed(1.2680);
                      small_stepper.step(-311);
                      small_stepper.setSpeed(3.7447);
                      small_stepper.step(-920);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-207);
                      delay(317);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(181);
                      delay(523);
                      small_stepper.setSpeed(2.6557);
                      small_stepper.step(652);
                      small_stepper.setSpeed(1.6302);
                      small_stepper.step(400);
                      small_stepper.setSpeed(1.2568);
                      small_stepper.step(309);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(214);
                      delay(261);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-167);
                      delay(637);
                      small_stepper.setSpeed(1.2145);
                      small_stepper.step(-298);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-145);
                      delay(823);
                      small_stepper.setSpeed(1.3885);
                      small_stepper.step(-341);
                      small_stepper.setSpeed(1.1660);
                      small_stepper.step(-286);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(58);
                      delay(1530);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(22);
                      delay(1818);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(43);
                      delay(1648);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(118);
                      delay(1038);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-244);
                      delay(11);
                      small_stepper.setSpeed(2.0559);
                      small_stepper.step(-505);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-14);
                      delay(1884);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1999);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1996);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1995);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-1);
                      delay(1994);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-1);
                      delay(1994);
                      small_stepper.setSpeed(1.4665);
                      small_stepper.step(360);
                      small_stepper.setSpeed(2.6952);
                      small_stepper.step(662);
                      small_stepper.setSpeed(1.0498);
                      small_stepper.step(258);
                      small_stepper.setSpeed(1.1831);
                      small_stepper.step(-291);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-238);
                      delay(65);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(71);
                      delay(1418);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-107);
                      delay(1131);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-51);
                      delay(1582);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(60);
                      delay(1511);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(20);
                      delay(1838);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-98);
                      delay(1199);
                      small_stepper.setSpeed(1.6719);
                      small_stepper.step(-411);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-235);
                      delay(89);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1997);
                      small_stepper.setSpeed(1.8815);
                      small_stepper.step(462);
                      small_stepper.setSpeed(1.5871);
                      small_stepper.step(390);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-72);
                      delay(1413);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-223);
                      delay(184);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-99);
                      delay(1195);
                      small_stepper.setSpeed(1.2883);
                      small_stepper.step(316);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(111);
                      delay(1095);
                      small_stepper.setSpeed(1.1055);
                      small_stepper.step(-272);
                      small_stepper.setSpeed(1.1591);
                      small_stepper.step(-285);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-184);
                      delay(504);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-117);
                      delay(1046);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(176);
                      delay(571);
                      small_stepper.setSpeed(1.6838);
                      small_stepper.step(414);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(149);
                      delay(789);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-226);
                      delay(157);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-212);
                      delay(276);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(75);
                      delay(1390);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-117);
                      delay(1048);
                      small_stepper.setSpeed(1.0690);
                      small_stepper.step(-263);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-24);
                      delay(1803);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1993);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-1);
                      delay(1995);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-2);
                      delay(1986);
                      small_stepper.setSpeed(1.1487);
                      small_stepper.step(282);
                      small_stepper.setSpeed(2.7774);
                      small_stepper.step(682);
                      small_stepper.setSpeed(1.0874);
                      small_stepper.step(267);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-215);
                      delay(247);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-240);
                      delay(47);
                      small_stepper.setSpeed(1.2608);
                      small_stepper.step(-310);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-91);
                      delay(1262);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-10);
                      delay(1921);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-197);
                      delay(396);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-146);
                      delay(809);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(7);
                      delay(1942);
                      small_stepper.setSpeed(1.2209);
                      small_stepper.step(300);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(228);
                      delay(143);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-31);
                      delay(1747);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-204);
                      delay(342);
                      small_stepper.setSpeed(1.0958);
                      small_stepper.step(-269);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-41);
                      delay(1667);
                      small_stepper.setSpeed(1.7793);
                      small_stepper.step(437);
                      small_stepper.setSpeed(1.5755);
                      small_stepper.step(387);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(189);
                      delay(461);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-132);
                      delay(922);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-140);
                      delay(861);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-62);
                      delay(1494);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-235);
                      delay(89);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(101);
                      delay(1181);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-2);
                      delay(1987);
                      small_stepper.setSpeed(1.0362);
                      small_stepper.step(-255);
                      small_stepper.setSpeed(1.0119);
                      small_stepper.step(-249);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-51);
                      delay(1587);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(167);
                      delay(643);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(120);
                      delay(1021);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-40);
                      delay(1675);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(4);
                      delay(1964);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(45);
                      delay(1631);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-120);
                      delay(1026);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-174);
                      delay(586);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-4);
                      delay(1966);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1992);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-1);
                      delay(1994);
                      small_stepper.setSpeed(1.0910);
                      small_stepper.step(268);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(237);
                      delay(67);
                      small_stepper.setSpeed(1.3093);
                      small_stepper.step(322);
                      small_stepper.setSpeed(1.5576);
                      small_stepper.step(383);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(86);
                      delay(1300);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-4);
                      delay(1969);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-227);
                      delay(150);
                      small_stepper.setSpeed(1.1597);
                      small_stepper.step(-285);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-121);
                      delay(1019);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-228);
                      delay(144);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-157);
                      delay(719);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-97);
                      delay(1213);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-172);
                      delay(603);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-7);
                      delay(1939);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1997);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1994);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1998);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-1);
                      delay(1994);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(156);
                      delay(728);
                      small_stepper.setSpeed(1.3875);
                      small_stepper.step(341);
                      small_stepper.setSpeed(1.3378);
                      small_stepper.step(329);
                      small_stepper.setSpeed(1.0566);
                      small_stepper.step(-260);
                      small_stepper.setSpeed(1.9758);
                      small_stepper.step(-485);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-77);
                      delay(1371);
                      small_stepper.setSpeed(1.8091);
                      small_stepper.step(444);
                      small_stepper.setSpeed(3.6271);
                      small_stepper.step(891);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-141);
                      delay(855);
                      small_stepper.setSpeed(2.0454);
                      small_stepper.step(-502);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(64);
                      delay(1480);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-125);
                      delay(978);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(104);
                      delay(1155);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-205);
                      delay(333);
                      small_stepper.setSpeed(1.9152);
                      small_stepper.step(-470);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-62);
                      delay(1499);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(94);
                      delay(1234);
                      small_stepper.setSpeed(2.1150);
                      small_stepper.step(519);
                      small_stepper.setSpeed(1.2367);
                      small_stepper.step(304);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(230);
                      delay(130);
                      small_stepper.setSpeed(2.9549);
                      small_stepper.step(726);
                      small_stepper.setSpeed(1.8946);
                      small_stepper.step(-465);
                      small_stepper.setSpeed(2.4963);
                      small_stepper.step(-613);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(96);
                      delay(1217);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(86);
                      delay(1299);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-79);
                      delay(1355);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-192);
                      delay(435);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-223);
                      delay(181);
                      small_stepper.setSpeed(1.0146);
                      small_stepper.step(-249);
                      small_stepper.setSpeed(1.6395);
                      small_stepper.step(403);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(131);
                      delay(930);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-195);
                      delay(415);
                      small_stepper.setSpeed(1.1301);
                      small_stepper.step(-278);
                      small_stepper.setSpeed(1.1558);
                      small_stepper.step(-284);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(85);
                      delay(1306);
                      small_stepper.setSpeed(2.9040);
                      small_stepper.step(713);
                      small_stepper.setSpeed(1.6319);
                      small_stepper.step(401);
                      small_stepper.setSpeed(1.9568);
                      small_stepper.step(-481);
                      small_stepper.setSpeed(1.1144);
                      small_stepper.step(274);
                      small_stepper.setSpeed(1.2771);
                      small_stepper.step(314);
                      small_stepper.setSpeed(2.2630);
                      small_stepper.step(-556);
                      small_stepper.setSpeed(1.2380);
                      small_stepper.step(-304);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-40);
                      delay(1674);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-79);
                      delay(1354);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(202);
                      delay(354);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-54);
                      delay(1562);
                      small_stepper.setSpeed(1.5258);
                      small_stepper.step(-375);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-111);
                      delay(1099);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-1);
                      delay(1996);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(2000);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1995);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(7);
                      delay(1942);
                      small_stepper.setSpeed(2.5704);
                      small_stepper.step(631);
                      small_stepper.setSpeed(3.8248);
                      small_stepper.step(939);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-69);
                      delay(1440);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-122);
                      delay(1007);
                      small_stepper.setSpeed(1.0525);
                      small_stepper.step(-259);
                      small_stepper.setSpeed(2.7382);
                      small_stepper.step(-673);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(46);
                      delay(1626);
                      small_stepper.setSpeed(1.1338);
                      small_stepper.step(278);
                      small_stepper.setSpeed(1.3114);
                      small_stepper.step(322);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-50);
                      delay(1596);
                      small_stepper.setSpeed(2.6093);
                      small_stepper.step(-641);
                      small_stepper.setSpeed(1.5434);
                      small_stepper.step(-379);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-30);
                      delay(1758);
                      small_stepper.setSpeed(2.0068);
                      small_stepper.step(493);
                      small_stepper.setSpeed(1.4885);
                      small_stepper.step(366);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-85);
                      delay(1309);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(170);
                      delay(612);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-82);
                      delay(1333);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-44);
                      delay(1642);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-138);
                      delay(876);
                      small_stepper.setSpeed(1.9449);
                      small_stepper.step(-478);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-188);
                      delay(466);
                      small_stepper.setSpeed(1.7656);
                      small_stepper.step(434);
                      small_stepper.setSpeed(2.3482);
                      small_stepper.step(577);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(16);
                      delay(1869);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-22);
                      delay(1821);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-199);
                      delay(380);
                      small_stepper.setSpeed(1.6329);
                      small_stepper.step(-401);
                      small_stepper.setSpeed(1.0346);
                      small_stepper.step(254);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(239);
                      delay(58);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-245);
                      delay(1);
                      small_stepper.setSpeed(1.0086);
                      small_stepper.step(-248);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(2);
                      delay(1986);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-143);
                      delay(832);
                      small_stepper.setSpeed(1.1180);
                      small_stepper.step(-275);
                      small_stepper.setSpeed(1.1312);
                      small_stepper.step(278);
                      small_stepper.setSpeed(1.6717);
                      small_stepper.step(411);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-68);
                      delay(1447);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(23);
                      delay(1817);
                      small_stepper.setSpeed(1.0488);
                      small_stepper.step(258);
                      small_stepper.setSpeed(1.0525);
                      small_stepper.step(-259);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-152);
                      delay(765);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(38);
                      delay(1689);
                      small_stepper.setSpeed(1.2670);
                      small_stepper.step(-311);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-213);
                      delay(268);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-6);
                      delay(1948);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(87);
                      delay(1293);
                      small_stepper.setSpeed(2.4058);
                      small_stepper.step(591);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(129);
                      delay(947);
                      small_stepper.setSpeed(2.4097);
                      small_stepper.step(-592);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-3);
                      delay(1972);
                      small_stepper.setSpeed(1.8057);
                      small_stepper.step(443);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(124);
                      delay(992);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-226);
                      delay(161);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(242);
                      delay(27);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-109);
                      delay(1115);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-43);
                      delay(1648);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(83);
                      delay(1327);
                      small_stepper.setSpeed(1.0865);
                      small_stepper.step(-267);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-69);
                      delay(1440);
                      small_stepper.setSpeed(1.0971);
                      small_stepper.step(-269);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-53);
                      delay(1569);
                      small_stepper.setSpeed(1.3579);
                      small_stepper.step(334);
                      small_stepper.setSpeed(1.2099);
                      small_stepper.step(297);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(2);
                      delay(1987);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-119);
                      delay(1030);
                      small_stepper.setSpeed(1.0973);
                      small_stepper.step(-270);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-244);
                      delay(12);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-68);
                      delay(1444);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-4);
                      delay(1965);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1999);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1994);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1998);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-1);
                      delay(1992);
                      small_stepper.setSpeed(1.0917);
                      small_stepper.step(268);
                      small_stepper.setSpeed(2.5177);
                      small_stepper.step(618);
                      small_stepper.setSpeed(1.2608);
                      small_stepper.step(310);
                      small_stepper.setSpeed(1.8297);
                      small_stepper.step(-449);
                      small_stepper.setSpeed(1.5972);
                      small_stepper.step(-392);
                      small_stepper.setSpeed(1.0882);
                      small_stepper.step(267);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(51);
                      delay(1588);
                      small_stepper.setSpeed(1.2698);
                      small_stepper.step(-312);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-236);
                      delay(81);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-124);
                      delay(990);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1999);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1990);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(1);
                      delay(1994);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-2);
                      delay(1985);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(242);
                      delay(25);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(207);
                      delay(312);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(177);
                      delay(562);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-131);
                      delay(932);
                      small_stepper.setSpeed(1.7030);
                      small_stepper.step(-418);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-76);
                      delay(1381);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(5);
                      delay(1959);
                      small_stepper.setSpeed(1.0452);
                      small_stepper.step(257);
                      small_stepper.setSpeed(1.5417);
                      small_stepper.step(379);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-68);
                      delay(1448);
                      small_stepper.setSpeed(1.3966);
                      small_stepper.step(-343);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-188);
                      delay(465);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-42);
                      delay(1655);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-3);
                      delay(1978);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(-3);
                      delay(1975);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(1999);
                      small_stepper.setSpeed(1.0000);
                      small_stepper.step(0);
                      delay(2000);
                      small_stepper.setSpeed(2.9998);
                      small_stepper.step(0);
                      
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
                      for (int i =1; i<n+2; i++){
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
    //Serial.print(results.value, HEX);
    //Serial.print('\n');
    irrecv.resume(); // receive the next value
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
    digitalWrite(11, LOW);       
  }
}/* --end main loop -- */
