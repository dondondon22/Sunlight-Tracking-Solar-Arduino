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

int posV = 90;
int posH = 90;