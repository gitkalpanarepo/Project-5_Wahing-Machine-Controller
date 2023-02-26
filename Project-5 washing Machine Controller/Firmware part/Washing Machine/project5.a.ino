#include <LiquidCrystal.h>
#include<Wire.h>

int drainSwitch = 13;
int waterTank = 12;
int drainValve = 9;
int washingMotor = 10;
int LED = 11;
int timerSetting = A0;

LiquidCrystal lcd(7,6,5,4,3,2);

int timerValue;

void setup() {
  pinMode(drainSwitch, INPUT);
  pinMode(waterTank, INPUT);
  pinMode(drainValve, OUTPUT);
  pinMode(washingMotor, OUTPUT);
  pinMode(LED, OUTPUT);
  lcd.begin(20, 4);
  lcd.print(" Washing Machine ");
  lcd.setCursor(0,1);
  lcd.print("    Controller   ");
  lcd.setCursor(0,2);
  lcd.print("       By          ");
  lcd.setCursor(0,3);
  lcd.print(" Kalpana ");
  delay(1000);
  lcd.clear();
}

void loop() {
  // Check for drain switch
  if (digitalRead(drainSwitch) == HIGH) {
    // Wait for water to drain out
    lcd.setCursor(0,0);
    lcd.print("wait");
    lcd.setCursor(2,1);
    lcd.print("..Draining..");
    delay(3000);
    // Check for empty water tank
    if (digitalRead(waterTank) == HIGH) {
      // Close drain valve
      digitalWrite(drainValve, HIGH);
      lcd.clear();
      lcd.print("Drain valve closed");
      delay(1000);
      digitalWrite(drainValve, LOW);
      // Ask for timer setting
      lcd.clear();
      lcd.print("Set washing timer:");
      timerValue = analogRead(timerSetting);
      // Convert timer value to minutes
      timerValue = map(timerValue, 0, 1023, 0, 60);
      lcd.setCursor(0, 1);
      lcd.print(timerValue);
      lcd.print(" mins");
      delay(1000);
      // Start washing
     // lcd.clear();
     // lcd.print("Washing...");
      digitalWrite(washingMotor, HIGH);
      lcd.setCursor(0,1);
      lcd.print("Washing...");
      delay(timerValue * 60000);
      digitalWrite(washingMotor, LOW);
      // Open drain valve
      digitalWrite(drainValve, HIGH);
      lcd.clear();
      lcd.print("Drain valve opened");
      delay(3000);
      // Buzzer beeps until drain valve closed
     // while (digitalRead(drainSwitch) == HIGH) {
       // digitalWrite(buzzer, HIGH);
       // delay(500);
      //  digitalWrite(buzzer, LOW);
      //  delay(500);
     // }
      // Close drain valve and indicate washing completed
      digitalWrite(drainValve, LOW);
      lcd.clear();
      lcd.print("Washing completed!");
      digitalWrite(LED, HIGH);
      delay(1000);
      digitalWrite(LED, LOW);
      delay(3000);
    }
  }
}
