#define IN_LM35 A0
#define IN_PHOTORESISTER A1
#define OUT_LED_R 11
#define OUT_LED_G 10
#define OUT_LED_B 9
#define THRESHOLD_A 26
#define THRESHOLD_B 28
#define THRESHOLD_C 30
#define THRESHOLD_LIGHT 850

void setup() {
  // Pin Setup - OUTPUT
  pinMode(OUT_LED_R, OUTPUT);
  pinMode(OUT_LED_G, OUTPUT);
  pinMode(OUT_LED_B, OUTPUT);

  // Serial Setup
  Serial.begin(9600);

}

void loop() {
  int led_R = 0;
  int led_G = 0;
  int led_B = 0;
  char fire_level = 'X';
  bool box_opened = false;
  
  // Input
  int raw_photoresister = analogRead(IN_PHOTORESISTER);
  int raw_lm35 = analogRead(IN_LM35);

  // Calculate Temperature
  float temp = (5.0 * raw_lm35 * 100) / 1024;

  // Set LED Value
  if (temp >= THRESHOLD_C) {
    fire_level = 'C';
    led_R = 255;
  }
  else if (temp >= THRESHOLD_B) {
    fire_level = 'B';
    led_G = 255;
  }
  else if (temp >= THRESHOLD_A) {
    fire_level = 'A';
    led_B = 255;
  }

  // Set Box Value
  if (raw_photoresister >= THRESHOLD_LIGHT) {
    box_opened = true;
  }
  
  // Output - Write Values to LED
  analogWrite(OUT_LED_R, led_R);
  analogWrite(OUT_LED_G, led_G);
  analogWrite(OUT_LED_B, led_B);

  // Output - Write Temperature and Fire Level to Serial
  Serial.print("t");
  Serial.print(":");
  Serial.print(temp);
  Serial.print(":");
  Serial.print(fire_level);
  Serial.println();

  // Output - Write Box Status to Serial
  Serial.print("b:");
  Serial.print(box_opened);
  Serial.println();

  // Delay
  delay(1000);

}
