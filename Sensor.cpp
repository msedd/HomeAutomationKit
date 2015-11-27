/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#include "Sensor.h"

Sensor::Sensor(uint16_t deviceID, const char *name, DeviceTypes::type type, SENSOR_CALLBACK_SIGNATURE) :
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
    msg.type = ProtocolTypes::DEVICE_VALUE_BROADCAST;
    memset(msg.data,0,sizeof(msg.data));
    msg.data[0]=value;
	callback(msg);
}
