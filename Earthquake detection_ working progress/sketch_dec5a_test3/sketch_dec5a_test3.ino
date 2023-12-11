#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Vibration sensor setup
int vs = 9;

// NeoPixel setup
#define PIN 6
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, PIN);

// Buzzer setup
#define BUZZER_PIN 11

// OLED setup
#define SCREEN_I2C_ADDR 0x3C // or 0x3C
#define SCREEN_WIDTH 128     // OLED display width, in pixels
#define SCREEN_HEIGHT 64     // OLED display height, in pixels
#define OLED_RST_PIN -1      // Reset pin (-1 if not available)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

void setup() {
  // Initialize vibration sensor
  pinMode(vs, INPUT); 
  Serial.begin(9600);

  // Initialize NeoPixels
  pixels.begin();

  // Initialize OLED display
  display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR);

  // Initialize the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);
}

long vibration() {
  // Wait for the pin to get HIGH and returns measurement
  long measurement = pulseIn(vs, HIGH); 
  return measurement;
}

void loop() {
  long measurement = vibration();
  delay(50);
  Serial.println(measurement);

  if (measurement > 30000) {
    triggerAlarm("Earthquake RUN!!!!!");
  } else if (measurement > 5000) {
    blinkOrange(5);
  } else {
    digitalWrite(BUZZER_PIN, LOW);
    setNeoPixelColor(0, 150, 0); // Green color
    displayMessageOnOled("SAFE", 5);
  }
}

void setNeoPixelColor(byte red, byte green, byte blue) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, red, green, blue);
  }
  pixels.show();
}

void displayMessageOnOled(const char* message, int textSize) {
  display.clearDisplay();
  display.setTextSize(textSize); 
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, (SCREEN_HEIGHT - 8 * textSize) / 2); // Center text vertically
  display.println(message);
  display.display();
}

void triggerAlarm(const char* message) {
  // Play sound with the buzzer
  for (int i = 0; i < 6; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }

  // Blink NeoPixels with red color
  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < NUMPIXELS; j++) {
      pixels.setPixelColor(j, 150, 0, 0); // Red color
    }
    pixels.show();

    // Display the message on OLED
    displayMessageOnOled(message, 2);

    delay(500); // Visible for 500ms

    // Turn off NeoPixels
    pixels.clear();
    pixels.show();

    // Clear OLED display
    display.clearDisplay();
    display.display();

    delay(500); // Not visible for 500ms
  }
}

void blinkOrange(int blinkCount) {
  for (int i = 0; i < blinkCount; i++) {
    // Turn on the orange LEDs
    setNeoPixelColor(255, 165, 0); // Orange color
    pixels.show();
    
    // Display the message on the OLED
    displayMessageOnOled("Earthquake", 2);

    delay(500); // Visible for 500ms

    // Turn off the orange LEDs
    pixels.clear();
    pixels.show();

    // Clear the message on the OLED
    display.clearDisplay();
    display.display();

    delay(500); // Not visible for 500ms
  }
}
