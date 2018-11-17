#include <Adafruit_GFX.h>
#include <Adafruit_SPITFT.h>
#include <Adafruit_SPITFT_Macros.h>
#include <gfxfont.h>

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

const int button1Pin = 9;
const int button2Pin = 8;
const int button3Pin = 7;

const int sound = 6;

int button1State = 0;
int button2State = 0;
int button3State = 0;



// 'intro 1', 128x64px
const unsigned char intro [] PROGMEM = {
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xb8, 0x3a, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xc7, 0x96, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xdf, 0xde, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xcf, 0xce, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x78, 0x7c, 0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0xbb, 0x7e, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfc, 0x7b, 0x7c, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfd, 0x7c, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0xfb, 0x7f, 0xff, 0xff, 0xff, 0xcc, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xdf, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xb3, 0x7f, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 0x0f, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x7f, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xbf, 0x7f, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xde, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xed, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xf3, 0xff, 0xcc,
  0xff, 0xfe, 0x03, 0x01, 0x3c, 0x9c, 0x9c, 0xe0, 0xf0, 0x30, 0x70, 0x0c, 0x13, 0x9f, 0xff, 0xcc,
  0xff, 0xfe, 0x03, 0x01, 0x3c, 0x9c, 0x9c, 0xe0, 0xf0, 0x30, 0x70, 0x0c, 0x13, 0x93, 0xff, 0xff,
  0x33, 0xfe, 0x79, 0x3f, 0x0c, 0x9c, 0x9c, 0x9f, 0x27, 0xe7, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xff,
  0x33, 0xfe, 0x79, 0x3f, 0x0c, 0x9c, 0x9c, 0x9f, 0x27, 0xe7, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xcc,
  0xff, 0xfe, 0x79, 0x3f, 0x24, 0x99, 0x9c, 0x9f, 0x27, 0xe7, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xcc,
  0xff, 0xfe, 0x79, 0x3f, 0x24, 0x81, 0x9c, 0x9f, 0x27, 0xe7, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xff,
  0x33, 0xfe, 0x79, 0x03, 0x30, 0x83, 0xe4, 0x9f, 0x27, 0xe7, 0x9e, 0x79, 0xf0, 0x13, 0xff, 0xff,
  0x33, 0xfe, 0x03, 0x03, 0x30, 0x91, 0xe0, 0x9f, 0x27, 0xe7, 0x9e, 0x79, 0xf0, 0x13, 0xff, 0xcc,
  0xff, 0xfe, 0x03, 0x3f, 0x38, 0x99, 0xf0, 0x9f, 0x26, 0x27, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xcc,
  0xff, 0xfe, 0x79, 0x3f, 0x38, 0x9c, 0xfc, 0x9f, 0x26, 0x27, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xff,
  0x33, 0xfe, 0x79, 0x3f, 0x3c, 0x9c, 0xfc, 0x9f, 0x27, 0xa7, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xff,
  0x33, 0xfe, 0x79, 0x3f, 0x3c, 0x9c, 0xf8, 0x9f, 0x27, 0xa7, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xcc,
  0xff, 0xfe, 0x79, 0x3f, 0x3c, 0x9c, 0xf0, 0x9f, 0x27, 0xa7, 0x9e, 0x79, 0xf3, 0x93, 0xff, 0xcc,
  0xff, 0xfe, 0x03, 0x01, 0x3c, 0x9c, 0xc3, 0xe0, 0xf8, 0x78, 0x7e, 0x78, 0x13, 0x93, 0xff, 0xff,
  0x33, 0xfe, 0x03, 0x01, 0x3c, 0x9c, 0xcf, 0xe0, 0xf8, 0x78, 0x7e, 0x7e, 0x13, 0x93, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0x74, 0xbb, 0x37, 0x4e, 0x31, 0xab, 0xbf, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x75, 0xb6, 0xd2, 0x5e, 0xd5, 0x6b, 0xbf, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0x74, 0xb6, 0xd5, 0x4e, 0x31, 0x67, 0xbf, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0x55, 0xb6, 0xd7, 0x5e, 0xd5, 0x6b, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xac, 0x9b, 0x37, 0x4e, 0x35, 0xab, 0xbf, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc,
  0x33, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xcc
};

// 'dead', 24x24px
const unsigned char death [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x00, 0x00, 0x1f, 0x80, 0x00, 0x30, 0xc0, 0x00,
	0x64, 0x20, 0x00, 0x4e, 0x20, 0x00, 0x44, 0x20, 0x00, 0x84, 0x10, 0x00, 0x80, 0x10, 0x00, 0x80,
	0x10, 0x01, 0x9b, 0x98, 0x01, 0x80, 0x18, 0x01, 0xbb, 0x58, 0x01, 0x80, 0x18, 0x25, 0xc0, 0x3c,
	0x11, 0xff, 0xf4, 0x04, 0xf9, 0x98, 0x03, 0xa6, 0xa0, 0x06, 0x40, 0xd0, 0x21, 0x11, 0x00, 0x14,
	0x04, 0x00, 0x02, 0x00, 0x80, 0x00, 0x00, 0x00
};

// 'cat1', 46x46px
const unsigned char cat1 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x30, 0x00, 0x00, 0x00, 0xf0, 0x01, 0xd0, 0x00, 0x00,
  0x00, 0xce, 0x07, 0x10, 0x00, 0x00, 0x00, 0xdf, 0xf9, 0x90, 0x00, 0x00, 0x00, 0x56, 0xf9, 0x90,
  0xf0, 0x00, 0x00, 0xd1, 0xfa, 0xd0, 0x88, 0x00, 0x00, 0x61, 0xc9, 0x90, 0x88, 0x00, 0x00, 0xc0,
  0xf0, 0x50, 0x84, 0x00, 0x01, 0x00, 0x00, 0x30, 0x84, 0x00, 0x01, 0x10, 0x02, 0x10, 0x84, 0x00,
  0x03, 0x10, 0x02, 0x08, 0x82, 0x00, 0x03, 0x00, 0x80, 0x0c, 0x42, 0x00, 0x03, 0x01, 0x40, 0x0c,
  0x42, 0x00, 0x01, 0x80, 0x00, 0x08, 0x46, 0x00, 0x00, 0x80, 0x00, 0x18, 0x47, 0x00, 0x00, 0x60,
  0x00, 0x30, 0x27, 0x00, 0x00, 0x3f, 0xff, 0xf0, 0x27, 0x00, 0x00, 0x3f, 0xff, 0xf8, 0x13, 0x00,
  0x00, 0x20, 0x30, 0x78, 0x11, 0x00, 0x00, 0x20, 0x30, 0x7c, 0x11, 0x00, 0x00, 0x20, 0x48, 0x7e,
  0x09, 0x00, 0x00, 0x20, 0x30, 0x7e, 0x09, 0x00, 0x00, 0x20, 0x00, 0x7f, 0x09, 0x00, 0x00, 0x20,
  0x00, 0x3f, 0x09, 0x00, 0x00, 0x20, 0x00, 0x3f, 0x11, 0x00, 0x00, 0x20, 0x00, 0x0f, 0xa1, 0x00,
  0x00, 0x20, 0x00, 0x0f, 0xc2, 0x00, 0x00, 0x20, 0x00, 0x07, 0x86, 0x00, 0x00, 0x21, 0x21, 0x00,
  0x98, 0x00, 0x00, 0x21, 0x23, 0x00, 0x90, 0x00, 0x00, 0x21, 0x27, 0x01, 0x20, 0x00, 0x00, 0x21,
  0x2f, 0x01, 0xc0, 0x00, 0x00, 0x21, 0xef, 0x06, 0x00, 0x00, 0x00, 0x11, 0x1f, 0xf8, 0x00, 0x00,
  0x00, 0x0e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};
// 'cat2', 46x46px
const unsigned char cat2 [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x00, 0x30, 0x00, 0x00,
  0x00, 0xf0, 0x01, 0xd0, 0x00, 0x00, 0x00, 0xce, 0x07, 0x10, 0x00, 0x00, 0x00, 0xdf, 0xf9, 0x90,
  0x00, 0x00, 0x00, 0x56, 0xf9, 0x90, 0x00, 0x60, 0x00, 0xd1, 0xfa, 0xd0, 0x00, 0x90, 0x00, 0x61,
  0xc9, 0x90, 0x01, 0x90, 0x00, 0xc0, 0xf0, 0x50, 0x02, 0x10, 0x01, 0x00, 0x00, 0x30, 0x02, 0x30,
  0x01, 0x10, 0x02, 0x10, 0x02, 0x60, 0x03, 0x28, 0x05, 0x08, 0x04, 0xe0, 0x03, 0x00, 0x80, 0x0c,
  0x04, 0xe0, 0x03, 0x01, 0x40, 0x0c, 0x05, 0xe0, 0x01, 0x80, 0x00, 0x08, 0x05, 0xe0, 0x00, 0x80,
  0x00, 0x18, 0x04, 0xc0, 0x00, 0x60, 0x00, 0x30, 0x08, 0xc0, 0x00, 0x3f, 0xff, 0xf8, 0x08, 0x40,
  0x00, 0x23, 0xf0, 0x78, 0x08, 0x80, 0x00, 0x20, 0xc0, 0x7c, 0x10, 0x80, 0x00, 0x21, 0x20, 0x7e,
  0x11, 0x00, 0x00, 0x20, 0xc0, 0x7e, 0x21, 0x00, 0x00, 0x20, 0x00, 0x7f, 0x22, 0x00, 0x00, 0x20,
  0x00, 0x3f, 0x42, 0x00, 0x00, 0x20, 0x00, 0x3f, 0x84, 0x00, 0x00, 0x20, 0x00, 0x0f, 0x84, 0x00,
  0x00, 0x20, 0x00, 0x0f, 0x88, 0x00, 0x00, 0x20, 0x00, 0x07, 0x90, 0x00, 0x00, 0x21, 0x21, 0x00,
  0xa0, 0x00, 0x00, 0x21, 0x23, 0x00, 0xc0, 0x00, 0x00, 0x21, 0x27, 0x01, 0x00, 0x00, 0x00, 0x21,
  0x2f, 0x01, 0x80, 0x00, 0x00, 0x21, 0xef, 0x06, 0x00, 0x00, 0x00, 0x11, 0x1f, 0xf8, 0x00, 0x00,
  0x00, 0x0e, 0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};



const unsigned char* cat[2] = {
    cat1,cat2
    };


// 'cat1_sad', 46x46px
const unsigned char cat1_sad [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x24, 0x00,
  0x00, 0x00, 0x00, 0x14, 0x44, 0x01, 0x80, 0x00, 0x00, 0x22, 0x84, 0x06, 0x80, 0x00, 0x00, 0x21,
  0x9e, 0x08, 0x80, 0x00, 0x00, 0x21, 0x03, 0xf0, 0x80, 0x00, 0x00, 0x21, 0x01, 0xf8, 0x80, 0x00,
  0x00, 0x30, 0x81, 0xe0, 0x80, 0x00, 0x00, 0x18, 0x80, 0x00, 0x80, 0x00, 0x00, 0x1c, 0xfc, 0x00,
  0x80, 0x00, 0x00, 0x1e, 0xdf, 0x00, 0x80, 0x00, 0x00, 0x1e, 0x7f, 0x80, 0x80, 0x00, 0x00, 0x0e,
  0x7f, 0xe0, 0x80, 0x00, 0x00, 0x0c, 0x77, 0xf1, 0x00, 0x00, 0x00, 0x08, 0x7f, 0xfd, 0x00, 0x00,
  0x00, 0x18, 0x3f, 0xf3, 0x00, 0x00, 0x00, 0x14, 0x3f, 0xf2, 0x00, 0x00, 0x00, 0x24, 0x3f, 0xe1,
  0x00, 0x00, 0x00, 0x24, 0x3f, 0xe1, 0x00, 0x00, 0x00, 0x24, 0x3f, 0xc0, 0x80, 0x00, 0x00, 0x22,
  0x1f, 0x80, 0x80, 0x00, 0x00, 0x42, 0x17, 0x00, 0x40, 0x00, 0x00, 0x41, 0x18, 0x00, 0x40, 0x00,
  0x00, 0x21, 0x10, 0x00, 0x40, 0x00, 0x00, 0x21, 0x10, 0x00, 0x80, 0x00, 0x00, 0x20, 0x90, 0x00,
  0x80, 0x00, 0x00, 0x20, 0x40, 0x00, 0x80, 0x00, 0x00, 0x10, 0x20, 0x01, 0x00, 0x00, 0x00, 0x08,
  0x14, 0x02, 0x00, 0x00, 0x00, 0x04, 0x08, 0x0c, 0x00, 0x00, 0x00, 0x03, 0x95, 0x70, 0x00, 0x00,
  0x00, 0x00, 0x7e, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};

// 'cat2_sad', 46x46px
const unsigned char cat2_sad [] PROGMEM = {
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x50, 0x00, 0x00, 0x00, 0x00, 0x00, 0x88, 0x00, 0x00, 0x00, 0x00, 0x18, 0x84, 0x00,
  0x00, 0x00, 0x00, 0x14, 0x82, 0x00, 0x00, 0x00, 0x00, 0x22, 0x83, 0xe0, 0x00, 0x00, 0x00, 0x21,
  0x9f, 0xff, 0xfc, 0x00, 0x00, 0x21, 0x03, 0xf0, 0x02, 0x00, 0x00, 0x21, 0x03, 0xf8, 0x04, 0x00,
  0x00, 0x30, 0x81, 0xe0, 0x08, 0x00, 0x00, 0x18, 0x80, 0x00, 0xb0, 0x00, 0x00, 0x1c, 0xfc, 0x00,
  0xc0, 0x00, 0x00, 0x1e, 0xdf, 0x00, 0x80, 0x00, 0x00, 0x1e, 0x7f, 0x80, 0x80, 0x00, 0x00, 0x0e,
  0x7f, 0xe0, 0x80, 0x00, 0x00, 0x0c, 0x77, 0xf1, 0x00, 0x00, 0x00, 0x08, 0x7f, 0xfd, 0x00, 0x00,
  0x00, 0x18, 0x3f, 0xf3, 0x00, 0x00, 0x00, 0x14, 0x3f, 0xf3, 0x00, 0x00, 0x00, 0x24, 0x3f, 0xe1,
  0x80, 0x00, 0x00, 0x24, 0x3f, 0xe1, 0x80, 0x00, 0x00, 0x24, 0x3f, 0xc0, 0xc0, 0x00, 0x00, 0x26,
  0x1f, 0x80, 0x80, 0x00, 0x00, 0x42, 0x17, 0x00, 0x40, 0x00, 0x00, 0x43, 0x18, 0x00, 0x40, 0x00,
  0x00, 0x61, 0x10, 0x00, 0x40, 0x00, 0x00, 0x21, 0x90, 0x00, 0x80, 0x00, 0x00, 0x30, 0x90, 0x00,
  0x80, 0x00, 0x00, 0x30, 0x40, 0x00, 0x80, 0x00, 0x00, 0x18, 0x20, 0x01, 0x00, 0x00, 0x00, 0x08,
  0x14, 0x02, 0x00, 0x00, 0x00, 0x04, 0x08, 0x0c, 0x00, 0x00, 0x00, 0x03, 0x95, 0x70, 0x00, 0x00,
  0x00, 0x00, 0x7e, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
  0x00, 0x00, 0x00, 0x00
};


const unsigned char* catsad[2] = {
    cat1_sad,cat2_sad
    };


// EATING

/*=======================Pear============================*/
// 'pear1', 24x24px
const unsigned char pear1 [] PROGMEM = {
0x00, 0x00, 0x80, 0x00, 0x01, 0x00, 0x04, 0x03, 0x00, 0x0a, 0x02, 0x00, 0x04, 0x1f, 0xe0, 0x00,
0x15, 0xd0, 0x00, 0x7e, 0x10, 0x00, 0x77, 0xe0, 0x00, 0x74, 0x00, 0x00, 0x76, 0x00, 0x00, 0x7c,
0x00, 0x00, 0xfe, 0x00, 0x01, 0xfd, 0x00, 0x03, 0xfe, 0x80, 0x03, 0xfe, 0x40, 0x05, 0xff, 0x20,
0x01, 0xff, 0xe0, 0x05, 0xff, 0xe0, 0x05, 0xff, 0xe2, 0x04, 0xff, 0xe5, 0x02, 0xff, 0xc2, 0x02,
0x7f, 0xc0, 0x01, 0xcf, 0x80, 0x00, 0x7f, 0x00
    };

// 'pear2', 24x24px
const unsigned char pear2 [] PROGMEM = {
0x00, 0x00, 0x80, 0x00, 0x01, 0x00, 0x04, 0x03, 0x00, 0x0a, 0x02, 0x00, 0x04, 0x1f, 0xe0, 0x00,
0x15, 0xd0, 0x00, 0x7e, 0x10, 0x00, 0x77, 0xe0, 0x00, 0x74, 0x00, 0x00, 0x76, 0x00, 0x00, 0x7c,
0x00, 0x00, 0xfe, 0x00, 0x00, 0x7d, 0x00, 0x00, 0x1e, 0x80, 0x00, 0x0e, 0x40, 0x00, 0x0f, 0x20,
0x00, 0x07, 0xe0, 0x00, 0x07, 0xe0, 0x00, 0x07, 0xe2, 0x00, 0x07, 0xe5, 0x00, 0x0f, 0xc2, 0x00,
0x1f, 0xc0, 0x00, 0x0f, 0x80, 0x00, 0x7f, 0x00
    };

// 'pear3', 24x24px
const unsigned char pear3 [] PROGMEM = {
0x00, 0x00, 0x80, 0x00, 0x01, 0x00, 0x00, 0x03, 0x00, 0x00, 0x02, 0x00, 0x00, 0x1f, 0xe0, 0x00,
0x15, 0xd0, 0x00, 0x7e, 0x10, 0x00, 0x77, 0xe0, 0x00, 0x74, 0x00, 0x00, 0x76, 0x00, 0x00, 0x7c,
0x00, 0x00, 0xfc, 0x00, 0x00, 0x7c, 0x00, 0x00, 0x1c, 0x00, 0x00, 0x0c, 0x00, 0x00, 0x0c, 0x00,
0x00, 0x04, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x07, 0x00, 0x00, 0x0f, 0x80, 0x00,
0x1f, 0x80, 0x00, 0x0f, 0x80, 0x00, 0x7f, 0x00
    };

const unsigned char* pear[3] = {
    pear1,pear2,pear3
    };
/*===========================================================*/

/*========================Pizza==============================*/
// 'pizza1', 24x24px
const unsigned char pizza1 [] PROGMEM = {
	0x40, 0x00, 0x00, 0xa0, 0xfc, 0x00, 0x41, 0xfb, 0x80, 0x01, 0xdf, 0x40, 0x01, 0x39, 0xf0, 0x01,
	0x86, 0x08, 0x03, 0xfd, 0x4c, 0x03, 0x3f, 0xec, 0x02, 0x37, 0xfa, 0x06, 0x1f, 0x4a, 0x07, 0x3f,
	0x86, 0x07, 0xff, 0xca, 0x0f, 0xff, 0xfc, 0x0f, 0xbc, 0xe8, 0x0f, 0x78, 0x70, 0x11, 0xf8, 0x60,
	0x11, 0xfc, 0x80, 0x10, 0xdf, 0x00, 0x19, 0xfe, 0x00, 0x2f, 0xf8, 0x00, 0x3e, 0xf0, 0x02, 0x37,
	0xc0, 0x05, 0x6e, 0x00, 0x02, 0x70, 0x00, 0x00
};

// 'pizza2', 24x24px
const unsigned char pizza2 [] PROGMEM = {
	0x20, 0x00, 0x00, 0x50, 0xfc, 0x00, 0x21, 0xfb, 0x80, 0x01, 0xdf, 0x40, 0x01, 0x39, 0x80, 0x01,
	0x86, 0x00, 0x03, 0xfc, 0x00, 0x03, 0x3e, 0x02, 0x02, 0x34, 0x05, 0x06, 0x1c, 0x02, 0x07, 0x3c,
	0x00, 0x07, 0xfc, 0x00, 0x0f, 0xfe, 0x00, 0x0f, 0xbc, 0x00, 0x0f, 0x78, 0x00, 0x11, 0xf8, 0x40,
	0x11, 0xfc, 0x80, 0x10, 0xdf, 0x00, 0x19, 0xfe, 0x00, 0x2f, 0xf8, 0x00, 0x3e, 0xf0, 0x00, 0x37,
	0xc0, 0x00, 0x6e, 0x00, 0x00, 0x70, 0x00, 0x00
};

// 'pizza3', 24x24px
const unsigned char pizza3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0xfc, 0x00, 0x01, 0xfb, 0x80, 0x01, 0xdf, 0x40, 0x01, 0x39, 0x80, 0x01,
	0x86, 0x00, 0x03, 0xfc, 0x00, 0x03, 0x3e, 0x00, 0x02, 0x35, 0x00, 0x06, 0x1d, 0x00, 0x07, 0x3d,
	0x00, 0x07, 0xfd, 0x00, 0x0f, 0xfe, 0x00, 0x03, 0xbc, 0x80, 0x01, 0x78, 0x00, 0x01, 0xf8, 0x40,
	0x00, 0xfc, 0x80, 0x00, 0xdf, 0x00, 0x00, 0xfe, 0x00, 0x00, 0xf8, 0x00, 0x00, 0xf0, 0x00, 0x00,
	0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char* pizza[3] = {
    pizza1,pizza2,pizza3
    };

/*=======================================================/*

/*=======================Onigiri=========================*/
// 'onigiri1', 24x24px
const unsigned char onigiri1 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x04, 0x00, 0x7f, 0x0a, 0x00, 0xff, 0x04, 0x01,
	0xff, 0x80, 0x01, 0xfb, 0xc0, 0x03, 0xff, 0xc0, 0x03, 0xff, 0xe0, 0x07, 0xff, 0xf0, 0x0e, 0xff,
	0xf0, 0x1f, 0xef, 0xf8, 0x1f, 0xff, 0xfc, 0x3f, 0xff, 0xbe, 0x3f, 0xff, 0xfe, 0x3f, 0x80, 0xfe,
	0x3d, 0x80, 0xee, 0x1f, 0x80, 0xfc, 0x0f, 0x80, 0xf8, 0x07, 0x80, 0xf0, 0x41, 0x80, 0xc0, 0xa0,
	0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'onigiri2', 24x24px
const unsigned char onigiri2 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3c, 0x04, 0x00, 0x78, 0x0a, 0x00, 0xf4, 0x04, 0x01,
	0xf0, 0x00, 0x01, 0xf0, 0x00, 0x03, 0xf0, 0x00, 0x03, 0xf0, 0x00, 0x07, 0xf0, 0x00, 0x0e, 0xf4,
	0x00, 0x1f, 0xea, 0x00, 0x1f, 0xfc, 0x0c, 0x3f, 0xff, 0xbe, 0x3f, 0xff, 0xfe, 0x3f, 0x80, 0xfe,
	0x3d, 0x80, 0xee, 0x1f, 0x80, 0xfc, 0x0f, 0x80, 0xf8, 0x07, 0x80, 0xf0, 0x41, 0x80, 0xc0, 0xa0,
	0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00
};

// 'onigiri3', 24x24px
const unsigned char onigiri3 [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x24, 0x00, 0x00, 0x10, 0x00, 0x00, 0xc0, 0x00, 0x01,
	0x20, 0x00, 0x01, 0x80, 0x00, 0x02, 0x80, 0x00, 0x03, 0x80, 0x00, 0x07, 0x40, 0x00, 0x0e, 0x00,
	0x00, 0x1f, 0xa0, 0x00, 0x1f, 0x00, 0x00, 0x3f, 0x88, 0x02, 0x3f, 0xd1, 0x80, 0x3f, 0x80, 0x06,
	0x3d, 0x80, 0xee, 0x1f, 0x80, 0xfc, 0x0f, 0x80, 0xf8, 0x07, 0x80, 0xf0, 0x01, 0x80, 0xc0, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

const unsigned char* onigiri[3] = {
    onigiri1,onigiri2,onigiri3
    };



/*=======================================================*/

// menus
bool menuOpened = false;
int menu=0;
int subMenu=1;
bool menuDepth=false;
bool justOpened=false;
#define MENUSIZE 9
#define STRING_SIZE 11



const char mainMenu[MENUSIZE][9][STRING_SIZE] PROGMEM = {
  {"food","pear","onigiri","pizza",NULL},
  {"study"},
  {"play",NULL},
  {"visit the doctor",NULL},
  {"stats","hunger","happiness","health",NULL},
  {"avatar","coins","level"},
  {"settings","sound",NULL},
};


/* ======================================/*
/* ------- PET STATS ------- */

float hunger=100;
float happiness=100;
float health=100;
int coins = 0;
float level=0;

//settings
bool soundEnabled=true;

int action=0;
int setting=0;

bool dead = true;
bool studying = false;
bool notification = false;
int notificationBlink=0;

#define ACTIVATED LOW

void setup() {
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);

  digitalWrite(button1Pin, HIGH);
  digitalWrite(button2Pin, HIGH);
  digitalWrite(button3Pin, HIGH);
  // or just
  // pinMode(button1Pin, INPUT_PULLUP)
  // etc

  pinMode(sound, OUTPUT);

  pinMode(13,OUTPUT);

  randomSeed(analogRead(0));

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // Pantalla de entrada (Benkyogotchi -Welcome back!)
  display.drawBitmap(0,0,intro,128,64,WHITE);
  display.display();

  //El sonido de entrada

  tone(sound,802,500);
  delay(200);
  tone(sound,670,300);
  delay(390);
  tone(sound,590,300);
  delay(200);
  tone(sound,970,700);
  delay(2200);
  // Termino de entrada


  display.clearDisplay();

}
/* ======================================*/


void loop() {


  button1State = digitalRead(button1Pin);
  button2State = digitalRead(button2Pin);
  button3State = digitalRead(button3Pin);


    if(!dead){
      display.setCursor(0,0);

     /* ------- BUTTON PRESS ACTIONS ------- */

    /* ------- BUTTON 1 - MENU ------- */
    if(button1State==ACTIVATED){
        // MENU

        if(soundEnabled){
          tone(sound,300,80);
        }

        if(soundEnabled){
          tone(sound,300,80);
        }

        if(!menuOpened){
          menuOpened=true;
        }else{
          if(menuDepth){

            if((const char*)pgm_read_word(&(mainMenu[menu][subMenu+1]))==NULL){
              subMenu=1;
            }else{
              ++subMenu;
            }
            setting=100*(menu+1)+subMenu;
          }else{
            if(menu==MENUSIZE-1){
              menu=0;
            }else{
              ++menu;
            }

            if((const char*)pgm_read_word(&(mainMenu[menu][1]))!=NULL){
              subMenu=1;

              justOpened=true;
            }
            setting=100*(menu+1)+subMenu;
          }
        }

        delay(60);

      }



    /* ------- BUTTON 2 - SELECT ------- */
    if(button2State==ACTIVATED){
    if(soundEnabled){
      tone(sound,600,80);
    }

    if(menuOpened){

      if(subMenu!=1 && (const char*)pgm_read_word(&(mainMenu[menu][1][0]))!=NULL){
        action=100*(menu+1)+subMenu;
      }
      if(subMenu==1 && (const char*)pgm_read_word(&(mainMenu[menu][1][0]))==NULL){
        action=100*(menu+1)+subMenu;
      }
      if(subMenu==1 && (const char*)pgm_read_word(&(mainMenu[menu][1][0]))!=NULL && menuDepth){
        action=100*(menu+1)+subMenu;
      }
      if((const char*)pgm_read_word(&(mainMenu[menu][1][0]))!=NULL){
        setting=100*(menu+1)+subMenu;
        menuDepth=true;
      }
    }

    else{
      action=NULL;

      menuOpened=true;
      menuDepth=true;
      subMenu=1;
      menu=6;
      action=701;
      setting=701;
    }
    justOpened=false;

    delay(60);
}


  /* ------- BUTTON 3 - BACK ------- */
  if(button3State==ACTIVATED){
    if(soundEnabled){
      tone(sound,1000,80);
    }
    if(!menuDepth){
        menuOpened=false;
        menu=0;
        setting=0;
      }else{
        menuDepth=false;
        setting=100*(menu+1)+1;
      }
      action=NULL;
      subMenu=1;



    delay(60);
  }


  /* -------- MODIFY PET STATS -------- */
  if(studying){
    hunger-=0.00005;
    if(happiness+0.02<100){
      happiness+=0.02;
    }
  }
  else{
    hunger-=0.00025;
    if(happiness-0.001>0){
      happiness-=0.001;
    }

  }

  if(hunger<=0 || health<=0 || happiness<=0){
    dead=true;
    if(soundEnabled){
      tone(sound,500,500);
      delay(550);
      tone(sound,400,500);
      delay(550);
      tone(sound,300,600);
    }
  }



  if (!menuOpened){
    if(happiness >30){
        for(int i=0; i<2; i++){
            display.drawBitmap(40, 10, cat[i] , 46, 46, WHITE);
            display.display();
            display.clearDisplay();
            delay(600);
        }
      }

    if(happiness <=30){
         for(int i=0;i<2;i++){
            display.drawBitmap(40, 10, catsad[i] , 46, 46, WHITE);
            display.display();
            display.clearDisplay();
            delay(600);
            }
          }
        }

    /* ------- MENUS AND ACTIONS ------- */
    //render menu
    if(menuOpened and !studying){
      display.fillRect(0,0,display.width(),30,BLACK);
      display.drawRect(0,0,display.width(),29,WHITE);
      display.fillRect(1,1,display.width()-2,27,BLACK);
      display.drawRect(0,0,display.width(),12,WHITE);
      display.setCursor(8,2);
      display.setTextSize(1);
      if(menuDepth){
        display.fillRect(0,0,display.width(),12,WHITE);
        display.fillRect(1,18,1,5,WHITE);
        display.fillRect(2,19,1,3,WHITE);
        display.fillRect(3,20,1,1,WHITE);
        display.setTextColor(BLACK,WHITE);
      }else{
        display.fillRect(1,3,1,5,WHITE);
        display.fillRect(2,4,1,3,WHITE);
        display.fillRect(3,5,1,1,WHITE);
        display.setTextColor(WHITE);
      }
      char oneItem [STRING_SIZE];
      memcpy_P (&oneItem, &mainMenu[menu][0], sizeof oneItem);
      //display.println(getItem(menu,0));
      display.println(oneItem);
      if(subMenu){
        display.setTextColor(WHITE);
        display.setCursor(8,16);
        char subItem [STRING_SIZE];
        memcpy_P (&subItem, &mainMenu[menu][subMenu], sizeof subItem);
        //display.println(getItem(menu,subMenu));
        display.println(subItem);
      }
    }

    //do actions

    if(action>0){

      if((action==101 || action==102 || action==103) && !studying){

        //animate eating

        display.fillRect(0,0,display.width(),display.height(),BLACK);
        for(int i=0; i<3; i++){
            display.clearDisplay();
            switch(action){
                case 101:
                //pear
                    if(coins >=50){
                        display.drawBitmap(80,24,pear[i],48,40,WHITE);
                        delay(150);
                        display.display();
                    }
                    else{
                        display.setCursor(30,30);
                        display.print(F("Not enough coins!"));
                        display.display();
                        delay(200);
                        display.clearDisplay();
                    }
                    break;
                case 102:
                //pizza
                    if(coins>=35){
                    display.drawBitmap(80,24,pizza[i],48,40,WHITE);
                    delay(150);
                    display.display();
                    }
                    else{
                        display.setCursor(32,32);
                        display.print(F("Not enough coins!"));
                        display.display();
                        delay(150);
                        display.clearDisplay();
                    }
                    break;

                case 103:
                //onigiri
                    if (coins >=35){
                    display.drawBitmap(80,24,onigiri[i],48,40,WHITE);
                    delay(150);
                    display.display();
                    }
                    else{
                        display.setCursor(32,32);
                        display.print(F("Not enough coins!"));
                        display.display();
                        delay(150);
                    }
                    break;

            }
          }




        switch(action){
          //Pear - restores 20 points of health
          case 101:
            if(hunger+30>100){
                hunger=100;
                level += 0.05;
                happiness += 5;
            }else{
                hunger+=20;
                level += 0.05;
                happiness += 5;
            }
            if(health+1<=100){
                health+=1;
                level += 0.05;
                happiness += 5;
            }
            coins-=50;
            break;
          //Pizza -restores 10 points of health
          case 102:
            if(hunger+10>100){
              hunger=100;
              happiness += 5;
              level += 0.05;
            }else{
              hunger+=10;
              happiness += 5;
              level += 0.05;
            }
            coins -=35;
            break;
          //Onigiri - restores 10 points of health
          case 103:
            if(hunger+5<=100){
              hunger=100;
              happiness += 5;
            }else{
              hunger +=5;
              happiness +=5;
            }
            coins-=35;
            break;
        }

      }



    else{
        if(action==101 || action==102 || action==103){
          if(soundEnabled){
            tone(sound,500,200);
            delay(250);
          }
        }
      }


      switch(action){
        case 201:
          //Studying
            unsigned long startTime = millis ();
            unsigned long interval = 25*60000; /*time in miliseconds*/

            while (millis() - startTime >= interval)
                {
                display.clearDisplay();
                display.setCursor(10,00);
                printDigits(0);
                display.display(); // display screen showing 00:00s
                }
                break;



          coins += 25;
          level += 0.15;
          happiness += 10;

          break;

        case 501:
          //Restore health
            if(coins >=50){
                if(health<60){
                  health=100;
                  level += 0.5;
                  happiness += 30;
                  display.setCursor(32,32);
                  display.print(F("Benkyogotchi is feeling better now!"));
                  display.display();
                  delay(500);
                  }

            }else{
                display.setCursor(32,32);
                display.print(F("Not enough coins!"));
                display.display();
                delay(600);
            }

            break;

          case 801:
            soundEnabled=!soundEnabled;
          break;
      }
      action=0;
    }



    //Settings
    if(setting>0 and !studying){
      display.setCursor(8,16);
      if(setting==201){
        display.println(F("Study time! (25 [min])"));
      }
      if(setting==501){
        display.println(F("Go to the doctor"));
      }
      if(setting==601){
        display.println(F("Play with Benkyogotchi!"));
      }
      if(setting==701 || setting==702 || setting==703 || setting==704){
        display.drawRect(70,17,52,7,WHITE);
      }
      if(setting==701){
        drawBar(hunger);
      }
      if(setting==702){
        drawBar(happiness);
      }
      if(setting==703){
        drawBar(health);
      }
      if(setting==705 || setting==706 || setting==801){
        display.setCursor(80,16);
      }
      if(setting==705){
        //display.setCursor(80,16);
        display.print(coins,1);
      }
      if(setting==706){
        display.print(level,1);
      }
      if(setting==801){
        if(soundEnabled){
          display.println(F("on"));
        }else{
          display.println(F("off"));
        }
      }
    }

    //display notification
    if(notification){
      ++notificationBlink;
      if(notificationBlink==10){
        notificationBlink=0;
      }
      if(notificationBlink!=1){
        display.drawRect(117,28,11,11,WHITE);
        display.setTextColor(WHITE);
        digitalWrite(13,LOW);
      }else{
        display.fillRect(117,28,11,11,WHITE);
        display.setTextColor(BLACK);
        digitalWrite(13,HIGH);
      }
      display.setCursor(120,30);
      display.println(F("!"));
      if(dead){
         digitalWrite(13,LOW);
      }
    }
  }





/*==============================================================*/

else{
    //Dead.
    display.setTextColor(WHITE);
    display.println(F("\n     Benkyogotchi     \n       has died!            "));
    display.display();
    display.drawBitmap(50,35,death,24,24,WHITE);
    display.display();
    delay(5000);
    while(button1State != ACTIVATED){
    display.clearDisplay();
    display.setCursor(0,0);
    display.println(F("\n Restart the journey? \n       Press 1       \n    to resurrect           your pet. "));
    display.display();
    // display.drawBitmap(50,40,death_wreath,24,24,WHITE);
    //display.display();

    /*User wishes to restart*/
    if(button1State==ACTIVATED){
      if(soundEnabled){
        tone(sound,300,80);
        delay(200);
      }
      noTone(sound);
      asm volatile ("  jmp 0");
    }
  }
}

}

/*=========================================================*/
char* getItem(int menu, int index){
  char oneItem [STRING_SIZE];
  memcpy_P (&oneItem, &mainMenu[menu][index], sizeof oneItem);
  return oneItem;
}


void drawBar(float value){
  display.fillRect(72,19,48*value/100,3,WHITE);
}


/*timer function*/
const long minute = 60000;
void printDigits(long timeInMillis){
               // convert the time from milliseconds to four digit SS:HH
               // seconds and hundredths and display at current cursor position
               int seconds;
               int hundredths;
               seconds = timeInMillis /1000;
               seconds = seconds % 60; // seconds never more than 60
               hundredths = (timeInMillis % 1000)/10;

               if (seconds <10){ // print leading zero if necessary
                 display.print("0");
               }
               display.print(seconds);
               display.print(":");
               if (hundredths <10){ //print leading zero if necessary
               display.print("0");

               }
               display.print(hundredths);
               display.print("s");
               display.display();
             }
