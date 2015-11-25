/*
 * Device.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include <Arduino.h>
#include "Types.h"


typedef struct {
    uint8_t type;
    uint16_t id;
    uint16_t deviceType;
    char data[19];
} Protocol;

class Device {
public:
    Device(uint16_t deviceID, const char *name,DeviceTypes::type type) {
		id = deviceID;
        deviceType = type;
        deviceName = name;
	}
	virtual ~Device() {
	}
	uint16_t getDeviceID() {
		return id;
	}
    DeviceTypes::type getDeviceType() {
        return deviceType;
    }
private:
	uint16_t id;
    DeviceTypes::type deviceType;
    const char *deviceName;
};

#endif /* DEVICE_H_ */
