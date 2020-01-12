#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#define mF 2
#define mB 3
#define mS 5

RF24 radio(7, 8); // CE, CSN

Servo myservo;

const byte address[][6] = {"GAYAN"};
long blink_time1,blink_time2;
int CH1,CH2,CH3,CH4;

void setup() {
  Serial.begin(9600);
  
  pinMode(mF,OUTPUT);
  pinMode(mB,OUTPUT);
  pinMode(mS,OUTPUT);

  pinMode(4,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(10,OUTPUT);
  
  radio.begin();
  radio.openReadingPipe(0, address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();  

  myservo.attach(9);
  blink_time1=millis();
  blink_time2=millis();
}

void loop() {

  if(radio.available()){
    int received_value;
    radio.read(&received_value, sizeof(received_value));
    byte CH_NO = received_value/1000;
    int CH_VAL  = received_value%1000;
    
    if(CH_NO==1){
      CH1 = CH_VAL;
      motors(CH1);
      delay(4);   
    }

    if(CH_NO==2){     
      CH2 = CH_VAL;
      servo(CH2);
      delay(4);  
    }

    if(CH_NO==3){
      CH3 = CH_VAL;
        if(millis()-blink_time2>CH3){
          blink_time2=millis();
          blue_light_blink(CH3);
        }
    }

    if(CH_NO==4){
      CH4 = CH_VAL;
      led_bar(CH4);
      delay(4); 
    }
    //print_values();
  }

  if(!radio.available()){
    CH1=255;
    CH2=90;
    CH3=0;  //digitalWrite(4,CH3);
    CH4=0;  //analogWrite(6,CH4);
  }
    
}

void print_values(){
  Serial.print("CH1: ");
  Serial.print(CH1);
  Serial.print("\t");
  Serial.print("CH2: ");
  Serial.print(CH2);
  Serial.print("\t");
  Serial.print("CH3: ");
  Serial.print(CH3);
  Serial.print("\t");
  Serial.print("CH4: ");
  Serial.println(CH4);
}

void motors(int set_speed){

  if(set_speed>255){
    digitalWrite(mF,HIGH);
    digitalWrite(mB,LOW);
    analogWrite(mS,set_speed-255);
      if(millis()-blink_time1>(unsigned int)510-set_speed){
        blink_time1=millis();
        digitalWrite(10,!digitalRead(10));  
      } 
  }
  if(set_speed<255){
    digitalWrite(mF,LOW);
    digitalWrite(mB,HIGH);
    analogWrite(mS,255-set_speed); 
      if(millis()-blink_time1>(unsigned int)set_speed){
        blink_time1=millis();
        digitalWrite(10,!digitalRead(10));  
      }
  }
  if(set_speed==255){
    digitalWrite(mF,LOW);
    digitalWrite(mB,LOW);
    analogWrite(mS,0);
      if(millis()-blink_time1>(unsigned int)set_speed){
        blink_time1=millis();
        digitalWrite(10,!digitalRead(10));  
      }  
  }
  
}

void servo(int pos){
  myservo.write(pos);
}

void led_bar(int brightness){
  analogWrite(6,brightness); 
}

void blue_light_blink(int t){
  digitalWrite(4,!digitalRead(4));
}
