#include <iostream>

#include "DynamicArray.h"

using namespace std;

/*template <typename T>

void DynamicArray<T>::Print() {
	for (int i = 0; i < size; i++) {
		cout << i << "-ый элемент равен " << data[i] << endl;
	}
	cout << endl;
}

template <typename T>

int DynamicArray<T>::GetSize() {
	return size;
}

template <typename T>

void DynamicArray<T>::Set(int index, T value) {
	if (index < 0 || index > size) throw "IndexOutOfRange";
	size++;
	data = (T*)realloc(data, size * sizeof(T));
	memcpy(&data[index + 1], &data[index], (size - index - 1) * sizeof(T));
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
		delete[] data;
		data = nullptr;
	}
}
*/