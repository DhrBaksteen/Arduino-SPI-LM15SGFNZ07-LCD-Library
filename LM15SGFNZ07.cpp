/**
 * Siemens M55 LCD (LM15SGFNZ07) library
 *
 * This library enables you to control an LM15SGFNZ07 LCD module with your Arduino. This updated version of the library
 * supports more of the capabilities of the LCD and runs quicker than the original one thanks to using the SPI port for
 * communication with the LCD. To import this library into your Arduino IDE use the import library function and select
 * the library folder or ZIP file. After importing you can run the included demo found under LM15SGFNZ07 of the examples
 * menu to get an understanding of this library's awesome capabilities.
 *
 * Original code by Mindogas 2011. markauskas.mindaugas@gmail.com
 * Adapted by Maarten Janssen in 2015.
 *
 * Latest version of the libaray can be downloaded from my GitHub page: http://github.com/DhrBaksteen
 * Contact me at maarten@cheerful.nl
 *
 * The LM15SGFNZ07 is an LCD with a 101x80 pixels resolution, capable of displaying 4096 colors. It is found in Siemens
 * mobile phones (models A65, M55, C60, MC60, S55, A60). Connect the LCD to your Arduino as follows:
 * LCD pin   -->   Arduino pin
 *   1 (/CS)         6
 *   2 (/RST)        5
 *   3 (RS)          4
 *   4 (Sclk)        13 (or SPI SCK)
 *   5 (Sdata)       11 (or SPI MOSI)
 *   6 (+3.3v)       3.3v
 *   7 (GND)         GND
 *   8 (LED1)        3.3v
 *   9 (GND)         GND
 *  10 (LED2)        3.3v
 *
 * Note 1: You are free to use any of the Arduino's digital pins for LCD communication. This is configure in the
 *         library's constructor function.
 * Note 2: Pin 1 of the LCD is the right most pin, closest to the edge.
 */


#include <SPI.h>
#include <Arduino.h>
#include <avr/pgmspace.h>
#include <digitalWriteFast.h>
#include <font.h>
#include "LM15SGFNZ07.h"


#define LCD_RS_ON       digitalWriteFast(LCD_RS,HIGH);      // Put LCD in command mode
#define LCD_RS_OFF      digitalWriteFast(LCD_RS,LOW);     // Put LCD in data mode
#define LCD_CS_OFF      digitalWriteFast(LCD_CS,HIGH);      // Disable LCD
#define LCD_CS_ON       digitalWriteFast(LCD_CS,LOW);     // Enable LCD
#define LCD_RESET_ON    digitalWriteFast(LCD_RESET,LOW);    // Put LCD in reset mode
#define LCD_RESET_OFF   digitalWriteFast(LCD_RESET,HIGH);   // Put LCD in normal mode


const unsigned char initData[139] PROGMEM = {
  0xF4, 0x90, 0xB3, 0xA0, 0xD0, 0xF0, 0xE2, 0xD4, 0x70, 0x66,
  0xB2, 0xBA, 0xA1, 0xA3, 0xAB, 0x94, 0x95, 0x95, 0x95, 0xF5,
  0x90, 0xF1, 0x00, 0x10, 0x22, 0x30, 0x45, 0x50, 0x68, 0x70,
  0x8A, 0x90, 0xAC, 0xB0, 0xCE, 0xD0, 0xF2, 0x0F, 0x10, 0x20,
  0x30, 0x43, 0x50, 0x66, 0x70, 0x89, 0x90, 0xAB, 0xB0, 0xCD,
  0xD0, 0xF3, 0x0E, 0x10, 0x2F, 0x30, 0x40, 0x50, 0x64, 0x70,
  0x87, 0x90, 0xAA, 0xB0, 0xCB, 0xD0, 0xF4, 0x0D, 0x10, 0x2E,
  0x30, 0x4F, 0x50, 0xF5, 0x91, 0xF1, 0x01, 0x11, 0x22, 0x31,
  0x43, 0x51, 0x64, 0x71, 0x86, 0x91, 0xA8, 0xB1, 0xCB, 0xD1,
  0xF2, 0x0F, 0x11, 0x21, 0x31, 0x42, 0x51, 0x63, 0x71, 0x85,
  0x91, 0xA6, 0xB1, 0xC8, 0xD1, 0xF3, 0x0B, 0x11, 0x2F, 0x31,
  0x41, 0x51, 0x62, 0x71, 0x83, 0x91, 0xA4, 0xB1, 0xC6, 0xD1,
  0xF4, 0x08, 0x11, 0x2B, 0x31, 0x4F, 0x51, 0x80, 0x94, 0xF5,
  0xA2, 0xF4, 0x60, 0xF0, 0x40, 0x50, 0xC0, 0xF4, 0x70
};

const unsigned char setupData[19] PROGMEM = {
  0xF0, 0x81, 0xF4, 0xB3, 0xA0, 0xF0, 0x06, 0x10, 0x20, 0x30,
  0xF5, 0x0F, 0x1C, 0x2F, 0x34, 0xF0, 0x91, 0xF5, 0x80
};


/**
 * Constructor for the LM15SGFNZ07 library.
 *
 * pinCs    - Arduino pin number connected to LCD's chip select pin (LCD pin 1)
 * pinReset - Arduino pin number connected to LCD's reset pin (LCD pin 2)
 * pinRs    - Arduino pin number connected to LCD's register select pin (LCD pin 3)
 */
LM15SGFNZ07::LM15SGFNZ07(byte pinCs, byte pinReset, byte pinRs) {
  this->LCD_CS    = pinCs;
  this->LCD_RESET = pinReset;
  this->LCD_RS    = pinRs;
}


/**
 * Initialize the LCD.
 */
void LM15SGFNZ07::init(void) {
  SPI.begin();
  pinMode(LCD_CS, OUTPUT);
  pinMode(LCD_RESET, OUTPUT);
  pinMode(LCD_RS, OUTPUT);

  LCD_CS_OFF;
  LCD_RESET_OFF;
  LCD_RS_OFF;
  LCD_RESET_ON;
  delay(10);
  LCD_RESET_OFF;
  delay(10);
  LCD_RS_ON;
  LCD_CS_ON;

  for (int i = 0; i < 139; i ++) {
    SPI.transfer(pgm_read_byte_near(initData + i));
  }

  delay(1);
  LCD_CS_OFF;
  delay(1);
  LCD_CS_ON;

  for (int i = 0; i < 19; i ++) {
    SPI.transfer(pgm_read_byte_near(setupData + i));
  }

  LCD_RS_OFF;

  setContrast(0x1A);
  delay(100);
}


/**
 * Clear the screen with the given color.
 *
 * color - 12-bit color value
 */
void LM15SGFNZ07::clear(unsigned int color) {
  LCD_CS_ON;
  setWindow(0, 0, 101, 80);
  for (int i = 0; i < 8080; i++) {
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
  }
  LCD_CS_OFF;
}


/**
 * Draw a bitmap onto the screen at the given position.
 *
 * x      - Left coordinate
 * y      - Top coordinate
 * width  - Width of the bitmap
 * height - Height of the bitmap
 * bitmap - Pointer to the bitmap image
 */
void LM15SGFNZ07::drawBitmap(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned short *bitmap) {
  LCD_CS_ON;
  setWindow(x, y, width, height);
  for (int i = 0; i < width * height; i ++) {
    SPI.transfer(bitmap[i] >> 8);
    SPI.transfer(bitmap[i] & 0xFF);
  }
  LCD_CS_OFF;
}


/**
 * Draw a bitmap stored in progam memory onto the screen at the given position.
 *
 * x      - Left coordinate
 * y      - Top coordinate
 * width  - Width of the bitmap
 * height - Height of the bitmap
 * bitmap - Pointer to the bitmap image
 */
void LM15SGFNZ07::drawBitmap(unsigned char x,unsigned char y, unsigned char width, unsigned char height, const PROGMEM unsigned short *bitmap) {
  LCD_CS_ON;
  setWindow(x, y, width, height);
  for (int i = 0; i < width * height; i ++) {
    unsigned int data = pgm_read_word_near(bitmap ++);
    SPI.transfer(data >> 8);
    SPI.transfer(data & 0xFF);
  }
  LCD_CS_OFF;
}


/**
 * Draw a line between two points in the given color.
 *
 * x1    - X coordinate of the first point
 * y1    - Y coordinate of the first point
 * x2    - X coordinate of the second point
 * y2    - Y coordinate of the second point
 * color - 12-bit color value
 */
void LM15SGFNZ07::drawLine(unsigned char x1, unsigned char y1, unsigned x2, unsigned char y2, unsigned int color) {
  LCD_CS_ON;
  if (y1 == y2) {
    // Simple solution for horizontal lines.
    setWindow(x1, y1, abs(x2 - x1) + 1, 1);
    for (int i = 0; i <= abs(x2 - x1); i ++) {
      SPI.transfer(color >> 8 );
      SPI.transfer(color & 0xFF);
    }

  } else if (x1 == x2) {
    // Simple solution for vertical lines.
    setWindow(x1, y1, 1, abs(y2 - y1) + 1);
    for (int i = 0; i <= abs(y2 - y1); i ++) {
      SPI.transfer(color >> 8 );
      SPI.transfer(color & 0xFF);
    }

  } else {
    // Draw diagonal line using Bresenham's algorithm.
    if (x2 < x1) {
      unsigned char t = x1;
      x1 = x2;
      x2 = t;
    }

    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    float err = (dx > dy ? dx : -dy) / 2;
    float e2;

    for (;;) {
      drawPixel(x1, y1, color);
      if (x1 == x2 && y1 == y2) break;
      e2 = err;
      if (e2 > -dx) {
        err -= dy;
        x1 += sx;
      }
      if (e2 < dy) {
        err += dx;
        y1 += sy;
      }
    }
  }
  LCD_CS_OFF;
}


/**
 * Draw a pixel on screen in the given color. Note that drawing individual pixels is slow due to having to set the 
 * active window for each pixel.
 *
 * x     - X coordinate of pixel
 * y     - Y coordinate of pixel
 * color - 12-bit color value
 */
void LM15SGFNZ07::drawPixel(unsigned char x, unsigned char y, unsigned int color) {
  LCD_CS_ON;
  setWindow(x, y, 1, 1);
  SPI.transfer(color >> 8 );
  SPI.transfer(color & 0xFF);
  LCD_CS_OFF;
}


/**
 * Draw a rectangular area on the screen with a given color.
 *
 * x      - Left coordinate
 * y      - Top coordinate
 * width  - Rectangle width
 * height - Rectangle height
 * color  - 12-bit color value
 */
void LM15SGFNZ07::drawRect(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned int color) {
  LCD_CS_ON;
  // Top
  setWindow(x, y, width, 1);
  for (int i = 0; i < width; i ++) {
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
  }

  // Bottom
  setWindow(x, y + height - 1, width, 1);
  for (int i = 0; i < width; i ++) {
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
  }

  // Left
  setWindow(x, y, 1, height);
  for (int i = 0; i < height; i ++) {
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
  }

  // Right
  setWindow(x + width - 1, y, 1, height);
  for (int i = 0; i < height; i ++) {
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
  }
  LCD_CS_OFF;
}


/**
 * Draw a string on screen.
 *
 * str        - Pointer to the string to display.
 * x          - X position of the text
 * y          - Y position of the text
 * color      - 12-bit text color
 * background - 12-bit background color
 */
void LM15SGFNZ07::drawString(char *str, unsigned char x, unsigned char y, unsigned int color, unsigned int background) {
  LCD_CS_ON;
  int strPos = 0;

  while (str[strPos] != 0) {
    unsigned int glyphPtr   = (str[strPos] - 32) * 6;
    unsigned int glyphWidth = pgm_read_byte_near(font + (glyphPtr ++));

    for (int i = 0; i < glyphWidth; i ++) {
      setWindow(x ++, y, 1, 8);
      unsigned char glyphData = pgm_read_byte_near(font + (glyphPtr ++));

      for (unsigned char mask = 0x80; mask; mask >>= 1) {
        SPI.transfer(glyphData & mask ? color >> 8 : background >> 8);
        SPI.transfer(glyphData & mask ? color & 0xFF : background & 0xFF);
      }
    }

    setWindow(x ++, y, 1, 8);
    for (unsigned char j = 0; j < 8; j ++) {
      SPI.transfer(background >> 8);
      SPI.transfer(background & 0xFF);
    }
    strPos ++;
  }
  LCD_CS_OFF;
}


/**
 * Fill a rectangular area of the screen with a given color.
 *
 * x      - Left coordinate
 * y      - Top coordinate
 * width  - Rectangle width
 * height - Rectangle height
 * color  - 12-bit color value
 */
void LM15SGFNZ07::fillRect(unsigned char x, unsigned char y, unsigned char width, unsigned char height, unsigned int color) {
  LCD_CS_ON;
  setWindow(x, y, width, height);
  for (int i = 0; i < width * height; i ++) {
    SPI.transfer(color >> 8);
    SPI.transfer(color & 0xFF);
  }
  LCD_CS_OFF;
}


/**
 * Toggle inverse display.
 *
 * inverse - Turns inverse display on when true.
 */
void LM15SGFNZ07::inverseScreen(bool inverse) {
  LCD_RS_ON;
  LCD_CS_ON;
  SPI.transfer(0xF0);
  SPI.transfer(0x90 | (inverse ? 0x09 : 0x01));
  LCD_CS_OFF;
  LCD_RS_OFF;
}


/**
 * Set a number of rows on the display to be inversed using the given inverting mode.
 *
 * y           - The row to start inverting
 * height      - The number of rows to invert
 * inverseMode - The inverting function to be used this can be one of the following:
 *          LCD_INVERSE_OFF:   Turns off line inversions
 *          LCD_INVERSE_ON:    Inversed lines are shown in negative
 *          LCD_INVERSE_BLINK: Inversed lines alternate between positive and negative
 */
void LM15SGFNZ07::setInverseLines(unsigned char y, unsigned char height, unsigned char inverseMode) {
  LCD_RS_ON;
  LCD_CS_ON;
  SPI.transfer(0xF5);
  SPI.transfer(0x40 | (y & 0x0F));
  SPI.transfer(0x50 | (y >> 4));
  SPI.transfer(0xF5);
  SPI.transfer(0x60 | ((y + height - 1) & 0x0F));
  SPI.transfer(0x70 | ((y + height - 1) >> 4));
  SPI.transfer(0xF5);
  SPI.transfer(0x80 | (inverseMode & 0x03));
  LCD_CS_OFF;
  LCD_RS_OFF;
}


/**
 * Set LCD contrast.
 *
 * contrast - Contrast value to set in a range from 0 to 127. A good value for this seems to be 0x1A.
 */
void LM15SGFNZ07::setContrast(unsigned char contrast) {
  LCD_RS_ON;
  LCD_CS_ON;
  SPI.transfer(0xF4);
  SPI.transfer(0xB0 | (contrast >> 4));
  SPI.transfer(0xA0 | (contrast & 0x0F));
  LCD_CS_OFF;
  LCD_RS_OFF;
}


/**
 * Turn the LCD on or off. When turned off display content is preserved.
 *
 * on - Turns the LCD on when true and off when false
 */
void LM15SGFNZ07::setLcdOn(bool on) {
  LCD_RS_ON;
  LCD_CS_ON;
  SPI.transfer(0xF0);
  SPI.transfer(0x80 | (on ? 0x01 : 0x00));
  LCD_CS_OFF;
  LCD_RS_OFF;
}


/**
 * Set which is the top line of the LCD and wrap around display contents.
 *
 * y - Line number to be drawn first in a range from 0 to 79
 */
void LM15SGFNZ07::setStartLine(unsigned char y) {
  LCD_RS_ON;
  LCD_CS_ON;
  SPI.transfer(0xF0);
  SPI.transfer(0x40 | (y & 0x0F));
  SPI.transfer(0x50 | (y >> 4));
  LCD_CS_OFF;
  LCD_RS_OFF;
}


/**
 * Set the active drawing area of the LCD. The cursor will be set to the given (x, y) position.
 *
 * x      - Left coordinate
 * y      - Top coodrinate
 * width  - Width of the active drawing area
 * height - Height of the active drawing area
 */
void LM15SGFNZ07::setWindow(unsigned char x, unsigned char y, unsigned char width, unsigned char height) {
  unsigned char xStart = (x << 1) + 6;
  unsigned char xEnd = ((x + width - 1) << 1) + 7;
  unsigned char yStart = y;
  unsigned char yEnd = y + height - 1;

  LCD_RS_ON;
  SPI.transfer(0xF0);
  SPI.transfer(0x00 | (xStart & 0x0F));
  SPI.transfer(0x10 | (xStart >> 4));
  SPI.transfer(0x20 | (yStart & 0x0F));
  SPI.transfer(0x30 | (yStart >> 4));
  SPI.transfer(0xF5);
  SPI.transfer(0x00 | (xEnd & 0x0F));
  SPI.transfer(0x10 | (xEnd >> 4));
  SPI.transfer(0x20 | (yEnd & 0x0F));
  SPI.transfer(0x30 | (yEnd >> 4));
  LCD_RS_OFF;
}
