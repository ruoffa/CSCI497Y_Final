int led = 6;
/// add individual LEDs and ledArray
int button = A4;
/// light sensor

int mode = 0;
int lastButtonState = HIGH;
int flashInterval = 250;
unsigned long flashTimer = 0;
bool ledOn = false;

// variables for other modes, currentLed, lineTimer

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  // additional LEDs
}

void loop() {
  int buttonState = digitalRead(button);
  
  // detects button press through transition from HIGH to LOW
  if (buttonState == LOW && lastButtonState == HIGH) {
    mode = (mode + 1) % 3; // more modes
    delay(50);
  }
  lastButtonState = buttonState;
  
  // 0: led off, 1: led on, 2: led flashing
  //Additional modes
  if (mode == 0) {
    digitalWrite(led, LOW);
  } else if (mode == 1) {
    digitalWrite(led, HIGH);
  } else if (mode == 2) {
    if (millis() - flashTimer > flashInterval) {
      ledOn = !ledOn;
      digitalWrite(led, ledOn);
      flashTimer = millis();
    }
  }
  // mode 3, lignt up in a line
  // similar to flashing but use currentLED, ledArray, lineTimer

  // mode 4, light sensitive
  // map light value to brightness, use analogWrite
}
