/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#include "Button.h"

Button::Button(int sensorID,const char *name, int port, SENSOR_CALLBACK_SIGNATURE) :
Sensor(sensorID,name,DeviceTypes::NO_TYPE_AVAILABLE,callback) {
	digitalPort = port;
	pinMode(digitalPort, INPUT);
}

Button::~Button() {
}

int Button::readValue() {
	int value = digitalRead(digitalPort);
	return value;
}
