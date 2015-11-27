/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#ifndef ACTOR_H_
#define ACTOR_H_

#include "Device.h"
class Actor: public Device {
public:
    Actor(uint16_t, const char*, DeviceTypes::type);
	virtual ~Actor();

	virtual void writeValue(int)=0;
};

#endif /* ACTOR_H_ */
