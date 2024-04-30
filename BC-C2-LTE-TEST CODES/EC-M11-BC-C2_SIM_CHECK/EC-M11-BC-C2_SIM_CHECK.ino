// EC-M11-EG-C2
/*
 * Digital Input Test
 * RS-485 Serial print
 * 12V Booster Enable / Disable
 * 
 */

#include <Adafruit_ADS1X15.h>

#define DIGITAL_IN1 34
#define DIGITAL_IN2 35
#define I2C_SCL 17
#define I2C_SDA 16
#define ADS1115_INT 18

Adafruit_ADS1115 ads1;

String adcString[8];

#define GSM_RX 26
#define GSM_TX 25
#define GSM_PWR 22
#define GSM_RST 32

unsigned long int timer1 = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, GSM_RX, GSM_TX); 

  Wire.begin(16,17);
  delay(1000); 
  Serial.println("The device is powered up");

  pinMode(34, INPUT);  
  pinMode(35, INPUT);    // Digital Input 2


  pinMode(18, OUTPUT);    // 12V boosted output enable

  pinMode(GSM_PWR, OUTPUT);    // 12V boosted output enable
  pinMode(GSM_RST, OUTPUT);    // SIM7000 Power - only on LTE version

  digitalWrite(GSM_RST, HIGH);
  digitalWrite(GSM_PWR, HIGH);
  delay(1000);
  digitalWrite(GSM_PWR, LOW);

  delay(3000);
 
  timer1 = millis();
  Serial2.println("AT");
  while(millis()<timer1+10000){
    while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
    }
  }

  timer1 = millis();
  Serial2.println("AT+CPIN?");
  while(millis()<timer1+10000){
    while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
    }
  }

  Serial.println("AT SCAN DONE");
   
  if (!ads1.begin(0x49)) {
    Serial.println("Failed to initialize ADS 1 .");
    while (1);
  }
}

void loop() {
  Serial.print("I1: ");Serial.println(digitalRead(34));
  Serial.print("I2: ");Serial.println(digitalRead(35));
  digitalWrite(18,HIGH);

  int16_t adc0, adc1, adc2, adc3;
  adc0 = ads1.readADC_SingleEnded(0);
  adc1 = ads1.readADC_SingleEnded(1);
  adc2 = ads1.readADC_SingleEnded(2);
  adc3 = ads1.readADC_SingleEnded(3);

  Serial.println("-----------------------------------------------------------");
  Serial.print("AIN1: "); Serial.print(adc0); Serial.println("  ");
  Serial.print("AIN2: "); Serial.print(adc1); Serial.println("  ");
  Serial.print("SOLAR: "); Serial.print(adc2); Serial.println("  ");

  Serial.print("Battery Voltage: ");Serial.println(readBattery());
  delay(800);

  while (Serial.available()) {
    int inByte = Serial.read();
    Serial2.write(inByte);
  }

  while (Serial2.available()) {
    int inByte = Serial2.read();
    Serial.write(inByte);
  }
  
  delay(1);
}

int readBattery(){
  unsigned int analog_value;
  analog_value = analogRead(36);
  return analog_value;
}
