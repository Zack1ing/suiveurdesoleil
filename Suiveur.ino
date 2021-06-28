//01000101 01001110 01001100
#include <Servo.h>
//déclaration des moteur vertical et horizontal
Servo servohorizontal; //servohori
int servoh = 0;
int servohLimitHigh = 160;
int servohLimitLow = 60;

Servo servovertical; //servoverti
int servov = 0; 
int servovLimitHigh = 160;
int servovLimitLow = 60;
//les entres PIN des Photorésistance
int ldrtopl = 2; // haut gauch 
int ldrtopr = 1; // haut droit
int ldrbotl = 3; // bas gauch 
int ldrbotr = 0; // bas droit 

 void setup () 
 {
  servohorizontal.attach(10); // relais le servo moteur 1 sur le pin 10
  servohorizontal.write(60); // l'angle par defaut 60°
  servovertical.attach(9);  // relais le servo moteur 2 sur le pin 9
  servovertical.write(60); // l'angle par defaut 60°
  Serial.begin(9600);
  delay(500);
  
 }

void loop()
{
  servoh = servohorizontal.read();
  servov = servovertical.read();
  // les Valeur analogique de la photorésistance
  int topl = analogRead(ldrtopl);
  int topr = analogRead(ldrtopr);
  int botl = analogRead(ldrbotl);
  int botr = analogRead(ldrbotr);
  // Calcule de la valeur moyenne
  int avgtop = (topl + topr) ; //average of top 
  int avgbot = (botl + botr) ; //average of bottom 
  int avgleft = (topl + botl) ; //average of left 
  int avgright = (topr + botr) ; //average of right 

  if (avgtop < avgbot)
  {
    servovertical.write(servov +1);
    if (servov > servovLimitHigh) 
     { 
      servov = servovLimitHigh;
     }
    delay(10);
  }
  else if (avgbot < avgtop)
  {
    servovertical.write(servov -1);
    if (servov < servovLimitLow)
  {
    servov = servovLimitLow;
  }
    delay(10);
  }
  else 
  {
    servovertical.write(servov);
  }
  
  if (avgleft > avgright)
  {
    servohorizontal.write(servoh +1);
    if (servoh > servohLimitHigh)
    {
    servoh = servohLimitHigh;
    }
    delay(10);
  }
  else if (avgright > avgleft)
  {
    servohorizontal.write(servoh -1);
    if (servoh < servohLimitLow)
     {
     servoh = servohLimitLow;
     }
    delay(10);
  }
  else 
  {
    servohorizontal.write(servoh);
  }
  delay(50);
}
