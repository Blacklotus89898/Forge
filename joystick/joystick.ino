/*
 * Created by ArduinoGetStarted.com
 *
 * This example code is in the public domain
 *
 * Tutorial page: https://arduinogetstarted.com/tutorials/arduino-joystick
 */

#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A0 // Arduino pin connected to VRY pin
#define SW 2

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int sw = LOW;

void setup() {
  Serial.begin(9600) ;
  // need to add calibration 
  for (int i = 0; )
  // Implement normalization
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  sw = digitalRead(SW);

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", y = ");
  Serial.println(yValue);
  Serial.print(", B = ");
  Serial.println(sw);
  delay(200);
}
