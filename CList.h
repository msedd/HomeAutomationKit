/*************************************************************************
 * Arduino Library for Home Automation and Device Control
 * Distributed under Apache 2 License (http://www.apache.org/licenses/)
 * Visit http://marko-seifert.de/blog/?page_id=1042 for more information.
 * (C) Marko Seifert (DeveloperPodcast)
 *************************************************************************/

#ifndef CLIST_H_
#define CLIST_H_

#include <stdio.h>
class CList {

public:

	CList();
	~CList();
	void append(int, const void*);
	int getSize();
	const void* getElemet(int);
	const void* getElemetByKey(int);

private:

	class CListElement {
	public:
		CListElement() {
			next = 0;
			data = 0;
			key = 0;
		}
		~CListElement() {
			delete next;
			//delete data;
			key = 0;
		}
		const void* data;
		int key;
		CListElement* next;

	};
	CListElement* root;
	CListElement* ptr;
	int size;
};

#endif /* CLIST_H_ */
