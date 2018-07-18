#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

vector<string> names;
vector<int> scores;

int GetScore(string name)
{
	int result = -1;
	for(int i = 0; i < names.size(); i++)
	{
		if(names[i] == name)
		{
			result = scores[i];
			break;
		}
	}

	return result;
}
vector<string>* GetNames(int score)
{
	vector<string>* result = new vector<string>();
	for(int i = 0; i < scores.size(); i++)
	{
		if(scores[i] == score)
		{
			result->push_back(names[i]);
		}
	}
	return result;
}

int main() {

	// writing phase
	while(true)
	{
		string name = "";
		int score;
		
		cin >> name >> score;
		
		// exit
		if (name.empty() || name == "exit")
			break;

		// check duplicate name
		if(GetScore(name) != -1)
		{
			cout << "Error : Duplicate Name!" << endl;
			return 0;
		}

		// add data
		names.push_back(name);
		scores.push_back(score);
	}

	// print phase 1
	for(int i = 0; i < names.size(); i++)
	{
		cout << names[i] << " " << scores[i] << endl;
	}
	cout << endl;

	// print phase 2
	string name;
	cout << "Input Name : ";
	cin >> name;
	int score = GetScore(name);
	if(score != -1)
	{
		cout << name << "'s Score : " << score << endl << endl;
	} else
	{
		cout << "No corresponding score!" << endl << endl;
	}

	// print phase 3
	cout << "Input Score : ";
	cin >> score;
	vector<string>* result = GetNames(score);

	if(result->empty())
	{
		cout << "No corresponding name!" << endl;
	} else
	{
		for (int i = 0; i < result->size(); i++) {
			cout << (*result)[i] << endl;
		}
	}

	system("pause");

	return 0;
}