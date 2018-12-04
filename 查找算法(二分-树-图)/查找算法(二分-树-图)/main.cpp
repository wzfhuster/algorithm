#include<iostream>
#include"binarySearch.h"
using namespace std;


void testBinarySearch();



int main()
{
	testBinarySearch();

	cout << endl << endl << endl;
	return 0;
}


void testBinarySearch()
{
	const int n = 10;
	int a[n] = { 1,3,3,3,6,8,8,10,99,123 };
	const int n1 = 5;
	int a1[n1] = { 1,2,3,4,5 };
	int k;
	while (true)
	{
		cout << "intput the num: ";
		cin >> k;
		if (k == 0) break;
		//cout << "its index is : " << binarySearch1(a, 0, n - 1, k) << "\n\n\n";
		//cout << "its index is : " << binarySearch2(a1, n1,k) << "\n\n\n";
		//cout << "its numbers is : " << countTimes(a, n, k) << "\n\n\n";
		cout << "its index is : " << getFirstGreater(a, n, k) << "\n\n\n";
		//cout << "its index is : " << getLastLower(a, n, k) << "\n\n\n";

	}
}