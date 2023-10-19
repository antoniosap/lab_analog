#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <SPI.h>

#include "./ADS1256.h"
#undef  pinDRDY
#define pinDRDY   (39) 
#define pinPWDN   (33)

LiquidCrystal_I2C lcd(0x27, 20, 4);  // set the LCD address to 0x27
ADS1256           adc(800000U, 2.5, MISO, MOSI, SCK, SS, pinDRDY, false, 0);

char appname[]    = "INFO: lab_analog start";
double analogsV[] = { 0, 0, 0, 0, 0, 0, 0, 0};

#define LOOP_PERIOD   500 // 500ms loop period
uint32_t lastLoop = 0;

void ADS1256setup() {
  uint8_t ADCstatus;

  pinMode(pinPWDN, OUTPUT);
  pinMode(pinPWDN, HIGH);

  adc.begin(ADS1256_DRATE_5SPS, ADS1256_GAIN_1, true);
  ADCstatus = adc.getStatus();
  Serial.print("ADC status: ");
  Serial.println(ADCstatus, BIN);
  lcd.setCursor(0,2);
  lcd.printf("  ADS1256 status %X", ADCstatus);
  delay(2000);
}

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
  Serial.print("pinDRDY: ");
  Serial.println(pinDRDY);
  Serial.print("pinCS: ");
  Serial.println(pinCS);
  Serial.print("pinPWDN: ");
  Serial.println(pinPWDN);
  Serial.print("MISO: ");
  Serial.println(MISO);
  Serial.print("MOSI: ");
  Serial.println(MOSI);
  Serial.print("SCK: ");
  Serial.println(SCK);
  Serial.print("SS: ");
  Serial.println(SS);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("     lab_analog     ");
  lcd.setCursor(0,1);
  lcd.print("     12.10.2023     ");
  delay(2000);

  ADS1256setup();
  
  lcd.clear();
}

double randomDouble(double minf, double maxf) {
  randomSeed(analogRead(0));
  return minf + random(1UL << 31) * (maxf - minf) / (1UL << 31);  // use 1ULL<<63 for max double values)
}

void readMeasure(byte channel) {
  adc.waitDRDY();
  adc.setChannel(channel);
  analogsV[channel] = adc.readCurrentChannel();
}

void showMeasure() {
  lcd.setCursor(0,0);
  lcd.printf("1|%+6.5f%+6.5f|5", analogsV[0], analogsV[4]);
  lcd.setCursor(0,1);
  lcd.printf("2|%+6.5f%+6.5f|6", analogsV[1], analogsV[5]);
  lcd.setCursor(0,2);
  lcd.printf("3|%+6.5f%+6.5f|7", analogsV[2], analogsV[6]);
  lcd.setCursor(0,3);
  lcd.printf("4|%+6.5f%+6.5f|8", analogsV[3], analogsV[7]);
}

void loop() {
  // limit loop period
  if (millis() - lastLoop < LOOP_PERIOD)  {
    return;
  }
  lastLoop = millis();

  // working
  readMeasure(0);
  readMeasure(1);
  readMeasure(2);
  readMeasure(3);
  readMeasure(4);
  readMeasure(5);
  readMeasure(6);
  readMeasure(7);
  showMeasure();
}