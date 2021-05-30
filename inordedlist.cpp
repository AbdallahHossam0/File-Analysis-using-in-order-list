/*
 * inordedlist.cpp
 *
 *  Created on: May 2, 2021
 *      Author: student
 */

#include "inorderlist.h"

InOrderList::InOrderList(){
	current = NULL;
	head = NULL;
	tail = NULL;
}
bool InOrderList::sortedInsert(const string &data, const int &counter){
	link addedNode;
	link ptr;
	link prev;

	addedNode = new Node;
	if(addedNode == NULL)
		return false;

	addedNode -> data = data;
	addedNode -> counter = counter;
	addedNode -> next = NULL;


	if(head == NULL || data.compare(head -> data) < 0){
		addedNode->next = head;
		head = addedNode;
		return true;
	}

	ptr = head;
	prev = head;

	while(ptr != NULL && data.compare(ptr->data) >= 0){
		prev = ptr;
		ptr = ptr -> next;
	}
	addedNode -> next = ptr;
	prev -> next = addedNode;
	return true;
}
bool InOrderList::readFirst(string &data, int &counter){
	if(head != NULL){
		current = head;
		data = head -> data;
		counter = head -> counter;
		return true;
	}
	else{
		return false;
	}
}
bool InOrderList::readNext(string &data, int &counter){
	if(head == NULL || head -> next == NULL){
		return false;
	}
	else{
		if(current == NULL || current -> next == NULL){
			return false;
		}
		else{
			current = current -> next;
			data = current -> data;
			counter = current -> counter;
			return true;
		}
	}
}


void InOrderList::deleteWholeList(void){
	current = head;
	while(head != NULL){
		head = head -> next;
		delete current;
		current = head;
	}
}
