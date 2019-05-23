#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

void print(vector<int> v)
{
	for (int i = 0; i < v.size(); i++)
	{
		cout << v[i] << " ";
	}
	cout << endl;
}

void sort(vector<int> &nums, int low, int high)
{
	int left, right, pivot;
	if (high > low)
	{
		left = low;
		right = high;
		pivot = nums[low];

		while (right > left)
		{
			while (pivot <= nums[right] && right > left)
			{
				right--;
			}

			nums[left] = nums[right];

			while (pivot > nums[left] && right > left)
			{
				left++;
			}

			nums[right] = nums[left];
		}

		nums[left] = pivot;

		sort(nums, low, left - 1);
		sort(nums, right + 1, high);
	}
}

vector<int> sortArray(vector<int> &nums)
{
	sort(nums, 0, nums.size() - 1);
	print(nums);
	return vector<int>(nums);
}

int main()
{
	int myints[] = {7, 3, 1, 5, 6, 7};
	vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

	sortArray(fifth);

	return 0;
}
