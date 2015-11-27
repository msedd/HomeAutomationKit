/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#include "LED.h"

LED::LED(int sensorID, const char *name, int port) :
Actor(sensorID, name, DeviceTypes::LED) {
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

