/*
 * File Name: ProteinProblem.ino
 * 
 * Description:
 * This Arduino sketch is designed to measure protein concentration using urinalysis strips and a color sensor.
 * The sensor measures red, green, and blue color frequencies from the strip and calculates an estimated protein level.
 * 
 * NOTE: This sketch contains placeholder calculations.
 * The current implementation includes placeholder calculations. You MUST build and calibrate the system yourself to obtain accurate results.
 * 
 * Hardware:
 * - LCD display connected to pins 12, 11, 5, 4, 3, 2
 * - Color sensor connected to pins 6, 7, 8, 9, 13
 * - Button connected to pin 10
 * - Bluetooth module connected for serial communication with a mobile device to record and transmit results
 * 
 * Usage:
 * - Dip the urinalysis strip into the sample.
 * - Insert the strip into the sensor.
 * - Press the button to start the measurement.
 * - The sketch will display the estimated protein concentration on the LCD and transmit the results via Bluetooth.
 * 
 * History:
 * - Original Code: December 2018
 * - Updated: August 2024 for code readability
 */

// Libraries
#include <LiquidCrystal.h>
#include <math.h>

// Define the LCD interface pins
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Define the color sensor pins
#define S0 6
#define S1 7
#define S2 8
#define S3 9
#define sensorOut 13

// Define the button pin
#define buttonPin 10

// Define constants for the program
const int accuracy = 5;

void setup() {
  // Initialize pin modes
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(sensorOut, INPUT);
  pinMode(buttonPin, INPUT);

  // Set the frequency scaling to 20%
  digitalWrite(S0, LOW);
  digitalWrite(S1, HIGH);

  // Initialize the LCD and serial communication
  lcd.begin(16, 2);
  Serial.begin(9600);

  // Display initial message
  lcd.clear();
  lcd.print("Dip a stick and");
  lcd.setCursor(0, 1);
  lcd.print("press the button");
}

void loop() {
  // Check if the button is pressed or serial data is received
  int buttonStart = digitalRead(buttonPin);

  if (Serial.available() > 0 || buttonStart == HIGH) {
    char data = Serial.read();
    if (data == '1' || buttonStart == HIGH) {
      startMeasurement();
    }
  }
}

void startMeasurement() {
  // Clear the LCD and reset the array location
  lcd.clear();

  // Display a countdown message for 60 seconds
  for (int i = 0; i < 60; i++) {
    lcd.clear();
    lcd.print(60 - i);
    lcd.print(" seconds left");
    lcd.setCursor(0, 1);
    lcd.print("Insert stick now");
    delay(1000);
  }

  // Clear the LCD and start measuring color frequencies
  lcd.clear();
  delay(1000);

  int redArray[accuracy] = {0};
  int greenArray[accuracy] = {0};
  int blueArray[accuracy] = {0};

  measureColors(redArray, greenArray, blueArray);

  if (validateReadings(redArray, greenArray, blueArray)) {
    double redAverage = calculateAverage(redArray);
    double greenAverage = calculateAverage(greenArray);
    double blueAverage = calculateAverage(blueArray);
    double protein = calculateProteinLevel(redAverage, greenAverage, blueAverage);
    displayResults(protein);
  } else {
    displayError();
  }
}

void measureColors(int* redArray, int* greenArray, int* blueArray) {
  for (int i = 0; i < accuracy; i++) {
    // Measure red frequency
    digitalWrite(S2, LOW);
    digitalWrite(S3, LOW);
    redArray[i] = pulseIn(sensorOut, LOW);
    delay(10);

    // Measure green frequency
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    greenArray[i] = pulseIn(sensorOut, LOW);
    delay(10);

    // Measure blue frequency
    digitalWrite(S2, LOW);
    digitalWrite(S3, HIGH);
    blueArray[i] = pulseIn(sensorOut, LOW);
    delay(10);
  }
}

bool validateReadings(int* redArray, int* greenArray, int* blueArray) {
  for (int i = 0; i < accuracy; i++) {
    if (redArray[i] < 0 || greenArray[i] < 0 || blueArray[i] < 0 || redArray[i] > 3500 || greenArray[i] > 3500 || blueArray[i] > 3500) {
      return false;
    }
  }
  return true;
}

double calculateAverage(int* colorArray) {
  int sum = 0;
  for (int i = 0; i < accuracy; i++) {
    sum += colorArray[i];
  }
  return sum / accuracy;
}

double calculateProteinLevel(double redAverage, double greenAverage, double blueAverage) {
  // Placeholder function for protein calculation
  // TODO: Implement actual calibration curves and calculations here for device
  // Use the measured red, green, and blue sampled averages to calculate the protein concentration
  
  // Just returning a dummy value for now...
  return 0;
}

void displayResults(double protein) {
  // Determine the protein level and display the results
  String level = "";

  if (protein >= 2000) {
    level = "++++";
  } else if (protein >= 300) {
    level = "+++";
  } else if (protein >= 100) {
    level = "++";
  } else if (protein >= 30) {
    level = "+";
  } else {
    level = "Negative";
  }

  Serial.println((String)protein);
  delay(2000);
  Serial.println(level);
  lcd.print(protein);
  lcd.print(" mg of");
  lcd.setCursor(0, 1);
  lcd.print("albumin/dL");
}

void displayError() {
  // Display an error message if no strip is detected
  lcd.print("No strip");
  lcd.setCursor(0, 1);
  lcd.print("inserted!");
  Serial.println("No strip!");
  delay(2000);
}
