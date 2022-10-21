#include <SPI.h>
#include <RFID.h>
#define SS_PIN 10
#define RST_PIN A6
RFID rfid(SS_PIN, RST_PIN);
String rfidCard;
#define LF A0
#define LR A2
#define RF A4
#define RR A5
char t;
bool status_=true;
 
void setup() {
  pinMode(3,OUTPUT);
   pinMode(5,OUTPUT);
pinMode(A0,OUTPUT);   //left motors forward
pinMode(A2,OUTPUT);   //left motors reverse
pinMode(A4,OUTPUT);   //right motors forward
pinMode(A5,OUTPUT);   //right motors reverse
//Led
Serial.begin(9600);
 Serial.println("Starting the RFID Reader...");
  SPI.begin();
  rfid.init();
 
}
 
void loop()
{
   if (rfid.isCard()) {
    if (rfid.readCardSerial()) {
      rfidCard = String(rfid.serNum[0]) + " " + String(rfid.serNum[1]) + " " + String(rfid.serNum[2]) + " " + String(rfid.serNum[3]);
      Serial.println(rfidCard);
      Serial.println(status_);
      digitalWrite(5,HIGH);
      delay(500);
      digitalWrite(5,LOW);
      }
      if (rfidCard == "99 203 29 19"){
        status_^=1;}
        
      }
      
      if (status_==false){
          digitalWrite(3,HIGH);
           blu();
        }
        else
      {
         digitalWrite(3,LOW);}
         }
      
void blu()
{
if(Serial.available()){
  t = Serial.read();
  Serial.println(t);
}
 
if(t == 'F'){            //move forward(all motors rotate in forward direction)
  digitalWrite(LF,HIGH);
  digitalWrite(RF,HIGH);
}
 
else if(t == 'B'){      //move reverse (all motors rotate in reverse direction)
  digitalWrite(LR,HIGH);
  digitalWrite(RR,HIGH);
}
 
else if(t == 'L'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
  digitalWrite(RF,HIGH);
}
 
else if(t == 'R'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
  digitalWrite(LF,HIGH);
}

else if(t == 'W'){    //turn led on or off)
  digitalWrite(9,HIGH);
}
else if(t == 'w'){
  digitalWrite(9,LOW);
}
 
else if(t == 'S'){      //STOP (all motors stop)
  digitalWrite(LF,LOW);
  digitalWrite(LR,LOW);
  digitalWrite(RF,LOW);
  digitalWrite(RR,LOW);
}
}
