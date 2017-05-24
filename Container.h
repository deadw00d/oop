#pragma once

template<typename T> 
class Container {
public:
		Container();
		~Container();
		void pushFirst(T item);
		void pushLast(T item);
		T& getItem(int index);
		void deleteFirst();
		void deleteLast();
		bool isEmpty();
		unsigned int getCount();
		void clear();
private:
		struct List {
			T item;
			struct List * next;
		};
		List * head;
		unsigned int size;
};


template<typename T> 
Container<T>::Container() {
	head = NULL;
	size = 0;
}

template<typename T> 
Container<T>::~Container() {
	clear();
}

template<typename T>
T& Container<T>::getItem(int index) {
	if (index < 0 || index > size-1) {
		throw "Index out of container range";
	}
	List * tmp = head;
	for (int i = 0; i < index; i++) {
		tmp = tmp->next;
	}
	return tmp->item;
}

template<typename T> 
void Container<T>::pushFirst(T item) {
	Container::List * newHead = new List();
	newHead->next = head;
	newHead->item = item;
	head = newHead;
	size++;
	return;
}

template<typename T> 
void Container<T>::pushLast(T item) {
	Container::List * newItem = new List();
	newItem->next = NULL;
	newItem->item = item;
	size++;
	if (head == NULL) {
		head = newItem;
		return;
	}
	List * tmp = head;
	while (tmp->next != NULL) {
		tmp = tmp->next;
	}
	tmp->next = newItem;
	return;
}

template<typename T> 
void Container<T>::deleteFirst() {
	if (size == 0) throw "Cant delete element from empty container.";
	List * tmp = head->next;
	delete head;
	size--;
	head = tmp;
	return;
}

template<typename T> 
void Container<T>::deleteLast() {
	if (size == 0) return;
	List * tmp = head;
	if (size == 1) {
		delete head;
		head = NULL;
		size = 0;
		return;
	}
	while (tmp->next->next != NULL) {
		tmp = tmp->next;
	}
	delete tmp->next->next;
	tmp->next = NULL;
	size--;
	return;
}

template<typename T>
void Container<T>::clear() {
	if (size == 0) return;
	List * tmp = head;
	while (tmp != NULL) {
		head = tmp->next;
		delete tmp->item;
		delete tmp;
		size--;
		tmp = head;
	}
	return;
}

template<typename T> 
unsigned int Container<T>::getCount() {
	return size;
}

template<typename T> 
bool Container<T>::isEmpty() {
	if (head == NULL) return true;
	return false;
}
