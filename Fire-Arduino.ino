#define IN_LM35 A0
#define OUT_LED_R 11
#define OUT_LED_G 10
#define OUT_LED_B 9
#define THRESHOLD_A 25
#define THRESHOLD_B 27
#define THRESHOLD_C 30

void setup() {
  // put your setup code here, to run once:

  // Pin Setup - OUTPUT
  pinMode(OUT_LED_R, OUTPUT);
  pinMode(OUT_LED_G, OUTPUT);
  pinMode(OUT_LED_B, OUTPUT);

  // Serial Setup
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  int led_R = 0;
  int led_G = 0;
  int led_B = 0;
  
  int sensor = analogRead(IN_LM35);
  float temp = (5.0 * sensor * 100) / 1024;

  // Log
  Serial.println(temp);

  if (temp >= THRESHOLD_C) {
    led_R = 255;
  }
  else if (temp >= THRESHOLD_B) {
    led_G = 255;
  }
  else if (temp >= THRESHOLD_A) {
    led_B = 255;
  }
  
  analogWrite(OUT_LED_R, led_R);
  analogWrite(OUT_LED_G, led_G);
  analogWrite(OUT_LED_B, led_B);

  delay(1000);

}
