/*
 * Button.cpp
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#include "Button.h"

Button::Button(int sensorID,const char *name, int port, SENSOR_CALLBACK_SIGNATURE) :
Sensor(sensorID,name,DeviceType::NO_TYPE_AVAILABLE,callback) {
	digitalPort = port;
	pinMode(digitalPort, INPUT);
}

Button::~Button() {
}

int Button::readValue() {
	int value = digitalRead(digitalPort);
	return value;
}
