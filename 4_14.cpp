#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int max = 1;

	cin >> max;

	if (max <= 1)
		return 0;

	vector<bool> primeArray;

	for (int i = 0; i <= max; i++)
		primeArray.push_back(true);

	for (int i = 2; i <= max; i++)
	{
		if(primeArray[i])
		{
			for (int j = i * i; j <= max; j += i) primeArray[j] = false;
		}
	}

	for (int i = 2; i <= max; i++)
	{
		if (primeArray[i])
			cout << i << ", ";
	}


	system("pause");

	return 0;
}