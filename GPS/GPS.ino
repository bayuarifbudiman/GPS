#include "TinyGPS++.h"
#include "SoftwareSerial.h"
#include <Wire.h>

SoftwareSerial serial_connection(10, 11); //RX=pin 10, TX=pin 11 untuk mendifined Tx dan Rx Pin
TinyGPSPlus gps;//This is the GPS object that will pretty much do all the grunt work with the NMEA data
void setup()
{
  Serial.begin(9600);//Baudrate 9600
  delay(500);
  serial_connection.begin(9600);//utk membuka komunikasi dgn GPS
  Wire.begin();
  delay(1000);
}

void loop()
{
  while(serial_connection.available())//While there are characters to come from the GPS
  {
    gps.encode(serial_connection.read());//This feeds the serial NMEA data into the library one char at a time
  }
  if(gps.location.isUpdated())//This will pretty much be fired all the time anyway but will at least reduce it to only after a package of NMEA data comes in
    {
    //Get the latest info from the gps object which it derived from the data sent by the GPS unit
    Serial.println("=======================================================");
    Serial.println("REFRESH DATA!");
    Serial.print("Satellite Count, Speed MPH :"); 
    Serial.print(gps.satellites.value());
    Serial.println(gps.speed.mph());
    Serial.print("Lat, Long, Alt :"); 
    Serial.print(gps.location.lat(), 6);Serial.print(", "); 
    Serial.print(gps.location.lng(), 6);Serial.print(", "); 
    Serial.println(gps.altitude.feet());   
    Serial.println("=======================================================");
    delay(1000);
    }
}
