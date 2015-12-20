/**
 * Demo sketch for the LM15SGFNZ07 LCD display library. This demo lets you play the PaddleWar! game from the Commander
 * Keen series. Connect a potentionmeter to A0, +5v and GND to control your paddle. Simple sounds are provided if you
 * connect a small speaker between pins 7 and GND. The game will start automatically and end when either you or the
 * Arduino reach 21 points. Reset your Arduino for another game.
 * Coded by Maarten Janssen in 2015.
 *
 * Latest version of the libaray can be downloaded from my GitHub page: http://github.com/DhrBaksteen
 * Contact me at maarten@cheerful.nl
 *
 * The LM15SGFNZ07 is an LCD with a 101x80 pixels resolution, capable of displaying 4096 colors. It is found in Siemens
 * mobile phones (models A65, M55, C60, MC60, S55, A60). Connect the LCD to your Arduino as follows:
 * LCD pin   -->   Arduino pin
 *   1 (/CS)        6
 *   2 (/RST)       5
 *   3 (RS)         4
 *   4 (Sclk)       13 (or SPI SCK)
 *   5 (Sdata)      11 (or SPI MOSI)
 *   6 (+3.3v)      3.3v
 *   7 (GND)        GND
 *   8 (LED1)       3.3v
 *   9 (GND)        GND
 *  10 (LED2)       3.3v
 */

#include <SPI.h>
#include <digitalWriteFast.h>
#include <font.h>
#include <LM15SGFNZ07.h>


const unsigned short bmpPaddleWar[296] PROGMEM = {
  0x555, 0x5F5, 0x5F5, 0x5F5, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x5F5,
  0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x5F5,
  0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x555, 0x5F5,
  0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x555, 0x5F5,
  0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5,
  0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x5F5, 0x555, 0x555, 0x5F5,
  0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x555,
  0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x555, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x5F5, 0x555, 0x5F5, 0x555, 0x555, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5, 0x555, 0x5F5
};

const unsigned short bmpPaddle[36] PROGMEM = {
  0x555, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x555,
  0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5,
  0x555, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x5F5, 0x555
};

const unsigned short bmpBall[16] PROGMEM = {
  0x555, 0x5F5, 0x5F5, 0x555,
  0x5F5, 0x5F5, 0x5F5, 0x5F5,
  0x5F5, 0x5F5, 0x5F5, 0x5F5,
  0x555, 0x5F5, 0x5F5, 0x555
};


LM15SGFNZ07 lcd(6,5,4);

int paddleBottom = 0;
float paddleTop = 43;
int p1Score = 0;
int p2Score = 0;
int hold = 0;
float ballX = 48;
float ballY = 42;
float ballDx = 0.5;
float ballDy = -0.5;


/**
 * Initialize LCD and PaddleWar game.
 */
void setup() {
  lcd.init();
  lcd.clear(0x555);
  lcd.drawLine(0, 10, 101, 10, 0x5F5);
  lcd.drawLine(0, 75, 101, 75, 0x5F5);
  lcd.drawString("0", 2, 2, 0x5F5, 0x555);
  lcd.drawString("0", 88, 2, 0x5F5, 0x555);
  lcd.drawBitmap(32, 1, 37, 8, bmpPaddleWar);

  ballDx = (random(2) - 0.5) / 2;
  ballDy = random(2) - 0.5;
  hold = 100;
}


/**
 * Main game loop.
 */
void loop() {
  // Update player paddle position and remove old sprites.
  int newpaddleBottom = analogRead(0) / 12 + 2;
  if (paddleBottom != newpaddleBottom) {
    lcd.fillRect(paddleBottom, 71, 14, 3, 0x555);
    paddleBottom = newpaddleBottom;
  }
  lcd.fillRect((int)paddleTop, 12, 14, 3, 0x555);
  lcd.fillRect((int)ballX, (int)ballY, 4, 4, 0x555);

  if (hold == 0) {
    // Move Arduino's paddle.
    if (ballX < paddleTop + 5 && paddleTop > 0) {
      paddleTop -= 0.25;
    } else if (ballX > paddleTop + 5 && paddleTop < 89) {
      paddleTop += 0.25;
    }

    // Horizontal ball movement and bounce.
    ballX += ballDx;
    if (ballX >= 97) {
      ballX = 97;
      ballDx = -ballDx;
      tone(7, 1000, 100);
    } else if (ballX <= 0) {
      ballX = 0;
      ballDx = -ballDx;
      tone(7, 1000, 100);
    }

    // Vertical ball movement.
    ballY += ballDy;
    if (ballY > 68 && ballY < 71 && ballDy > 0) {
      // Bounce off player's paddle.
      bouncePaddle(paddleBottom);
    } else if (ballY < 15 && ballY > 11 && ballDy < 0) {
      // Bounce off Arduino's paddle.
      bouncePaddle(paddleTop);
    } else if (ballY >= 71 || ballY <= 11) {
      // Player or Arduino missed the ball.
      miss();
    }
  } else {
    hold --;
  }

  // Paint ball and paddles.
  if (hold == 0) {
    lcd.drawBitmap((int)ballX, (int)ballY, 4, 4, bmpBall);
  }
  lcd.drawBitmap((int)paddleTop, 12, 12, 3, bmpPaddle);
  lcd.drawBitmap(paddleBottom, 71, 12, 3, bmpPaddle);

  delay(10);
}


/**
 * Check whether the baddle hits the ball and make it bounce off.
 */
void bouncePaddle(int paddleX) {
  int collision = ballX - paddleX + 4;
  if (collision > 0 && collision < 16) {
    // If the ball is hit reverse Y direction and determine
    // X direction from where the ball hit the paddle
    ballDy = -ballDy;
    tone(7, 1200, 100);
    if (collision < 4) {
      ballDx = -0.5;
    } else if (collision < 8) {
      ballDx = -0.25;
    } else if (collision < 12) {
      ballDx = 0.25;
    } else {
      ballDx = 0.5;
    }
  }
}


/**
 * Either the player or the Arduino missed the ball.
 */
void miss() {
  char score[3];
  if (ballY <= 11) {
    // Update player score. End game if 21.
    p1Score ++;
    tone(7, 600, 100);
    String(p1Score).toCharArray(score, 3);
    lcd.fillRect(1, 2, 12, 8, 0x555);
    lcd.drawString(score, 1, 1, 0x5F5, 0x555);
    if (p1Score == 21) endGame(true);
  } else {
    // Update Arduino's score. End game if 21.
    p2Score ++;
    tone(7, 100, 500);
    String(p2Score).toCharArray(score, 3);
    lcd.fillRect(88, 2, 12, 8, 0x555);
    lcd.drawString(score, 88, 1, 0x5F5, 0x555);
    if (p2Score == 21) endGame(false);
  }

  // Set up next ball.
  ballY = 42;
  ballX = 48;
  ballDx = (random(2) - 0.5) / 2;
  hold = 100;
}


/**
 * Show win or lose message when game ends and stop.
 */
void endGame(bool hasWon) {
  for (int i = 1; i < 180; i += 2) {
    lcd.drawLine(0, i, i, 0, 0x555);
  }
  lcd.fillRect(20, 22, 60, 36, 0x555);
  lcd.drawRect(20, 22, 60, 36, 0x5F5);
  lcd.drawBitmap(32, 25, 37, 8, bmpPaddleWar);
  lcd.drawLine(20, 35, 79, 35, 0x5F5);
  if (hasWon) {
    lcd.drawString("You win!", 34, 43, 0x5F5, 0x555);
  } else {
    lcd.drawString("You lost!", 32, 43, 0x5F5, 0x555);
  }
  while(true);
}
