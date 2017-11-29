/*
	Sorted Linked List Single

	Does not accept duplicates.

	Uses non zero based index for return values.

	Copies data inserted into list, this means data in list
	is independent from scope at insertion.

	Velly Simeonov
*/

#pragma once
#ifndef SORTEDLINKEDLISTS_H
#define SORTEDLINKEDLISTS_H

#define _template template<class T>

_template
class SortedLinkedListS {
private:
	struct Node {
		T *data = nullptr;
		Node *next = nullptr;

		Node(const T *input) {
			if (input != nullptr)
				data = new T(*input); // make node data independent from source
		}
		~Node() {
			if (data != nullptr)
				delete data;
		}
	};

	int _count;
	Node *_head;

public:
	SortedLinkedListS() {
		_count = 0;
		_head = new Node(nullptr);
	}
	~SortedLinkedListS() {
		Node *tmp, *walker = _head;
		while (walker != nullptr) {
			tmp = walker;
			walker = walker->next;
			delete tmp;
		}
	}
	int insert(const T& input);
	int remove(const T& input);
	int remove (const int& index);
	int find(const T& input);
	int size() { return _count };
	T * get(const int& index);
};

_template
int SortedLinkedListS<T>::insert(const T& input) { // non 0 based index return
	Node *walker = _head;
	int i;
	for (i = 0; (i < _count)
		&& (walker->next != nullptr)
		&& (input > *walker->next->data); ++i) {

		walker = walker->next;
	}

	if ((walker->next != nullptr) && (*walker->next->data == input)) return 0;

	Node *tmp = new Node(&input);
	tmp->next = walker->next;
	walker->next = tmp;
	++_count;

	return i+1;
}

_template
int SortedLinkedListS<T>::remove(const T& input) { 
	Node *walker = _head;

	for (int i = 0; (i < _count)
		&& (walker->next != nullptr)
		&& (input > *walker->next->data); ++i) {

		walker = walker->next;
	}

	if ((walker->next != nullptr) && (*walker->next->data == input)) {
		Node *tmp = walker->next;
		walker->next = tmp->next;
		delete tmp;
		--_count;
		return 1;
	}

	return 0;
}

_template
int SortedLinkedListS<T>::remove(const int& index) {
	if ((index < 1) || (index > _count)) return 0;
	Node *walker = _head;

	for (int i = 1; i < _count; ++i) {
		walker = walker->next;
	}

	Node *tmp = walker->next;
	walker->next = tmp->next;
	delete tmp;
	--_count;
	return 1;

}

_template
int SortedLinkedListS<T>::find(const T& input) { // not 0 based index return
	Node *walker = _head;
	int i;

	for (i = 0; (i < _count)
		&& (walker->next != nullptr)
		&& (input > *walker->next->data); ++i) {

		walker = walker->next;
	}

	if ((walker->next != nullptr) && (*walker->next->data == input)) return i+1;


	return 0;
}

_template
T* SortedLinkedListS<T>::get(const int& index) { // non 0 based index
	if ((index < 1) || (index > _count)) return nullptr;
	Node *walker = _head;
	for (int i = 0; i < index; ++i) {
		walker = walker->next;
	}
	return walker->data;
}





#endif // !SLINKEDLIST_H
