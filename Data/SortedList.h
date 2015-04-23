// SortedVector.h
// Ryan McGrail


#ifndef SORTEDLIST_H
#define SORTEDLIST_H

#include <deque>
using namespace std;

template <typename T>
class SortedList {
	public:
		SortedList();				// Constructor

		int size();					// Get Size of SortedList
		T add(T);					// Add Element to Vector
		void destroy(T);			// Destroy Given Element
		void removeDestroyed();		// Clean SortedList, Remove Destroyed Elements

		T operator[](int);			// Random Access w/ [] Operator

	private:
		deque<T> objDeque;			// Deque of Objects
		deque<T> removeDeque;		// Deque of Objects to be Removed
};


// MEMBER FUNCTIONS
///////////////////////////////////////////////////////////////////

// Default Constructor
template <typename T>
SortedList<T> :: SortedList() {
}

// Add Object to SortedList
template <typename T>
T SortedList<T> :: add(T obj) {

	objDeque.push_back(obj);
	return obj;
}

// Get Sorted List's Size
template <typename T>
int SortedList<T> :: size() {
	return objDeque.size();
}

// Destroy Element in SortedList
template <typename T>
void SortedList<T> :: destroy(T obj) {

	// Add to "To be Removed" Deque
	removeDeque.push_back(obj);
}

// Removing Destroyed Elements in List
template <typename T>
void SortedList<T> :: removeDestroyed() {
	T inst;

	// Loop through Remove Deque
	for(int i = 0; i < removeDeque.size(); i++) {
		inst = removeDeque[i];

		// Find Element to be Removed, Remove It
		for(int j = 0; j < objDeque.size(); j++)
			if(objDeque[j] == inst) {
				objDeque.erase(objDeque.begin()+j);
				break;
			}
	}

	// Clear Remove Deque
	removeDeque.clear();
}

// Operator[] for Sorted List
template <typename T>
T SortedList<T> :: operator[](int offset) {
	return objDeque[offset];
}

#endif
