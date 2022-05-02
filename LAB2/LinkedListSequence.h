#pragma once

#include "Sequence.h"
#include "LinkedList.h"

template <class T>
class LinkedListSequence : public Sequence<T> {
private:
	LinkedList<T>* items;

	void Clear() {
		delete items;
		items = new LinkedList<T>;
	}

public:

//constructors
	LinkedListSequence();

	LinkedListSequence(int count);

	LinkedListSequence(T* items, int count);

	LinkedListSequence(const LinkedListSequence <T>& list);

//destructor
	~LinkedListSequence();

//operators

	T& operator [] (int index) override;

	LinkedListSequence& operator = (const LinkedListSequence<T>& sequence);

	bool operator == (const LinkedListSequence<T>& sequence);

//methods

	T GetFirst() override;

	T GetLast() override;

	int GetLength() override;

	T Get(int index) override;

	void Append(T item) override;

	void Prepend(T item) override;

	void InsertAt(int index, T item) override;

	T& Pop(int index);

	Sequence<T>* GetSubSequence(int startIndex, int endIndex) override;

	Sequence <T>* Concat(Sequence <T>* list) override;
	//map-reduce

	Sequence<T>* Where(bool (*function)(T item)) override;

	void Map(T(*function)(T item)) override;

	T Reduce(T(*function)(T, T), T C) override;

}; 


//constructors

template <typename T>

LinkedListSequence<T>::LinkedListSequence() {
	this->items = new LinkedList<T>;
}

template <typename T>

LinkedListSequence<T>::LinkedListSequence(int count) {
	this->items = new LinkedList<T>(count);
}

template <typename T>

LinkedListSequence<T>::LinkedListSequence(T* items, int count) {
	this->items = new LinkedList<T>(items, count);
}

template <typename T>

LinkedListSequence<T>::LinkedListSequence(const LinkedListSequence <T>& list) {
	items = new LinkedList<T>(*(list.items));
}


//destructor

template <typename T>

LinkedListSequence<T>::~LinkedListSequence() {
	delete items;
}

//operators

template <typename T>

T& LinkedListSequence<T>::operator [] (int index) {
	if (index < 0 || index >= items->GetLength()) throw exception("IndexOutOfRange");
	return this->operator [](index);
}


template <typename T>

LinkedListSequence<T>& LinkedListSequence<T>::operator = (const LinkedListSequence<T>& sequence) {
	Clear();
	this->items = sequence->items;
	return (*this);
}

template <typename T>

bool LinkedListSequence<T>::operator == (const LinkedListSequence<T>& sequence) {
	if (*(this->items) == *(sequence.items)) return true;
	return false;
}

//methods

template <typename T>

T LinkedListSequence<T>::GetFirst(){
	return items->GetFirst();
}

template <typename T>

T LinkedListSequence<T>::GetLast() {
	return items->GetLast();
}

template <typename T>

int LinkedListSequence<T>::GetLength() {
	return items->GetLength();
}

template <typename T>

T LinkedListSequence<T>::Get(int index)  {
	return items->Get(index);
}

template <typename T>

void LinkedListSequence<T>::Append(T item) {
	items->Append(item);
}

template <typename T>

void LinkedListSequence<T>::Prepend(T item) {
	items->Prepend(item);
}

template <typename T>

void LinkedListSequence<T>::InsertAt(int index, T item){
	items->InsertAt(item, index);
}

template <typename T>

T& LinkedListSequence<T>::Pop(int index) {
	return items->Pop(index);
}

template <typename T>

Sequence<T>* LinkedListSequence<T>::GetSubSequence(int startIndex, int endIndex)  {
	LinkedListSequence<T>* newSequenceItems = new LinkedListSequence<T>;
	newSequenceItems->items = items->GetSubList(startIndex, endIndex);
	return newSequenceItems;
}

template <typename T>

Sequence <T>* LinkedListSequence<T>::Concat(Sequence <T>* list) {
	LinkedListSequence<T>* newSequenceItems = new LinkedListSequence<T>;
	newSequenceItems->items = items->Concat(((LinkedListSequence<T>*)(list))->items);
	return newSequenceItems;
}

template <typename T>

//map-reduce

Sequence<T>* LinkedListSequence<T>::Where(bool (*function)(T item)) {
	int length = GetLength();
	Sequence<T>* newList = new LinkedListSequence<T>;
	for (int i = 0; i < length; i++) {
		if ((*function)((*items)[i])) {
			Append((*items)[i]);
		}
	}
	return newList;
}

template <typename T>

void LinkedListSequence<T>::Map(T(*function)(T item)) {
	int length = GetLength();
	for (int i = 0; i < length; i++) {
		(*items)[i] = (*function)((*items)[i]);
	}
}

template <typename T>

T LinkedListSequence<T>::Reduce(T(*function)(T, T), T C) {
	T result = C;
	int length = GetLength();
	for (int i = 0; i < length; i++) {
		result = function((*items)[i], result);
	}
	return result;
}