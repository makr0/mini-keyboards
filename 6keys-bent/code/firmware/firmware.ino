#include <NeoPixelBus.h>
#include <Keyboard.h>

int ledBrightness = 5;
HslColor red(RgbColor(ledBrightness, 0, 0));
HslColor green(RgbColor(0, ledBrightness, 0));
HslColor blue(RgbColor(0, 0, ledBrightness));
HslColor white(RgbColor(ledBrightness));
HslColor black(RgbColor(0));

#define NUM_KEYS 6
// Hardware
// 4-7,14,16 buttons
// 8 analog potentiometer
// 9 leds, 8x WS2812
// 2,3 encoder
// 10 encoder button
#define Poti_PIN 8
//
// button Numbers
// +----------------+
// |  ------------- |
// |  | 1 | 2 | 3 | |
// |  ------------- |
// |  | 4 | 5 | 6 | |
// |    ----------- |
// +----------------+
//
//                          1   2    3   4    5

int buttonPins[NUM_KEYS] = {4,14,16,7,6,5};
void macro_Button1() {
  Keyboard.press( KEY_LEFT_SHIFT );
  Keyboard.press( KEY_F8 );
  delay(100);
  Keyboard.releaseAll();
}
void macro_Button2() {
  Keyboard.press( KEY_F8 );
  Keyboard.releaseAll();
}
void macro_Button3() {
  Keyboard.press( KEY_F7 );
  Keyboard.releaseAll();
}
void macro_Button4() {
  Keyboard.press( KEY_LEFT_SHIFT );
  Keyboard.press( KEY_LEFT_CTRL );
  Keyboard.press( KEY_F8 );
  delay(100);
  Keyboard.releaseAll();
}
void macro_Button5() {
  Keyboard.press( KEY_F7 );
  Keyboard.releaseAll();
}
void macro_Button6() {
  Keyboard.press( KEY_F9 );
  Keyboard.releaseAll();
}


typedef void (*button_func) ();
button_func macros[NUM_KEYS] = {macro_Button1, macro_Button2, macro_Button3, macro_Button4, macro_Button5, macro_Button6};

// String macros[NUM_KEYS] = {"/","]d","a","f","d"};

void setup()
{
  initLEDs();
  for (int i=0; i<NUM_KEYS; i++)
  {
    pinMode(buttonPins[i], INPUT);  // Set all keypad pins as inputs
    digitalWrite(buttonPins[i], HIGH);  // pull all keypad pins high
  }
}

void loop()
{
  for (int i=0; i<NUM_KEYS; i++)
  {
    if (!digitalRead(buttonPins[i])) {
      setSingleLED(i,red);
      macros[i]();
      delay(2);
      while(!digitalRead(buttonPins[i])) {
        delay(2);
      }
      setSingleLED(i,black);
    }
  }
}
