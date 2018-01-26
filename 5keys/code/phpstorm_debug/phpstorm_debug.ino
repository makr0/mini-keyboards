#include <NeoPixelBus.h>
#include <Keyboard.h>

#define NUM_KEYS 5
int buttonPins[NUM_KEYS] = {2, 3, 4, 5, 6};
//
// button Numbers
// +----------------+
// |  ------------- |
// |  | 3 | 4 | 5 | |
// |  ------------- |
// |    | 1 | 2 |   |
// |    ---------   |
// +----------------+
//
//                          1   2    3   4    5

const uint16_t PixelCount = 16; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 16;  // make sure to set this to the correct pin, ignored for Esp8266

#define colorSaturation 50

// three element pixels, in different order and speeds
NeoPixelBus<NeoGrbFeature, NeoAvr800KbpsMethod> strip(PixelCount, PixelPin);
RgbColor red(colorSaturation, 0, 0);
RgbColor green(0, colorSaturation, 0);
RgbColor blue(0, 0, colorSaturation);
RgbColor white(colorSaturation);
RgbColor black(0);

void macro_Button1() {
  Keyboard.press( KEY_LEFT_SHIFT );
  Keyboard.press( KEY_LEFT_CTRL );
  Keyboard.press( KEY_F8 );
  delay(100);
  Keyboard.releaseAll();
}
void macro_Button2() {
  Keyboard.press( KEY_F9 );
  Keyboard.releaseAll();
}
void macro_Button3() {
  Keyboard.press( KEY_LEFT_SHIFT );
  Keyboard.press( KEY_F8 );
  delay(100);
  Keyboard.releaseAll();
}
void macro_Button4() {
  Keyboard.press( KEY_F8 );
  Keyboard.releaseAll();
}
void macro_Button5() {
  Keyboard.press( KEY_F7 );
  Keyboard.releaseAll();
}


typedef void (*button_func) ();
button_func macros[NUM_KEYS] = {macro_Button1, macro_Button2, macro_Button3, macro_Button4, macro_Button5};

// String macros[NUM_KEYS] = {"/","]d","a","f","d"};

void setup()
{
  for (int i = 0; i < NUM_KEYS; i++)
  {
    pinMode(buttonPins[i], INPUT);  // Set all keypad pins as inputs
    digitalWrite(buttonPins[i], HIGH);  // pull all keypad pins high
  }
  Serial.begin(115200);

  Serial.println();
  Serial.println("Initializing...");
  Serial.flush();

  // this resets all the neopixels to an off state
  strip.Begin();
  strip.Show();


  Serial.println();
  Serial.println("Running...");
}

void leds_on() {
  Serial.println("on...");
  for (int i = 0; i < PixelCount; i++)
    strip.SetPixelColor(i, blue);
  strip.Show();
}

void leds_off() {
  Serial.println("off.");
  for (int i = 0; i < PixelCount; i++)
    strip.SetPixelColor(i, red);
  strip.Show();
}

void loop()
{
  leds_on();
  delay (500);
  leds_off();
  delay(500);
  for (int i = 0; i < NUM_KEYS; i++)
  {
    if (!digitalRead(buttonPins[i])) {
      macros[i]();
      delay(10);
      while (!digitalRead(buttonPins[i])) {
        delay(20);
      }
    }
  }
}
