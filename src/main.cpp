#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#define EXT_INT_PIN         2

volatile bool LongPress = false;
volatile bool ShortPress = false;
volatile bool ButtonPressed = false;
volatile uint32_t Interval = 0;

void Button(void);
void ShortButtonPressed(void);
void LongButtonPressed(void);

void setup() {
  Serial.begin(9600);
  attachInterrupt(digitalPinToInterrupt(EXT_INT_PIN), Button, CHANGE);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Interval > 500 && Interval <= 2000)
  {
    ShortButtonPressed();
  }
  else if(Interval > 3000)
  {
    LongButtonPressed();
  }
}

void Button(void)
{
  Serial.println("Inside ISR.");
  static volatile uint32_t PreviousTm, CurrTm;
  if(ButtonPressed == false)
  {
    PreviousTm = millis();
    ButtonPressed = true;
  }
  else
  {
    CurrTm = millis();
    Interval = CurrTm - PreviousTm;
    ButtonPressed = false;
  }
}

void ShortButtonPressed(void)
{
  Serial.println("Sort button pressed.");
  Interval = 0;
}


void LongButtonPressed(void)
{
  Serial.println("Long button pressed.");
  Interval = 0;
}
