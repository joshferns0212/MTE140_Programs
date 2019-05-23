#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void print(vector<int> v)
{
	for (int i : v)
		cout << i << " ";

	cout << endl;
}

void rotate(vector<int> &nums, int k)
{
	int temp;

	for (int i = 0; i < k; i++)
	{
		temp = nums[nums.size() - 1];

		nums.assign(nums.begin(), nums.end() - 1);

		nums.emplace(nums.begin(), temp);

		print(nums);
	}
}

int main()
{
	int myints[] = {1, 2, 3};
	vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	rotate(fifth, 3);

	return 0;
}
