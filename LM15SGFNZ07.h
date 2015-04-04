/**
 * LM15SGFNZ07.h
 * Siemens M55 LCD (LM15SGFNZ07) library
 * 
 * Original code by Mindogas 2011. markauskas.mindaugas at gmail.com
 * Adapted by Maarten Janssen in 2015. maarten@cheerful.nl
 */

#ifndef LM15SGFNZ07 _h
#define LM15SGFNZ07 _h

#include <Arduino.h>


// Basic colors definitions
#define BLACK   0x000
#define BLUE    0x00F
#define GREEN   0x0F0
#define CYAN    0x0FF
#define RED     0xF00
#define PINK    0xF0F
#define YELLOW  0xFF0
#define WHITE   0xFFF

// Line inverse options
#define LCD_INVERSE_OFF   0x00
#define LCD_INVERSE_ON    0x01
#define LCD_INVERSE_BLINK 0x03


class LM15SGFNZ07 {
	public:
		LM15SGFNZ07(byte pinSdata, byte pinSclk, byte pinRs, byte pinReset, byte pinCs);
		void init(void);
		void clear(unsigned int color);
		void drawBitmap(unsigned char x,unsigned char y, unsigned char width, unsigned char height, unsigned int *bitmap);
		void drawBitmap(unsigned char x,unsigned char y, unsigned char width, unsigned char height, const PROGMEM unsigned int *bitmap);
		void drawLine(unsigned char x1, unsigned char y1, unsigned x2, unsigned char y2, unsigned int color);
		void drawPixel(unsigned char x, unsigned char y,unsigned int color);
		void drawRect(unsigned char x,unsigned char y, unsigned char width, unsigned char height, unsigned int color);
		void drawString(char *str, unsigned char x, unsigned char y, unsigned int color, unsigned int background);
		void fillRect(unsigned char x,unsigned char y, unsigned char width, unsigned char height, unsigned int color);
		void inverseScreen(bool inverse);
		void test(unsigned char value);
		void setContrast(unsigned char contrast);
		void setInverseLines(unsigned char y, unsigned char height, unsigned char inverseMode);
		void setLcdOn(bool on);
		void setStartLine(unsigned char y);
		void setWindow(unsigned char x, unsigned char y, unsigned char width, unsigned char height);
		void send(unsigned char data);
		void sendSafe(unsigned char data);

	private:
		byte LCD_SDATA;
		byte LCD_SCLK;
		byte LCD_RS;
		byte LCD_RESET;
		byte LCD_CS;
};

#endif
