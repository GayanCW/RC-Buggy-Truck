#define mF 2
#define mB 3
#define mS 5

void setup() {
  
  pinMode(mF,OUTPUT);
  pinMode(mB,OUTPUT);
  pinMode(mS,OUTPUT);
  
}

void loop() {

  motors(255);

}

void motors(int set_speed){

  if(set_speed>255){
    digitalWrite(mF,HIGH);
    digitalWrite(mB,LOW);
    analogWrite(mS,set_speed-255); 
  }
  if(set_speed<255){
    digitalWrite(mF,LOW);
    digitalWrite(mB,HIGH);
    analogWrite(mS,255-set_speed); 
  }
  if(set_speed==255){
    digitalWrite(mF,LOW);
    digitalWrite(mB,LOW);
    analogWrite(mS,0); 
  }
  
}
