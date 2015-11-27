/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/



#ifndef SENSOR_H_
#define SENSOR_H_

#include "Device.h"
#define SENSOR_CALLBACK_SIGNATURE void (*callback)(Protocol)



class Sensor : public Device {
public:
    Sensor(uint16_t, const char*,DeviceTypes::type, SENSOR_CALLBACK_SIGNATURE);
	virtual ~Sensor();
	void readAndDispatch();


protected:
	virtual int readValue()=0;

private:
    SENSOR_CALLBACK_SIGNATURE;

	bool hasChanged();
	void sendEvent(int);
    void setCallback(SENSOR_CALLBACK_SIGNATURE);
	int lastValue;
};

#endif /* SENSOR_H_ */
