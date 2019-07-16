#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	delete_BST(root);
}

void BinarySearchTree::delete_BST(TaskItem* curr) {
	if (!curr)
		return;
	delete_BST(curr->left);
	delete_BST(curr->right);
	delete curr;
}


// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (!get_size())
		return BinarySearchTree::TaskItem(-1, "N/A");

	BinarySearchTree::TaskItem* curr = root;

	while (curr->right) {
		curr = curr->right;
	}

	return BinarySearchTree::TaskItem(*curr);
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (!get_size())
		return BinarySearchTree::TaskItem(-1, "N/A");

	BinarySearchTree::TaskItem* curr = root;

	while (curr->left) {
		curr = curr->left;
	}

	return BinarySearchTree::TaskItem(*curr);
}

unsigned int BinarySearchTree::max_height(TaskItem* curr) const{
	if (!curr)
		return 0;

	int left_height = max_height(curr->left);
	int right_height = max_height(curr->right);

	return (1 + ((left_height > right_height) ? left_height : right_height));
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	if (!get_size())
		return 0;
	TaskItem* temp = root;
	unsigned int height = max_height(temp);
	return (height - 1);
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	cout << "Tree: ";
	traverse_BST(root);
	cout << endl;
}

void BinarySearchTree::traverse_BST(BinarySearchTree::TaskItem* curr) const{
	if (!curr)
		return;
	cout << curr->description << "\n";
	traverse_BST(curr->left);
	traverse_BST(curr->right);
}

// PURPOSE: Returns true if a node with the value val exists in the tree
// otherwise, returns false
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val) const {
	return search_BST(val, root);
}

bool BinarySearchTree::search_BST(BinarySearchTree::TaskItem val, BinarySearchTree::TaskItem* curr) const{
	if (!curr)
		return false;

	while (curr->priority != val.priority) {
		if (val.priority < curr->priority) {
			curr = curr->left;
		} else if (val.priority > curr->priority) {
			curr = curr->right;
		}
		if (!curr) {
			return false;
		}
	}
	return (*curr == val);
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
	return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
	return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert(BinarySearchTree::TaskItem val) {
	if (!get_size()) {
		root = new BinarySearchTree::TaskItem(val);
		size++;
		return true;
	}
	BinarySearchTree::TaskItem* curr = root;

	while (curr->left || curr->right) {
		if (val.priority < curr->priority) {
			if (!curr->left)
				break;
			curr = curr->left;
		} else if (val.priority > curr->priority) {
			if (!curr->right)
				break;
			curr = curr->right;
		} else {
			return false;
		}
	}

	if (val.priority < curr->priority) {
		curr->left = new BinarySearchTree::TaskItem(val);
	} else if (val.priority > curr->priority) {
		curr->right = new BinarySearchTree::TaskItem(val);
	}
	size++;
	return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	if (!exists(val))
		return false;

	BinarySearchTree::TaskItem* curr = root;
	BinarySearchTree::TaskItem* prev = NULL;
	int direction = 0;

	while (!(*curr == val)) {
		prev = curr;
		if (val.priority < curr->priority) {
			curr = curr->left;
			direction = -1;
		} else if (val.priority > curr->priority) {
			curr = curr->right;
			direction = 1;
		}
	}

	if (curr->right && curr->left) {
		BinarySearchTree::TaskItem* temp = curr;

		prev = curr;
		curr = curr->right;

		while (curr->left) {
			prev = curr;
			curr = curr->left;
		}

		temp->priority = curr->priority;
		temp->description = curr->description;

		if (temp == prev)
			prev->right = curr->right;
		else
			prev->left = curr->right;
	} else {
		if (direction == 1) {
			if (curr->right) {
				prev->right = curr->right;
			} else if (curr->left){
				prev->right = curr->left;
			} else {
				prev->right = NULL;
			}
		} else if (direction == -1) {
			if (curr->right) {
				prev->left = curr->right;
			} else if (curr->left){
				prev->left = curr->left;
			} else {
				prev->left = NULL;
			}
		} else if (direction == 0) {
			if (curr->right) {
				root = curr->right;
			} else if (curr->left){
				root= curr->left;
			} else {
				root = NULL;
			}
		}
	}

	delete curr;
	size--;
	return true;
}
