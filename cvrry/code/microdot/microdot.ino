#include <Wire.h> // Enable this line if using Arduino Uno, Mega, etc.
#include <Adafruit_GFX.h>
#include "Adafruit_LEDBackpack.h"

Adafruit_7segment matrix = Adafruit_7segment();

//-----
//setup

#define disp34 0x62    //0x62
#define disp56 0x61    //0x61


byte x = 0;
int x1 = 0;
byte y = 0;
byte rowx = 0;
byte coly = 0;
byte digit = 0;
byte number = 0;
byte colindex = 0;
byte rowindex = 0;
byte asciioffset = 0x10;
byte ampm = 0x21;

byte row[7];

byte col[480] = {                     // even digits (2,4,6) have column bit map for each column of 5x7 matrix
    0x00, 0x00, 0x00, 0x00, 0x00, // (space)  00
    0x00, 0x00, 0x5F, 0x00, 0x00, // !        01
    0x00, 0x07, 0x00, 0x07, 0x00, // "        02
    0x14, 0x7F, 0x14, 0x7F, 0x14, // #        03
    0x24, 0x2A, 0x7F, 0x2A, 0x12, // $        04
    0x23, 0x13, 0x08, 0x64, 0x62, // %        05
    0x36, 0x49, 0x55, 0x22, 0x50, // &        06
    0x00, 0x05, 0x03, 0x00, 0x00, // '        07
    0x00, 0x1C, 0x22, 0x41, 0x00, // (        08
    0x00, 0x41, 0x22, 0x1C, 0x00, // )        09
    0x08, 0x2A, 0x1C, 0x2A, 0x08, // *        0a
    0x08, 0x08, 0x3E, 0x08, 0x08, // +        0b
    0x00, 0x50, 0x30, 0x00, 0x00, // ,        0c
    0x08, 0x08, 0x08, 0x08, 0x08, // -        0d
    0x00, 0x60, 0x60, 0x00, 0x00, // .        0e
    0x20, 0x10, 0x08, 0x04, 0x02, // /        0f
    0x3E, 0x51, 0x49, 0x45, 0x3E, // 0        10
    0x00, 0x42, 0x7F, 0x40, 0x00, // 1        11
    0x42, 0x61, 0x51, 0x49, 0x46, // 2        12
    0x21, 0x41, 0x45, 0x4B, 0x31, // 3        13
    0x18, 0x14, 0x12, 0x7F, 0x10, // 4        14
    0x27, 0x45, 0x45, 0x45, 0x39, // 5        15
    0x3C, 0x4A, 0x49, 0x49, 0x30, // 6        16
    0x01, 0x71, 0x09, 0x05, 0x03, // 7        17
    0x36, 0x49, 0x49, 0x49, 0x36, // 8        18
    0x06, 0x49, 0x49, 0x29, 0x1E, // 9        19
    0x00, 0x36, 0x36, 0x00, 0x00, // :        1a
    0x00, 0x56, 0x36, 0x00, 0x00, // ;        1b
    0x00, 0x08, 0x14, 0x22, 0x41, // <        1c
    0x14, 0x14, 0x14, 0x14, 0x14, // =        1d
    0x41, 0x22, 0x14, 0x08, 0x00, // >        1e
    0x02, 0x01, 0x51, 0x09, 0x06, // ?        1f
    0x32, 0x49, 0x79, 0x41, 0x3E, // @        20
    0x7E, 0x11, 0x11, 0x11, 0x7E, // A        21
    0x7F, 0x49, 0x49, 0x49, 0x36, // B        22
    0x3E, 0x41, 0x41, 0x41, 0x22, // C        23
    0x7F, 0x41, 0x41, 0x22, 0x1C, // D        24
    0x7F, 0x49, 0x49, 0x49, 0x41, // E        25
    0x7F, 0x09, 0x09, 0x01, 0x01, // F        26
    0x3E, 0x41, 0x41, 0x51, 0x32, // G        27
    0x7F, 0x08, 0x08, 0x08, 0x7F, // H        28
    0x00, 0x41, 0x7F, 0x41, 0x00, // I        29
    0x20, 0x40, 0x41, 0x3F, 0x01, // J        2a
    0x7F, 0x08, 0x14, 0x22, 0x41, // K        2b
    0x7F, 0x40, 0x40, 0x40, 0x40, // L        2c
    0x7F, 0x02, 0x04, 0x02, 0x7F, // M        2d
    0x7F, 0x04, 0x08, 0x10, 0x7F, // N        2e
    0x3E, 0x41, 0x41, 0x41, 0x3E, // O        2f
    0x7F, 0x09, 0x09, 0x09, 0x06, // P        30
    0x3E, 0x41, 0x51, 0x21, 0x5E, // Q        31
    0x7F, 0x09, 0x19, 0x29, 0x46, // R        32
    0x46, 0x49, 0x49, 0x49, 0x31, // S        33
    0x01, 0x01, 0x7F, 0x01, 0x01, // T        34
    0x3F, 0x40, 0x40, 0x40, 0x3F, // U        35
    0x1F, 0x20, 0x40, 0x20, 0x1F, // V        36
    0x7F, 0x20, 0x18, 0x20, 0x7F, // W        37
    0x63, 0x14, 0x08, 0x14, 0x63, // X        38
    0x03, 0x04, 0x78, 0x04, 0x03, // Y        39
    0x61, 0x51, 0x49, 0x45, 0x43, // Z        3A
    0x00, 0x00, 0x7F, 0x41, 0x41, // [        3B
    0x02, 0x04, 0x08, 0x10, 0x20, // "\"      3C
    0x41, 0x41, 0x7F, 0x00, 0x00, // ]        3D
    0x04, 0x02, 0x01, 0x02, 0x04, // ^        3E
    0x40, 0x40, 0x40, 0x40, 0x40, // _        3F
    0x00, 0x01, 0x02, 0x04, 0x00, // `        40
    0x20, 0x54, 0x54, 0x54, 0x78, // a        41
    0x7F, 0x48, 0x44, 0x44, 0x38, // b        42
    0x38, 0x44, 0x44, 0x44, 0x20, // c        43
    0x38, 0x44, 0x44, 0x48, 0x7F, // d        44
    0x38, 0x54, 0x54, 0x54, 0x18, // e        45
    0x08, 0x7E, 0x09, 0x01, 0x02, // f        46
    0x08, 0x14, 0x54, 0x54, 0x3C, // g        47
    0x7F, 0x08, 0x04, 0x04, 0x78, // h        48
    0x00, 0x44, 0x7D, 0x40, 0x00, // i        49
    0x20, 0x40, 0x44, 0x3D, 0x00, // j        4A
    0x00, 0x7F, 0x10, 0x28, 0x44, // k        4B
    0x00, 0x41, 0x7F, 0x40, 0x00, // l        4C
    0x7C, 0x04, 0x18, 0x04, 0x78, // m        4D
    0x7C, 0x08, 0x04, 0x04, 0x78, // n        4E
    0x38, 0x44, 0x44, 0x44, 0x38, // o        4F
    0x7C, 0x14, 0x14, 0x14, 0x08, // p        50
    0x08, 0x14, 0x14, 0x18, 0x7C, // q        51
    0x7C, 0x08, 0x04, 0x04, 0x08, // r        52
    0x48, 0x54, 0x54, 0x54, 0x20, // s        53
    0x04, 0x3F, 0x44, 0x40, 0x20, // t        54
    0x3C, 0x40, 0x40, 0x20, 0x7C, // u        55
    0x1C, 0x20, 0x40, 0x20, 0x1C, // v        56
    0x3C, 0x40, 0x30, 0x40, 0x3C, // w        57
    0x44, 0x28, 0x10, 0x28, 0x44, // x        58
    0x0C, 0x50, 0x50, 0x50, 0x3C, // y        59
    0x44, 0x64, 0x54, 0x4C, 0x44, // z        5A
    0x00, 0x08, 0x36, 0x41, 0x00, // {        5B
    0x00, 0x00, 0x7F, 0x00, 0x00, // |        5C
    0x00, 0x41, 0x36, 0x08, 0x00, // }        5D
    0x08, 0x08, 0x2A, 0x1C, 0x08, // ->       5E
    0x08, 0x1C, 0x2A, 0x08, 0x08}; // <-      5F



//------------------------------------------------------
void setup()
{

    matrix.begin(0x70);
    
  Serial.begin(9600);
  while (!Serial) ; // Needed for Leonardo only
  delay(250);

    Serial.println("moin");

//----------------------------------------------------
// microdot setup

// setup up display controllers
//-------------------------------------------------------------------

  Wire.beginTransmission(disp12 );    //  write i2c address 0x61
  Wire.write(0x00);                 // write to configuration register
  Wire.write(0x19);                 //write row data
  Wire.endTransmission(); 
  
  Wire.beginTransmission(disp12 );    //  write i2c address 0x61
  Wire.write(0x0D);                 // write to INTENSITY CONTROL REGISTER
  Wire.write(0x09);                 //write row data
  Wire.endTransmission(); 

  Wire.beginTransmission(disp12 );    //  write i2c address 0x61
  Wire.write(0x19);                 // write to INTENSITY CONTROL REGISTER
  Wire.write(0x80);                 //write row data
  Wire.endTransmission(); 

    Wire.beginTransmission(disp34 );    //  write i2c address 0x61
  Wire.write(0x00);                 // write to configuration register
  Wire.write(0x19);                 //write row data
  Wire.endTransmission(); 
  
  Wire.beginTransmission(disp34);    //  write i2c address 0x61
  Wire.write(0x0D);                 // write to INTENSITY CONTROL REGISTER
  Wire.write(0x09);                 //write row data
  Wire.endTransmission(); 

  Wire.beginTransmission(disp34);    //  write i2c address 0x61
  Wire.write(0x19);                 // write to INTENSITY CONTROL REGISTER
  Wire.write(0x80);                 //write row data

    Wire.beginTransmission(disp56 );    //  write i2c address 0x61
  Wire.write(0x00);                 // write to configuration register
  Wire.write(0x19);                 //write row data
  Wire.endTransmission(); 
  
  Wire.beginTransmission(disp56);    //  write i2c address 0x61
  Wire.write(0x0D);                 // write to INTENSITY CONTROL REGISTER
  Wire.write(0x09);                 //write row data
  Wire.endTransmission(); 

  Wire.beginTransmission(disp56);    //  write i2c address 0x61
  Wire.write(0x19);                 // write to INTENSITY CONTROL REGISTER
  Wire.write(0x80);                 //write row data
  Wire.endTransmission(); 

  delay(15);

//-----