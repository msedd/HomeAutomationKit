/*
 * Device.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <Arduino.h>
#include "DeviceType.h"

class Device {
public:
    Device(int sensorID, const char *name,DeviceType::types type) {
		id = sensorID;
        deviceType = type;
        deviceName = name;
	}
	virtual ~Device() {
	}
	int getID() {
		return id;
	}


private:
	int id;
    DeviceType::types deviceType;
    const char *deviceName;
};

#endif /* DEVICE_H_ */
