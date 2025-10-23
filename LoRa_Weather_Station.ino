#include <SparkFunBME280.h>
#include <Wire.h>
#include <HardwareSerial.h>
HardwareSerial Anemo(2);
BME280 BMESENS;

#define RXD2 16
#define TXD2 17
#define RS485_EN 4
float BMETemp = 0;
float BMEHum = 0;
float BMEPres = 0;
float windspeed = 0;
float winddir = 0;

bool parsedata (char *data){
  char *comma = strchr(data , ',');
  if (!comma) return false;
  *comma = '\0';
  windspeed = atof(data);
  winddir = atof(comma + 1);
  return true;
}

bool getWind(){
  char buffer[64];
  int idx = 0;
  unsigned long start = millis();
  while (millis() - start <1000){
    if(Anemo.available()){
      char c = Anemo.read();
      if (c == '\n' || idx >= 63){
        buffer[idx] = '\0';
        if(idx > 0){
          return parsedata(buffer);
        }
        idx =0;
      }
      else if (c >= 32 && c <=126){
        buffer[idx++] = c;
      }
    }
  }
  return false;
}

void getBMEReadings(){
  BMEHum = BMESENS.readFloatHumidity();
  BMETemp = BMESENS.readTempC();
  BMEPres = BMESENS.readFloatPressure();
}

void setup() {
  if (BMESENS.beginI2C(MYWIRE) == false) serial.println("BME FAIL")  // put your i2c pin here

}

void loop() {
  // put your main code here, to run repeatedly:

}
