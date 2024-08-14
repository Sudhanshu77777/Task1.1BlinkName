const byte ledPin = LED_BUILTIN;
const byte interruptPin = 2;
volatile bool resetMorse = false;
volatile bool buttonPressed = false;

const int dotLength = 200;  
const int dashLength = 650;
const int letterSpace = 700;
const int wordSpace = 1500;

void setup() 
{
  pinMode(ledPin, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, CHANGE);
  digitalWrite(ledPin, LOW); 
}

void blink() {
  if (!buttonPressed) {
    buttonPressed = true;
    resetMorse = false;
  } else {
    resetMorse = true;
  }
}

void sendMorseCode(char c) {
  if (c == 'S') {
    dot(); dot(); dot();
  } else if (c == 'U') {
    dot(); dot(); dash();
  } else if (c == 'D') {
    dash(); dot(); dot();
  } else if (c == 'H') {
    dot(); dot(); dot(); dot();
  } else if (c == 'A') {
    dot(); dash();
  } else if (c == 'N') {
    dash(); dot();
  }
}

void dot() {
  digitalWrite(ledPin, HIGH);
  delay(dotLength);
  digitalWrite(ledPin, LOW);
  delay(dotLength); 
}

void dash() {
  digitalWrite(ledPin, HIGH);
  delay(dashLength);
  digitalWrite(ledPin, LOW);
  delay(dotLength); 
}

void loop() {
  if (buttonPressed) {
    buttonPressed = false;  

    const char* name = "SUDHANSHU";
    
    for (int i = 0; name[i] != '\0'; i++) {
      if (resetMorse) {
        resetMorse = false;
        break;  
      }
      sendMorseCode(name[i]);
      if (!resetMorse) {
        delay(letterSpace);
      }
    }
    digitalWrite(ledPin, LOW);  
    delay(wordSpace); 
  }
}
