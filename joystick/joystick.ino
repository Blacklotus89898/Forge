#define VRX_PIN  A1 // Arduino pin connected to VRX pin
#define VRY_PIN  A0 // Arduino pin connected to VRY pin
#define SW 2

const int numSamples = 100; // Number of samples for calibration
float xBaseline = 0;
float yBaseline = 0;
float xMinValue = 1023; // Initialize to max possible analog value
float xMaxValue = 0;    // Initialize to min possible analog value
float yMinValue = 1023;
float yMaxValue = 0;

int xValue = 0; // To store value of the X axis
int yValue = 0; // To store value of the Y axis
int sw = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(SW, INPUT);
  calibrateSensor();
}

void loop() {
  // read analog X and Y analog values
  xValue = analogRead(VRX_PIN);
  yValue = analogRead(VRY_PIN);
  sw = digitalRead(SW);

  // Normalize the values
  float xNormalizedValue = normalizeValue(xValue, xMinValue, xMaxValue);
  float yNormalizedValue = normalizeValue(yValue, yMinValue, yMaxValue);

  // print data to Serial Monitor on Arduino IDE
  Serial.print("x = ");
  Serial.print(xValue);
  Serial.print(", x (normalized) = ");
  Serial.print(xNormalizedValue);
  Serial.print(", y = ");
  Serial.print(yValue);
  Serial.print(", y (normalized) = ");
  Serial.println(yNormalizedValue);
  Serial.print(", B = ");
  Serial.println(sw);
  delay(200);
}

void calibrateSensor() {
  long xSum = 0;
  long ySum = 0;
  for (int i = 0; i < numSamples; i++) {
    int xVal = analogRead(VRX_PIN);
    int yVal = analogRead(VRY_PIN);
    xSum += xVal;
    ySum += yVal;
    if (xVal < xMinValue) {
      xMinValue = xVal;
    }
    if (xVal > xMaxValue) {
      xMaxValue = xVal;
    }
    if (yVal < yMinValue) {
      yMinValue = yVal;
    }
    if (yVal > yMaxValue) {
      yMaxValue = yVal;
    }
    delay(10);
  }
  xBaseline = xSum / numSamples;
  yBaseline = ySum / numSamples;
  Serial.print("Calibration done: xBaseline = ");
  Serial.print(xBaseline);
  Serial.print(", xMinValue = ");
  Serial.print(xMinValue);
  Serial.print(", xMaxValue = ");
  Serial.print(xMaxValue);
  Serial.print(", yBaseline = ");
  Serial.print(yBaseline);
  Serial.print(", yMinValue = ");
  Serial.print(yMinValue);
  Serial.print(", yMaxValue = ");
  Serial.println(yMaxValue);
}

float normalizeValue(int rawValue, float minValue, float maxValue) {
  return (rawValue - minValue) / (maxValue - minValue);
}
