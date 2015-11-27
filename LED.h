/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#ifndef LED_H_
#define LED_H_

#include "Actor.h"
class LED: public Actor {
public:
	LED(int, const char*, int);
	virtual ~LED();
	virtual void writeValue(int);

private:
	int digitalPort;
};

#endif /* LED_H_ */
