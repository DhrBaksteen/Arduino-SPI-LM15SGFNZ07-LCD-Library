/**
 * Demo sketch for the LM15SGFNZ07 LCD display library. This demo consists of 3 parts to show most of the capabilities
 * of the LM15SGFNZ07 library.
 * Coded by Maarten Janssen in 2015.
 *
 * Latest version of the libaray can be downloaded from my GitHub page: http://github.com/DhrBaksteen
 * Contact me at maarten@cheerful.nl
 *
 * The LM15SGFNZ07 is an LCD with a 101x80 pixels resolution, capable of displaying 4096 colors. It is found in Siemens
 * mobile phones (models A65, M55, C60, MC60, S55, A60). Connect the LCD to your Arduino as follows:
 * LCD pin   -->   Arduino pin
 *   1 (/CS)        6 (Through 10k resistor)
 *   2 (/RST)       5 (Through 10k resistor)
 *   3 (RS)         4 (Through 10k resistor)
 *   4 (Sclk)       3 (Through 10k resistor)
 *   5 (Sdata)      2 (Through 10k resistor)
 *   6 (+3.3v)      3.3v
 *   7 (GND)        GND
 *   8 (LED1)       3.3v
 *   9 (GND)        GND
 *  10 (LED2)       3.3v
 */

#include <LM15SGFNZ07.h>
#include "icon.h"

LM15SGFNZ07 lcd(2,3,4,5,6);

void setup()
{
  lcd.init();
}

void loop() {
  demo1();
  demo2();
  demo3();
}

void demo1() {
  lcd.clear(0x000);
  lcd.fillRect(1,  0, 14, 45, 0xFFF);
  lcd.fillRect(15, 0, 14, 45, 0xFF0);
  lcd.fillRect(29, 0, 14, 45, 0x0FF);
  lcd.fillRect(43, 0, 14, 45, 0x0F0);
  lcd.fillRect(57, 0, 14, 45, 0xF0F);
  lcd.fillRect(71, 0, 14, 45, 0xF00);
  lcd.fillRect(85, 0, 14, 45, 0x00F);
  
  lcd.fillRect(1, 45, 98, 15, 0xF00);
  lcd.drawString("LM15SGFNZ07", 18, 49, 0xFFF, 0xF00);
  
  for (int i = 0; i < 16; i ++) {
    lcd.fillRect(i * 6 + 1, 60, 8, 5, (i << 8) + (i << 4) + i);
    lcd.fillRect(i * 6 + 1, 65, 8, 5, i << 8);
    lcd.fillRect(i * 6 + 1, 70, 8, 5, i << 4);
    lcd.fillRect(i * 6 + 1, 75, 8, 5, i);
  }
  
  delay(10000);
}


void demo2() {
  lcd.clear(0xFFF);
  
  for (int i = 2; i < 80; i += 5) {
    lcd.drawLine(0, i, 100, i, 0x888);
  }
  
  for (int i = 2; i < 101; i += 5) {
    lcd.drawLine(i, 0, i, 79, 0x888);
  }
  
  lcd.fillRect(0, 0, 10, 10, 0x00F);
  lcd.fillRect(91, 0, 10, 10, 0x0F0);
  lcd.fillRect(91, 70, 10, 10, 0xFF0);
  lcd.fillRect(0, 70, 10, 10, 0xF00);
  
  lcd.fillRect(10, 0, 81, 5, 0x0FF);
  lcd.fillRect(96, 10, 5, 60, 0x8F0);
  lcd.fillRect(10, 75, 81, 5, 0xF80);
  lcd.fillRect(0, 10, 5, 60, 0xF0F);
  
  lcd.drawBitmap(34, 24, 32, 32, icon);
  delay(10000);
}


void demo3() {
  lcd.clear(0x22F);
  lcd.drawRect(0, 0, 101, 80, 0xFFF);
  
  for (unsigned char x = 0; x <= 80; x += 10) {
    lcd.drawLine(0, x, x, 80, 0xFFF);
    lcd.drawLine(20 + x, 0, 100, x, 0xFFF);
  }
 
  lcd.drawString("Arduino", 28, 35, 0xFFF, 0x22F);
  lcd.drawBitmap(63, 34, 11, 9, heart);
  delay(10000);
}

