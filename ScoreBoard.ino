// team A Pins
int teamALed0 = 3;
int teamALed1 = 2;

int teamAButton = 12;
int teamAButtonIsPressed = false;

int teamAScore = 0;
int teamAGames = 0;

// team B Pins
int teamBLed0 = 5;
int teamBLed1 = 4;

int teamBButton = 11;
int teamBButtonIsPressed = false;

int teamBScore = 0;
int teamBGames = 0;
 

void setup() {
  pinMode(teamALed0, OUTPUT);
  pinMode(teamALed1, OUTPUT);
  pinMode(teamAButton, INPUT);

  pinMode(teamBLed0, OUTPUT);
  pinMode(teamBLed1, OUTPUT);
  pinMode(teamBButton, INPUT);
}

void loop() {
  if (teamAButtonIsPressed || teamBButtonIsPressed) {
    delay(300);
    teamAButtonIsPressed = false;
    teamBButtonIsPressed = false;
  }
  
  teamAButtonIsPressed = digitalRead(teamAButton);
  teamBButtonIsPressed = digitalRead(teamBButton);

  if (teamAButtonIsPressed) {
    raiseScore('a');
  }

  if (teamBButtonIsPressed) {
    raiseScore('b');
  }
}

void raiseScore(char team) {
  int *led0, *led1, *score, *games;

  if (team == 'a') {
    led0 = &teamALed0;
    led1 = &teamALed1;
    score = &teamAScore;
    games = &teamAGames;
  } else {
    led0 = &teamBLed0;
    led1 = &teamBLed1;
    score = &teamBScore;
    games = &teamBGames;
  }

  *score += 1;

  if (*score == 4) {
    *games += 1;
    *score = 0;
  }

  updateLeds(*score, led0, led1);
}

void updateLeds(int score, int* led0, int* led1) {
  int state0, state1;
  
  switch(score) {
    case 0:
      state0 = LOW;
      state1 = LOW;
      break;
    case 1:
      state0 = HIGH;
      state1 = LOW;
      break;
    case 2:
      state0 = LOW;
      state1 = HIGH;
      break;
    case 3:
      state0 = HIGH;
      state1 = HIGH;
      break;
  }

  digitalWrite(*led0, state0);
  digitalWrite(*led1, state1);
}

