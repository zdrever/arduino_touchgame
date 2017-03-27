#include <Arduino.h>
#include <UTFT.h>
#include <ITDB02_Touch.h>
#include <EEPROM.h>
#include "FinalProject.h"

UTFT myGLCD(SSD1289, 38, 39, 40, 41);
ITDB02_Touch myTouch (6, 5, 4, 3, 2);

extern uint8_t BigFont[];

#define RADIUS 30
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

uint8_t SCORE = 0;
uint8_t LIVES = 3;

uint32_t TIME = 1000;
const double TIME_FACTOR = 0.95;

int GAME_MODE = 0;

void setup(){
  init();
  Serial.begin(9600);

  myGLCD.InitLCD(LANDSCAPE);
  myGLCD.clrScr();

  myTouch.InitTouch(LANDSCAPE);
  myTouch.setPrecision(PREC_LOW);

  myGLCD.setFont(BigFont);
}

/*
Prints the score and lives in the bottom 16 bits of the screen
*/
void displayScore(){
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.printNumI(SCORE, 272, 224, 3);
  myGLCD.printNumI(LIVES, 112, 224, 1);
}

/*
Provide buttons for new game and high score table
*/
void startScreen(){
  char new_game_str[9] = "NEW GAME";
  char high_score_string[12] = "HIGH SCORES";

  myGLCD.setColor(VGA_BLUE);
  myGLCD.fillRoundRect(62, 50, 258, 90);
  myGLCD.fillRoundRect(62, 134, 258, 174);
  myGLCD.setColor(VGA_WHITE);
  myGLCD.setBackColor(VGA_BLUE);
  myGLCD.print(new_game_str, 96, 62);
  myGLCD.print(high_score_string, 72, 146);

  GAME_MODE = 5;

  myGLCD.setBackColor(VGA_BLACK);
  char scorestr[7] = "SCORE:";
  char livesstr[7] = "LIVES:";
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(scorestr, 176, 224);
  myGLCD.print(livesstr, 0, 224);

}

void drawKeyboard(){
  // Writes the INITIAL :
  myGLCD.setBackColor(VGA_BLACK);
  myGLCD.setColor(VGA_WHITE);
  char initialstring [10] = "INITIALS:" ;
  myGLCD.print( initialstring,  10 , 208);
  myGLCD.setBackColor(VGA_BLUE);

  // Draw the upper row of buttons
  for (int x=0; x<9; x++){
    char alphstring[10] = {65 + x};
    myGLCD.setColor(VGA_BLUE);
    myGLCD.fillRoundRect (5+(x*35), 20, 35+(x*35), 50);
    myGLCD.setColor(VGA_WHITE);
    myGLCD.drawRoundRect (5+(x*35), 20, 35+(x*35), 50);
    myGLCD.print(alphstring, 12+(x*35), 28 );
  }

  // MIDDLE ROW

  for (int i=0; i<9; i++){
    char alphstring[10] = {74 + i};
    myGLCD.setColor(VGA_BLUE);
    myGLCD.fillRoundRect (5+(i*35), 75, 35+(i*35), 105);
    myGLCD.setColor(VGA_WHITE);
    myGLCD.drawRoundRect (5+(i*35), 75, 35+(i*35), 105);
    myGLCD.print(alphstring, 12+(i*35), 83 );
  }


  // BOTTOM ROW
  for (int j = 0; j<8; j++){
    char alphstring[9] = {83 + j};
    myGLCD.setColor(VGA_BLUE);
    myGLCD.fillRoundRect (22+(j*35), 130, 52+(j*35), 160);
    myGLCD.setColor(VGA_WHITE);
    myGLCD.drawRoundRect(22+(j*35), 130, 52+(j*35), 160);
    myGLCD.print(alphstring, 28+(j*35), 138 );
  }
}

char getKeyboardInput(){
  while (true)
  {
    if (myTouch.dataAvailable())
    {
      myTouch.read();
      int x=myTouch.getX();
      int y=myTouch.getY();

      if ((y>=20) && (y<=50))  // Upper row
      {
        if ((x>=5) && (x<=35))  // Button: 1
        {
          return 'A';
          delay(100);
        }
        if ((x>=40) && (x<=70))  // Button: 2
        {
          return 'B';
          delay(100);
        }
        if ((x>=75) && (x<=105))  // Button: 3
        {
          return 'C';
          delay(100);
        }
        if ((x>=110) && (x<=140))  // Button: 4
        {
          return'D';
          delay(100);
        }
        if ((x>=145) && (x<=175))  // Button: 5
        {
          return 'E';
          delay(100);
        }
        if ((x>=180) && (x<=210))  // Button: 6
        {
          return 'F';
          delay(100);
        }
        if ((x>=215) && (x<=245))  // Button: 7
        {
          return'G';
          delay(100);
        }
        if ((x>=250) && (x<=280))  // Button: 8
        {
          return 'H';
          delay(100);
        }
        if ((x>=285) && (x<=315))  // Button: 9
        {
          return'I';
          delay(100);
        }
      }

      // MIDDLE ROW
      if ((y>=75) && (y<=105))  // MIDDLE ROW
      {
        if ((x>=5) && (x<=35))  // Button: 1
        {
          return 'J';
          delay(100);
        }
        if ((x>=40) && (x<=70))  // Button: 2
        {
          return 'K';
          delay(100);
        }
        if ((x>=75) && (x<=105))  // Button: 3
        {
          return'L';
          delay(100);
        }
        if ((x>=110) && (x<=140))  // Button: 4
        {
          return'M';
          delay(100);
        }
        if ((x>=145) && (x<=175))  // Button: 5
        {
          return 'N';
          delay(100);
        }
        if ((x>=180) && (x<=210))  // Button: 6
        {
          return 'O';
          delay(100);
        }
        if ((x>=215) && (x<=245))  // Button: 7
        {
          return 'P';
          delay(100);
        }
        if ((x>=250) && (x<=280))  // Button: 8
        {
          return 'Q';
          delay(100);
        }
        if ((x>=285) && (x<=315))  // Button: 9
        {
          return 'R';
          delay(100);
        }
      }

      // BOTTOM ROW
      if ((y>=130) && (y<=160))  // BOTTOM ROW
      {
        if ((x>=22) && (x<=52))  // Button: 1
        {
          return 'S';
          delay(100);
        }
        if ((x>=57) && (x<=87))  // Button: 2
        {
          return 'T';
          delay(100);
        }
        if ((x>=92) && (x<=122))  // Button: 3
        {
          return 'U';
          delay(100);
        }
        if ((x>=127) && (x<=157))  // Button: 4
        {
          return 'V';
          delay(100);
        }
        if ((x>=162) && (x<=192))  // Button: 5
        {
          return 'W';
          delay(100);
        }
        if ((x>=197) && (x<=227))  // Button: 6
        {
          return 'X';
          delay(100);
        }
        if ((x>=232) && (x<=262))  // Button: 7
        {
          return 'Y';
          delay(100);
        }
        if ((x>=267) && (x<=297))  // Button: 8
        {
          return 'Z' ;
          delay(100);
        }
      }

    }
  }
}

/*
Over writes the EEPROM and shifts highscores down the table
*/
void eepromShift(int address, highScore hs){
  //shift down
  for (int i = 12; i >= address; i -= 3){
    EEPROM[i] = EEPROM[i-3];
    EEPROM[i+1] = EEPROM[i-2];
    EEPROM[i+2] = EEPROM[i-1];
  }
  EEPROM[address] = hs.firstIni;
  EEPROM[address + 1] = hs.lastIni;
  EEPROM[address + 2] = hs.score;
}

/*
Compares the score at the last game to the highscores stored in the EEPROM
high score table.
*/
void searchHighscore(){
  for(int address = 2; address < 15; address += 3){
    if (EEPROM[address] < SCORE){
      drawKeyboard();
      highScore hs;
      hs.firstIni = getKeyboardInput();
      myGLCD.setBackColor(VGA_BLACK);
      myGLCD.setColor(VGA_WHITE);
      char firstIni [2] = {hs.firstIni};
      myGLCD.print(firstIni, 180, 208);
      delay(500);
      hs.lastIni = getKeyboardInput();
      char lastIni [2] = {hs.lastIni};
      myGLCD.print(lastIni, 196, 208);
      hs.score = SCORE;
      eepromShift(address-2, hs);
      break;
    }
  }
}


void printHighScores(){
  char highScoreStr[12] = "HIGH SCORES";
  myGLCD.setColor(VGA_WHITE);
  myGLCD.print(highScoreStr, 80, 50);
  int x = 1;

  for (int i = 0; i < 15; i+=3){
    char initials[3] = {EEPROM[i], EEPROM[i+1]};
    myGLCD.print(initials, 132, 100+(x*16));
    myGLCD.printNumI(EEPROM[i+2], 165, 100+(x*16), 3);
    ++x;
  }
}

void gameOver(){
  myGLCD.setBackColor(VGA_BLACK);
  char game_over_string[10] = "GAME OVER";
  myGLCD.setColor(VGA_RED);
  myGLCD.print(game_over_string, 88, 112);
  LIVES = 3;
  SCORE = 0;
  TIME = 1000;
  delay(3000);
  myGLCD.setColor(VGA_BLACK);
  myGLCD.fillRoundRect(88, 112, 232, 200);
}

/*
Generates a random 16 bit number by reading the voltage of an Arduino pin.
*/
uint16_t random_gen() {
  uint16_t random_num;
  uint16_t bin;
  for (uint16_t i=0; i<16; ++i){
    bin = analogRead(1); //read the voltage coming from unconnected Arduino pin
    random_num ^= bin%2 << i; //take the lowest bit and append to random number to create random uint32_t
    delay(20); //delay so the voltage across the pin has time to fluctuate
  }
  return random_num;
}


/*
Returns true if the correct area of the touchscreen is pressed. Takes the upper and lower bounds
of the area you want to be pressed.
*/
bool pressDetect(int x_lower, int x_upper,int y_lower, int y_upper){
  myTouch.read();
  int x_touch = myTouch.getX();
  int y_touch = myTouch.getY();

  if (x_touch >= x_lower && x_touch <= x_upper && y_touch >= y_lower && y_touch <=y_upper) {
    return 1;
  }
  else {
    return 0;
  }
}

int main(){
  setup();
  //variables for drawing the circles

  while (true){
    if (GAME_MODE == 0){
      startScreen();
    }
    while(myTouch.dataAvailable()){
      if (pressDetect(62, 258, 50, 90) == 1){
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect(62, 50, 258, 90);
        myGLCD.fillRoundRect(62, 134, 258, 174);
        GAME_MODE = 1; //
      }
      else if(pressDetect(62, 258, 134, 174) == 1){
        myGLCD.setColor(VGA_BLACK);
        myGLCD.fillRoundRect(62, 50, 258, 90);
        myGLCD.fillRoundRect(62, 134, 258, 174);
        GAME_MODE = 2; //HIGH SCORE screen
      }
    }

    if (GAME_MODE == 1){
      int hit_count = 0;
      uint16_t x_rand;
      uint16_t y_rand;
      uint8_t score_multiplier = 1;
      bool hit_miss;
      bool touch;
      uint32_t current;

      while (LIVES > 0) {
        displayScore();
        x_rand = RADIUS + (random_gen() % 260);
        y_rand = RADIUS + (random_gen() % 164);
        myGLCD.setColor(VGA_WHITE);
        myGLCD.fillCircle(x_rand, y_rand, RADIUS);
        touch = 0;

        current = millis();

        while(millis() < (current + TIME)) {
          if (myTouch.dataAvailable() == 1){
            hit_miss = pressDetect(x_rand-RADIUS, x_rand+RADIUS, y_rand-RADIUS, y_rand+RADIUS);
            touch = 1;
            if (hit_miss == 1){
              //set to Green and increment score
              myGLCD.setColor(VGA_LIME);
              myGLCD.fillCircle(x_rand, y_rand, RADIUS);
              SCORE += 1*score_multiplier;
              displayScore();
              Serial.println((current+TIME)- millis());
              if ((current+TIME) > millis()){
                delay((current + TIME)- millis());
              }
              hit_count++;

            }
            else if (hit_miss == 0){
              //set to red, decrement score
              myGLCD.setColor(VGA_RED);
              myGLCD.fillCircle(x_rand, y_rand, RADIUS);
              LIVES--;
              if ((current+TIME) > millis()){
                delay((current + TIME)- millis());
              }
              hit_count = 0;
              score_multiplier = 1;
            }
          }
        }
        if (touch == 0){
          myGLCD.setColor(VGA_RED);
          myGLCD.fillCircle(x_rand, y_rand, RADIUS);
          hit_count = 0;
          score_multiplier = 1;
          LIVES--;
        }
        displayScore();
        TIME = TIME*TIME_FACTOR;

        if (hit_count >= 5){
          score_multiplier++;
          hit_count = 0;
        }

        delay(200);

        myGLCD.setColor(0, 0, 0);
        myGLCD.fillCircle(x_rand, y_rand, RADIUS);
      }

      searchHighscore();

      GAME_MODE = 3;
    }

    if (GAME_MODE == 2){
      printHighScores();
      if (myTouch.dataAvailable()){
        myGLCD.fillScr(VGA_BLACK);
        GAME_MODE = 0;
        delay(500);
      }
    }

    if (GAME_MODE == 3){
      myGLCD.fillScr(VGA_BLACK);
      delay(500);
      gameOver();
      GAME_MODE = 0;
    }

  }
  Serial.end();
  return 0;
}
