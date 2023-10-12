#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27

char appname[]    = "INFO: lab_analog start";
double analogsV[] = { 0, 0, 0, 0, 0, 0, 0, 0};

#define LOOP_PERIOD   500 // 500ms loop period
uint32_t lastLoop = 0;

void setup() {
  Serial.begin(115200);
  delay(5000);

  Serial.println();
  Serial.println(appname);
  Serial.flush();

  Serial.print("SDA: ");
  Serial.println(SDA);
  Serial.print("SCL: ");
  Serial.println(SCL);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("     lab_analog     ");
  lcd.setCursor(0,2);
  lcd.print("     12.10.2023     ");
  delay(2000);
  
  lcd.clear();
}

double randomDouble(double minf, double maxf) {
  randomSeed(analogRead(0));
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}

void loop() {
  // limit loop period
  if (millis() - lastLoop < LOOP_PERIOD)  {
    return;
  }
  lastLoop = millis();

  analogsV[0] = randomDouble(0.0001, 9.99999);
  analogsV[1] = randomDouble(0.0001, 9.99999);
  analogsV[2] = randomDouble(0.0001, 9.99999);
  analogsV[3] = randomDouble(0.0001, 9.99999);
  analogsV[4] = randomDouble(0.0001, 9.99999);
  analogsV[5] = randomDouble(0.0001, 9.99999);
  analogsV[6] = randomDouble(0.0001, 9.99999);
  analogsV[7] = randomDouble(0.0001, 9.99999);

  lcd.setCursor(0,0);
  lcd.printf("1|%6.5f  %6.5f|5", analogsV[0], analogsV[4]);
  lcd.setCursor(0,1);
  lcd.printf("2|%6.5f  %6.5f|6", analogsV[1], analogsV[5]);
  lcd.setCursor(0,2);
  lcd.printf("3|%6.5f  %6.5f|7", analogsV[2], analogsV[6]);
  lcd.setCursor(0,3);
  lcd.printf("4|%6.5f  %6.5f|8", analogsV[3], analogsV[7]);
}