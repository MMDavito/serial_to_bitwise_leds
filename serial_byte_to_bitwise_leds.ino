
//LSB order
byte leds[8] = {2, 3, 4, 5, 6, 8, 7, 9};
byte prevValue = 0b00000000;
byte currValue = 0b00000000;


void setup() {
  Serial.begin(9600);
  for (int i = 0; i < 8; i++) {
    pinMode(leds[i], OUTPUT);
  }
}

void writeToLeds(byte b_to_write)
{
  for (int i = 0; i < 8; i++) {
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
    if (temp > 0) {
      digitalWrite(leds[i], HIGH);
    }
    else {
      digitalWrite(leds[i], LOW);
    }
  }
}
byte readSerial() {
  delay(5);
  String recieved = "";
  int numChars = 0;
  while (Serial.available()) {
    byte b = Serial.read() - '0';
    if (b == 218) break;
    recieved += b;
    numChars ++;
    //if(numChars == 3) return recieved.toInt();
  }
  return recieved.toInt();
}

void loop() {
  bool updated = false;

  String recieved = "";
  if (Serial.available())
  {
    for (int i = 0; i < 8; i++) {
      digitalWrite(leds[i], LOW);
    }
    currValue = readSerial();
  }
  if (currValue != prevValue) {
    writeToLeds(currValue);
    prevValue = currValue;
  }
}
