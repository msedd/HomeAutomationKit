/*
 * Actor.h
 *
 *  Created on: 14.02.2013
 *      Author: mse
 */

#ifndef ACTOR_H_
#define ACTOR_H_

#include "Device.h"
class Actor: public Device {
public:
    Actor(uint16_t, const char*, Types::deviceType);
	virtual ~Actor();

	virtual void writeValue(int)=0;
};

#endif /* ACTOR_H_ */
