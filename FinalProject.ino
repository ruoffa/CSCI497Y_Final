// LEDs
int redLED = 6;
int yellowLED = A5;
int greenLED = A7;
int blueLED = A8;
int ledArray[] = {redLED, yellowLED, greenLED, blueLED};

// Sensors
int button = A4;
int lightSensor = A2;

// States
int mode = 0;
int lastButtonState = HIGH;
int flashInterval = 250;
unsigned long flashTimer = 0;
bool ledOn = false;

// Line mode
int currentLED = 0;
int lineInterval = 200;
unsigned long lineTimer = 0;

void setup() {
  pinMode(redLED, OUTPUT);
  pinMode(yellowLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  pinMode(blueLED, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  pinMode(lightSensor, INPUT);
}

void loop() {
  int buttonState = digitalRead(button);
  
  // detects button press through transition from HIGH to LOW
  if (buttonState == LOW && lastButtonState == HIGH) {
    mode = (mode + 1) % 3; // more modes
    delay(50);
  }
  lastButtonState = buttonState;
  
  // 0: led off, 1: all on, 2: flashing, 3: line, 4: light sensitive
  if (mode == 0) {
    digitalWrite(redLED, LOW);
    digitalWrite(yellowLED, LOW);
    digitalWrite(greenLED, LOW);
    digitalWrite(blueLED, LOW);
  } else if (mode == 1) {
    digitalWrite(redLED, HIGH);
    digitalWrite(yellowLED, HIGH);
    digitalWrite(greenLED, HIGH);
    digitalWrite(blueLED, HIGH);
  } else if (mode == 2) {
    if (millis() - flashTimer > flashInterval) {
      ledOn = !ledOn;
      digitalWrite(redLED, ledOn);
      digitalWrite(yellowLED, ledOn);
      digitalWrite(greenLED, ledOn);
      digitalWrite(blueLED, ledOn);
      flashTimer = millis();
    }
  } else if (mode == 3) {
    if (millis() - lineTimer > lineInterval) {
      for (int i = 0; i < 4; i++) {
        digitalWrite(ledArray[i], LOW);
      }
      digitalWrite(ledArray[currentLED], HIGH);
      currentLED = (currentLED + 1) % 4;
      lineTimer = millis();
    }
  } else if (mode == 4) {
    int lightValue = analogRead(lightSensor);
    int brightness = map(lightValue, 0, 1023, 0, 255);
    analogWrite(redLED, brightness);
    analogWrite(yellowLED, brightness);
    analogWrite(greenLED, brightness);
    analogWrite(blueLED, brightness);
  }
}
