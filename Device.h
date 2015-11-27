/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

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
