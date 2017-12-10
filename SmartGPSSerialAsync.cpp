#include "SmartGPSSerialAsync.h"

byte SmartGPS::isReady() {
  return readyToGet;
};

void SmartGPS::setRun(char *b, int l) {
  buf = ptr = b;
  len = l;
}

void SmartGPS::doneRead() {
  readyToGet=0; // прочитано, но снова не надо читать
}

void SmartGPS::continueRun() {
  if (!reading) { // если уже прочитали
    reading = 1;
    found = 0;
    setRun(commandBuf, COMMAND_BUFFER);
  }
};

void SmartGPS::run() {
  while (port->available()) {
    if (reading) {
      *ptr = port->read();
      if (ptr - buf == len - 1 || *ptr == ',' || *ptr == '\n' || *ptr == '\r' ) {
        *ptr = 0;
        //Serial.print("Token:");
        //Serial.println(buf);
        if (0 == strcmp(buf, "$GPRMC")) {
          fieldNum = 0;
          found = 1;
        }
        if (found) {
          switch (fieldNum) {
            case 0:
              setRun(data->timeUTC, sizeof(GPSData::timeUTC));
              break;
            case 1:
              setRun(data->valid, sizeof(GPSData::valid));
              break;
            case 2:
              setRun(data->lattitud, sizeof(GPSData::lattitud));
              break;
            case 3:
              setRun(data->lattitudDir, sizeof(GPSData::lattitudDir));
              break;
            case 4:
              setRun(data->longitud, sizeof(GPSData::longitud));
              break;
            case 5:
              setRun(data->longitudDir, sizeof(GPSData::longitudDir));
              break;
            case 6:
              setRun(data->speedKnots, sizeof(GPSData::speedKnots));
              break;
            case 7:
              setRun(data->course, sizeof(GPSData::course));
              break;
            case 8:
              setRun(data->date, sizeof(GPSData::date));
              break;
            default:
              reading = 0;
              readyToGet = 1;
              //Serial.println("Stop reading");
              break;
          }
          fieldNum++;
        } else {
          ptr = buf;
        }
      } else {
        ptr++;
      }
    } else {
      port->read();
    }
  }
}


