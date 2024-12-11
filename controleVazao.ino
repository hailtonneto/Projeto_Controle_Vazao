#include <LiquidCrystal_I2C.h>

const int sensorPin = 3;
const int botaoPin = 2;
volatile unsigned long pulseCount = 0;
unsigned long previousMillis = 0;
unsigned long interval = 100;
float calibrationFactor = 32;

float flowRate = 0.0;
float totalLiters = 0.0;

LiquidCrystal_I2C lcd(0x27, 16, 2);

void pulseCounter() {
  pulseCount++;
}

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");

  pinMode(sensorPin, INPUT);
  pinMode(botaoPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(sensorPin), pulseCounter, FALLING);

  delay(2000);
  lcd.clear();
}

void loop() {
  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    flowRate = ((pulseCount / calibrationFactor) / (interval / 1000.0));
    totalLiters += (flowRate / 60.0);

    lcd.setCursor(0, 0);
    lcd.print("F: ");
    lcd.print(flowRate, 3);
    lcd.print(" ");

    lcd.setCursor(0, 1);
    lcd.print("T: ");
    lcd.print(totalLiters, 2);
    lcd.print(" ");

    pulseCount = 0;

    if (digitalRead(botaoPin) == LOW) {
      totalLiters = 0;
    }
  }
}