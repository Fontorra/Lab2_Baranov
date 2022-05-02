#pragma once
#include "Sequence.h"
#include "DynamicArray.h"

template <class T>
class DynamicArraySequence : public Sequence<T> {
private:
	DynamicArray<T>* items;

	void Clear() {
		delete items;
		items = new DynamicArray<T>;
	}
public:
	//constructors

	DynamicArraySequence();

	DynamicArraySequence(T* items, int count);
	
	DynamicArraySequence(int count);
	
	DynamicArraySequence(const DynamicArraySequence<T>& sequence);

	//destructor

	~DynamicArraySequence();

	//operators

	DynamicArraySequence<T>& operator = (const DynamicArraySequence<T>& sequence);

	T& operator [] (int index) override;

	bool operator == (const DynamicArraySequence<T>& sequence);
	
	//methods

	T Get(int index) override;

	T GetFirst() override;
	
	T GetLast() override;
	
	int GetLength() override;
	
	void Append(T item) override;

	void Prepend(T item) override;
	
	void InsertAt(int index, T item) override;
	
	T& Pop(int index);

	Sequence<T>* GetSubSequence(int startIndex, int endIndex) override;

	Sequence <T>* Concat(Sequence <T>* list) override;
	
	//map-reduce

	void Map(T(*function)(T item)) override;

	T Reduce(T(*function)(T, T), T C) override ;

	Sequence<T>* Where(bool (*function)(T item)) override;
};

//constructors

template <typename T>

DynamicArraySequence<T>::DynamicArraySequence() {
	this->items = new DynamicArray<T>;
}

template <typename T>

DynamicArraySequence<T>::DynamicArraySequence(T* items, int count) {
	this->items = new DynamicArray<T>(items, count);
}

template <typename T>

DynamicArraySequence<T>::DynamicArraySequence(int count) {
	items = new DynamicArray<T>(count);
}

template <typename T>

DynamicArraySequence<T>::DynamicArraySequence(const DynamicArraySequence<T>& sequence) {
	this->items = new DynamicArray<T>(*sequence.items);
}

//destructor
template <typename T>

DynamicArraySequence<T>::~DynamicArraySequence() {
	delete items;
}

//operators
template <typename T>

DynamicArraySequence<T>& DynamicArraySequence<T>::operator = (const DynamicArraySequence<T>& sequence) {
	Clear();
	(*this->items) = *sequence.items;
	return (*this);
}

template <typename T>

T& DynamicArraySequence<T>::operator [] (int index){
	return (*items)[index];
}

template <typename T>

bool DynamicArraySequence<T>::operator == (const DynamicArraySequence<T>& sequence) {
	if (*(this->items) == *(sequence.items)) return true;
	return false;
}

//methods

template <typename T>

T DynamicArraySequence<T>::Get(int index) {
	return items->Get(index);
}

template <typename T>

T DynamicArraySequence<T>::GetFirst() {
	return (*items)[0];
}

template <typename T>

T DynamicArraySequence<T>::GetLast(){
	return (*items)[items->GetSize() - 1];
}

template <typename T>

int DynamicArraySequence<T>::GetLength(){
	return items->GetSize();
}

template <typename T>

void DynamicArraySequence<T>::Append(T item){
	items->InsertAt(items->GetSize(), item);
}

template <typename T>

void DynamicArraySequence<T>::Prepend(T item) {
	items->InsertAt(0, item);
}

template <typename T>

void DynamicArraySequence<T>::InsertAt(int index, T item) {
	items->InsertAt(index, item);
}

template <typename T>

T& DynamicArraySequence<T>::Pop(int index) {
	return items->Pop(index);
}

template <typename T>

Sequence<T>* DynamicArraySequence<T>::GetSubSequence(int startIndex, int endIndex) {
	if (items == nullptr) return nullptr;
	int length = items->GetSize();
	if (startIndex >= length || startIndex < 0 || endIndex >= length || endIndex < 0) throw exception("IndexOutOfRange");
	if (startIndex > endIndex) {
		DynamicArraySequence<T>* newSequenceItems = new DynamicArraySequence<T>;
		return newSequenceItems;
	}
	DynamicArraySequence<T>* newSequenceItems = new DynamicArraySequence<T>;
	for (int i = 0; i < endIndex - startIndex + 1; i++) {
		newSequenceItems->Append(items->Get(i + startIndex));
	}
	return newSequenceItems;
}

template <typename T>

Sequence <T>* DynamicArraySequence<T>::Concat(Sequence <T>* list) {
	int thisSize = this->items->GetSize();
	int listSize = ((DynamicArraySequence*)list)->items->GetSize();
	DynamicArraySequence<T>* newSequenceItems = new DynamicArraySequence<T>;
	for (int i = 0; i < thisSize; i++) {
		newSequenceItems->Append((*items)[i]);
	}
	for (int i = thisSize; i < thisSize + listSize; i++) {
		newSequenceItems->Append(((DynamicArraySequence<T>*)(list))->items->operator[](i - thisSize));
	}
	return newSequenceItems;
}

template <typename T>

//map-reduce

void DynamicArraySequence<T>::Map(T(*function)(T item)) {
	int length = GetLength();
	for (int i = 0; i < length; i++) {
		(*items)[i] = (*function)((*items)[i]);
	}
}

template <typename T>

T DynamicArraySequence<T>::Reduce(T(*function)(T, T), T C) {
	T result = C;
	int length = GetLength();
	for (int i = 0; i < length; i++) {
		result = function((*items)[i], result);
	}
	return result;
}

template <typename T>

Sequence<T>* DynamicArraySequence<T>::Where(bool (*function)(T item)) {
	int length = GetLength();
	Sequence<T>* newList = new DynamicArraySequence<T>;
	for (int i = 0; i < length; i++) {
		if ((*function)((*items)[i])) {
			newList->Append((*items)[i]);
		}
	}
	return newList;
}