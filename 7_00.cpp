#include <iostream>
#include <string>
#include <vector>

// 주의점
// 1. primary에서 name 처리하는거 언급안한 듯
// 2. Token_stream:get() 에서 '='의 case 추가 말로함

using namespace std;

void error(string s) { throw runtime_error{ s }; }

// Variable
const char name = 'a';
const char let = 'L';
const string declkey = "let";

const char number = '8';

const char quit = 'q';
const char print = ';';
const string prompt = "> ";		// 표현식 입력을 요구하는 프롬프트
const string result = "= ";		// 결과 출력을 알리는 지시자

#pragma region Variable

class Variable
{
public:
	string name;
	double value;
	Variable(string var, double val) : name{ var }, value{ val } {}
};

vector<Variable> var_table;

double get_value(string s)
{
	for (const Variable& v : var_table)
		if (v.name == s) return v.value;
	error("get: 정의되지 않은 변수 " + s);
}

void set_value(string s, double d)
{
	for (Variable& v : var_table)
	{
		if(v.name == s)
		{
			v.value = d;
			return;
		}
	}
	error("set: 정의되지 않은 변수 " + s);
}

bool is_declared(string var)
{
	for (Variable& v : var_table) {
		if (v.name == var) return true;
	}
	return false;
}

double define_name(string var, double val)
{
	if (is_declared(var)) error(var + "가 재정의됨");
	var_table.push_back(Variable(var, val));
	return val;
}

#pragma endregion 

#pragma region	Token


class Token {
public:
	char kind;
	double value;
	string name;
	Token(char ch) : kind{ch} { }
	Token(char ch, double val) : kind{ch}, value{val} { }
	Token(char ch, string n) : kind{ch}, name{n} { }

};
class Token_stream {
public:
	Token get();				// Token 가져오기
	void putback(Token t);		// Token 되돌려 놓기
	void ignore(char c);		// c를 찾을 때까지 c를 포함한 문자열 버리기
private:
	bool full{ false };
	Token buffer{ NULL };
};

Token Token_stream::get() {
	if (full) {
		full = false;
		return buffer;
	}

	char ch;
	cin >> ch;
	switch (ch) {
	case print:
	case quit:
	case '{': case '}': case '(': case ')': case '+': case '-': case '*': case '/': case '%': case '=':
		return Token{ ch };
	case '.':
	case '0': case '1': case '2': case '3': case '4':
	case '5': case '6': case '7': case '8': case '9':
	{
		cin.putback(ch);
		double val;
		cin >> val;
		return Token{ number, val };
	}
	default:
		if (isalpha(ch)) 
		{
			string s;
			s += ch;
			while (cin.get(ch) && (isalpha(ch) || isdigit(ch))) s += ch;
			cin.putback(ch);
			if (s == declkey) return Token(let);
			return Token{ name, s };
		}

		error("잘못된 토큰");
	}
}
void Token_stream::putback(Token t) {
	if (full) error("가득 찬 버퍼에 putback() 시도");
	buffer = t;
	full = true;
}
void Token_stream::ignore(char c) {
	// 우선 버퍼를 본다
	if (full & c == buffer.kind) {
		full = false;
		return;
	}

	full = false;

	// 이제 입력을 찾음
	char ch = 0;
	while (cin >> ch)
		if (ch == c) return;
}

#pragma endregion 

Token_stream ts;
double expression();

void clean_up_mess()
{
	ts.ignore(print);
}

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
	case number:
		return t.value;
	case name:
		return get_value(t.name);
	case '-' :
		return -primary();
	case '+':
		return primary();
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
			if (d == 0) error("0으로 나눔");
			left /= d;
			t = ts.get();
			break;
			}
		case '%':
			{
			double d = primary();
			if (d == 0) error("0으로 나눔");
			left = fmod(left, d);
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
double declaration()
// "let"이 이미 나왔다는 가정하
{
	Token t = ts.get();
	if (t.kind != name) error("선언에는 이름이 필요함");
	string var_name = t.name;

	Token t2 = ts.get();
	if (t2.kind != '=') error("선언에서 =가 빠짐 : " + var_name);

	double d = expression();
	define_name(var_name, d);
	return d;
}
double statement()
{
	Token t = ts.get();
	switch (t.kind)
	{
	case let:
		return declaration();
	default:
		ts.putback(t);
		return expression();
	}
}

void keep_window_open()
{
	cout << "창을 닫으려면 문자 ~를 입력하세요\n";
	for (char ch; cin >> ch;)
		if (ch == '~') return;
	return;
}

void calculate()
{
	while (cin) 
	try
	{
		cout << prompt;
		Token t = ts.get();
		while (t.kind == print) t = ts.get();	// ';' 처리
		if (t.kind == quit)	return;
		ts.putback(t);
		cout << result << statement() << endl;
	}catch(exception e)
	{
		cerr << e.what() << endl;;
		clean_up_mess();
	}
}

int main()
{
	define_name("pi", 3.1415926535);
	define_name("e", 2.7182818284);

	calculate();
	keep_window_open();
	return 0;
}