#define IN_LM35 A0
#define IN_POTENTIOMETER A1
#define OUT_LED 3
#define THRESHOLD_A 26
#define THRESHOLD_B 28
#define THRESHOLD_C 30
#define THRESHOLD_POTEN 400

void setup() {
  // Pin Setup - OUTPUT
  pinMode(OUT_LED, OUTPUT);

  // Serial Setup
  Serial.begin(9600);

}

void loop() {
  int led = 0;
  char fire_level = 'X';
  bool box_opened = false;
  
  // Input
  int raw_potentiometer = analogRead(IN_POTENTIOMETER);
  int raw_lm35 = analogRead(IN_LM35);

  // Calculate Temperature
  float temp = (5.0 * raw_lm35 * 100) / 1024;

  // Set LED Value
  if (temp >= THRESHOLD_C) {
    fire_level = 'C';
    led = 255;
  }
  else if (temp >= THRESHOLD_B) {
    fire_level = 'B';
    led = 100;
  }
  else if (temp >= THRESHOLD_A) {
    fire_level = 'A';
    led = 10;
  }

  // Set Box Value
  if (raw_potentiometer >= THRESHOLD_POTEN) {
    box_opened = true;
  }
  
  // Output - Write Values to LED
  analogWrite(OUT_LED, led);

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
