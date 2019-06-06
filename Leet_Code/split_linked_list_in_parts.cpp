#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
#include <iomanip>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void print(vector<ListNode*> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i]->val << " ";
	}
	cout << endl;
}

vector<ListNode*> splitListToParts(ListNode *root, int k)
{
	vector<ListNode *> output;
	ListNode *curr = root;
	ListNode *temp;
	ListNode *start;
	int numOfNodes = 0, sizeOfGroup, modulus, counter = 0;

	while (curr)
	{
		numOfNodes++;
		curr = curr->next;
	}

	int sizes[k] = { };

	sizeOfGroup = numOfNodes / k;

	for (int i = 0; i < k; i++)
		sizes[i] = sizeOfGroup;

	modulus = numOfNodes % k;

	for (int i = 0; i < modulus; i++)
		sizes[i]++;

	curr = root;

	for (int i = 0; i < k; i++)
	{
		output.push_back(curr);
		for (int j = 0; j < sizes[i] - 1; j++)
		{
			curr = curr->next;
		}
		temp = curr->next;
		curr->next = NULL;
		curr = temp;
		if (!curr)
			break;
	}

	if (output.size() < k)
	{
		for (int i = output.size(); i < k; i++)
		{
			ListNode *blankNode;
			output.push_back(blankNode);
		}
	}

	return output;
}

int main()
{
	ListNode* first = new ListNode(1);
	first->next = new ListNode(2);
	first->next->next = new ListNode(3);
	first->next->next->next = new ListNode(4);
	print(splitListToParts(first,2));
	return 0;
}
