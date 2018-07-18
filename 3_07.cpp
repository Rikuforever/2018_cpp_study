#include <iostream>
#include <string>

using namespace std;

int main()
{
	string str1;
	string str2;
	string str3;
	
	string min;
	string middle;
	string max;

	cin >> str1;
	cin >> str2;
	cin >> str3;

	if(str1 < str2)
	{
		if(str2 < str3)
		{
			min = str1; middle = str2; max = str3;
		} else if (str1 < str3)
		{
			min = str1; middle = str3; max = str2;
		} else
		{
			min = str3; middle = str1; max = str2;
		}
	} else
	{
		if (str1 < str3) {
			min = str2; middle = str1; max = str3;
		}
		else if (str2 < str3) {
			min = str2; middle = str3; max = str1;
		}
		else {
			min = str3; middle = str2; max = str1;
		}
	}

	cout << min << ", " << middle << ", " << max;

	system("pause");

	return 0;
}