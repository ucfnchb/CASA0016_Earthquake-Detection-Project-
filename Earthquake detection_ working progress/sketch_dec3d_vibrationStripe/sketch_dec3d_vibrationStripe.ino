#include <Adafruit_NeoPixel.h>

int vs = 9; // Vibration sensor setup

// NeoPixel setup
#define PIN 6
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

void setup() {
  // Initialize vibration sensor
  pinMode(vs, INPUT); 
  Serial.begin(9600);

  // Initialize NeoPixels
  pixels.begin();
}

void loop() {
  long measurement = vibration();
  delay(50);
  Serial.println(measurement);

  if (measurement > 50) {
    // If vibration detected, light up NeoPixels
    for(int i = 0; i < NUMPIXELS; i++) {
      pixels.setPixelColor(i, 150, 0, 0); // Red color
      pixels.show();
      delay(500); // Delay between each pixel lighting up
    }
  } else {
    // No vibration detected, turn off NeoPixels
    pixels.clear();
    pixels.show();
  }
}

long vibration() {
  long measurement = pulseIn(vs, HIGH); // Wait for the pin to get HIGH and returns measurement
  return measurement;
}
