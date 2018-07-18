#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main()
{
	int max = 1;

	cin >> max;

	for(int val = 1; val <= max; val++)
	{
		bool isPrime = true;
		for(int i = 2; i < val; i++)
		{
			if(val % i == 0)
			{
				isPrime = false;
				break;
			}
		}
		if (isPrime) cout << val << ", " << endl;
	}

	system("pause");

	return 0;
}