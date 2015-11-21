/*
 * Device.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <Arduino.h>

class Device {
public:
	Device(int sensorID) {
		id = sensorID;
	}
	virtual ~Device() {
	}
	int getID() {
		return id;
	}

private:
	int id;
};

#endif /* DEVICE_H_ */
