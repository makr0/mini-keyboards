#include <Keyboard.h>

#define NUM_KEYS 5
int buttonPins[NUM_KEYS] = {2,3,4,5,6};
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
      macros[i]();
      delay(10);
      while(!digitalRead(buttonPins[i])) {
        delay(20);
      }
    }
  }
}
