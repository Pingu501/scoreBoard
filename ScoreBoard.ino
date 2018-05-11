byte scoreToByte(int score) {
  // yyy0xxx0
  switch(score) {
        case 0:
          // 00
          // 00000000
          return 0;
        case 1:
          // 15
          // 00101010
          return 42;
        case 2:
          // 30
          // 01100000
          return 96;
        case 3:
          // 45
          // 10001010
          return 138;
        default:
          // 11111111
          return 255;
      }
}

void updateShiftRegister(int dataPin, int clockPin, int latchPin, byte data) {
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, LSBFIRST, data);
   digitalWrite(latchPin, HIGH);
}

bool wasPressed = false;

class Team {
  public:
    int dataPin, clockPin, latchPin, buttonPin, score, games;
    
    Team() {
      score = 0;
      games = 0;
    }
    
    void setPins(int dataPin, int clockPin, int latchPin, int buttonPin) {
        this->dataPin = dataPin;
        this->clockPin = clockPin;
        this->latchPin = latchPin;
        this->buttonPin = buttonPin;

        pinMode(dataPin, OUTPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(latchPin, OUTPUT);
        pinMode(buttonPin, INPUT);
    }

    void checkForUpdate(void) {
      bool buttonWasPressed = buttonIsPressed();
      if (buttonWasPressed) {
        this->score += 1;

        if (this->score == 4) {
          this->score = 0;
          this->games += 1;
        }

        updateLeds();
      }
    }

    void updateLeds() {
      byte scoreAsByte = scoreToByte(score);
      updateShiftRegister(dataPin, clockPin, latchPin, scoreAsByte);
    }

    bool buttonIsPressed(void) {
      bool buttonWasPressed = digitalRead(buttonPin);
      if (buttonWasPressed) {
        wasPressed = true;
      }
      return buttonWasPressed;
    }
};

Team team1;
Team team2;

void setup() {
  team1.setPins(5, 7, 6, 4);
  // team2.setPins(7, 8, 9, 6);
}

void loop() {
  if (wasPressed) {
    delay(400);
    wasPressed = false;
  }
  
  team1.checkForUpdate();
  // team2.checkForUpdate();
}

