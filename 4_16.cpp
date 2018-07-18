#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
	vector<int> inputV = { 1, 2, 3, 3, 3, 4, 4, 5, 6,6,6 };

	vector<int> keyV;
	vector<int> valueV;

	// cal
	for(int val : inputV)
	{
		bool isNew = true;
		for (int i = 0; i < keyV.size(); i++)
		{
			if (keyV[i] == val)
			{
				valueV[i]++;
				isNew = false;
				break;
			}
		}
		if(isNew)
		{
			keyV.push_back(val);
			valueV.push_back(1);
		}
	}

	// result
	int max = 0;
	for(int i = 0; i < valueV.size(); i++)
	{
		if (max < valueV[i])
			max = valueV[i];
	}
	for (int i =0; i < valueV.size(); i++)
	{
		if (max == valueV[i])
			cout << keyV[i] << endl;
	}

	system("pause");

	return 0;
}