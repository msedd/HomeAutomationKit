/*
 * Button.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

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
