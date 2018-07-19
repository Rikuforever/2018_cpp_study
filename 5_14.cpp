#include <iostream>
#include <string>
#include <vector>

using namespace std;


int main() {
	vector<int> days(7);
	int errors = 0;

	string day;
	int num;
	for(;cin >> day >> num;)
	{
		int dayIndex = -1;
		if (day == "Monday" || day == "Mon" || day == "monday" || day == "mon")
			dayIndex = 0;
		else if (day == "Tuesday" || day == "Tue" || day == "tuesday" || day == "tue")
			dayIndex = 1;
		else if (day == "Wednesday" || day == "Wed" || day == "wednesday" || day == "wed")
			dayIndex = 2;
		else if (day == "Thursday" || day == "Thu" || day == "thusday" || day == "thu")
			dayIndex = 3;
		else if (day == "Friday" || day == "Fri" || day == "friday" || day == "fri")
			dayIndex = 4;
		else if (day == "Saturday" || day == "Sat" || day == "saturday" || day == "sat")
			dayIndex = 5;
		else if (day == "Sunday" || day == "Sun" || day == "sunday" || day == "sun")
			dayIndex = 6;

		if (dayIndex != -1)
			days[dayIndex] += num;
		else
			errors += 1;
	}

	cout << "Monday : " << days[0] << endl;
	cout << "Tuesday : " << days[1] << endl;
	cout << "Wednesday : " << days[2] << endl;
	cout << "Thursday : " << days[3] << endl;
	cout << "Friday : " << days[4] << endl;
	cout << "Saturday : " << days[5] << endl;
	cout << "Sunday : " << days[6] << endl;

	cout << "Error Count : " << errors << endl;

	system("pause");

	return 0;
}