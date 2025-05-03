/*Automatic Sunlight Tracking using LDRs
*3B Case Study
*/

#include <Servo.h>
#include <LCD_I2C.h>

LCD_I2C lcd(0x27);
Servo v; //Vertical servo
Servo h; //Horizontal servo

int ldrU = A0;
int ldrD = A1;
int ldrR = A2;
int ldrL = A3;

//Initital Servo Position at startup
int posV = 90;
int posH = 90;

//Initialize variables for blinking arrows in lcd
unsigned long UprevMillis = 0;
unsigned long DprevMillis = 0;
unsigned long LprevMillis = 0;
unsigned long RprevMillis = 0;
const long arrowinterval = 500;
bool Uvisib = true;
bool Dvisib = true;
bool Lvisib = true;
bool Rvisib = true;

//create symbols to show on lcd
byte sun[8] = {
    0b00100,
    0b10001,
    0b01110,
    0b10001,
    0b10001,
    0b01110,
    0b10001,
    0b00100
  };
  byte arrowUp[8] = {
    0b00000,
    0b00100,
    0b01110,
    0b11111,
    0b01110,
    0b01110,
    0b01110,
    0b00000
  };
  byte arrowDown[8] = {
    0b00000,
    0b01110,
    0b01110,
    0b01110,
    0b11111,
    0b01110,
    0b00100,
    0b00000
  };
  byte arrowRight[8] = {
    0b00000,
    0b00100,
    0b00110,
    0b11111,
    0b11111,
    0b00110,
    0b00100,
    0b00000
  };
  byte arrowLeft[8] = {
    0b00000,
    0b00100,
    0b01100,
    0b11111,
    0b11111,
    0b01100,
    0b00100,
    0b00000
  };

  //Place a permanent simple Sun symbol on the LCD
  void setSun(){
    lcd.createChar(0, sun);
    lcd.setCursor(15, 0);
    lcd.write(byte(0));
  }

  void setup(){
    v.attach(9);
    h.attach(10);
    lcd.begin();
    lcd.blacklight();
    setSun();
  }