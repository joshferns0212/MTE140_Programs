#include <iostream>
#include <string>

#include "lab2_drones_manager_test.hpp"
#include "lab2_drones_manager.hpp"

using namespace std;

DronesManager::DronesManager() : first(NULL), last(NULL), size(0) {
}

DronesManager::~DronesManager() {
	DroneRecord* curr = first;
	DroneRecord* temp;
	while(curr)
	{
		temp = curr->next;
		delete curr;
		curr = temp;
	}
}

bool operator==(const DronesManager::DroneRecord& lhs, const DronesManager::DroneRecord& rhs) {
	return (lhs.droneID == rhs.droneID && lhs.range == rhs.range
          && lhs.yearBought == rhs.yearBought && lhs.droneType == rhs.droneType
          && lhs.manufacturer == rhs.manufacturer && lhs.description == rhs.description
          && lhs.batteryType == rhs.batteryType);
}

unsigned int DronesManager::get_size() const {
	return size;
}

bool DronesManager::empty() const {
  return (!size);
}

DronesManager::DroneRecord DronesManager::select(unsigned int index) const {
  if (empty())
    return DroneRecord(0);

  DroneRecord* output = first;

  for(int i = 0; i < index; ++i) {
    output = first->next;
    if(index == i)
    	return *last;
  }

  return *output;
}

unsigned int DronesManager::search(DroneRecord value) const {
	if (empty())
      return 0;
  	for(int i = 0; i < get_size(); ++i) {
      if(value == DroneRecord(i))
        return i;
    }
  return get_size();
}

void DronesManager::print() const {
  	if (empty()) {
    	cout << "Empty DronesManager";
      	return;
    }

	DroneRecord* curr = first;

  	cout << "droneID\trange\tyearBought\tdroneType\tmanufacturer\tdescription\tbatteryType\n\n";

  	while (curr)
  	{
    	cout << curr->droneID << "\t" << curr->range << "\t" << curr->yearBought << "\t" << curr->droneType << "\t" << curr->manufacturer << "\t" << curr->description << "\t" << curr->batteryType << "\n";
    	curr = curr->next;
  	}
}

bool DronesManager::insert(DroneRecord value, unsigned int index) {
  	DroneRecord* curr = first;
  	if(index >= get_size())
      return false;
  	for(int i = 0; i < index; ++i) {
		curr = curr->next;
    }
	DroneRecord* temp = new DroneRecord(value);
  	DroneRecord* prev = curr->prev;

  	prev->next = temp;
    curr->prev = temp;
  	temp->prev = prev;
  	temp->next = curr;

	return true;
}

bool DronesManager::insert_front(DroneRecord value) {
	if (empty()) {
    	first = last = new DroneRecord(value);
      	return true;
    }
  	DroneRecord* temp = first;
  	first->prev = new DroneRecord(value);
  	first = first->prev;
  	first->next = temp;
  	first->prev = NULL;
  	return true;
}

bool DronesManager::insert_back(DroneRecord value) {
	if (empty()) {
    	first = last = new DroneRecord(value);
      	return true;
    }
  	DroneRecord* temp = last;
  	last->next = new DroneRecord(value);
  	last = last->next;
  	last->prev = temp;
  	last->next = NULL;
  	return true;
}

bool DronesManager::remove(unsigned int index) {
  DroneRecord* curr = first;
  	if(empty())
		return false;
  	for(int i = 0; i < index; ++i){
      curr = curr->next;
    }
  	curr->prev->next = curr->next;
    curr->next->prev = curr->prev;
  	delete curr;
  return true;
}

bool DronesManager::remove_front() {
  	if(empty())
      return false;
  	if(get_size() == 1) {
      delete first;
      first = last = NULL;
      return true;
    }

  	DroneRecord* new_first = first->next;
  	delete first;
  	first = new_first;
  	first->prev = NULL;

	return true;
}

bool DronesManager::remove_back() {
	if(empty())
      return false;
  	if(get_size() == 1) {
      delete last;
      first = last = NULL;
      return true;
    }

  	DroneRecord* new_last = last->prev;
  	delete last;
  	last = new_last;
  	last->next = NULL;

	return true;
}

bool DronesManager::replace(unsigned int index, DroneRecord value) {
  	DroneRecord* curr = first;
  	if(empty())
      return false;
  	else if(index >= size)
      return false;
  	for(int i = 0; i < index; ++i){
      curr = curr->next;
    }
  	*curr = value;
	return true;
}

bool DronesManager::reverse_list() {
	if (empty())
    	return false;
  	if (get_size() == 1)
      	return true;

  	DroneRecord* prev = NULL;
  	DroneRecord* curr = first;
  	DroneRecord* next = NULL;
  	DroneRecord* old_first = first;

  	while (curr) {
		next = curr->next;
		curr->next = prev;
      	curr->prev = next;

		prev = curr;
		curr = next;
    }
    first = prev;
  	// first->prev = NULL;
  	last = first;
  	// last->next = NULL;
  	return true;
}

string get_status_str(bool status) {
    return status ? "TEST PASSED" : "TEST FAILED";
}

int main() {
    DronesManagerTest drones_manager_test;


	string test_descriptions[10] = {
      "Test1: new empty list is valid",
      "Test2: insert_front() and insert_back() on zero-element list",
      "Test3: select() and search() work properly",
	  "Test4: remove_front() and remove_back() on one-element list",
      "Test5: replace() and reverse_list() work properly",
      "Test6: insert_front() keeps moving elements forward",
      "Test7: inserting at different positions in the list",
      "Test8: try to remove too many elements, then add a few elements",
      "Test9: lots of inserts and deletes, some of them invalid",
      "Test10: lots of inserts, reverse the list, and then lots of removes until empty"
	};

	bool test_results[10];
    test_results[0] = drones_manager_test.test1();
    test_results[1] = drones_manager_test.test2();
    test_results[2] = drones_manager_test.test3();
    test_results[3] = drones_manager_test.test4();
    test_results[4] = drones_manager_test.test5();
    test_results[5] = drones_manager_test.test6();
    test_results[6] = drones_manager_test.test7();
    test_results[7] = drones_manager_test.test8();
    test_results[8] = drones_manager_test.test9();
    test_results[9] = drones_manager_test.test10();

	cout << "DRONES MANAGER TEST RESULTS \n";
	cout << "*************************** \n";
	for (int index = 9; index < 10; ++index) {
    	cout << test_descriptions[index] << endl << get_status_str(test_results[index]) << endl;
	}
    system("pause");
    return 0;
}
