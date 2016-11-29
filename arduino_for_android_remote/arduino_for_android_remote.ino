/*
 * Projekt Arduino wykonany przez 
 * Mateusza Osiak 
 * do Pracy Inżynierskiej
 */
#include <NewPing.h>
#define TRIGGER_PIN  6
#define ECHO_PIN     5
#define MAX_DISTANCE 400 

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

const int pinA1=13;//I1
const int pinA2=8;//I2
const int speedpinA=11;//EA(PWM)to control the motor_1 speed

const int pinB1=12;//I3
const int pinB2=9;//I4
const int speedpinB=3;//EB(PWM]) to control the motor_2 speed
const int limit = 15;


void setup() {  
  Serial.begin(9600);
   for(int i=8;i<14;i++)
    pinMode(i,OUTPUT); 
}

void loop() {
  robot();
  sensor();
}
void sensor(){
  unsigned int uS = sonar.ping(); 
  unsigned int odleglosc = (uS / US_ROUNDTRIP_CM);
  delay(500);
  Serial.print(odleglosc); 
  Serial.println("cm");

  if( odleglosc < limit) {
      digitalWrite(pinA1,LOW );
      digitalWrite(pinA2,HIGH);
      
      digitalWrite(pinB1,HIGH);
      digitalWrite(pinB2,LOW);
      
      analogWrite(speedpinA,0);
      analogWrite(speedpinB,0);
    }
}
void robot(){
 if (Serial.available() > 0) {
    // read the oldest byte in the serial buffer:
    int incomingByte = Serial.read();

    switch (incomingByte) {
      case 'F':
         moveForward("F");
        break;
      case 'R':
        turn("R");
        break;
      case 'L':
        turn("L");
        break;
      case 'D':
         moveForward("D");
        break;
      case 'S':
        moveForward("S");
        break;
      default: 
        // if nothing matches, do nothing
        break;
    } 
  }
  }
void moveForward(String move){
     if (move=="F"){
        analogWrite(speedpinA,150);
        analogWrite(speedpinB,130);

        digitalWrite(pinA1,LOW);
        digitalWrite(pinA2,LOW);
        digitalWrite(pinB1,LOW);
        digitalWrite(pinB2,LOW);
    }
    
    else if (move=="D") {
        digitalWrite(pinA1,HIGH);
        digitalWrite(pinA2,LOW);
        digitalWrite(pinB1,HIGH);
        digitalWrite(pinB2,LOW);
        analogWrite(speedpinA,150);
         analogWrite(speedpinB,130);
    }
    else {
          digitalWrite(pinA1,LOW );
          digitalWrite(pinA2,HIGH);

          digitalWrite(pinB1,HIGH);
          digitalWrite(pinB2,LOW);
          analogWrite(speedpinA,0);
          analogWrite(speedpinB,0);
          }

}

void turn(String right){
  //boolean right controls motor direction
    if (right=="R"){
        digitalWrite(pinA1,HIGH);
        digitalWrite(pinA2,LOW);
        digitalWrite(pinB1,LOW);
        digitalWrite(pinB2,LOW);
    }
    else{
       digitalWrite(pinA1,LOW);
       digitalWrite(pinA2,LOW);
       digitalWrite(pinB1,HIGH);
      digitalWrite(pinB2,LOW);
    }
     analogWrite(speedpinA,150);
  analogWrite(speedpinB,130);
}

