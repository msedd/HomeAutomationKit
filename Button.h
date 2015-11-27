/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#ifndef BUTTON_H_
#define BUTTON_H_

#include "Sensor.h"

class Button : public Sensor {
public:
    Button(int, const char*,int, SENSOR_CALLBACK_SIGNATURE);
	virtual ~Button();
protected:
	virtual int readValue();
private:
	int digitalPort;
};

#endif /* BUTTON_H_ */
