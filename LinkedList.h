#pragma once
#include "SomeCLasses.h"

using namespace std;

template <class T>

class LinkedList {
public:
	//constructors
	LinkedList();

	LinkedList(int count);

	LinkedList(T* items, int count);

	LinkedList(const LinkedList <T>& list);

	//destructor

	~LinkedList();

	//operators

	LinkedList<T>& operator = (const LinkedList <T>& list);

	T& operator [](int index);

	bool operator == (LinkedList<T>& linkedList);
	
	//methods

	T& Pop(int index);

	T Get(int index);
	
	T GetFirst();

	T GetLast();

	int GetLength();

	void Append(T item);

	void Prepend(T item);

	void InsertAt(int index, T item);
	
	void Set(int index, T item);

	LinkedList<T>* GetSubList(int startIndex, int endIndex);
	
	LinkedList<T>* Concat(LinkedList<T>* list);


private:

	typedef struct item {
		T elem;
		item* next;
		item* prev;
	}item;

	int length = 0;
	item* start = nullptr;
	item* end = nullptr;

	void Clear() {
		if (this != nullptr) {
			item* nowitem = start;
			while (nowitem != nullptr) {
				item* nextitem = nowitem->next;
				delete nowitem;
				nowitem = nextitem;
			}
			length = 0;
			start = nullptr;
			end = nullptr;
		}
	}
};


//constructors

template <typename T>
LinkedList<T>::LinkedList() {
	length = 0;
	start = nullptr;
	end = nullptr;
}

template <typename T>

LinkedList<T>::LinkedList(int count) {
	length = count;
	if (length > 0) {
		start = new item[1];
		start->prev = nullptr;
		start->elem = T();
		item* temp = start;
		for (int i = 1; i < count - 1; i++) {
			item* newitem = new item[1];
			newitem->prev = temp;
			newitem->elem = T();
			temp->next = newitem;
			temp = newitem;
		}
		end = new item[1];
		end->next = nullptr;
		end->prev = temp;
		end->elem = T();
		temp->next = end;
	}
}

template <typename T>

LinkedList<T>::LinkedList(T* items, int count) {
	length = count;
	if (length > 0) {
		start = new item[1];
		start->prev = nullptr;
		start->elem = items[0];
		item* temp = start;
		for (int i = 1; i < count - 1; i++) {
			item* newitem = new item[1];
			newitem->prev = temp;
			newitem->elem = items[i];
			temp->next = newitem;
			temp = newitem;
		}
		end = new item[1];
		end->next = nullptr;
		end->prev = temp;
		end->elem = items[count - 1];
		temp->next = end;
	}
}

template <typename T>

LinkedList<T>::LinkedList(const LinkedList <T>& list) {
	length = list.length;
	if (length > 0) {
		start = new item[1];
		start->prev = nullptr;
		start->elem = list.start->elem;
		item* temp = start;
		item* nowitem = list.start->next;
		while (nowitem != nullptr) {
			item* newitem = new item[1];
			newitem->prev = temp;
			newitem->elem = nowitem->elem;
			temp->next = newitem;
			temp = newitem;
			nowitem = nowitem->next;
		}
		temp->next = nullptr;
		end = temp;
	}
}

//destructor

template <typename T>

LinkedList<T>::~LinkedList() {
	item* nowitem = start;
	while (nowitem != nullptr) {
		item* nextitem = nowitem->next;
		delete[] nowitem;
		nowitem = nextitem;
	}
}


//operators

template <typename T>

LinkedList<T>& LinkedList<T>::operator = (const LinkedList <T>& list) {
	Clear();
	length = list.length;
	if (length > 0) {
		start = new item[1];
		start->prev = nullptr;
		start->elem = list.start->elem;
		item* temp = start;
		item* nowitem = list.start->next;
		while (nowitem != nullptr) {
			item* newitem = new item[1];
			newitem->prev = temp;
			newitem->elem = nowitem->elem;
			temp->next = newitem;
			temp = newitem;
			nowitem = nowitem->next;
		}
		temp->next = nullptr;
		end = temp;
	}
	return *this;
}

template <typename T>

T& LinkedList<T>::operator [](int index) {
	if (index < 0 || index >= length) throw exception("IndexOutOfRange");
	item* now = start;
	for (int i = 0; i < index; i++) {
		now = now->next;
	}
	return now->elem;
}

template <typename T>

bool LinkedList<T>::operator == (LinkedList<T>& linkedList) {
	if (length == linkedList.length) {
		for (int i = 0; i < length; i++) {
			if (this->Get(i) != linkedList[i]) return false;
		}
		return true;
	}
	return false;
}

//methods

template <typename T>

T& LinkedList<T>::Pop(int index) {
	if (index < 0 || index >= length || length == 0) throw exception("IndexOutOfRange");
	length--;
	item* nowitem = this->start;
	for (int i = 0; i < index; i++) {
		nowitem = nowitem->next;
	}
	T thisItem = nowitem->elem;
	if (length == 0) {
		start = nullptr;
		end = nullptr;
		delete[] nowitem;
		return thisItem;
	}
	item* prevItem = nowitem->prev;
	if (index == length) {
		prevItem->next = nullptr;
		delete[] nowitem;
		return thisItem;
	}
	item* nextItem = nowitem->next;
	if (index == 0) {
		nextItem->prev = nullptr;
		start = nextItem;
		return thisItem;
	}
	prevItem->next = nextItem;
	nextItem->prev = prevItem;
	delete[] nowitem;
	return thisItem;
}

template <typename T>

T LinkedList<T>::Get(int index) {
	if (index < 0 || index >= length) throw exception("IndexOutOfRange");
	item* now = start;
	for (int i = 0; i < index; i++) {
		now = now->next;
	}
	return now->elem;
}

template <typename T>

T LinkedList<T>::GetFirst() {
	if (start == nullptr || length == 0) throw exception("IndexOutOfRange");
	return start->elem;
}

template <typename T>

T LinkedList<T>::GetLast() {
	if (end == nullptr) throw exception("IndexOutOfRange");
	return end->elem;
}

template <typename T>

int LinkedList<T>::GetLength() {
	return length;
}

template <typename T>

void LinkedList<T>::Append(T item) {
	if (end == nullptr) {
		length = 1;
		end = new struct item[1];
		end->elem = item;
		end->next = nullptr;
		end->prev = nullptr;
		start = end;
	}
	else {
		struct item* newitem = new struct item[1];
		newitem->elem = item;
		newitem->next = nullptr;
		newitem->prev = end;
		end->next = newitem;
		end = newitem;
		length++;
	}
}

template <typename T>

void LinkedList<T>::Prepend(T item) {
	if (start == nullptr) {
		length = 1;
		start = new struct item[1];
		start->next = nullptr;
		start->prev = nullptr;
		start->elem = item;
		end = start;
	}
	else {
		struct item* newitem = new struct item[1];
		newitem->elem = item;
		newitem->prev = nullptr;
		newitem->next = start;
		start = newitem;
		length++;
	}
}

template <typename T>

void LinkedList<T>::InsertAt(int index, T item) {
	if (index > length || index < 0) throw exception("IndexOutOfRange");
	if (index == 0) Prepend(item);
	else
	{
		if (index == length) Append(item);
		else
		{
			struct item* nowitem = start;
			for (int i = 0; i < index; i++) nowitem = nowitem->next;
			struct item* newitem = new struct item[1];
			newitem->elem = item;
			newitem->next = nowitem;
			newitem->prev = nowitem->prev;
			nowitem->prev = newitem;
			newitem->prev->next = newitem;
			length++;
		}
	}
}

template <typename T>

void LinkedList<T>::Set(int index, T item) {
	if (index >= length || index < 0) throw exception("IndexOutOfRange");
	struct item* nowitem = start;
	for (int i = 0; i < index; i++) nowitem = nowitem->next;
	nowitem->elem = item;
}

template <typename T>

LinkedList<T>* LinkedList<T>::GetSubList(int startIndex, int endIndex) {
	if (startIndex >= length || startIndex < 0 || endIndex >= length || endIndex < 0) throw exception("IndexOutOfRange");
	if (startIndex > endIndex) {
		LinkedList <T>* result = new LinkedList<T>;
		return result;
	}
	LinkedList* result = new LinkedList<T>;
	result->length = endIndex - startIndex + 1;
	item* nowitem = start;
	for (int i = 0; i < startIndex; i++) {
		nowitem = nowitem->next;
	}
	result->start = new item[1];
	result->start->prev = nullptr;
	result->start->elem = nowitem->elem;
	item* temp = result->start;
	nowitem = nowitem->next;
	for (int i = startIndex + 1; i <= endIndex; i++) {
		item* newitem = new item[1];
		newitem->prev = temp;
		newitem->elem = nowitem->elem;
		temp->next = newitem;
		temp = newitem;
		nowitem = nowitem->next;
	}
	temp->next = nullptr;
	result->end = temp;
	return result;
}

template <typename T>

LinkedList<T>* LinkedList<T>::Concat(LinkedList<T>* list) {
	LinkedList* result = new LinkedList<T>(*this);
	if (list->GetLength() == 0) return result;
	item* temp = new item[1];
	result->end->next = temp;
	temp->prev = result->end;
	temp->elem = list->start->elem;
	item* nowitem = list->start->next;
	for (int i = 1; i < list->length; i++) {
		item* newitem = new item[1];
		temp->next = newitem;
		newitem->prev = temp;
		newitem->elem = nowitem->elem;
		nowitem = nowitem->next;
		temp = newitem;

	}
	temp->next = nullptr;
	result->end = temp;
	result->length = this->length + list->length;
	return result;
}