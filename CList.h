/*
 * CList.h
 *
 *  Created on: 25.05.2012
 *      Author: mse
 */

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
