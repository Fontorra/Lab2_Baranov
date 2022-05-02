#pragma once

template <class T>
class Sequence {
public:

	virtual T GetFirst() = 0;
	virtual T GetLast() = 0;
	virtual Sequence<T>* GetSubSequence(int startIndex, int endIndex) = 0;
	virtual int GetLength() = 0;
	virtual void Append(T item) = 0;
	virtual void Prepend(T item) = 0;
	virtual void InsertAt(int index, T item) = 0;
	virtual Sequence <T>* Concat(Sequence <T>* list) = 0;
	virtual T& operator [] (int index) = 0;
	virtual T Get(int index) = 0;
	virtual T& Pop(int index) = 0;
	virtual Sequence<T>* Where(bool (*function)(T item)) = 0;
	virtual void Map(T (*function)(T item)) = 0;
	virtual T Reduce(T(*function)(T, T), T C) = 0;

};