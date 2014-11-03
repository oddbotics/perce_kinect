#include <Herkulex.h>
int n=1; //motor ID - verify your ID !!!!

void setup()  
{
  delay(2000);  //a delay to have time for serial monitor opening
  Serial.begin(115200);    // Open serial communications
  Serial.println("Begin E");
  Herkulex.beginSerial2(115200); //open serial port 1 
  Herkulex.reboot(n); //reboot first motor
  Herkulex.reboot(2); //reboot first motor
  delay(500); 
  Herkulex.initialize(); //initialize motors
  delay(200);  
}

void loop(){
  Serial.println("Move Angle: -100 degrees");
  Herkulex.moveOneAngle(n, -100, 1000, LED_BLUE); //move motor with 300 speed  
  Herkulex.moveOneAngle(2, -100, 1000, LED_GREEN);
  delay(2200);
  Serial.print("Get servo Angle:");
  Serial.println(Herkulex.getAngle(n));
  Serial.println("Move Angle: 100 degrees");
  Herkulex.moveOneAngle(n, 100, 1000, LED_BLUE); //move motor with 300 speed  
  delay(2200);
  Serial.print("Get servo Angle:");
  Serial.println(Herkulex.getAngle(n));
  
}


