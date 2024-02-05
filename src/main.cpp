#include <Arduino.h>
#include <Wire.h>
#define SSD1306_NO_SPLASH
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Encoder.h>
#include "OneButton.h"
// #include <Servo.h>
#include <VarSpeedServo.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library.
// On an arduino NANO v3:       A4(SDA), A5(SCL)
#define OLED_RESET -1       // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// The pins with interrupt feature are:
// On an arduino NANO v3:       D2, D3
Encoder myEnc(2, 3);
volatile long oldPosition = -999;

#define BUT_PIN 4
OneButton button(BUT_PIN, true);
volatile long count = 0;

#define SPEED1 40
#define SPEED2 30
VarSpeedServo myservo; // create servo object to control a servo
int pos = 0;           // variable to store the servo position

#define LOGO_HEIGHT 24
#define LOGO_WIDTH 24
static const unsigned char PROGMEM logo_bmp[] =
    {0x00, 0xff, 0x00, 0x07, 0xff, 0xe0, 0x0f, 0x00, 0xf0, 0x1c, 0x00, 0x30, 0x18, 0x00, 0x18, 0x18, 
	0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x3f, 0xff, 0xfc, 0x7f, 0xff, 
	0xfe, 0xff, 0xff, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xc1, 0xff, 0xff, 0x80, 0xff, 0xff, 0x81, 0xff, 
	0xff, 0xe3, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 
	0xff, 0xff, 0x7f, 0xff, 0xff, 0x3f, 0xff, 0xfc};
#define NUMFLAKES 10 // Number of snowflakes in the animation example

void doubleClick(void);
void singleClick(void);

void setup()
{
  Serial.begin(9600);

  myservo.attach(6);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;)
      ; // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.display();
  delay(2000); // Pause for 2 seconds

  // Clear the buffer
  display.clearDisplay();

  // Draw a single pixel in white
  display.drawBitmap(SCREEN_WIDTH/2 - LOGO_WIDTH/2, SCREEN_HEIGHT/2 - LOGO_HEIGHT/2, logo_bmp, LOGO_WIDTH, LOGO_HEIGHT, WHITE);

  // Show the display buffer on the screen. You MUST call display() after
  // drawing commands to make them visible on screen!
  display.display();

  Serial.println("Basic Servo Test:");
  myservo.write(90, SPEED1);
  myservo.wait();
  myservo.write(0, SPEED2);
  myservo.wait();
  myservo.detach();

  Serial.println("Basic Encoder Test:");

  // link the doubleclick function to be called on a click events.
  button.attachClick(singleClick);
  button.attachDoubleClick(doubleClick);
}

void loop()
{
  volatile long newPosition = myEnc.read();
  if (newPosition != oldPosition)
  {
    oldPosition = newPosition;
    Serial.println(newPosition);
  }

  // keep watching the push button:
  button.tick();
}

void singleClick(void)
{
  count++;
  Serial.println(count);
}

void doubleClick(void)
{
  count--;
  Serial.println(count);
}