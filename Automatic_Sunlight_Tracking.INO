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
    lcd.backlight();
    setSun();
  }
  //update X and Y servo angles shown on the LCD
  void updateLCDXY(int posX_Prev, int posY_Prev, int posX, int posY) {
    if (posX != posX_Prev || posY != posY_Prev){
      lcd.setCursor(0, 0);
      lcd.print("               ");
    }
    lcd.setCursor(0, 0);
    lcd.print("X: ");
    lcd.setCursor(2, 0);
    lcd.print(posX);
    lcd.setCursor(6, 0);
    lcd.print("Y: ");
    lcd.setCursor(8, 0);
    lcd.print(posY);
    setSun();
  }

  //Blinking of Up, Down, Left, Right Arrows
  void updateUDLR(int posX_Prev, int posY_Prev, int posX, int posY) {
    unsigned long currentMillis = millis();
  
    lcd.setCursor(0, 1);
    lcd.print("U");
  
    if (currentMillis - UprevMillis >= arrowinterval) {
      UprevMillis = currentMillis;
      if (Uvisib) {
        lcd.createChar(1, arrowUp);
        lcd.setCursor(1, 1);
        lcd.write(byte(1));
      } else {
        if (posY_Prev > posY && posY_Prev != posY) {
          lcd.setCursor(1, 1);
          lcd.print(" ");
        }
      }
      
      Uvisib = !Uvisib;
    }
  
    lcd.setCursor(3, 1);
    lcd.print("D");
  
    if (currentMillis - DprevMillis >= arrowinterval) {
      DprevMillis = currentMillis;
      if (Dvisib) {
        lcd.createChar(2, arrowDown);
        lcd.setCursor(4, 1);
        lcd.write(byte(2));
      } else {
        if (posY_Prev < posY && posY_Prev != posY) {
          lcd.setCursor(4, 1);
          lcd.print(" ");
        }
      }
      
      Dvisib = !Dvisib;
    }
  
    lcd.setCursor(6, 1);
    lcd.print("L");
  
    if (currentMillis - LprevMillis >= arrowinterval) {
      LprevMillis = currentMillis;
      if (Lvisib) {
        lcd.createChar(3, arrowLeft);
        lcd.setCursor(7, 1);
        lcd.write(byte(3));
      } else {
        if (posX_Prev > posX && posX_Prev != posX) {
          lcd.setCursor(7, 1);
          lcd.print(" ");
        }
      }
      
      Lvisib = !Lvisib;
    }
  
  
    lcd.setCursor(9, 1);
    lcd.print("R");
  
    if (currentMillis - RprevMillis >= arrowinterval) {
      RprevMillis = currentMillis;
      if (Rvisib) {
        lcd.createChar(4, arrowRight);
        lcd.setCursor(10, 1);
        lcd.write(byte(4));
      } else {
        if (posX_Prev < posX && posX_Prev != posX) {
          lcd.setCursor(10, 1);
          lcd.print(" ");
        }
      }
      
      Rvisib = !Rvisib;
    }
}

void loop() {
    int valU = analogRead(ldrU);
    int valD = analogRead(ldrD);
    int valR = analogRead(ldrR);
    int valL = analogRead(ldrL);

   // Tolerance to prevent jittering
  int tolerance = 50;

  int posV_Prev = posV;
  int posH_Prev = posH;

  // Up and Down value for Vservo motion
  if (abs(valU - valD) > tolerance) {
    if (valU > valD) {
      posV--;
    } else {
      posV++;
    }
  }

  //Right and Left value for Hservo motion
  if (abs(valR - valL) > tolerance) {
    if (valR > valL) {
      posH++;
    } else {
      posH--;
    }
  }

  // Constrain servo angle positions
  posV = constrain(posV, 2, 177);
  posH = constrain(posH, 2, 177);

  updateLCDXY(posH_Prev, posV_Prev, posH, posV);
  updateUDLR(posH_Prev, posV_Prev, posH, posV);

  // Move servos
  v.write(posV);
  h.write(posH);

  delay(200); // Small delay to prevent too fast motion
}