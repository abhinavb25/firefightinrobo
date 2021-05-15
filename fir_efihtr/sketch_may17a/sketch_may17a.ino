/*------ Arduino Fire Fighting Robot Code----- */
#include <SoftwareSerial.h>
#include <Servo.h>
Servo myservo;
SoftwareSerial sim(10, 11); 
String number = "+918800198206"; // +880 is the country code
 
int pos = 0;    
boolean fire = false;
 
/*-------defining Inputs------*/
#define Left_S 9      // left sensor
#define Right_S 13      // right sensor
#define Forward_S 8 //forward sensor
 
/*-------defining Outputs------*/
#define LM1 2       // left motor
#define LM2 3       // left motor
#define RM1 4       // right motor
#define RM2 5       // right motor
#define pum1 6
#define pum2 7
 
void setup()
{
  pinMode(Left_S, INPUT);
  pinMode(Right_S, INPUT);
  pinMode(Forward_S, INPUT);
  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pum1, OUTPUT);
  pinMode(pum2, OUTPUT);
  myservo.attach(12);
  myservo.write(90); 
}
 
void put_off_fire()
{
    delay (500);
    SendMessage();
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, HIGH);
    digitalWrite(pum2,LOW);
   digitalWrite(pum1, HIGH); delay(700);
    
    for (pos = 50; pos <= 130; pos += 1) { 
    myservo.write(pos); 
    delay(10);  
  }
  for (pos = 130; pos >= 50; pos -= 1) { 
    myservo.write(pos); 
    delay(10);
  }
  
  digitalWrite(pum1,LOW);
  digitalWrite(pum2,LOW);
  myservo.write(90);
  
  fire=false;
}
 
void loop()
{  
   myservo.write(90); //Sweep_Servo();  
 
    if (digitalRead(Left_S) ==1 && digitalRead(Right_S)==1 && digitalRead(Forward_S) ==1) //If Fire not detected all sensors are zero
    {
    //Do not move the robot
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
    
    else if (digitalRead(Forward_S) ==0) //If Fire is straight ahead
    {
    //Move the robot forward
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    fire = true;
    }
    
    else if (digitalRead(Left_S) ==0) //If Fire is to the left
    {
    //Move the robot left
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, HIGH);
    }
    
    else if (digitalRead(Right_S) ==0) //If Fire is to the right
    {
    //Move the robot right
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, HIGH);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    }
    
delay(700); //Slow down the speed of robot
 
     while (fire == true)
     {
      put_off_fire();
     }
}
void SendMessage()
{
  sim.println("AT+CMGF=1");
  delay(1000);
  sim.println("AT+CMGS=\"" + number + "\"\r");
  delay(1000);
  String SMS = "FIRE DETECTED";
  sim.println(SMS);
  delay(100);
  sim.println((char)26);
  delay(1000);
}
