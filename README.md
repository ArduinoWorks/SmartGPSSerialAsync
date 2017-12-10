# gps-neo-6m
Serial NMEA interface to GPS module Neo 6M


```
SoftwareSerial ss(10, 11);
GPSData data;
SmartGPS gps(&ss, &data);

void setup() {
  ss.begin(9600);
  ssd1306_128x32_i2c_init();
  ssd1306_fillScreen( 0x00 );
  Serial.begin(9600);
  while (!Serial);
  Serial.println("Ready");
}

void loop() {
  char buf[200];

  gps.run(); // Call it as much as possible

  if (gps.isReady()) { // Data is ready and already collected and parsed.
    Serial.println("===============");
    sprintf(buf, "Lat: %1s%s", data.lattitudDir, data.lattitud);
    Serial.println(buf);
    sprintf(buf, "Lon: %1s%s", data.longitudDir, data.longitud);
    Serial.println(buf);
    sprintf(buf, "S: %s C:", data.speedKnots, data.course);
    Serial.println(buf);
    sprintf(buf, "Tim: %s %s", data.timeUTC, data.valid);
    Serial.println(buf);
    gps.continueRun(); // Collect a next portion of data. Run it once a several seconds.
  }
}
```
