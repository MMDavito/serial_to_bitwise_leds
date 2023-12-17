
//LSB order
byte leds[8] = {2,3,4,5,6,7,8,9};
byte currValue = 0b00000001;


void setup() {
  Serial.begin(9600);
  for(int i=0; i<8; i++){
    pinMode(leds[i], OUTPUT);
  }
}

void writeToLeds(byte b_to_write)
{
  for(int i=0; i<8; i++){
    byte temp = 0b00000000;
    switch (i) {
      case 0:
        temp = b_to_write & 0b00000001;
        break;
      case 1:
        temp = b_to_write & 0b00000010;
        break;
      case 2:
        temp = b_to_write & 0b00000100;
        break;
      case 3:
        temp = b_to_write & 0b00001000;
        break;
      case 4:
        temp = b_to_write & 0b00010000;
        break;
      case 5:
        temp = b_to_write & 0b00100000;
        break;
      case 6:
        temp = b_to_write & 0b01000000;
        break;
      case 7:
        temp = b_to_write & 0b10000000;
        break;
    }
    if(temp > 0){
      digitalWrite(leds[i],HIGH);
    }
    else{
      digitalWrite(leds[i],LOW);
    }
  }
}

void loop() {
  int numChars = 0;
  bool updated = false;
  while (Serial.available() > 0)
  {
    if(updated==false){
      for(int i=0; i<8; i++){
        digitalWrite(leds[i],LOW);
      }
    }
    
    //Create a place to hold the incoming message
    byte inByte = Serial.parseInt();
    if(inByte == NULL && numChars > 0) continue;
    numChars += 1;
    currValue = inByte;
    updated = true;
  }
  writeToLeds(currValue);
  delay(10);
}
