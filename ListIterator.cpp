#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>

using namespace std;

ListIterator::ListIterator(const SortedIndexedList& list) : list(list) {
	this->current = this->list.head;
}

void ListIterator::first(){
	this->current = this->list.head;

}

void ListIterator::next(){
	if (valid() == false) {
		throw exception();
	}
	this->current = this->current->next;
}

bool ListIterator::valid() const{
	if (this->current == nullptr) {
		return false;
	}
	return true;
}

TComp ListIterator::getCurrent() const{
	return this->current->data;
}