# gps-neo-6m
Serial NMEA interface to GPS module Neo 6M


```
#define SERIAL_GPS_SOFTWARE

#include "SmartGPSSerialAsync.h"
#include "SmartDelay.h"

SoftwareSerial ss(10, 11);
GPSData data;
SmartGPS gps(&ss, &data);
SmartDelay disp(5 * 1000UL * 1000UL); // 5 sec

SmartDelay t1(1700UL*1000Ul);
SmartDelay t2(1300UL*1000Ul);

void setup() {
  ss.begin(9600);
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Ready");
}

void loop() {
  char buf[200];
  static byte dn=0;

  gps.run();

  if (gps.isReady()) {
    dn=1;
  }
  if (dn && disp.Now()) {
    Serial.println("===============");
    sprintf(buf, "Lat: %1s%s", data.lattitudDir, data.lattitud);
    Serial.println(buf);
    sprintf(buf, "Lon: %1s%s", data.longitudDir, data.longitud);
    Serial.println(buf);
    sprintf(buf, "S: %s C:", data.speedKnots, data.course);
    Serial.println(buf);
    sprintf(buf, "Tim: %s %s", data.timeUTC, data.valid);
    Serial.println(buf);
    gps.continueRun();
    dn=0;
  }
  if (t1.Now()) {
    Serial.println("Task 1");
  }
  if (t2.Now()) {
    Serial.println("Task 2");
  }
}
```
