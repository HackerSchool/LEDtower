int latchPin = 2;
int clockPin = 13;
int dataPin = 11;
int outenable = 4; 

void setup() 
{
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(outenable, OUTPUT);
  
  
//  bytein(B00000000, false);
  bytein(B11111111, false); //red
  bytein(B11111111, false);
  bytein(B11111111, false); //green
  bytein(B11111111, false);
  bytein(B11111111, false); //blue
  bytein(B11111111, false);  
  bytein(B11111111, true);
  
}
 
void loop() 
{  
/*  int i;
  for(i=0; i<8; i++){
    bytein(B00000000, false);
    bytein(B00000000, false);
    bytein(B00000000, false);
    bytein(B00000000, false);
    bytein(B11111111, false);
    bytein(B11111111, false);
    bytein(1<<i, true);
    delay(200);
  }
  for(i=8; i>=0; i--){
    bytein(B00000000, false);
    bytein(B00000001, false);
    bytein(B00000000, false);
    bytein(B00000000, false);
    bytein(B11111111, false);
    bytein(B11111110, false);
    bytein(1<<i, true);
    delay(200);
  }
  for(i=0; i<8; i++){
    bytein(B00000000, false);
    bytein(B00000000, false);
    bytein(B00000000, false);
    bytein(B00000001, false);
    bytein(B11111111, false);
    bytein(B11111110, false);
    bytein(1<<i, true);
    delay(200);
  }
  */
}

void bytein(byte data, boolean Latch)
{
  int i;
  digitalWrite(outenable, HIGH);
  for(i=7; i>=0; i--){

    digitalWrite(dataPin, bitRead(data, i));
    digitalWrite(clockPin, HIGH);
    digitalWrite(clockPin, LOW);
    if (Latch==true){
      digitalWrite(latchPin, HIGH);
      digitalWrite(latchPin, LOW);
    }  
  }
  digitalWrite(outenable, LOW);
}

  
