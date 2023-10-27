#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 8, 5, 4, 3, 2);

//pins
const int buttonPin = 7;
const int ldrPin = A0;
const int redPin = 6;
const int greenPin = 11;
const int bluePin = 10;

//comparitive final
int valueAtNegative = 0;
int valueAtTrace = 0;
int valueAtOne = 0;
int valueAtTwo = 0;
int valueAtThree = 0;
int valueAtFour = 0;

//constants
int negative[3] = {225, 234, 134};
int traces[3] = {198, 220, 112};
int one[3] = {175, 212, 134};
int two[3] = {119, 191, 154};
int three[3] = {73, 163, 154};
int four[3] = {20, 154, 150};


//setup
void setup() {
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ldrPin, INPUT);
  lcd.begin(16, 2);
  Serial.begin(9600);
  lcd.clear();
}

//main loop
void loop() {
int buttonState = digitalRead(buttonPin);

  if (buttonState == HIGH) {
      lcd.clear();
      analogWrite(redPin, negative[0]);
      analogWrite(greenPin, negative[1]);
      analogWrite(bluePin, negative[2]);
      delay(1000);
      valueAtNegative = analogRead(ldrPin);
      delay(500); 
      analogWrite(redPin, traces[0]);
      analogWrite(greenPin, traces[1]);
      analogWrite(bluePin, traces[2]);
      delay(1000);
      valueAtTrace = analogRead(ldrPin);
      delay(500); 
      analogWrite(redPin, one[0]);
      analogWrite(greenPin, one[1]);
      analogWrite(bluePin, one[2]);
      delay(1000);
      valueAtOne = analogRead(ldrPin);
      delay(500); 
      analogWrite(redPin, two[0]);
      analogWrite(greenPin, two[1]);
      analogWrite(bluePin, two[2]);
      delay(1000);
      valueAtTwo = analogRead(ldrPin);
      delay(500); 
      analogWrite(redPin, three[0]);
      analogWrite(greenPin, three[1]);
      analogWrite(bluePin, three[2]);
      delay(1000);
      valueAtThree = analogRead(ldrPin);
      delay(500); 
      analogWrite(redPin, four[0]);
      analogWrite(greenPin, four[1]);
      analogWrite(bluePin, four[2]);
      delay(1000);
      valueAtFour = analogRead(ldrPin);
      delay(500); 
      int checkArray[6] = {valueAtNegative, valueAtTrace, valueAtOne, valueAtTwo, valueAtThree, valueAtFour};
      int currentHighest = 0;
      int indexOfHighest = -1;
      for (int i = 0; i < 6; i++) {
        if (checkArray[i] > currentHighest) {
          currentHighest = checkArray[i];
          indexOfHighest = i;
        }
      }
      String toPrint = "";
      if (indexOfHighest == 0) {
        toPrint = "Negative";
      } else if (indexOfHighest == 1) {
        toPrint = "Trace";
      } else if (indexOfHighest == 2) {
        toPrint = "One";
      } else if (indexOfHighest == 3) {
        toPrint = "Two";
      } else if (indexOfHighest == 4) {
        toPrint = "Three";
      } else if (indexOfHighest == 5) {
        toPrint = "Four";
      } 
      lcd.print(toPrint);  
  } else {
    analogWrite(redPin, 0);
    analogWrite(greenPin, 0);
    analogWrite(bluePin, 0);
  }
}
