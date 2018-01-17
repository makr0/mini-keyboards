
const uint16_t PixelCount = 8; // this example assumes 4 pixels, making it smaller will cause a failure
const uint8_t PixelPin = 9;  // make sure to set this to the correct pin, ignored for Esp8266
NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

void initLEDs() {
    strip.Begin();
    strip.Show();
    for (int i=0; i<PixelCount; i++) {
      setLED(i,blue);
      delay(20);
    }
    delay(100);
    for (int i=0; i<PixelCount; i++) {
      setLED(i,black);
      delay(20);
    }
}

void setLED(int pos, RgbColor color) {
    strip.SetPixelColor(pos, color);
    strip.Show();
}

void setSingleLED(int pos, RgbColor color) {
  for(int i=0; i<PixelCount; i++) {
    strip.SetPixelColor(i,black);
  }
  strip.SetPixelColor(pos, color);
  strip.Show();
}

void setAllLEDs( RgbColor color) {
  for(int i=0; i<PixelCount; i++) {
    strip.SetPixelColor(i,color);
  }
  strip.Show();
}
