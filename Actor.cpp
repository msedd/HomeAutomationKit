/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#include "Actor.h"

Actor::Actor(uint16_t deviceID, const char *name,DeviceTypes::type type):Device (deviceID,name,type){


}

Actor::~Actor() {
	// TODO Auto-generated destructor stub
}

