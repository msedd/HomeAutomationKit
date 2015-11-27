/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#include "CList.h"

CList::CList() {
	root = 0;
	ptr = 0;
	size = 0;

}

CList::~CList() {
	// TODO Auto-generated destructor stub
}
void CList::append(int key, const void* data) {

	size++;
	CListElement* d = new CListElement();
	d->data = data;
	d->key = key;

	// beim ersten Element
	if (!root && !ptr) {
		root = d;
		ptr = d;
	} else {
		ptr->next = d;
		ptr = d;
	}

}
int CList::getSize() {
	return size;
}

const void* CList::getElemet(int count) {

	int c = 0;
	CListElement* element = root;
	while (element) {

		if (c == count) {

			return element->data;
		}

		element = element->next;
		c++;
	}

	return 0;
}
const void* CList::getElemetByKey(int key) {

	CListElement* element = root;
	while (element) {
		if (element->key == key) {

			return element->data;
		}

		element = element->next;
	}
	return 0;
}
