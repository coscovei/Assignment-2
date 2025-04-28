#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <iostream>
using namespace std;
#include <exception>

SortedIndexedList::SortedIndexedList(Relation r) {
	this->relation = r;
	this->head = nullptr;
	this->listSize = 0;
}

int SortedIndexedList::size() const {
	return listSize;
} // Constant time complexity

bool SortedIndexedList::isEmpty() const {
	if (this->head == nullptr) {
		return true;
	}
	return false;
} // Constant time complexity

TComp SortedIndexedList::getElement(int i) const{
	if (i < 0 || i >= this->size()) {
		throw exception();
	}
	Node* current = this->head;
	for (int j = 0; j < i; j++) { 
		current = current->next;
	}
	return current->data;
} // Best case: Θ(1); Worst case: Θ(n); Total complexity: O(n)

TComp SortedIndexedList::remove(int i) {
	if (i < 0 || i >= this->size()) {
		throw exception();
	}
	Node* current = this->head;
	for (int j = 0; j < i - 1; j++) {
		current = current->next;
	}
	if (i == 0) {
		TComp removed = this->head->data;
		Node* toDelete = this->head;
		this->head = this->head->next;
		delete toDelete;
		this->listSize--;
		return removed;
	}
	else {
		TComp removed = current->next->data;
		Node* toDelete = current->next;
		current->next = current->next->next;
		delete toDelete;
		this->listSize--;
		return removed;
	} // Best case: Θ(1); Worst case: Θ(n); Total complexity: O(n)
}

int SortedIndexedList::search(TComp e) const {
	for(int i = 0; i < this->size(); i++) {
		if (this->getElement(i) == e) {
			return i;
		}
	}
	return -1;
} // Best case: Θ(1); Worst case: Θ(n); Total complexity: O(n)

void SortedIndexedList::add(TComp e) {
	if (this->head == nullptr || this->relation(e, this->head->data)) {
		Node* newNode = new Node;
		newNode->data = e;
		newNode->next = this->head;
		this->head = newNode;
	}
	else {
		Node* current = this->head;
		while (current->next != nullptr && this->relation(current->next->data, e)) {
			current = current->next;
		}
		Node* newNode = new Node;
		newNode->data = e;
		newNode->next = current->next;
		current->next = newNode;
	}
	this->listSize++;
} // Best case: Θ(1); Worst case: Θ(n); Total complexity: O(n)

ListIterator SortedIndexedList::iterator(){
	return ListIterator(*this);
} // Constant time complexity

//destructor
SortedIndexedList::~SortedIndexedList() {
	Node* current = head;
	while( current != 0 ) {
		Node* next = current->next;
		delete current;
		current = next;
	}
	head = nullptr;
	listSize = 0;
}