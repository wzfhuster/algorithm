#include<iostream>
#include"c_function.h"

using namespace std;

int main()
{
	//char a[10] = "hetyoabc";
	//char b[10] = "goodhei";
	//cout << (char*)myMemcpy2(a+2, a, 4);
	//cout << endl << a << endl;

	//cout << memcmp("hello", "hello",13) << endl;
	//cout << memcmp("hell", "hello",14) << endl;
	//cout << memcmp("hello", "hell",15) << endl;
	//cout << memcmp("ajfoie", "ljgroife",12) << endl;
	//cout << memcmp("ajfoiefjoe", "afeo",11) << endl;

	char a[20] = "hello  ";
	char b[20] = "shit";
	cout << strcat(a, b);

	cout << endl << endl << endl;
	return 0;
}