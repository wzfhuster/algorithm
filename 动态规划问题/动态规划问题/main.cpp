#include<iostream>
#include<string>
#include<vector>
#include<iomanip>
using namespace std;

//����������� ( �ݹ�ͷǵݹ� ��
int longestSonStr(string str1, string str2,int n1,int n2);
void longestSonStr2(string str1, string str2);
void testLongestSonStr()
{
	while (true)
	{
		string str1, str2;
		cout << "input str1: ";
		cin >> str1;
		if (str1 == "0")
			break;
		cout << "input str2: ";
		cin >> str2;
		longestSonStr2(str1, str2);
		cout << "\n\n\n\n";
	}
}


//��������
void backpack(vector<int> &w, vector<int> &v,int n,int m);
void testBackpack()
{
	int n = 6;
	vector<int> w = {4,6,2,2,5,1};
	vector<int> v = {8,10,6,3,7,2};
	backpack(w, v, n, 12);
}



//ǰk���Ϊnum, ע������Ҫ����Ǳ����� k ������ӵĺ�Ϊnum����͹غ��� d[i][j] �Ƿ���Ե��� d[i-1][j] �ˣ�
void kNum(vector<int> &vec, int sum);
void testKNum()
{
	vector<int> kn = { 5, 6, 3, 2,9,13,21 };
	int sum = 25;
	kNum(kn, sum);
}



//�������С·���ͣ������Ͻǵ����½ǣ�ֻ�����Һ����£������·��
//˼�룺�����½ǵ��ŷ�����������ߺ��ұߵ���С���Ǹ���Сѡ�ĸ�. . . . . . 
int min(int a, int b)
{
	return a > b ? b : a;
}


void printPath(vector<vector<int>> &matrix, vector<vector<int>> &vec, int i, int j)
{
	if (i == 0 && j == 0)
		cout << matrix[i][j];
	else
	{
		if (i == 0)
			printPath(matrix, vec, i, j - 1);
		else if (j == 0)
			printPath(matrix, vec, i - 1, j);
		else if (vec[i][j - 1] < vec[i - 1][j])
			printPath(matrix, vec, i, j - 1);
		else
			printPath(matrix, vec, i - 1, j);
		cout << "----->" << matrix[i][j];
	}
}
int matrixMinPath(vector<vector<int>> &matrix)
{
	int i, j, m = matrix.size(), n = matrix[0].size();
	vector<vector<int>> vec(m, vector<int>(n));
	vec[0][0] = matrix[0][0];
	for (i = 1; i < n; i++)
		vec[0][i] = vec[0][i - 1] + matrix[0][i];
	for (i = 1; i < m; i++)
		vec[i][0] = vec[i - 1][0] + matrix[i][0];
	for (i = 1; i < m; i++)
		for (j = 1; j < n; j++)
			vec[i][j] = matrix[i][j] + min(vec[i - 1][j], vec[i][j - 1]);
	printPath(matrix, vec, m - 1, n - 1);
	return vec[m - 1][n - 1];
}
//��������
/*
input the rows: 4
input the columns: 4
1 3 5 9
8 1 3 4
5 0 6 1
8 8 4 0
1----->3----->1----->0----->6----->1----->0
*/
void testMatrixMinPath()
{
	int m, n,i,j;
	while (true)
	{
		cout << "input the rows: ";
		cin >> m;
		cout << "input the columns: ";
		cin >> n;
		if (m == 0 || n == 0) break;
		vector<vector<int>> matrix(m, vector<int>(n, 0));
		for (i = 0; i < m; i++)
			for (j = 0; j < n; j++)
				cin >> matrix[i][j];
		cout<<"	 ministSum = "<<matrixMinPath(matrix)<<"\n\n\n";
	}
}



//��Ǯ�����ٻ�����
/*
	1. arr=[5,2,3], aim=20;   ÿ����ֵ�Ļ�����������
			�������޵Ļ���ô dp[i][j] = min(dp[i-1][j], dp[i][j-a[i]]+1)  ע������ �� dp[i][j] = dp[i][j-a[i]]+1 ��������;������

	2. ÿ����ֵ�Ļ���������һ��
	        ����ͼ��� dp[i][j] = min(dp[i-1][j], dp[i-1][j-a[i]]+1)  ע�����������ʽ�����𣡣���
*/
void minCoins1()
{


}




int main()
{

	//testLongestSonStr();

	//testBackpack();

	//testKNum();

	testMatrixMinPath();

	cout << "\n\n\n\n";
	return 0;
}





//����������� ( �ݹ�ͷǵݹ� ��
int longestSonStr(string str1, string str2, int n1, int n2)
{
	if (n1 < 0 || n2 < 0)
		return 0;
	else if (str1[n1] == str2[n2])
	{
		int tmp = longestSonStr(str1, str2, n1 - 1, n2 - 1) + 1;
		return tmp;
	}
	else
	{
		int a = longestSonStr(str1, str2, n1 - 1, n2);
		int b = longestSonStr(str1, str2, n1, n2-1);
		return a > b ? a : b;
	}
}
void longestSonStr2(string str1, string str2)
{
	int i, j, n1 = str1.size() + 1, n2 = str2.size() + 1;
	vector<vector<int>> vec(n1, vector<int>(n2, 0));
	for(i=1;i<n1;i++)
		for (j = 1; j < n2; j++)
		{
			if (str1[i - 1] == str2[j - 1])
				vec[i][j] = vec[i - 1][j - 1] + 1;
			else if (vec[i - 1][j] >= vec[i][j - 1])
				vec[i][j] = vec[i - 1][j];
			else
				vec[i][j] = vec[i][j - 1];
		}
	cout << "\n\n      ";
	for (i = 0; i < n2 - 1; i++)
		cout << str2[i] << "  ";
	cout << endl << endl;
	for (i = 0; i < n1; i++)
	{
		if (i > 0)
			cout << str1[i-1] << "  ";
		else
			cout << "   ";
		for (j = 0; j < n2; j++)
			cout << vec[i][j] << "  ";
		cout << endl << endl;
	}
	cout << "\n\n\n���ĳ���Ϊ��" << vec[n1 - 1][n2 - 1];
	cout << "\n������Ϊ��";
	i = n1 - 1;
	j = n2 - 1;
	vector<char> v;
	while (i>0&&j>0)
	{
		if (str1[i-1]==str2[j-1])	//vec[i][j]==vec[i-1][j-1]+1����ǲ��е� ����������
		{
			v.push_back(str1[i - 1]);
			--i;
			--j;
		}
		else if (vec[i - 1][j] == vec[i][j])
			--i;
		else
			--j;
	}
	n1 = v.size();
	for (i = n1-1; i>=0; --i)
		cout << v[i];

}



//��������,w��������v�Ƕ�Ӧ�ļ�ֵ, n����Ʒ��������m�����Ƶ��������
int max(int a, int b)
{
	return a > b ? a : b;
}
void backpack(vector<int> &w, vector<int> &v,int n, int m)
{
	int i, j;
	vector<vector<int>> vec(n + 1, vector<int>(m + 1, 0));
	for(i=1;i<n+1;i++)
		for (j = 1; j < m + 1; j++)
		{
			if (w[i - 1] > j)		//������ǰk���Ϊm��ͬ�ĵط�Ϊ����ά���������Ϊ��Ӧ������Ʒ�����Ǹ���ʾ���ٸ���
				vec[i][j] = vec[i - 1][j];	
			else
				vec[i][j] = max(vec[i - 1][j], vec[i - 1][j - w[i - 1]] + v[i - 1]);
		}
	cout << "����ֵΪ��" << vec[n][m];
	vector<int> vv;
	i = n; j = m;
	while (i > 0)
	{
		if (vec[i][j] != vec[i - 1][j])	//��ʾw[i] ��Ʒû��ѡ��
		{
			j -= w[i - 1];
			vv.push_back(w[i - 1]);
		}
		--i;
	}
	i = vv.size()-1;
	cout << endl;
	for (; i >= 0; i--)
		cout << vv[i] << "  ";

	//cout << "\n\n";
	//for (i = 0; i <= n; i++)
	//{
	//	for (j = 0; j <= m; j++)
	//		cout << vec[i][j] << "  ";
	//	cout << endl << endl;
	//}
}



//ǰk���Ϊnum
void printMatrix(vector<vector<int>> &f, int n, int sum)
{
	int i, j;
	cout << "       ";
	for (i = 0; i <= sum; i++)
		cout << setw(2) << i << "  ";
	cout << endl << endl << endl;
	for (i = 0; i <= n; i++)
	{
		cout << "   " << i << "   ";
		for (j = 0; j <= sum; j++)
			cout << setw(2) << f[i][j] << "  ";
		cout << endl << endl;
	}
	cout << endl;
}
void printNum(vector<vector<int>> &vec, int n,int m,vector<int> &v, int cur, vector<int> &p,int sum, int *ways)
{
	if (n < 1)
	{
		int i = p.size() - 1;
		cout << sum << " = ";
		for (; i > 0; i--)
			cout << p[i] << " + ";
		cout << p[0]<<"\n";
		(*ways)++;
	}
	else
	{
		for (; cur >= 0; cur--)		//����ע��cur���ϲ㴫������ֵ��ʼ����Ϊ�ڵó������ʱ���Ǵӵ�һ���ڵ����ۼӺ���ڵ�õ���
		{
			if (m>=v[cur] && vec[n - 1][m - v[cur]] == 1)
			{
				p.push_back(v[cur]);
				printNum(vec, n - 1, m - v[cur], v, cur - 1, p,sum,ways);
				p.pop_back();
			}
		}
	}
}
void kNum(vector<int> &vec, int sum)
{
	int n = vec.size();
	vector<vector<int>> f(n + 1, vector<int>(sum + 1, 0));
	int i, j, k;
	f[0][0] = 1;
	for (i = 1; i <= n; i++)
	{
		for (k = i; k >0; k--)		//����һ��Ҫ���ű���
			for (j = vec[i - 1]; j <= sum; j++)
			{
				if (f[k - 1][j - vec[i - 1]] == 1)
					f[k][j] = 1;
			}
	}

////////////////////////��ӡ���ɵľ���
	printMatrix(f, n, sum);		

//////////////////////////////// ��ӡ�����п��ܵĽ��
	int Sum = sum;
	int ways = 0;
	while (true)
	{
		ways = 0;
		cout << "\n\n\n\n\n\ninput the sum: ";
		cin >> sum;
		if (sum == 0)
			break;
		else if (sum > Sum)
			continue;
		i = n;
		while (i && !f[i][sum]) --i;
		if (i == 0)
			cout << "�Ҳ���";
		else
			for (; i>0; i--)
				if (f[i][sum] == 1)
				{
					cout << "\n��" << i << "����֮��Ϊ" << sum << " : " << endl;
					vector<int> p;
					printNum(f, i, sum, vec, n - 1, p, sum,&ways);
				}
		if(ways)
			cout << "\nһ����" << ways << "�ֽⷨ������! ! ! ! ! ! ! ! ! ! !";
	}
	
}


//ǰk���Ϊnum, �ϰ�ģ�Ч�ʱȽϵ���
void kNum1(vector<int> &vec, int sum)
{
	int n = vec.size();
	vector<vector<int>> f(n + 1, vector<int>(sum + 1, 0));
	vector<vector<int>> f1(n + 1, vector<int>(sum + 1, 0));
	int i, j, k, ii, jj;
	f[0][0] = 1;
	for (i = 1; i <= n; i++)
	{
		for (ii = 0; ii <= n; ii++)
			for (jj = 0; jj <= sum; jj++)
				f1[ii][jj] = 0;
		for (k = 1; k <= i; k++)
			for (j = vec[i - 1]; j <= sum; j++)
			{
				if (f[k - 1][j - vec[i - 1]] == 1)
					f1[k][j] = 1;
			}
		for (ii = 1; ii <= i; ii++)
			for (jj = vec[i - 1]; jj <= sum; jj++)
				f[ii][jj] = f[ii][jj] || f1[ii][jj];
	}
	///////////////////////////////////////////////////////////
	cout << "       ";
	for (i = 0; i <= sum; i++)
		cout << setw(2) << i << "  ";
	cout << endl << endl << endl;
	for (ii = 0; ii <= n; ii++)
	{
		cout << "   " << ii << "   ";
		for (jj = 0; jj <= sum; jj++)
			cout << setw(2) << f[ii][jj] << "  ";
		cout << endl << endl;
	}
	cout << endl;
	//////////////////////////////////////////////////////////////

	i = n;
	while (i && !f[i][sum]) --i;
	if (i == 0)
	{
		cout << "�Ҳ���";
		return;
	}
	cout << "��" << i << "����֮��Ϊ" << sum << endl;
	j = sum;
	vector<int> x;
	ii = n - 1;
	while (i)
	{
		for (k = ii; k >= 0; k--)
			if (j >= vec[k] && f[i - 1][j - vec[k]] == 1)
			{
				x.push_back(vec[k]);
				j -= vec[k];
				ii = k - 1;
				break;
			}
		--i;
	}
	i = x.size() - 1;
	cout << sum << " = ";
	for (; i > 0; i--)
		cout << x[i] << " + ";
	cout << x[0];
}