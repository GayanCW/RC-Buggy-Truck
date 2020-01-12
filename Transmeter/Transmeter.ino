#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7, 8); // CE, CSN

const byte address[][6] = {"GAYAN"};

int CH1,CH2,CH3,CH4;
byte max_left=50,max_right=140;

void setup() {
  Serial.begin(9600);
  radio.begin();
  radio.openWritingPipe(address[0]);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

}

void loop() {

  if(analogRead(A0)){
    set_vr_values(1);
    CH1 = CH1+1000;
    send_values(CH1);
      delay(4);  
  }

  if(analogRead(A1)){
    set_vr_values(2);
    CH2 = CH2+2000;
    send_values(CH2); 
      delay(4);  
  }

  if(analogRead(A2)){
    set_vr_values(3);
    CH3 = CH3+3000;
    send_values(CH3); 
      delay(4);  
  }

  if(analogRead(A3)){
    set_vr_values(4);
    CH4 = CH4+4000;
    send_values(CH4); 
      delay(4);  
  }

  //print_values();
  
}

void send_values(int SEND_VAL){
  radio.write(&SEND_VAL, sizeof(SEND_VAL));
}

void print_values(){
  Serial.print("CH1: ");
  Serial.print(analogRead(A0));
  Serial.print(" ");
  Serial.print(CH1%1000); 
  Serial.print("\t");
  Serial.print("CH2: ");
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.print(CH2%1000);
  Serial.print("\t");
  
  Serial.print("CH3: ");
  Serial.print(analogRead(A2));
  Serial.print(" ");
  Serial.print(CH3%1000);
  Serial.print("\t");
  Serial.print("CH4: ");
  Serial.print(analogRead(A3));
  Serial.print(" ");
  Serial.println(CH4%1000);
}

void set_vr_values(byte channel){
    
  if(channel==1){

    if(analogRead(A0)<470)  CH1=510;
    if(analogRead(A0)>=470 && analogRead(A0)<=600)  CH1 = map(analogRead(A0), 470, 600, 510, 255);
    if(analogRead(A0)>=700 && analogRead(A0)<=999)  CH1 = map(analogRead(A0), 700, 999, 255, 0);
    if(analogRead(A0)>999)  CH1=0;
    if(analogRead(A0)>600 && analogRead(A0)<700)  CH1=255;

  }
  
  if(channel==2){

    if(analogRead(A1)<470)  CH2=max_left;
    if(analogRead(A1)>=470 && analogRead(A1)<=556)  CH2 = map(analogRead(A1), 470, 556, max_left, 90);
    if(analogRead(A1)>=610 && analogRead(A1)<=970)  CH2 = map(analogRead(A1), 610, 970, 90, max_right);
    if(analogRead(A1)>970)  CH2=max_right;
    if(analogRead(A1)>556 && analogRead(A1)<610)  CH2=90;

  }

  if(channel==3){
    CH3 = map(analogRead(A2), 0, 1023, 0, 255);
  }

  if(channel==4){    
    CH4 = map(analogRead(A3), 40, 1023, 0, 255);
    if(analogRead(A3)<40) CH4=0;
  }
  
}
