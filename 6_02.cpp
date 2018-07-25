#include <iostream>
#include <string>
#include <vector>

using namespace std;

void error(string s) { throw runtime_error{ s }; }

class Token
{
public:
	char kind;
	double value;
};
class Token_stream
{
public:
	Token get();
	void putback(Token t);
private:
	bool full{ false };
	Token buffer;
};

Token Token_stream::get()
{
	if(full)
	{
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;
	switch (ch)
	{
	case ';':	// print
	case 'q':	// quit
	case '{': case '}': case '(': case ')': case '+': case '-': case '*': case '/':
		return Token{ ch };
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
		{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token{ '8', val };
		}
	default:
		error("잘못된 토큰");
	}
}
void Token_stream::putback(Token t)
{
	if (full) error("가득 찬 버퍼에 putback() 시도");
	buffer = t;
	full = true;
}

Token_stream ts;
double expression();

double primary()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case '(':
		{
		double d = expression();
		t = ts.get();
		if (t.kind != ')') error("')'가 나와야 함");
		return d;
;		}
	case '{':
		{
		double d = expression();
		t = ts.get();
		if (t.kind != '}') error("'}'가 나와야 함");
		return d;
		}
	case '8':
		return t.value;
	default :
		error("primary가 나와야 함");
	}
}
double term()
{
	double left = primary();
	Token t = ts.get();
	while(true)
	{
		switch (t.kind)
		{
		case '*':
			left *= primary();
			t = ts.get();
			break;
		case '/':
			{
			double d = primary();
			if (d == 0) error("영으로 나누기");
			left /= d;
			t = ts.get();
			break;
			}
		default:
			ts.putback(t);
			return left;
		}
	}
}
double expression()
{
	double left = term();
	Token t = ts.get();
	while(true)
	{
		switch(t.kind)
		{
		case '+':
			left += term();
			t = ts.get();
			break;
		case '-':
			left -= term();
			t = ts.get();
			break;
		default:
			ts.putback(t);
			return left;
		}
	}
}

int main() {
	
	cout << expression() << endl;

	system("pause");

	return 0;
}