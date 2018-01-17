#include <Encoder.h>
#include <NeoPixelBus.h>
#include <Keyboard.h>
#include <Mouse.h>
#include "layers.h"

int ledBrightness = 5;
HslColor red(RgbColor(ledBrightness, 0, 0));
HslColor green(RgbColor(0, ledBrightness, 0));
HslColor blue(RgbColor(0, 0, ledBrightness));
HslColor white(RgbColor(ledBrightness));
HslColor black(RgbColor(0));

#define NUM_KEYS 6
#define NUM_LAYERS 8
// Hardware
// 4-7,14,16 buttons
// 8 analog potentiometer
// 9 leds, 8x WS2812
// 2,3 encoder
// 10 encoder button
#define Poti_PIN 8
#define Encoder_button 10

int buttonPins[NUM_KEYS] = {4,14,16,7,6,5};
Encoder knob(2, 3);
long knobPos = 0;
long knobPos_old = 0;
typedef void (*button_func) ();
button_func macros[NUM_LAYERS][NUM_KEYS] = {
  {macro_11, macro_12, macro_13, macro_14, macro_15, macro_16},
  {macro_21, macro_22, macro_23, macro_24, macro_25, macro_26},
  {macro_31, macro_32, macro_33, macro_34, macro_35, macro_36},
  {macro_41, macro_42, macro_43, macro_44, macro_45, macro_46},
  {macro_51, macro_52, macro_53, macro_54, macro_55, macro_56},
  {macro_61, macro_62, macro_63, macro_64, macro_65, macro_66},
  {macro_71, macro_72, macro_73, macro_74, macro_75, macro_76},
  {macro_81, macro_82, macro_83, macro_84, macro_85, macro_86},
};
int layer = 0;

// String macros[NUM_KEYS] = {"/","]d","a","f","d"};

void setup()
{
  initLEDs();
  for (int i=0; i<NUM_KEYS; i++)
  {
    pinMode(buttonPins[i], INPUT);  // Set all keypad pins as inputs
    digitalWrite(buttonPins[i], HIGH);  // pull all keypad pins high
  }
  pinMode(Encoder_button, INPUT);  // Set all keypad pins as inputs
  digitalWrite(Encoder_button, HIGH);  // pull all keypad pins high
  knob.write(knobPos);
  setSingleLED(layer,red);
  Keyboard.begin();
  Mouse.begin();
}

void loop()
{
  for (int i=0; i<NUM_KEYS; i++)
  {
    if (!digitalRead(buttonPins[i])) {
      setSingleLED(layer,black);
      macros[layer][i]();
      delay(2);
      while(!digitalRead(buttonPins[i])) {
        delay(2);
      }
      setSingleLED(layer,red);
    }
  }
  handleLayerChange();
  handleMousewheel();
}

void handleLayerChange() {
  if (!digitalRead(Encoder_button)) {
      delay(2);
      while(!digitalRead(Encoder_button)) {
        delay(2);
      }
      knob.write(layer*4);
      while(digitalRead(Encoder_button)) {
        layer = knob.read()/4;
        layer=constrain(layer,0,NUM_LAYERS-1);
        setSingleLED(layer,green);
      }
      while(!digitalRead(Encoder_button)) {
        delay(50);
      }
      setSingleLED(layer,red);
      // restore old knobPos
      knob.write(knobPos);
  }
}
void handleMousewheel() {
  knobPos = knob.read();
  if( knobPos != knobPos_old ) {
    Mouse.move(0,0,(knobPos_old-knobPos));
    knobPos_old = knobPos;
  }
}
