/*
 * Sensor.cpp
 *
 *  Created on: 13.02.2013
 *      Author: mse
 */

#include "Sensor.h"

Sensor::Sensor(uint16_t deviceID, const char *name, DeviceType::types type, SENSOR_CALLBACK_SIGNATURE) :
		Device(deviceID,name, type) {
	lastValue = 0;
	this->callback = callback;
}

Sensor::~Sensor() {
}
void Sensor::readAndDispatch() {
	if (hasChanged()) {
		sendEvent(readValue());
	}

}

bool Sensor::hasChanged() {
	int v = readValue();
	if (v != lastValue) {
		lastValue = v;
		return true;
	}
	return false;
}
void Sensor::sendEvent(int value) {
	char buffer[10];
	sprintf(buffer, "[%d,%d]", getDeviceID(), value);
    Protocol msg;
    msg.id = getDeviceID();
    msg.deviceType = getDeviceType();
	callback(msg);
}
