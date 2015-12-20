#LM15SGFNZ07 LCD Library for Arduino

This library enables you to control an LM15SGFNZ07 LCD module with your Arduino. The LM15SGFNZ07 is an LCD with a 101x80 pixels resolution, capable of displaying 4096 colors. It is found in Siemens mobile phones (models A65, M55, C60, MC60, S55, A60).

This library is an updated version of the original by Mindogas (https://bitbucket.org/mindogas/lm15sgfnz07) that supports more of the capabilities of the LCD and runs quicker than the original thanks to the use of the Arduino's SPI port for communication. 

To import this library into your Arduino IDE use the import library function and select the library folder or ZIP file. After importing you can run the included demo and PaddleWar! game found under LM15SGFNZ07 of the examples menu to get an understanding of this library's awesome capabilities.

---

###Connecting the LCD to the Arduino

Connect the LCD using the following wiring configuration:

| LCD pin   | Arduino pin              |
|-----------|--------------------------|
| 1 (/cs)<sup>1</sup>   | 6<sup>2</sup> |
| 2 (/rst)  | 5<sup>2</sup> |
| 3 (rs)    | 4<sup>2</sup> |
| 4 (sclk)  | 13 (or SPI SCK) |
| 5 (sdata) | 11 (or SPI MOSI) |
| 6 (+3.3v) | 3.3v |
| 7 (gnd)   | gnd |
| 8 (led1)  | 3.3v |
| 9 (led gnd)   | gnd |
| 10 (led2) | 3.3v |

<sup>1</sup> *Pin 1 of the LCD is the right most pin, closest to the edge.*   
<sup>2</sup> *The Arduino pin numbers shown here are the default ones. You are free to use any of the Arduino's digital pins for LCD communication. This is configured when creating a library instance.*

If you are in desperate need for more free digital pins you can tie LCD pin 1 directly to ground, but stability of the LCD will suffer if you do so!

---

###Included examples

The library comes with two examples:  
* A showcase of the library functions.  
* The game PaddleWar. This is the same PaddleWar game as included in the Commander Keen games. You play a game of ping pong against the Arduino and try to be the first to score 21 points. To play the game connect a potentiometer between pins A0, +5v and GND and a small speaker between pins 7 and GND. The game will start automatically when you power up the Arduino. Use the potentiometer to move wour paddle and beat the other player. The first player to reach 21 points wins and the game ends. Reset your Arduino to play again.
  
<img src="/paddlewar_diagram.png" width="300"/>

---

###Geting started with the library

To get started be sure to first import the LM15SGFNZ07 library into your Arduino project. 
You then need to create an instance of the LCD driver and setup the pin configuration.
Before sending any commands to the LCD you must always initialize it first by calling the init() function. 
This puts the LCD in a ready state (you will probably see some garbage on screen).
See below for a boilerplate example or try the demo by selecting it from the Arduino IDE's examples menu.

```C
#include <SPI.h>
#include <LM15SGFNZ07.h>

LM15SGFNZ07 lcd(6, 5, 4);   // Create lcd instance and set pin configuration.

void setup() {
  lcd.init();                     // Initialize lcd.
  lcd.clear(0x000);
  lcd.drawString("Hello World!", 5, 5, 0xFFF);
}

void loop() {
  // Do something awesome!
}
```

---

###Functions reference
Below are the functions available in this library.
     
     
-----
####Constructor
```C
LM15SGFNZ07(byte pinSdata, byte pinSclk, byte pinRs, byte pinReset, byte pinCs);
```
Create an instance of the LCD driver and set pin configuration
<table>
<tr><td>pinSdata</td><td>Arduino pin number connected to LCD's serial data pin (LCD pin 5)</td></tr>
<tr><td>pinSclk</td><td>Arduino pin number connected to LCD's serial clock pin (LCD pin 4)</td></tr>     
<tr><td>pinRs</td><td>Arduino pin number connected to LCD's register select pin (LCD pin 3)</td></tr>
<tr><td>pinReset</td><td>Arduino pin number connected to LCD's reset pin (LCD pin 2)</td></tr>
<tr><td>pinCs</td><td>Arduino pin number connected to LCD's chip select pin (LCD pin 1)</td></tr>
</table>
     
     
-----
####init
```C
void init(void);
```
Configures the pinMode of the Arduino pins associated with the LCD and initializes the display controller.
This function must always be called before sending any subsequent commands.
     
     
-----
####clear
```C
void clear(unsigned int color);
```
Clears the screen with the given color value.
<table>
<tr><td>color</td><td>A 12-bit color value</td></tr>
</table>
     
     
-----
####drawBitmap
```C
void drawBitmap(unsigned char x,unsigned char y, unsigned char width, unsigned char height, unsigned int *bitmap);
void drawBitmap(unsigned char x,unsigned char y, unsigned char width, unsigned char height, const PROGMEM unsigned int *bitmap);
```
Draw a bitmap onto the screen. 
The bitmap can either be stored locally in SRAM or in program memory.
Bitmap data must be stored as a one-dimensional array of 16-bit integers where each integer represents a 12-bit color value.
<table>
<tr><td>x</td><td>X position on screen</td></tr>
<tr><td>y</td><td>Y position on screen</td></tr>
<tr><td>width</td><td>Width of the bitmap image</td></tr>
<tr><td>height</td><td>Height of the bitmap image</td></tr>
<tr><td>bitmap</td><td>Pointer to bitmap data in SRAM or program memory</td></tr>
</table>
     
     
-----
####drawLine
```C
void drawLine(unsigned char x1, unsigned char y1, unsigned x2, unsigned char y2, unsigned int color);
```
Draw a line between two points in the given color.
<table>
<tr><td>x1</td><td>X coordinate of start point</td></tr>
<tr><td>y1</td><td>Y coordinate of start point</td></tr>
<tr><td>x2</td><td>X coordinate of end point</td></tr>
<tr><td>y2</td><td>Y coordinate of end point</td></tr>
<tr><td>color</td><td>12-bit color value</td></tr>
</table>
     
     
-----
####drawPixel
```C
void drawPixel(unsigned char x, unsigned char y,unsigned int color);
```
Place a single pixel on screen.
<table>
<tr><td>x</td><td>X coordinate</td></tr>
<tr><td>y</td><td>Y coordinate</td></tr>
<tr><td>color</td><td>12-bit color value</td></tr>
</table>
     
     
-----
####drawRect
```C
void drawRect(unsigned char x,unsigned char y, unsigned char width, unsigned char height, unsigned int color);
```
Draw a rectangle on screen in the given color.
<table>
<tr><td>x</td><td>X coordinate of left edge</td></tr>
<tr><td>y</td><td>Y coordinate of top edge</td></tr>
<tr><td>width</td><td>Width of the rectangle</td></tr>
<tr><td>height</td><td>Height of the rectangle</td></tr>
<tr><td>color</td><td>12-bit color value</td></tr>
</table>
     
     
-----
####drawString
```C
void drawString(char *str, unsigned char x, unsigned char y, unsigned int color, unsigned int background);
```
Print a text on screen. 
Text can have any color and always has a solid background color.
In order to put as many characters on a small screen a proportional font is used.
Spacing between characters is 1 pixel.

To replace the font alter the font.h file that comes with the library.
For each glyph in the font we define the number of columns in the glyph bitmap between 1 and 5.
This is followed by the bit pattern of each column.
Glyphs that are less than 5 columns wide must be padded so that each glyph takes 6 bytes of data.
<table>
<tr><td>str</td><td>The text string to print</td></tr>
<tr><td>x</td><td>X coordinate of the text</td></tr>
<tr><td>y</td><td>Y coordinate of the text</td></tr>
<tr><td>color</td><td>12-bit color of the text</td></tr>
<tr><td>background</td><td>12-bit color of the text background</td></tr>
</table>
     
     
-----
####fillRect
```C
void fillRect(unsigned char x,unsigned char y, unsigned char width, unsigned char height, unsigned int color);
```
Draws a filled rectangle.
<table>
<tr><td>x</td><td>X coordinate of left edge</td></tr>
<tr><td>y</td><td>Y coordinate of top edge</td></tr>
<tr><td>width</td><td>Width of the rectangle</td></tr>
<tr><td>height</td><td>Height of the rectangle</td></tr>
<tr><td>color</td><td>12-bit color value</td></tr>
</table>
     
     
-----
####inverseScreen
```C
void inverseScreen(bool inverse);
```
Switches inverse colors on or off.
This can be useful to briefly flash the screen to get a users attention.
<table>
<tr><td>inverse</td><td>Switches inverse color mode on when true</td></tr>
</table>
     
     
-----
####setContrast
```C
void setContrast(unsigned char contrast);
```
Sets the contrast of the sreen.
A good contrast value seems to be 0x1A, which is also set as default by the init function.
<table>
<tr><td>contrast</td><td>A contrast value ranging from 0 to 127</td></tr>
</table>
     
     
-----
####setInverseLines
```C
void setInverseLines(unsigned char y, unsigned char height, unsigned char inverseMode);
```
Sets inverse or blink mode for a certain number of lines on the screen.
The controller of this LCD is able to blink a certain number of lines on the screen every 32 frames.
This can be a useful function to highlight certain areas on the screen.
For example a selected menu option.
If the screen is already in inverse mode then setting lines to inverse will reverse the effect.

Three inverting modes are available:
* LCD_INVERSE_OFF - Disables line inversion mode
* LCD_INVERSE_ON - Inverses the given area on screen
* LCD_INVERSE_BLINK - Inverses and blinks the given area
<table>
<tr><td>y</td><td>Start line</td></tr>
<tr><td>height</td><td>Number of lines to inverse</td></tr>
<tr><td>inverseMode</td><td>Defines how the lines are inverted</td></tr>
</table>
     
     
-----
####setLcdOn
```C
void setLcdOn(bool on);
```
Switches the LCD screen on or off.
The init method switches the screen on, so this function is not required prior to sending any commands.
When the screen is switched off the content is preserved.
<table>
<tr><td>on</td><td>Switches the screen on when true and off when false</td></tr>
</table>
     
     
-----
####setStartLine
```C
void setStartLine(unsigned char y);
```
Sets the line that is to be displayed as the first line in screen.
After line 79 the display wraps around to line 0.
<table>
<tr><td>y</td><td>Line number to be displayed on top ranging from 0 to 79</td></tr>
</table>
     
    
-----
####setWindow
```C
void setWindow(unsigned char x, unsigned char y, unsigned char width, unsigned char height);
```
Defines the active drawing area.
When color data is sent to the display it is placed in this area.
Both width and height wrap around when more data is sent than fit into the area.
<table>
<tr><td>x</td><td>X coordinate of the left edge of the active area</td></tr>
<tr><td>y</td><td>Y coordinate of the top edge of the active area</td></tr>
<tr><td>width</td><td>Width of the area</td></tr>
<tr><td>height</td><td>Height of the area</td></tr>
</table>
     
     
-----
####send
```C
void send(unsigned char data);
```
Send the given byte to the LCD controller.
This function assumes that the correct data/command register has already been selected.
<table>
<tr><td>data</td><td>The data or command to send to the LCD controller</td></tr>
</table>
     
     
-----
####sendSafe
```C
void sendSafe(unsigned char data);
```
Send the given byte to the LCD controller in a safe way by first toggling the /CS pin.
It is used by the functions of this library when sending commands only.
By toggling the /CS pin before sending the command we get more relyability, which is especially important when sending command bytes.
This function assumes that the correct data/command register has already been selected by LCD_RS_ON or LCD_RS_OFF.
<table>
<tr><td>data</td><td>The data or command to send to the LCD controller</td></tr>
</table>
     
     
-----
####Colors
The following predefined colors are available.
<table>
<tr><td>BLACK</td><td>0x000</td></tr>
<tr><td>BLUE</td><td>0x00F</td></tr>
<tr><td>GREEN</td><td>0x0F0</td></tr>
<tr><td>CYAN</td><td>0x0FF</td></tr>
<tr><td>RED</td><td>0xF00</td></tr>
<tr><td>PINK</td><td>0xF0F</td></tr>
<tr><td>YELLOW</td><td>0xFF0</td></tr>
<tr><td>WHITE</td><td>0xFFF</td></tr>
</table>
     
     
-----
####Pin toggle functions
The following functions toggle the control pins of the LCD.
<table>
<tr><td>LCD_RS_ON</td><td>Put the LCD in command mode</td></tr>
<tr><td>LCD_RS_OFF</td><td>Put the LCD in data mode</td></tr>
<tr><td>LCD_CS_OFF</td><td>Disables the LCD (current state is preserved)</td></tr>
<tr><td>LCD_CS_ON</td><td>Enables the LCD</td></tr>
<tr><td>LCD_RESET_ON</td><td>Puts the LCD in reset mode</td></tr>
<tr><td>LCD_RESET_OFF</td><td>Puts the LCD in normal mode</td></tr>
</table>
