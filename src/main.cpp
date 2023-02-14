#include <Arduino.h>

int yellow = 9;
int green = 6;
int blue = 5;
int red = 3;

int photoResistor = A0;
int buttonPin = 2;
int buttonState = 0;
int pattern = 0;

// debounce

byte lastButtonState;
unsigned long lastButtonStateChanged = millis();
unsigned long debounceDeration = 50; // milis

void allOff()
{
  analogWrite(red, LOW);
  analogWrite(blue, LOW);
  analogWrite(yellow, LOW);
  analogWrite(green, LOW);
}

void setup()
{
  Serial.begin(9600);
  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(photoResistor, INPUT); // setting photo resistor as input
  pinMode(buttonPin, INPUT);
  // debounce
  lastButtonState = digitalRead(buttonPin);
}

void loop()
{
  // debounce
  if (millis() - lastButtonStateChanged >= debounceDeration)
  {
    byte buttonStateDebounce = digitalRead(buttonPin);
    if (buttonStateDebounce != lastButtonState)
    {
      lastButtonStateChanged = millis();
      lastButtonState = buttonStateDebounce;
      if (buttonStateDebounce == LOW)
      {
        Serial.println("button has been relesed");

      }
    }
  }

  //Serial.println(buttonState);
  buttonState = digitalRead(buttonPin);

    if (buttonState == HIGH)
    {
      allOff();
      pattern = (pattern + 1) % 3;
    }

  if (pattern == 0)
  {
    digitalWrite(red, HIGH);
  }
  else if (pattern == 2)
  {
    digitalWrite(yellow, HIGH);
  }
  else if (pattern == 1)
  {
    int photoResistorStatus = analogRead(photoResistor); // read the status of photo resistor
    int ledVal = map(photoResistorStatus, 300, 800, 0, 200);
    //Serial.println(photoResistorStatus);
    //Serial.println(ledVal);
    Serial.println("case 2 is working");
    if (photoResistorStatus <= 450)
    {
      analogWrite(yellow, 5);
      delay(100);
      analogWrite(yellow, LOW);
      delay(100);
      analogWrite(green, ledVal);
      delay(100);
      analogWrite(green, LOW);
      delay(100);
      analogWrite(blue, 11);
      delay(100);
      analogWrite(blue, LOW);
      delay(100);
      analogWrite(red, 14);
      delay(100);
      analogWrite(red, LOW);
      delay(1000);
    }
  }
  else if (pattern == 3)
  {
    allOff();
  }
}
// void loop()
// {
//   buttonState = digitalRead(buttonPin);
//   Serial.println(buttonState);
//   if (buttonState == LOW)
//   { // increment the pattern.   the % make it so that the patern can only go up to 3 then loops back to 3 and repates
//     pattern = (pattern + 1) % 3;

//     switch (pattern)
//     {
//     case 0:
//       // make the led dim
//       for (int i = 0; i < 200; i++)
//       {
//         analogWrite(red, i);
//         analogWrite(blue, i);
//         analogWrite(yellow, i);
//         analogWrite(green, i);
//         delay(10); // delay for visibility
//       }

//       break;
//     case 1:
//       int photoResistorStatus = analogRead(photoResistor); // read the status of photo resistor
//       int ledVal = map(photoResistorStatus, 300, 800, 0, 200);
//       Serial.println(photoResistorStatus);
//       Serial.println(ledVal);
//       Serial.println("case 2 is working");
//       if (photoResistorStatus <= 450)
//       {
//         analogWrite(yellow, 5);
//         delay(100);
//         analogWrite(yellow, LOW);
//         delay(100);
//         analogWrite(green, ledVal);
//         delay(100);
//         analogWrite(green, LOW);
//         delay(100);
//         analogWrite(blue, 11);
//         delay(100);
//         analogWrite(blue, LOW);
//         delay(100);
//         analogWrite(red, 14);
//         delay(100);
//         analogWrite(red, LOW);
//         delay(1000);
//       }

//       break;
//     case 2:
//       allOff();

//       break;
//     // case 2:
//     //   allOff();
//     //   break;
//     }

//   }
// }

//   // if (buttonPin != 0)
//   // {
//   //   Serial.println("buttonPin is working working");
//   // }
//   // else
//   // {
//   //   analogWrite(red, LOW);
//   //   analogWrite(yellow, LOW);
//   //   analogWrite(blue, LOW);
//   //   analogWrite(green, LOW);
//   // }
