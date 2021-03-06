#include <Arduino.h>
#include <Servo.h>

const int EingangPoti = A0;
const int EingangButton = 7;
const int sensorPin = 8;

bool buttonPressed = false;
bool greiferStatus = false;
int soundWave = 0;

int buttonValue = 0;
int sensorWert = 0;
int servoValue = 0;
const int servoOpen = 14;
const int servoClosed = 76;

Servo Greifer;

void setup() {
  Serial.begin(9600);
  pinMode(EingangButton, INPUT);
  pinMode(sensorPin, INPUT);
  Greifer.attach(6);
  Serial.println("Serial Monitor Starts");
}

void loop() {
  delay(150);
  buttonValue = digitalRead(EingangButton);
  soundWave = digitalRead(sensorPin);
  if((soundWave!=0) && (greiferStatus==true)){
    Greifer.write(servoClosed);
    Serial.println("Greifer gescghlossen");
    greiferStatus = false;
    delay(1000);
  }
  else if(soundWave!=0){
    Greifer.write(servoOpen);
    Serial.println("Greifer geöffnet");
    greiferStatus = true;
    delay(1000);
  }

  if (buttonValue == HIGH) {
    buttonPressed = !buttonPressed;
    Serial.println("Taster gedrückt, Status: ");
    Serial.print(buttonPressed);
  }

  while (buttonPressed) {
    delay(150);
    //Servo nach Potentiometer steuern können
    buttonValue = digitalRead(EingangButton);
    if (buttonValue == HIGH) {
      Serial.println("Taster gedrückt, Status: ");
      Serial.print(buttonPressed);
      delay(10);
      buttonPressed = !buttonPressed;
    }
    sensorWert = analogRead(EingangPoti);
    servoValue = map(sensorWert, 0, 1023, 0, 180);
    Greifer.write(servoValue);
    Serial.print("Servo ist auf ");
    Serial.print(servoValue);
    Serial.print("° gefahren");
  }
}