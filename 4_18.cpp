#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main() {
	double a = 1;
	double b = 1;
	double c = 1;

	cout << "Input A : ";
	cin >> a;
	cout << "Input B : ";
	cin >> b;
	cout << "Input C : ";
	cin >> c;

	double temp = sqrt(b * b - 4 * a * c);
	double x1 = (-b + temp) / (2 * a);
	double x2 = (-b - temp) / (2 * a);

	cout << "X1 : " << x1 << endl;
	cout << "X2 : " << x2 << endl;

	system("pause");

	return 0;
}