#include <LiquidCrystal.h>

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int sensorPin = A1;

const int ledPin = 13;
const int redLedPin = 8; 

const int buzzerPin = 9;

int sensorValue;
float voltageThreshold = 2.0; 
int peopleCount = 0; 
bool countEnabled = true; 

void setup() {

  lcd.begin(16, 2);

  lcd.print("People count:");
  lcd.setCursor(0, 1);
  lcd.print(peopleCount);

  pinMode(ledPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  
  pinMode(buzzerPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {

  sensorValue = analogRead(sensorPin);
  float voltage = sensorValue * (5.0 / 1023.0);
  if (countEnabled) {
    if (voltage > voltageThreshold) {
  
      peopleCount++;

      lcd.clear();
      lcd.print("People count:");
      lcd.setCursor(0, 1);
      lcd.print(peopleCount);

      Serial.print("People count: ");
      Serial.println(peopleCount);

      digitalWrite(ledPin, HIGH); 
      delay(500);
      digitalWrite(ledPin, LOW); 

      buzzBuzzer();

      while (voltage > voltageThreshold) {
        sensorValue = analogRead(sensorPin);
        voltage = sensorValue * (5.0 / 1023.0);
      }

      if (peopleCount >= 10) {

        lcd.clear();
        lcd.print("People exceed");

        for (int i = 0; i < 5; i++) {
          digitalWrite(redLedPin, HIGH);
          digitalWrite(buzzerPin, HIGH); 
          delay(500);
          digitalWrite(redLedPin, LOW);
          digitalWrite(buzzerPin, LOW); 
          delay(500);
        }

        countEnabled = false;
      }
    }
  }
}

void buzzBuzzer() {
  digitalWrite(buzzerPin, HIGH); 
  delay(100); 
  digitalWrite(buzzerPin, LOW); 
}
