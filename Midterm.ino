int led = 6;
int button = A4;

int mode = 0;
int lastButtonState = HIGH;
int flashInterval = 250;
unsigned long flashTimer = 0;
bool ledOn = false;

void setup() {
  pinMode(led, OUTPUT);
  pinMode(button, INPUT_PULLUP);
}

void loop() {
  int buttonState = digitalRead(button);
  
  // detects button press through transition from HIGH to LOW
  if (buttonState == LOW && lastButtonState == HIGH) {
    mode = (mode + 1) % 3;
    delay(50);
  }
  lastButtonState = buttonState;
  
  // 0: led off, 1: led on, 2: led flashing
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
}
