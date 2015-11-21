/*
 * Sensor.h
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#define SENSOR_CALLBACK_SIGNATURE void (*callback)(int, int)

#ifndef SENSOR_H_
#define SENSOR_H_

#include "Device.h"

class Sensor : public Device {
public:
	Sensor(int, SENSOR_CALLBACK_SIGNATURE);
	virtual ~Sensor();
	void readAndDispatch();


protected:
	virtual int readValue()=0;

private:
    SENSOR_CALLBACK_SIGNATURE;

	bool hasChanged();
	void sendEvent(int);
    void setCallback(SENSOR_CALLBACK_SIGNATURE);
	int lastValue;
};

#endif /* SENSOR_H_ */
