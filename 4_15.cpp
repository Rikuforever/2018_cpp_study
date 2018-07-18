#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	int num = 0;
	int idx = 0;
	int prime = 1;
	cin >> num;

	while(idx < num)
	{
		for (int val = ++prime; true; val++) {
			bool isPrime = true;
			for (int i = 2; i < val; i++) {
				if (val % i == 0) {
					isPrime = false;
					break;
				}
			}
			if (isPrime)
			{
				prime = val;
				cout << ++idx << "th : " << prime << endl;
				break;
			}
		}
	}

	system("pause");

	return 0;
}