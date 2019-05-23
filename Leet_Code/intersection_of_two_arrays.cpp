#include <iostream>
#include <cstdlib>
#include <vector>

using namespace std;

vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
{
	vector<int> output;
	bool inOutput = false;

	for (int i : nums1)
	{
		if (!output.empty())
		{
			for (int j : output)
			{
				if (i == j)
				{
					inOutput = true;
					break;
				}
			}
		}

		if (!inOutput)
		{
			for (int k : nums2)
			{
				if (i == k)
				{
					output.push_back(k);
					break;
				}
			}
		}
		inOutput = false;
	}

	return output;
}
