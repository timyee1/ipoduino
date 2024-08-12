#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

const int PIN_MP3_TX = 2;
const int PIN_MP3_RX = 3;
const int NEXT_BUTTON = 6;
const int PAUSE_BUTTON = 7;
bool isPlaying = true;

DFRobotDFPlayerMini player;

void setup() {
  pinMode(NEXT_BUTTON, INPUT);
  pinMode(PAUSE_BUTTON, INPUT);

  SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
  Serial.begin(9600);
  softwareSerial.begin(9600);

  if (!player.begin(softwareSerial)) {
    Serial.println("Connecting to DFPlayer Mini failed!");
  }

  player.volume(30);
  player.play(1);
}

void handleNextButton() {
  int value = digitalRead(NEXT_BUTTON);
  if (value == LOW) {
    player.next();
    isPlaying = true;
  }

  while (value == LOW) {
    delay(10);
    value = digitalRead(NEXT_BUTTON);
  }
}

void handlePauseButton() {
  int value = digitalRead(PAUSE_BUTTON);
  if (value == LOW) {
    if (isPlaying) {
      player.pause();
      isPlaying = false;
    }
    
    else {
      player.start();
      isPlaying = true;
    }

    while(value == LOW) {
      delay(10);
      value = digitalRead(PAUSE_BUTTON);
    }
  }
}

void loop() {
  handleNextButton();
  handlePauseButton();
  delay(10);
}
