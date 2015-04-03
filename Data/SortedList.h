// SortedVector.h


#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <deque>
using namespace std;

template <typename T>
class SortedList {
	public:
		SortedList();

		int size();
		T add(T);
		void destroy(T);
		void removeDestroyed();

		T operator[](int);

	private:
		deque<T> objDeque;
		deque<T> removeDeque;
};

template <typename T>
SortedList<T> :: SortedList() {
}

template <typename T>
T SortedList<T> :: add(T obj) {

	objDeque.push_back(obj);
	return obj;
}

template <typename T>
int SortedList<T> :: size() {
	return objDeque.size();
}

template <typename T>
void SortedList<T> :: destroy(T obj) {

	removeDeque.push_back(obj);
}

template <typename T>
void SortedList<T> :: removeDestroyed() {
	T inst;

	for(int i = 0; i < removeDeque.size(); i++) {
		inst = removeDeque[i];

		for(int j = 0; j < objDeque.size(); j++)
			if(objDeque[j] == inst) {
				objDeque.erase(objDeque.begin()+j);
				break;
			}
	}

	removeDeque.clear();
}

template <typename T>
T SortedList<T> :: operator[](int offset) {
	return objDeque[offset];
}

#endif
