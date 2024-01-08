# Home Earthquake Alert System
Introduction
The increasing frequency of natural disasters like storms, earthquakes, heat waves, and floods has highlighted the need for better prediction and understanding of these events. Focusing on earthquakes, this project aims to explore IoT technology for providing timely alerts and warnings, critical for safety and reducing property damage.

## Project Objective
The primary goal is to develop a prototype capable of detecting early warning signs of earthquakes. This system is designed to increase safety and readiness in earthquake-prone areas through a reliable and efficient warning system.

## Working Progress
### 1st Stage: Device Design
 Display Mechanisms: Utilizes a 0.96-inch OLED display and an Adafruit NeoPixel Stick for seismic data presentation.
 Audio Output: Incorporates a buzzer for audible warnings.
 Power Source: Arduino Uno REV3.
 Seismic Detection: Employs the SW-420 Vibration Sensor.
 Timekeeping: Includes a DS3231 Real Time Clock for accurate event recording.
 Others: 400 breadboard, jumper wires.
![image](https://github.com/ucfnchb/CASA0016_Earthquake-Detection-Project-/assets/146333771/8b66269e-895a-41d4-971d-d24b2d29635c)


### 2nd Stage: Prototype Design
Development of a desk-sized, wooden house prototype.
Focus on portability, durability, and component accessibility.
![image](https://github.com/ucfnchb/CASA0016_Earthquake-Detection-Project-/assets/146333771/0be8254c-543c-41aa-ac81-0bed3624124e)


### 3rd Stage: Circuit Design and Testing
The project utilizes several libraries to interface with various hardware components. Here's an explanation of each library and its role in the project:
<Adafruit_NeoPixel.h>: This library is used to control Adafruit NeoPixel LED strips, it manages the Adafruit NeoPixel Stick, which consists of 8 RGB LEDs. The library provides functions to set the color and brightness of each LED individually, allowing for a wide range of visual alert signals.
<Adafruit_GFX.h>: Although the comment mentions "vibration sensor," this library is actually a graphics library used for drawing shapes, text, and images on small graphic displays. It's a dependency for the Adafruit SSD1306 library to render graphics and text on the OLED display.

<Adafruit_SSD1306.h>: This library is specifically designed for the SSD1306 OLED display. It allows to control the OLED display connected to the Arduino, enabling the project to show messages, time, and other relevant information visually. 
<Wire.h>: This is a standard Arduino library for communication over the I²C/TWI protocol. 
<RTClib.h>: This library is used to interface with Real Time Clock (RTC) modules like the DS3231. It provides functions to read and write the current date and time. 
Each of these libraries plays a critical role in enabling the Arduino to interact with the specific hardware components of the earthquake alert system. Various components are connected on a breadboard to form a functional circuit. Here's a detailed explanation of how these components is typically connected:
1. Vibration Sensor (SW-420)
The sensor has three pins: VCC, GND, and DO (Digital Output). VCC is connected to the 5V output on the Arduino, GND to one of the Arduino's ground (GND) pins, and DO to a digital input pin 9.
2. Adafruit NeoPixel Stick
The NeoPixel Stick has a VCC, GND, and DIN (Data Input) pin. Connect VCC to 5V and GND to a GND pin on the Arduino. The DIN pin 6 is connected to a digital output pin on the Arduino.
3. OLED Display (SSD1306)
This display uses I²C communication, which requires only two data lines: SDA (data line) and SCL (clock line). Connect the SDA and SCL pins of the OLED to the corresponding SDA and SCL pins on the Arduino. Additionally, connect the VCC and GND pins of the display to the 5V and GND pins on the Arduino, respectively.
4. Buzzer
The buzzer has two pins: one is connected to a digital output pin 11 on the Arduino, and the other to a GND pin.
5. Arduino Uno
Role: Serves as the central controller for the system.
The Arduino connects to all components as described above and acts as the main hub for data processing and signal control.
6. DS3231 Real Time Clock (RTC)
The DS3231 also uses I²C communication. Connect its SDA and SCL pins to the Arduino's SDA and SCL pins. Additionally, VCC goes to 5V, and GND to one of the Arduino's GND pins.
7. Power Source
Connections: The Arduino can be powered through its USB port or an external power supply. If using an external power supply, connect it to the Vin and GND pins of the Arduino.

![image](https://github.com/ucfnchb/CASA0016_Earthquake-Detection-Project-/assets/146333771/950f548b-70d9-4a77-ba32-d8b3f092a441)

![image](https://github.com/ucfnchb/CASA0016_Earthquake-Detection-Project-/assets/146333771/0dc98a3a-8623-4c60-8820-b90e1107357a)


### 4th Stage: System Testing: 
In final sketch, these libraries work together to create a system likely intended for detecting and alerting users of vibrations, possibly from earthquakes. The vibration sensor detects shakes or movements, the NeoPixel stick provides a visual alert, the buzzer gives an audible warning, the OLED display shows the status or messages, and the RTC keeps track of the current time for logging or scheduling purposes. Each component is initialized in the setup() function and utilized in the loop() and other functions according to the sensor inputs and programmed logic. Here's how each part works:
1. Vibration Sensor (SW-420): The vibration sensor detects vibrations or movements. When the detected vibration exceeds certain thresholds, it triggers different levels of alerts. The function long vibration () reads the vibration intensity and returns it for further processing.
2. Adafruit NeoPixel Stick: This is an 8-LED RGB strip, each LED of which can be controlled individually with the Adafruit NeoPixel library. In this code, the setNeoPixelColor() function sets all the LEDs to the same color, used to visually indicate the status of the system, and blinkOrange(int blinkCount) is specifically designed to create a blinking orange alert.
3. Buzzer: It emits an audible sound when activated. The function triggerAlarm(const char* message) uses the buzzer to create a repeating on-off sound pattern, serving as an auditory alarm during high vibration events.
4. 0.96-inch OLED Display: This screen displays messages or information using the Adafruit SSD1306 library. The function displayMessageOnOled(const char* message, int textSize) is used to show text on the screen, such as alert messages or the current time.
5. DS3231 Real Time Clock (RTC): This is used to keep track of the current time accurately. The time is displayed on the OLED and can be used in logging or timestamping events. The code checks if the RTC has lost power and resets the time if necessary.

The code operates in a loop, continuously checking the vibration sensor. Depending on the vibration level (measurement), it triggers different responses:
No significant vibration: The NeoPixel is set to green, and the current time is displayed on the OLED.

Moderate vibration (measurement > 5000): A less urgent alert is triggered, causing the NeoPixels to blink yellow orange using blinkOrange(5).

High vibration (measurement > 25000): This is treated as an emergency (e.g., potential earthquake). It triggers a more urgent alarm with triggerAlarm("Earthquake RUN!!!!!"), causing the buzzer to sound and NeoPixels to blink red while displaying a critical alert message on the OLED.

By setting different thresholds for vibration levels, the system can differentiate between normal conditions, potential threats, or emergency situations, responding with appropriate visual and auditory cues.

![image](https://github.com/ucfnchb/CASA0016_Earthquake-Detection-Project-/assets/146333771/74c28884-6920-4b3a-becb-842a6ca88a9c)

### 5th Stage: Refinement
Enhancement of the prototype's appearance and streamlining of code.
Comprehensive documentation including schematics, code, and user manuals.

![image](https://github.com/ucfnchb/CASA0016_Earthquake-Detection-Project-/assets/146333771/32c6c729-3773-4868-a85f-f4ebba9409a6)

## Feedback and Further Improvement
1. Stripboard Utilization: For stable connections and portability.
2. Integration with Raspberry Shake: For enhanced earthquake detection accuracy.
3. WiFi Module Addition: For immediate alerts and user connectivity.

## Conclusion
This project aims to create a more prepared and safer environment in earthquake-prone areas. The stages of development and testing ensure a reliable and efficient system, capable of providing critical early warnings.




