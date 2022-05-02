#pragma once

#include <iostream>

using namespace std;

template <class T>

class DynamicArray
{
public:

	//constructors
	
	DynamicArray(T* items, int count);

	DynamicArray();

	DynamicArray(int size);

	DynamicArray(const DynamicArray<T>& dynamicArray);

	//destructos

	~DynamicArray();

	//operators
	
	DynamicArray<T>& operator = (const DynamicArray<T>& dynamicArray);

	bool operator == (const DynamicArray<T>& dynamicArray);

	T& operator [] (int index);

	//methods

	T Get(int index);

	int GetSize();

	void Set(int index, T value);

	void InsertAt(int index, T value);

	void Resize(int newSize);

	T& Pop(int index);

private:

	void Clear() {
		delete[] data;
		data = nullptr;
		size = 0;
	}

	int size = 0;
	T* data = nullptr;

};

//constructors

template <typename T>

DynamicArray<T>::DynamicArray(T* items, int count) {
	data = new T[count];
	size = count;
	for (int i = 0; i < size; i++) {
		data[i] = items[i];
	}
}

template <typename T>

DynamicArray<T>::DynamicArray() {
	size = 0;
	data = nullptr;
}

template <typename T>

DynamicArray<T>::DynamicArray(int size) {
	data = new T[size];
	for (int i = 0; i < size; i++) {
		data[i] = T();
	}
	this->size = size;
}


template <typename T>

DynamicArray<T>::DynamicArray(const DynamicArray<T>& dynamicArray) {
	int size = dynamicArray.size;
	this->size = size;
	this->data = new T[size];
	for (int i = 0; i < size; i++) {
		data[i] = dynamicArray.data[i];
	}
}

//destructos

template <typename T>

DynamicArray<T>::~DynamicArray() {
	delete[] data;
}

//operators

template <typename T>

DynamicArray<T>& DynamicArray<T>::operator = (const DynamicArray<T>& dynamicArray) {
	Clear();
	int size = dynamicArray.size;
	this->size = size;
	this->data = new T[size];
	for (int i = 0; i < size; i++) {
		data[i] = dynamicArray.data[i];
	}
	return *this;
}

template <typename T>

T& DynamicArray<T>::operator [] (int index) {
	if (index < 0 || index >= size) throw exception("IndexOutOfRange");
	return data[index];
}

template <typename T>

bool DynamicArray<T>::operator == (const DynamicArray<T>& dynamicArray) {
	if (size == dynamicArray.size && data != dynamicArray.data) {
		for (int i = 0; i < size; i++) {
			if (data[i] != dynamicArray.data[i]) return false;
		}
		return true;
	}
	return false;
}

//methods

template <typename T>

T DynamicArray<T>::Get(int index) {
	if (index < 0 || index >= size) throw exception("IndexOutOfRange");
	return data[index];
}

template <typename T>

int DynamicArray<T>::GetSize() {
	return size;
}

template <typename T>

void DynamicArray<T>::Set(int index, T value) {
	if (index < 0 || index >= size) throw exception("IndexOutOfRange");
	data[index] = value;
}

template <typename T>

void DynamicArray<T>::InsertAt(int index, T value) {
	if (index < 0 || index > size) throw exception("IndexOutOfRange");
	size++;
	if (data == nullptr) data = new T[1];
	else Resize(size);
	memmove(&data[index + 1], &data[index], (size - index - 1) * sizeof(T));
	data[index] = value;
}

template <typename T>

void DynamicArray<T>::Resize(int newSize) {
	if (newSize > 0) {
		data = (T*)realloc(data, newSize * sizeof(T));
		if (newSize > size) {
			for (int i = 0; i < newSize; i++) data[i] = T();
		}
		size = newSize;
	}
	if (newSize == 0) {
		size = 0;
		delete data;
		data = nullptr;
	}
}

template <typename T>

T& DynamicArray<T>::Pop(int index) {
	if (index < 0 || index >= size || size == 0) throw exception("IndexOutOfRange");
	T thisItem = data[index];
	size--;
	if (index < size) memmove(&data[index], &data[index + 1], (size - index) * sizeof(T));
	Resize(size);
	return thisItem;
}