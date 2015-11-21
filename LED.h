/*
 * LED.h
 *
 *  Created on: 16.02.2013
 *      Author: mse
 */

#ifndef LED_H_
#define LED_H_

#include "Actor.h"
class LED: public Actor {
public:
	LED(int, int);
	virtual ~LED();
	virtual void writeValue(int);

private:
	int digitalPort;
};

#endif /* LED_H_ */
