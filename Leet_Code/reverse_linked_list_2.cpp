#include <iostream>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <vector>

using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

void print(ListNode *node)
{
	while (node)
	{
		cout << node->val << " ";
		node = node->next;
	}
	cout << endl;
}

ListNode *reverseBetween(ListNode *head, int m, int n)
{
	if (!head->next || n == m)
		return head;

	ListNode *prev = NULL;
	ListNode *curr = head;
	ListNode *next = head->next;
	ListNode *temp = NULL;
	ListNode *temp2 = NULL;

	for (int i = 0; i < m - 1; i++)
	{
		prev = curr;
		curr = curr->next;
		next = curr->next;
	}

	temp = curr;
	temp2 = prev;

	for (int i = 0; i < n - m; i++)
	{
		prev = curr;
		curr = next;
		next = curr->next;
		curr->next = prev;
	}
	temp->next = next;
	if (temp2)
	{
		temp2->next = curr;
	}
	else
	{
		head = curr;
	}

	return head;
}

int main()
{
	ListNode *first = new ListNode(3);
	first->next = new ListNode(5);
	// first->next->next = new ListNode(3);
	// first->next->next->next = new ListNode(4);
	// first->next->next->next->next = new ListNode(5);
	print(reverseBetween(first, 1, 2));

	system("PAUSE");
	return EXIT_SUCCESS;
}
