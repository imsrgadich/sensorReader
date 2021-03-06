#ifndef _IMU_H
#define _IMU_H

#include <chrono>
#include <stdint.h>

/*
 *  The base class declaring the sensor reading functions
 *  Write an implementation for different sensors
 *  @author jaava
 */


class IMU {
public:

    struct Output {
        float magValues[3];                     // sensor output is defined as [timestamp, sensorvalues ...]
        float gyroValues[3];
        float accValues[3];
        float baroValues[1];
        int rawMag[3];                          // raw nonscaled sensorvalues. for debugging 
        int rawGyro[3];
        int rawAcc[3];
        int rawBaro[1];
        uint64_t magTime;                       // timestamps
        uint64_t gyroTime;
        uint64_t accTime;
        uint64_t baroTime;
        bool newMag;                            // flag for new sensor values in the struct
        bool newGyro;
        bool newAcc;
        bool newBaro;
    };

    // Scaled readings
    virtual void readMag(Output &out) = 0;       // microteslas
    virtual void readAcc(Output &out) = 0;       // m/s^2
    virtual void readGyro(Output &out) = 0;      // rad/s
    virtual void readBaro(Output &out) = 0;
    virtual uint64_t readTime() = 0;               // returns the timestamp

    virtual void measureOffsets() = 0;          // could be used to calibrate sensors but not implemented atm.
    virtual void enable() = 0;                  // this sets the sensor chip settings. Has to be run at some point in initialization.
    
    virtual void read(Output &out) = 0;         //reads all the sensors to output

    bool hasMag() {return magAvailable;}
    bool hasGyro() {return gyroAvailable;}
    bool hasAcc() {return accAvailable;}
    bool hasBaro() {return baroAvailable;}

protected:
    int gyro_bias[3];              // gyro offset from zero
    
    // scaling values for sensor readings. The raw values are generally 16bit integers. 
    // these depend on the sensor settings (i.e. full range setting)
    float gyro_scale;
    float mag_scale;
    float acc_scale; 
    float baro_scale;
    // system timestamps. Sensors do not necessarily have their own clock at all
    std::chrono::steady_clock::time_point time0;
    std::chrono::steady_clock::time_point lasttime;
    // availability of sensors on particular imu implementation
    bool magAvailable, gyroAvailable, accAvailable, baroAvailable;

};

#endif
