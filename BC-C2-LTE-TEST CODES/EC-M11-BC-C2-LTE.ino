// EC-M11-EG-C1
/*
 * Analog Input Test
 * Digital Input Test
 * RS-485 Serial print
 * 12V Booster Enable / Disable
 * 
 */

 #include <Adafruit_ADS1X15.h>
 Adafruit_ADS1015 ads; 

String adcString[8];

#define GSM_RX 26
#define GSM_TX 25
#define GSM_PWR 22
#define GSM_RST 32

unsigned long int timer1 = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, GSM_RX, GSM_TX); 

  Wire.begin(16,17);

  delay(1000);
  
  Serial.println("The device is powered up");
  
  pinMode(35, INPUT);    // Digital Input 1
  pinMode(34, INPUT);    // Digital Input 2

  pinMode(21, INPUT);    // ADS1115 Interrupt

  //pinMode(36, INPUT);    // Analog input
    
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


}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print("I1: ");Serial.println(digitalRead(35));
  Serial.print("I2: ");Serial.println(digitalRead(34));
  Serial.print("Battery Voltage: ");Serial.println(readBattery());
  delay(100);
  digitalWrite(18,HIGH);


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
