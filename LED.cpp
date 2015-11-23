/*
 * LED.cpp
 *
 *  Created on: 16.02.2013
 *      Author: mse
 */

#include "LED.h"

LED::LED(int sensorID, const char *name, int port) :
Actor(sensorID, name, DeviceType::LED) {
	digitalPort = port;
	pinMode(digitalPort, OUTPUT);
	digitalWrite(digitalPort, LOW);
}

LED::~LED() {
	// TODO Auto-generated destructor stub
}
void LED::writeValue(int value) {

	digitalWrite(digitalPort, value);
}

