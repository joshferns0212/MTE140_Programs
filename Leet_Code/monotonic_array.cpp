#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

bool isMonotonic(vector<int> &A)
{
	int flag = 0;
	for (int i = 0; i < A.size() - 1; i++)
	{
		if (flag == 0)
		{
			if (A[i] < A[i + 1])
				flag = 1;
			else if (A[i] > A[i + 1])
				flag = -1;
		}
		else if (flag == 1)
		{
			if (!(A[i] <= A[i + 1]))
				return false;
		}
		else if (flag == -1)
		{
			if (!(A[i] >= A[i + 1]))
				return false;
		}
	}

	return true;
}
int main()
{
	int myints[] = {1, 2, 3, 4, 5, 6, 7};
	vector<int> myVector(myints, myints + sizeof(myints) / sizeof(int));

	cout << isMonotonic(myVector) << endl;

	return 0;
}
