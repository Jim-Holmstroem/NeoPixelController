#include <Adafruit_NeoPixel.h>

Adafruit_NeoPixel strip = Adafruit_NeoPixel(40, 6, NEO_GRB + NEO_KHZ800);

uint16_t n = 0;

void setup() {
  Serial.begin(115200);
  while (!Serial) { ; } // wait for serial port to connect
  Serial.setTimeout(1000);
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(8);
  n = strip.numPixels();
}


void readLED() {
  if (Serial.readStringUntil('{') != "@") { return; }
  uint16_t i = Serial.parseInt();
  Serial.readStringUntil(',');
  byte r = Serial.parseInt();
  Serial.readStringUntil(',');
  byte g = Serial.parseInt();
  Serial.readStringUntil(',');
  byte b = Serial.parseInt();
  Serial.readStringUntil('}');

  Serial.print("{");
  Serial.print(i, DEC);
  Serial.print(",");
  Serial.print(r, DEC);
  Serial.print(",");
  Serial.print(g, DEC);
  Serial.print(",");
  Serial.print(b, DEC);
  Serial.print("}");
  Serial.println();
  strip.setPixelColor(i, r, g, b);

}

char readByte() {
  char buf[] = { 0 };

  Serial.readBytes(buf, 1);

  return buf[0];

}

void readScreen() {
  if (Serial.readStringUntil('[') != "@") { return; }
  do {
    readLED();
  } while (readByte() == ',');
  readByte(); // '\n'
  strip.show();
  Serial.println(".show()");
}

void loop() {
  readScreen();
  Serial.println("loop()");
}
