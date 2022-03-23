#include <Wire.h>
#include <Adafruit_BME280.h>
#include <SD.h>

#define LOCK 1 
#define SD_SS 10

void setup()
{
    //initialize SD card and file object
    pinMode(10, OUTPUT);
    File data = SD.open("test.csv", FILE_WRITE);

    //initialize barometric sensor over I2C
    //library: https://github.com/adafruit/Adafruit_BME280_Library
    Adafruit_BME280 bme;
    bme.begin();

    //initialize relay for locks
    pinMode(LOCK, OUTPUT);
    digitalWrite(LOCK, LOW);

    //values are in hPa and meters
    float INITIAL_PRESSURE = bme.readPressure();
    float MIN_DEPLOY_ALTITUDE = 2000;
    float DEPLOYMENT_ALTITUDE = 1500;

    //loop continuously, until min altitude is reached
    float altitude;
    while(1)
    {
        altitude = bme.readAltitude(INITIAL_PRESSURE);
        if(altitude > MIN_DEPLOY_ALTITUDE){break;}
    }

    //wait for altitude to drop to DEPLOYMENT_ALTITUDE, and then 
    //release the payload from the bay
    while(1)
    {
        altitude = bme.readAltitude(INITIAL_PRESSURE);
        if(altitude < DEPLOYMENT_ALTITUDE)
        {
            digitalWrite(LOCK, HIGH);
            delay(1000);
            digtialWrite(LOCK, LOW);
        }
    }


}

void loop()
{
    
}