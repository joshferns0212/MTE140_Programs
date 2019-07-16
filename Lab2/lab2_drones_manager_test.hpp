#ifndef DRONES_MANAGER_TEST
#define DRONES_MANAGER_TEST

#include "lab2_drones_manager.hpp"

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

class DronesManagerTest {
public:
	// PURPOSE: New empty list is valid
	bool test1() {
		DronesManager manager;
		ASSERT_TRUE(manager.get_size() == 0)
		ASSERT_TRUE(manager.empty() == true)
		ASSERT_TRUE(manager.first == NULL)
		ASSERT_TRUE(manager.last == NULL)
	    return true;
	}
	
	// PURPOSE: insert_front() and insert_back() on zero-element list
	bool test2() {
		DronesManager manager1, manager2;
		manager1.insert_front(DronesManager::DroneRecord(100));
		manager2.insert_back(DronesManager::DroneRecord(100));
	    
		ASSERT_TRUE(manager1.get_size() == manager2.get_size() && manager1.get_size() == 1)
		ASSERT_TRUE(manager1.first != NULL && manager1.first == manager1.last)
		ASSERT_TRUE(manager2.first != NULL && manager2.first == manager2.last)
		ASSERT_TRUE(manager1.first->prev == NULL && manager1.last->next == NULL)
		ASSERT_TRUE(manager2.first->prev == NULL && manager2.last->next == NULL)
		ASSERT_TRUE(manager1.select(0) == manager2.select(0) && manager1.select(0) == DronesManager::DroneRecord(100))		
	    return true;
	}
	
	// TODO: Implement all of the test cases below
	
	// PURPOSE: select() and search() work properly
	bool test3() {
		DronesManager manager;
		
		ASSERT_FALSE(manager.select(5) == DronesManager::DroneRecord(0))
		ASSERT_TRUE(manager.search(DronesManager::DroneRecord(30)) == 0)

		DronesManager::DroneRecord record(100);
		manager.insert_front(record);
		
		ASSERT_TRUE(manager.select(5) == *manager.last)

		ASSERT_TRUE(manager.search(DronesManager::DroneRecord(30)) == 1)

		ASSERT_TRUE(manager.select(0) == record)
		
		ASSERT_TRUE(manager.search(DronesManager::DroneRecord(100)) == 0)

	    return true;
	}
	
	// PURPOSE: remove_front() and remove_back() on one-element list
	bool test4() {
		DronesManager manager;
		DronesManager::DroneRecord record(1);
		
		manager.insert_front(record); 
		ASSERT_TRUE(manager.remove_front()) //test 1 element
		ASSERT_FALSE(manager.remove_front()) //test empty
		
		manager.insert_front(record); //test normal remove_front
		manager.insert_front(record);
		ASSERT_TRUE(manager.remove_front())
		manager.remove_front();
		
		manager.insert_back(record);
		ASSERT_TRUE(manager.remove_back()) //test 1 element
		ASSERT_FALSE(manager.remove_back()) // test empty
		
		manager.insert_back(record); //test normal remove_back
		manager.insert_back(record);
		ASSERT_TRUE(manager.remove_back())
		manager.remove_back();
	    return true;
	}
	
	// PURPOSE: replace() and reverse_list() work properly
	bool test5() {
		DronesManager manager;
		DronesManager::DroneRecord record(5), record2(10);
		ASSERT_FALSE(manager.replace(0, record)) //test replace empty
		ASSERT_FALSE(manager.reverse_list()) //test reverse empty
		manager.insert_front(record);
		
		ASSERT_FALSE(manager.replace(7, record)) //test invalid index
		ASSERT_TRUE(manager.replace(0, record2)) //test normal index
		ASSERT_TRUE(manager.first->droneID == 10) //test correctly replaced
		ASSERT_TRUE(manager.reverse_list()) //test reverse size 1
	
		manager.insert_front(record);
		ASSERT_TRUE(manager.reverse_list()) //test normal reverse list
		ASSERT_TRUE(manager.first->droneID == 10)
	    return false;
	}
	
	// PURPOSE: insert_front() keeps moving elements forward
	bool test6() {
		DronesManager manager;
		
		for (int i = 0; i < 5; i++) {
			ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)) && manager.first->droneID == i)
		}
	    return true;
	}
	
	// PURPOSE: inserting at different positions in the list
	bool test7() {
		DronesManager manager;
		
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(3), 4))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(3), 0))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(2), 0) && manager.first->droneID == 2)
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(1), 1) && manager.first->droneID == 2 && manager.first->next->droneID == 1)

	    return true;
	}
	
	// PURPOSE: try to remove too many elements, then add a few elements
	bool test8() {
		DronesManager manager;
		
		for (int i = 0; i < 5; i++) {
			ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
		}
		for (int i = 0; i < 5; i++) {
			ASSERT_TRUE(manager.remove_front())
		}
		ASSERT_FALSE(manager.remove_front())
		for (int i = 0; i < 5; i++) {
			ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
		}
	    return true;
	}
	
	// PURPOSE: lots of inserts and deletes, some of them invalid
	bool test9() {
		DronesManager manager;
		
		ASSERT_FALSE(manager.insert(DronesManager::DroneRecord(9), 89))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(1), 0))
		ASSERT_FALSE(manager.remove(6))
		ASSERT_TRUE(manager.remove(0))
		ASSERT_FALSE(manager.remove(0))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(3), 0))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(1), 0))
		ASSERT_TRUE(manager.insert(DronesManager::DroneRecord(2), 1) && manager.first->droneID == 1 && manager.first->next->droneID == 2)
		
	}    
	    	
	// PURPOSE: lots of inserts, reverse the list, and then lots of removes until empty
	bool test10() {
		DronesManager manager;
		
		for (int i = 0; i < 5; i++) {
			ASSERT_TRUE(manager.insert_front(DronesManager::DroneRecord(i)))
		}
		
		ASSERT_TRUE(manager.reverse_list())
		
		while (manager.get_size()) {
			ASSERT_TRUE(manager.remove_front())
		}
	   return false;
	} 
};

#endif
