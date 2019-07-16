#include "lab3_priority_queue.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

// PURPOSE: Parametric constructor
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
	heap = new TaskItem*[n_capacity + 1];
	capacity = n_capacity;
	size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
	for (int i = 1; i < get_size(); i++) {
		delete heap[i];
	}
	delete[] heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
	return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
	return (!size);
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
	return (size == capacity);
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
	cout << "List of Tasks" << endl;
	if (empty()) {
		cout << "Empty" << endl;
	} else {
		for (int i = 1; i < size + 1; i ++) { //TODO: check if this needs to be dereferenced
			cout << (*(heap + i * sizeof(PriorityQueue::TaskItem*)))->priority << ": " << (*(heap + i * sizeof(PriorityQueue::TaskItem*)))->description << endl;
		}
	}
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
	return (empty() ? PriorityQueue::TaskItem(-1, "N/A") : *heap[1]);
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue(TaskItem val) {
	if (full())
		return false;

	heap[get_size() + 1] = new PriorityQueue::TaskItem(val);

	int child_index = get_size() + 1, parent_index = child_index / 2;

	while (parent_index >= 1 && (heap[parent_index]->priority < heap[child_index]->priority)) {
		PriorityQueue::TaskItem* temp = heap[parent_index];
		heap[parent_index] = heap[child_index];
		heap[child_index] = temp;
		child_index = parent_index;
		parent_index /= 2;
	}
	size++;
	return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
	if (empty())
		return false;

	PriorityQueue::TaskItem* temp = heap[1];
	heap[1] = heap[get_size()];
	delete temp;
	heap [get_size()] = NULL;
	size--;

	int index = 1;

	while (index * 2 < get_size()) {
		if (heap[index * 2] && heap[index]->priority < heap[index * 2]->priority) {
			temp = heap[index];
			heap[index] = heap[index * 2];
			heap[index * 2] = temp;
			index *= 2;
		} else if (heap[index * 2 + 1] && heap[index]->priority < heap[index * 2 + 1]->priority) {
			temp = heap[index];
			heap[index] = heap[index * 2 + 1];
			heap[index * 2 + 1]  = temp;
			index = index * 2 + 1;
		}
	}

	return true;
}
