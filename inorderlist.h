/*
 * inorderlist.h
 *
 *  Created on: May 2, 2021
 *      Author: student
 */

#ifndef INORDERLIST_H_
#define INORDERLIST_H_



#include <string>
using namespace std;



class InOrderList{
private:
	struct Node{
		string data;
		int counter;
		Node* next = NULL;
	};

	typedef Node* link;
	link head, current, tail;

public:
	InOrderList();
	bool sortedInsert(const string &data, const int &counter);
	bool readFirst(string &data, int &counter);
	bool readNext(string &data, int &counter);
	void deleteWholeList(void);
};


#endif /* INORDERLIST_H_ */
