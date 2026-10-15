#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "ACS712.h"
#include <ZMPT101B.h>

#define SENSITIVITY 500.0f

ACS712  ACS(A1, 5.0, 1023, 185);

#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 32
#define OLED_RESET     -1 
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


ZMPT101B voltageSensor(A0, 50.0);

// int led1 = A3;
float w = 0;

void setup() {
  Serial.begin(9600);

  pinMode(led1, OUTPUT);
  digitalWrite(led1, HIGH);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  
  voltageSensor.setSensitivity(SENSITIVITY);

  ACS.autoMidPoint();
  value = ACS.mA_AC();
}

void loop() {
  float voL = voltageSensor.getRmsVoltage();
  Serial.println(voL);

  float mA = ACS.mA_AC_sampling();
  //  float mA = ACS.mA_AC();

  // value += weight * (mA - value);

  // digitalWrite(led1, LOW);
  // mA = mA/1000;

  if(mA < 70) mA = 0;

  // digitalWrite(led1, (mA >= 70) ? LOW : HIGH);
    mA = mA/1000;
    w = voL * mA;

  Serial.print(" mA: ");
  Serial.print(mA);
  Serial.print(" V: ");
  Serial.print(voL);
  Serial.println();

  display.setTextSize(1);  
  display.setTextColor(WHITE);
  display.setCursor(30,0);
  display.print("Volt = ");
  display.setCursor(70 ,0);
  display.print(voL);

  display.setTextSize(1);  
  display.setTextColor(WHITE);
  display.setCursor(30,15);
  display.print("Arus = ");
  display.setCursor(70, 15);
  display.print(mA);

  display.display();
  display.setTextSize(1);  
  display.setTextColor(WHITE);
  display.setCursor(30, 25);
  display.print("Daya = ");
  display.setCursor(70, 25);
  display.print(w);
  display.display();
  delay(500);
  display.clearDisplay();
}
