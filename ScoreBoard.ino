byte scoreToByte(int score) {
  // 0yyy0xxx
  switch(score) {
        case 0:
          // 00
          // 00000000
          return 0;
        case 1:
          // 15
          // 01010001
          return 81;
        case 2:
          // 30
          // 00000011
          return 3;
        case 3:
          // 45
          // 01010100
          return 84;
        default:
          // 11111111
          return 255;
      }
}

byte gameToByte(int game) {
  switch(game) {
    case 0:
      return 0; // 00000000
    case 1:
      return 2; // 00000010 
    case 2:
      return 4; // 00000100
    case 3:
      return 6; // 00000110
    case 4:
      return 8; // 00001000
    case 5:
      return 10; // 00001010
    case 6:
      return 12; // 00001100
    case 7:
      return 14; // 00001110
    case 8:
      return 16; // 00010000
    case 9:
      return 18; // 00010010
    case 10:
      return 1; // 00000001
    case 11:
      return 3; // 00000011
    case 12:
      return 5; // 00000101
    case 13:
      return 7; // 00000111
    default:
      return 17; // 00010001
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
    int gameDataPin, gameClockPin, gameLatchPin;
    
    Team() {
      score = 0;
      games = 0;
    }
    
    void setDigitalPins(int dataPin, int clockPin, int latchPin, int buttonPin) {
        this->dataPin = dataPin;
        this->clockPin = clockPin;
        this->latchPin = latchPin;
        this->buttonPin = buttonPin;

        pinMode(dataPin, OUTPUT);
        pinMode(clockPin, OUTPUT);
        pinMode(latchPin, OUTPUT);
        pinMode(buttonPin, INPUT);
    }
  
    void setAnalogPins(int dataPin, int clockPin, int latchPin) {
      this->gameDataPin = dataPin;
      this->gameClockPin = clockPin;
      this->gameLatchPin = latchPin;
      
      pinMode(dataPin, OUTPUT);
      pinMode(clockPin, OUTPUT);
      pinMode(latchPin, OUTPUT);
    }

    bool checkForUpdate(void) {
      bool wasGame = false;
      bool buttonWasPressed = buttonIsPressed();
      if (buttonWasPressed) {
        this->score += 1;

        if (this->score == 4) {
          this->score = 0;
          this->games += 1;
          wasGame = true;
        }

        updateLeds();
        return wasGame;
      }
    }

    void updateLeds() {
      byte scoreAsByte = scoreToByte(score);
      updateShiftRegister(dataPin, clockPin, latchPin, scoreAsByte);
      byte gamesAsByte = gameToByte(games);
      updateShiftRegister(gameDataPin, gameClockPin, gameLatchPin, gamesAsByte);
    }
  
  void resetScore() {
    this->score = 0;
    updateLeds();
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
  team1.setDigitalPins(7, 9, 8, 6);
  team1.setAnalogPins(A0, A2, A1);
  team1.updateLeds();
  team2.setDigitalPins(3, 5, 4, 2);
  team2.setAnalogPins(A3, A5, A4);
  team2.updateLeds();
}

void loop() {
  if (wasPressed) {
    delay(100);
    wasPressed = false;
  }
  
  if (team1.checkForUpdate()) {
    team2.resetScore();
  }
  
  if (team2.checkForUpdate()) {
    team1.resetScore();
  }
}

