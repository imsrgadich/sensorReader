#ifndef _IMU_H
#define _IMU_H

#include <chrono>

/*
 *  The interface to read sensors
 *  @author jaava
 */


class IMU {
public:

    struct Output {
        float magValues[4];                     // sensor output is defined as [timestamp, sensorvalues ...]
        float gyroValues[4];
        float accValues[4];
        float baroValues[2];
        int rawMag[3];
        int rawGyro[3];
        int rawAcc[3];
        int rawBaro[1];
    };


    // Scaled readings
    virtual void readMag(Output &out) = 0;       // microteslas
    virtual void readAcc(Output &out) = 0;       // m/s^2
    virtual void readGyro(Output &out) = 0;      // rad/s
    virtual void readBaro(Output &out) = 0;
    virtual float readTime() = 0;               // returns the timestamp from system clock

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
