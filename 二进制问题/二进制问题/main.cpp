#include<iostream>
#include<vector>
#include<string>

using namespace std;

void printK(unsigned num,unsigned base);	//打印一个十进制数的 k 进制
void testPrintK();
void testBinaryReverse();	//二进制反序问题
void testBinaryOneNums();	//一个十进制数中二进制形式的 1 的个数

//一个数组中除了一个数之外，其它数都有两个，找出单独的那个数
int getOne(vector<int> vec);
//一个数组中有两个数是单独的，其它的都有两个，找出那两个数
void getTwo(vector<int> vec, int *a, int *b);
//一个数组中有一个数除外，其它数都有三个，找出那一个数
int getOneThree(vector<int> vec, int &a);
void testGetTwo();
void testOneThree();


int main()
{
	//testPrintK();
	//testBinaryReverse();
	//testBinaryOneNums();
	//testGetTwo();
	testOneThree();

	return 0;
}





//打印一个十进制数的 k 进制
void printK(unsigned num, unsigned base)
{
	if (num != 0)
	{
		printK(num / base, base);
		cout << num%base;
	}
}
void testPrintK()
{
	int num, base;
	while (true)
	{
		cout << "input the num: ";
		cin >> num;
		if (num == 0)
			break;
		cout << "input the base: ";
		cin >> base;
		cout << "output: ";
		printK(num, base);
		cout << "\n\n\n\n";
	}
}



//二进制反序问题
void testBinaryReverse()
{
	int num,tmp,res;
	while (true)
	{
		cout << "input the num: ";
		cin >> num;
		if (num == 0)
			break;
		cout << "Its binary is: ";
		printK(num, 2);
		cout << "\n\nIts reverse is: ";
		res = 0;
		while (num)
		{
			tmp = num & 1;
			res = (res << 1) + tmp;
			num >>= 1;
		}
		cout << res;
		cout << "\nIts binary reverse is: ";
		printK(res, 2);
		cout << "\n\n\n\n";
	}
}




//一个十进制数中二进制形式的 1 的个数
void testBinaryOneNums()
{
	int num, tmp, times;
	while (true)
	{
		cout << "input the num: ";
		cin >> num;
		if (num == 0)
			break;
		cout << "Its binary is: ";
		printK(num, 2);
		times = 0;
		//while (num)     //这种方法需要每一位的去判断
		//{
		//	if (num & 1)
		//		++times;
		//	num >>= 1;
		//}
/////////////////////////////////////////////////////////////////////////////////////////////
		while (num)		
		{
			++times;
			num &= (num - 1);      //这种方法更快，有多少个1，它就遍历多少次
		}
///////////////////////////////////////////////////////////////////////////////////////////////
		cout << "\nIts numbers of one in binary is: " << times;
		cout << "\n\n\n\n";
	}
}





//一个数组中除了一个数之外，其它数都有两个，找出单独的那个数
int getOne(vector<int> vec)
{
	int a = vec[0];
	int n = vec.size();
	for (int i = 1; i < n; i++)
		a ^= vec[i];
	return a;
}
//一个数组中有两个数是单独的，其它的都有两个，找出那两个数
void getTwo(vector<int> vec, int *a, int *b)
{
	int res = vec[0];
	int n = vec.size(), i, tmp;
	for (i = 1; i < n; i++)
		res ^= vec[i];
	vector<int> v1, v2;
	tmp = 1;
	while (!(res&tmp))
		tmp<<=1;
	cout << "\ntmp的二进制为：";
	printK(tmp, 2);
	for (auto &c : vec)
		if (c&tmp)
			v1.push_back(c);
		else
			v2.push_back(c);
	cout << "\nv1为：";
	for (i = 0; i < v1.size(); i++)
	{
		printK(v1[i], 2);
		cout << "[" << v1[i] << "]   ";

	}
	cout << "\nv2为：";
	for (i = 0; i < v2.size(); i++)
	{
		printK(v2[i], 2);
		cout << "["<<v2[i]<<"]   ";
	}
	cout << endl << endl << endl;

	res = v1[0];
	for (i = 1; i < v1.size(); i++)
		res ^= v1[i];
	*a = res;
	res = v2[0];
	for (i = 1; i < v2.size(); i++)
		res ^= v2[i];
	*b = res;
}
void testGetTwo()
{
	int n,i,tmp;
	int a, b;
	while (true)
	{
		cout << "请输入数组的大小: ";
		cin >> n;
		if (n == 0)
			break;
		vector<int> vec(n);
		cout << "输入一个只有两个数是单独的数组: \n";
		for (i = 0; i < n; i++)
			cin >> vec[i];
		getTwo(vec, &a, &b);
		cout << "结果是：" << a << "   " << b << endl;
		cout << "\n\n\n";
	}
}

//一个数组中有一个数除外，其它数都有三个，找出那一个数
int getOneThree(vector<int> vec, int &a)
{
	int i,n = 8 * sizeof(int);
	vector<int> arr(n, 0);
	for (auto tmp : vec)
	{
		i = 0;
		while (tmp)
		{
			arr[i++] += (tmp & 1);
			tmp >>= 1;
		}
	}
	i = n - 1;
	while (arr[i] == 0) --i;
	for (; i >= 0; i--)
		arr[i] %= 3;
	i = n - 1; a = 0;
	while (arr[i] == 0) --i;
	for (; i >= 0; i--)
		a = (a << 1) + arr[i];
	return a;
}
void testOneThree()
{
	int n, i;
	int a;
	while (true)
	{
		cout << "请输入数组的大小: ";
		cin >> n;
		if (n == 0)
			break;
		vector<int> vec(n);
		cout << "输入一个除了一个数其它是三个数的数组: \n";
		for (i = 0; i < n; i++)
			cin >> vec[i];
		getOneThree(vec, a);
		cout << "结果是："<<a<<"\n\n\n";
	}
}