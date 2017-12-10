#include <Arduino.h>

#ifndef SERIAL_GPS_SOFTWARE && SERIAL_GPS_HARDWARE
  #define SERIAL_GPS_SOFTWARE
#endif

#ifdef SERIAL_GPS_SOFTWARE
  #include <SoftwareSerial.h>
  #define DEFINED_Serial SoftwareSerial
#endif

#ifdef SERIAL_GPS_HARDWARE
  #include <HardwareSerial.h>
  #define DEFINED_Serial HardwareSerial
#endif

#define COMMAND_BUFFER 20

class GPSData {
  public:
    char timeUTC[20];
    char valid[2];
    char lattitud[15];
    char lattitudDir[2];
    char longitud[15];
    char longitudDir[2];
    char speedKnots[10];
    char course[10];
    char date[10];

    GPSData::GPSData() {};
    GPSData::~GPSData() {};
};


class SmartGPS {
  private:
    DEFINED_Serial *port;
    byte reading;
    byte fieldNum;
    byte readyToGet;
    GPSData *data;
    // для run
    char *buf;
    char *ptr;
    byte len;
    byte found;
    char commandBuf[COMMAND_BUFFER];
  public:
    SmartGPS::SmartGPS(DEFINED_Serial *p, GPSData *d) {
      port = p;
      reading = 1;
      fieldNum = 0;
      readyToGet = 0;
      data = d;
      found = 0;
      setRun(commandBuf, COMMAND_BUFFER);
    }
    SmartGPS::~SmartGPS() {};

    void run();
    byte isReady();
    void continueRun();
    void doneRead();
  private:
    void setRun(char *b, int l);
};

