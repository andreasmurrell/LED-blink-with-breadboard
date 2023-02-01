#include <Arduino.h>

int yellow = 9;
int green = 6;
int blue = 5;
int red = 3;
int photoResistor = A0;
int button = A5;
int buttonState = 0;
int pattern = 0;

void allOff()
{
  analogWrite(red, LOW);
  analogWrite(blue, LOW);
  analogWrite(yellow, LOW);
  analogWrite(green, LOW);
}
void setup()
{

  pinMode(yellow, OUTPUT);
  pinMode(green, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(red, OUTPUT);
  pinMode(photoResistor, INPUT); // setting photo resistor as input
}

void loop()
{

  buttonState = digitalRead(A5);
  Serial.println(buttonState);
  if (buttonState == LOW)
  { // increment the pattern.   the % make it so that the patern can only go up to 3 then loops back to 3 and repates
    pattern = (pattern + 1) % 3;

    switch (pattern)
    {
    case 1:
      // make the led dim
      for (int i = 0; i < 200; i++)
      {
        analogWrite(red, i);
        analogWrite(blue, i);
        analogWrite(yellow, i);
        analogWrite(green, i);
        delay(10); // delay for visibility
      }

      break;
    case 2:
      int photoResistorStatus = analogRead(photoResistor); // read the status of photo resiter
      int ledVal = map(photoResistorStatus, 300, 800, 0, 200);
      /// Serial.print("The photo resistor reading is: ");
      Serial.println(photoResistorStatus);
      Serial.println(ledVal);

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
      Serial.println("case 1 is working");
      break;
    case 3:
      allOff();
      break;
    }
  }
  else
  {
    // allOff();
  }
}

// if (button != 0)
// {
//   Serial.println("button is working working");
// }
// else
// {
//   analogWrite(red, LOW);
//   analogWrite(yellow, LOW);
//   analogWrite(blue, LOW);
//   analogWrite(green, LOW);
// }
