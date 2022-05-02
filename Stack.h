#pragma once
#include "DynamicArraySequence.h"
#include "LinkedListSequence.h" 
template <class T>
class Stack {
public:

	Stack(int ident = 1);

	Stack(int count, int ident = 1);

	Stack(T* items, int count, int ident = 1);

	Stack(const Stack<int>& stack);

	~Stack();

	bool operator == (const Stack<T>& stack);

	void Push(int item);

	T& Pop();

	T Peek();

	int GetLength();

	bool isEmpty();

	Stack<T>* GetSubSequence(int startIndex, int endIndex);

	Stack<T>* Concat(Stack <T>* list);

	Stack<T>* Where(bool (*function)(T item));

	void Map(T(*function)(T item));

	T Reduce(T(*function)(T item, T), T C);

	bool FindSubSequence(Stack<T>* stack);

	void TransferTo(Stack<T>* StackTo);
private:

	void Clear() {
		delete items;
		if (ident == 1) items = new DynamicArraySequence<T>;
		else items = new LinkedListSequence<T>;
	}

	Sequence<T>* items;
	int ident = 1;
};

template <typename T>

Stack<T>* TowerOfHanoi(Stack<T>* beginStack, Stack<T>* resultStack, Stack<T>* bufferStack) {

	if (beginStack->GetLength() <= 1) {
		resultStack->TransferTo(bufferStack);
		beginStack->TransferTo(resultStack);
		bufferStack->TransferTo(resultStack);
		return resultStack;
	}
	if (resultStack->isEmpty()) {
		resultStack->Push(beginStack->Pop());
		bufferStack->TransferTo(resultStack);
	}
	else {
		bufferStack->Push(beginStack->Pop());
		resultStack->TransferTo(bufferStack);
	}
	TowerOfHanoi(beginStack, resultStack, bufferStack);

}

template <typename T>

Stack<T>::Stack(int ident = 1) {
	if (ident == 2) {
		this->items = new LinkedListSequence<T>;
		this->ident = 2;
	}
	else this->items = new DynamicArraySequence<T>;
}

template <typename T>

Stack<T>::Stack(int count, int ident = 1) {
	if (ident == 2) this->items = new LinkedListSequence<T>(count);
	else this->items = new DynamicArraySequence<T>(count);
}

template <typename T>

Stack<T>::Stack(T* items, int count, int ident = 1) {
	if (ident == 2)this->items = new LinkedListSequence<T>(items, count);
	else this->items = new DynamicArraySequence<T>(items, count);
}

template <typename T>

Stack<T>::Stack(const Stack<int>& stack) {
	if (ident == 2) this->items = new LinkedListSequence<T>(*(LinkedListSequence<T>*)(stack.items));
	else this->items = new DynamicArraySequence<T>(*(DynamicArraySequence<T>*)stack.items);
}

template <typename T>

Stack<T>::~Stack() {
	delete items;
}

template <typename T>

bool Stack<T>::operator == (const Stack<T>& stack) {
	if (ident == 1) if (*(DynamicArraySequence<T>*)(this->items) == *(DynamicArraySequence<T>*)(stack.items)) return true;
	if (ident == 2) if (*(LinkedListSequence<T>*)(this->items) == *((LinkedListSequence<T>*)(stack.items))) return true;
	return false;
}

template <typename T>

void Stack<T>::Push(int item) {
	items->Prepend(item);
}

template <typename T>

T& Stack<T>::Pop() {
	return items->Pop(0);
}

template <typename T>

T Stack<T>::Peek() {
	return items->GetFirst();
}

template <typename T>

int Stack<T>::GetLength() {
	return items->GetLength();
}

template <typename T>

bool Stack<T>::isEmpty() {
	if (GetLength() == 0 || items == nullptr) return true;
	return false;
}

template <typename T>

Stack<T>* Stack<T>::GetSubSequence(int startIndex, int endIndex) {
	return items->GetSubSequence(startIndex, endIndex);
}

template <typename T>

Stack<T>* Stack<T>::Concat(Stack <T>* list) {
	Stack<T>* newStack = new Stack<T>;
	newStack->items = (this->items->Concat(list->items));
	return newStack;
}

template <typename T>

Stack<T>* Stack<T>::Where(bool (*function)(T item)) {
	Stack<T>* newStack = new Stack<T>;
	newStack->items = this->items->Where(function);
	return newStack;
}

template <typename T>

void Stack<T>::Map(T(*function)(T item)) {
	items->Map(function);
}

template <typename T>

T Stack<T>::Reduce(T(*function)(T item, T), T C) {
	return items->Reduce(function, C);
}

template <typename T>

bool Stack<T>::FindSubSequence(Stack<T>* stack) {
	int stackLength = stack->GetLength();
	if (stackLength == 0) return true;
	int thisLength = this->GetLength();
	int i = 0;
	for (int j = 0; j < thisLength; j++) {
		if (this->items->Get(j) == (stack->items->Get(i))) i++;
		if (i == stackLength) {
			return true;
		}
	}
	return false;
}

template <typename T>

void Stack<T>::TransferTo(Stack<T>* StackTo) {
	*StackTo = *(this->Concat(StackTo));
	this->Clear();
}
