#include<iostream>
#include<iomanip>  //用于格式化输出
#include<algorithm>
#include<fstream>  //读取文件
#include<cctype>   //有判断一个字符是否是数字或者字母的函数
#include<assert.h>
#include<set>
#include"kmp.h"
#include"Trie.h"
using namespace std;




/*
	1. 翻转字符串，整个单词顺序头尾对调，但是单个单词的顺序不变
		（1）可以在接受句子的时候用vector<string> 来接收，然后倒着输出vector即可
		（2）可以先翻转整个句子，再翻转单个单词，这里实现一下第二种方法
*/
void testReverseStr();


/*
	2. 求出一个字符串的左旋转：将前n个字符串移到尾部，abcdef 左旋转2后为 cdefab
		方法是使用三次reverse，先整体，然后再前n个，再后几个....
*/
void testLeftRotateStr();


/*
	3. 在字符串中删除特定的字符, 输入They are students.”和”aeiou”，则删除之后的第一个字符串变成”Thy r stdnts.”
		方法是可以维护两个指针，p1和p2, 用p2来判断当前字符是否要删，不删则复制到p1，要删则p2++跳过
		要删除的字符可以用hash表来存放和查找
*/
void testDelStr();



/*
	4. 题目：输入一个字符串，输出该字符串中对称的子字符串的最大长度。(求最长回文子串）
		比如输入字符串“google”，由于该字符串里最长的对称子字符串是“goog”，因此输出4
		(1)方法是 : 暴力求解三次循环嵌套，o(n3)
		(2)方法是 : 由内向外去判断，但注意要分奇数还是偶数判断，o(n2)
		(3)方法是 : Manacher算法，o(n)
*/
void testLongestSymmetricalLength();



/*
7. 求一个字符串最长不重复的子串

*/
void testGetLongestSubString();
int getLongestSubString(const string s);



/*
5. 全排列
	不多说，递归
*/
void testAllSeq();





/*
	6. 全组合
		采用二进制的形式，对每个元素用0或者1表示，表示选中或者没有选中
		（1）如果是求出所有的组合，则直接用1-n，判断二进制位输出即可
		（2）如果要求是取其中m个元素求其所有的组合，则建立一个m个1的和n-m个0的数组全排列再输出
*/
void testCombination();






//若干字符串的最长连续公共前缀
//使用字典树，或者n个字符串每个字符同时比较
void testTrie();
//字典树的一个应用找出一个文章中topK的单词
void testTopK();



//两个字符串最长公共子序列，这个是动态规划问题（放在动态规划里面实现）



//已知入栈顺序，求所有可能的出栈顺序:  (2n!)/(n!*(n+1)!)
void testStackSeq();
//判断一个序列是否是另一个序列的出栈序列
bool isStackSeq(vector<char> in_que, vector<char> out_que);


//字符串与模板字符是否通配匹配（？，*）
void testMatch();


//kmp算法，可以判断一个字符串是否是另一个字符串的“子串”
void testKmp();


//大数相加和大数相乘，也属于字符串的问题
void bigDataPlus(string str1, string str2);
void testBigData();


//自定义vector中的比较规则
struct cmp
{
	bool operator()(pair<string, int> pa, pair<string, int> pb)
	{
		return pa.second > pb.second;
	}
};


int main()
{

	//testKmp();
	//testMatch();
	//testTrie();
	//testTopK();
	//testStackSeq();
	//testBigData();
	//testReverseStr();
	//testLeftRotateStr();
	//testDelStr();
	//testLongestSymmetricalLength();
	//testAllSeq();
	//testCombination();
	//testGetLongestSubString();

	int a[4] = { -1 };
	cout << a[3];

	return 0;
}



//测试kmp算法
void testKmp()
{
	char s[20], p[20];
	int next[20],i,res;
	while (true)
	{
		cout << "请输入文本字符串：";
		cin >> s;
		if (strcmp("0", s) == 0) break;
		cout << "请输入匹配的模式串：";
		cin >> p;

		//getNext(p, next);
		getOptNext(p, next);
		res = kmpSearch(s, p, next);
		if (res == -1)
			cout << "Sorry, 没有找到匹配的位置！！！" << "\n\n\n\n\n";
		else
		{
			cout << "\n入文本字符串下标：";
			for (i = 0; i < 20; i++)
				cout << setw(2) << i << " ";
			cout << "\n输入的文本字符串：";
			i = 0;
			while (s[i])
			{
				cout << setw(2) << s[i] << " ";
				++i;
			}
			cout << "\n匹配的位置是: " << res << "\n\n\n\n\n";
		}
	}
	cout << endl << endl << endl;
}


//字符串与模板的匹配（包括通配符？，*）,0表示失败，1表示成功
int isMatch(char *s, char *p)
{
	if (*s == '\0' && *p == '\0')
		return 1;   //只有两个字符串同时到达尾部的时候才匹配正确
	else if (*s == '\0' || *p == '\0')
		return 0;
	else
	{
		if (*p == '?' || *s == *p)
		{
			++s;
			++p;
			return isMatch(s, p);
		}
		else if (*p == '*')
		{
			++p;
			while(true)		//这里要注意考虑到 j* 的情况
			{
				if (isMatch(s, p) == 1) 
					return 1;
				if (*s == '\0')  //所以这里s中的结尾符号'\0'也要和p进行比较，比如s=jfioen,p=j*的匹配 ！！！！！
					return 0;
				++s;
			}
			return 0;
		}
		else if (*s != *p)
			return 0;
	}
}
void testMatch()
{
	char s[20], p[20];
	int res;
	while (true)
	{
		cout << "input the text: ";
		cin >> s;
		if (strcmp("0", s) == 0) 
			break;
		cout << "input the pattern: ";
		cin >> p;
		res = isMatch(s, p);
		if (res == 0) cout << "Failed ! ! !\n\n\n\n";
		else cout << "Success ! ! !\n\n\n\n";
	}
	cout << endl << endl << endl;
}



//测试字典树
void testTrie()
{
	trieNode *root;
	int m, n, i,topK=3;  //topK设置k的大小
	string str;
	while (true)
	{
		vector<string> vec;
		cout << "请输入字符串的个数：";
		cin >> m;
		if (m == 0)
			break;
		for (i = 0; i < m; i++)
		{
			cin >> str;
			vec.push_back(str);
		}
		root = createTrie(vec);

		while (true)
		{
			cout << "\n\n请输入你要查找的字符串：";
			cin >> str;
			if (str == "0")
				break;
			cout << "字典树查找的结果是：" << findString(root, str) << "\n";
		}

		cout << "\n\n部分字符串的最长公共前缀是：" << getLongestComPrefix(root);
		cout << "\n所有字符串的最长公共前缀是：" << getLongestComPrefix(root, vec[0],vec.size()) << "\n\n\n";

		vector<char> vc;
		cout << "所有字符串去重后排序为：";
		trieSort(root, vc);
		cout << "\n所有字符串没有去重后排序为：";
		allTrieSort(root, vc);

		//TopK问题
		cout << "\n\n\nTop"<<topK<<"为：";
		vector<pair<string, int>> vp(topK, pair<string, int>("", 0));
		getTopK(root, vc, vp);
		sort(vp.begin(), vp.end(), cmp());
		for (auto &a : vp)
			cout << a.first << " : " << a.second << endl;


		deleteTrie(root);
		cout << "\n\n\n\n\n\n";
	}

	cout << endl << endl << endl;
}

//找出一个文章中topK的单词
void testTopK()
{
	trieNode *root;
	ifstream in;
	string filename,str;
	int k;
	while (true)
	{
		cout << "请输入要打开的txt文件名：";
		cin >> filename;
		if (filename == "0")
			break;
		in.open(filename);
		if (!in.is_open())
		{
			cout << "打开文件出错，请重新输入！！！" << endl << endl;
			continue;
		}

		vector<string> vec;
		//getline(in, s);   //逐行读取
		int left, right,len;
		while (!in.eof())
		{
			in >> str;

			left = 0;
			right = str.size() - 1;
			len = str.size();
			while (left<len && str[left] && (str[left]<0 || !isalpha(str[left])))
				++left;
			while (right>=0 && str[right] && (str[right]<0 || !isalpha(str[right])))
				--right;

			int ii=left, jj=right,flag;
			if (right >= left)
			{
				flag = 1;
				for(;ii<=jj;ii++)
					if (str[ii]<0 || !isalpha(str[ii]))		//isalpha()函数只能接受非负的整数!!!!!
					{
						flag = 0;
						break;
					}
				if (flag == 1)
				{
					if(left!=0 || right!=str.size()-1)
						str = str.substr(left, right - left + 1);
					transform(str.begin(), str.end(), str.begin(), ::tolower);
					//cout << str << endl;
					vec.push_back(str);
				}
			}
		}


		//创建字典树
		root = createTrie(vec);

		//TopK问题
		while (true)
		{
			cout << "\n\n请输入topK的k值：";
			cin >> k;
			if (k == 0)
				break;
			vector<char> vc;
			cout << "Top" << k << "为：\n\n";
			vector<pair<string, int>> vp(k, pair<string, int>("", 0));
			getTopK(root, vc, vp);
			sort(vp.begin(), vp.end(), cmp());
			for (auto &a : vp)
				cout << a.first << " : " << a.second << endl;
			cout << "\n\n\n";
		}

		deleteTrie(root);

		in.close();
		cout << "\n\n\n";
	}

}



//可能的出栈顺序
void getStackSeq(vector<char> &in_que, int cur, vector<char> &s, vector<char> &out_que)
{
	if (cur==in_que.size())  //当输入队列都遍历完了后，就将栈和输出队列中的值都打印出来，注意顺序
	{
		for (auto c : out_que)
			cout << c;
		if (!s.empty())
			for (int i = s.size() - 1; i >= 0; i--)
				cout << s[i];
		cout << endl;
	}
	else
	{
		s.push_back(in_que[cur]);
		getStackSeq(in_que, cur + 1, s, out_que);
		s.pop_back();

		if (!s.empty())
		{
			out_que.push_back(s[s.size() - 1]);
			s.pop_back();
			getStackSeq(in_que, cur, s, out_que);
			s.push_back(out_que[out_que.size() - 1]);
			out_que.pop_back();
		}
	}
}
//判断一个序列是否是另一个序列的出栈序列
bool isStackSeq(vector<char> in_que, vector<char> out_que)
{
	if (in_que.size() != out_que.size())
		return false;
	vector<char> s;
	int i = 0, j = 0;
	while (j<out_que.size())
	{
		if (i < in_que.size() && in_que[i] == out_que[j])
		{
			++i;
			++j;
		}
		else if (!s.empty() && s[s.size() - 1] == out_que[j])
		{
			s.pop_back();
			++j;
		}
		else if (i < in_que.size())
			s.push_back(in_que[i++]);
		else
			return false;
	}
	return i == in_que.size() && j == out_que.size();
}
bool isStackSeq(string str1, string str2)
{
	if (str1.size() != str2.size())
		return false;
	vector<char> s;
	int i = 0, j = 0, n = str1.size();
	while (j<n)
	{
		if (!s.empty() && s[s.size() - 1] == str2[j])  //这个更加简洁，
		{										//总是先判断栈顶元素是否和输出串相等，不相等则入栈。。。
			s.pop_back();
			++j;
		}
		else if (i < n)
			s.push_back(str1[i++]);
		else
			return false;
	}
	return true;
}
void testStackSeq()
{
	vector<char> in_que, s, out_que;
	string str,str1;
	while (true)
	{
		cout << "请输入入栈字符串：";
		cin >> str;
		if (str == "0")
			break;
		in_que.assign(str.begin(), str.end());
		cout << "可能的出栈顺序为：\n";
		getStackSeq(in_que, 0, s, out_que);
		cout << "\n\n\n\n";
	}

	cout << "\n\n\n\n----------------------测试判断一个字符串是否是另一个字符串的出栈顺序-------------------------\n\n";
	while (true)
	{
		vector<char> v1, v2;
		cout << "请输入入栈字符串：";
		cin >> str;
		if (str == "0")
			break;
		cout << "请输入出栈字符串：";
		cin >> str1;
		v1.assign(str.begin(), str.end());
		v2.assign(str1.begin(), str1.end());
		if (isStackSeq(v1, v2))
			cout << "yes";
		else
			cout << "no";
		if (isStackSeq(str, str1))
			cout << "   yes";
		else
			cout << "   no";
		cout << "\n\n\n\n";
	}
}



//大数相加和大数相乘，也属于字符串的问题
void bigDataPlus(string str1, string str2)
{
	int n1 = str1.size(), n2 = str2.size();
	int n = n1 > n2 ? n1 : n2;
	vector<int> a(n + 1, 0);
	vector<int> b(n + 1, 0);
	vector<int> res(n + 1, 0);
	int i, tmp;
	for (i = 0; i < n1; i++)
		a[i] = str1[n1 - 1 - i] - '0';
	for (i = 0; i < n2; i++)
		b[i] = str2[n2 - 1 - i] - '0';
	for (i = 0; i < n; i++)
	{
		tmp = a[i] + b[i] + res[i];
		res[i] = tmp % 10;
		res[i + 1] = tmp / 10;
	}
	while (n > 0 && res[n] == 0) --n;
	while (n > -1) cout << res[n--];
	cout << "\n";
}
void bigDataMul(string str1, string str2)
{
	int n1 = str1.size(), n2 = str2.size();
	int i, j, tmp, n = n1 + n2;
	vector<int> a(n1, 0);
	vector<int> b(n2, 0);
	vector<int> res(n, 0);		//一个m位和n位数相乘结果位数最多为m+n，最少为m+n-1
	for (i = 0; i < n1; i++)
		a[i] = str1[n1 - 1 - i] - '0';
	for (j = 0; j < n2; j++)
		b[j] = str2[n2 - 1 - j] - '0';
	for (i = 0; i<n1; i++)
		for (j = 0; j < n2; j++)
		{
			tmp = a[i] * b[j] + res[i + j];
			res[i + j] = tmp % 10;
			res[i + j + 1] += tmp / 10;    //注意这里要 +=
		}
	--n;
	while (n > 0 && res[n] == 0) --n;
	while (n > -1) cout << res[n--];
	cout << "\n";
}
void testBigData()
{
	string str1, str2;
	while (true)
	{
		cout << "输入str1: ";
		cin >> str1;
		if (str1 == "0") break;
		cout << "输入str2: ";
		cin >> str2;
		cout << "\n相加的结果是：";
		bigDataPlus(str1, str2);
		cout << "\n相乘的结果是：";
		bigDataMul(str1, str2);
		cout << "\n\n\n\n";
	}
	cout << "\n\n\n";
}



/*
1.翻转字符串，整个单词顺序头尾对调，但是单个单词的顺序不变
（1）可以在接受句子的时候用vector<string> 来接收，然后倒着输出vector即可
（2）可以先翻转整个句子，再翻转单个单词，这里实现一下第二种方法
*/
void reverse(char *begin, char *end)
{
	char tmp;
	while (begin<end)
	{
		tmp = *begin;
		*begin = *end;
		*end = tmp;
		++begin;
		--end;
	}
}
void reverseStr(string &str)
{
	if (str.size() == 0 || str.size() == 1)
		return;
	reverse(&str[0], &str[str.size() - 1]);
	char *begin = &str[0], *end;
	int n = str.size(),i;
	for (i = 0; i < n; i++)
	{
		if (i > 0 && str[i] == ' ' && str[i - 1] != ' ')
		{
			end = &str[i - 1];
			reverse(begin, end);
			begin = &str[i + 1];
		}
		else if (i == n - 1)
			reverse(begin, &str[i]);
	}
	
}
void testReverseStr()
{
	string str;
	while (true)
	{
		cout << "请输入一个字符串：";
		getline(cin, str);
		if (str == "0") break;
		cout << "翻转后的字符串为：";
		reverseStr(str);
		cout << str << "\n\n\n\n";
	}
}



/*
2.求出一个字符串的左旋转：将前n个字符串移到尾部，abcdef 左旋转2后为 cdefab
*/
void leftRotateStr(string &str, int m)  //前m个翻转
{
	if (str.size() == 0 || str.size() == 1 || m==str.size()) return;
	else if (m > str.size())
	{
		cout << "shit，旋转数大于字符串长度啦！！！\n\n\n\n";
		return;
	}
	reverse(&str[0], &str[str.size() - 1]);
	reverse(&str[0], &str[str.size() - m-1]);
	reverse(&str[str.size() - m], &str[str.size() - 1]);
}
void testLeftRotateStr()
{
	string str;
	int n;
	while (true)
	{
		cout << "请输入字符串：";
		cin >> str;
		if (str == "0") break;
		cout << "请输入旋转数：";
		cin >> n;
		cout << "旋转后的字符串为：";
		leftRotateStr(str, n);
		cout << str << "\n\n\n\n";
	}
}



/*
3.在字符串中删除特定的字符, 输入They are students.”和”aeiou”，则删除之后的第一个字符串变成”Thy r stdnts.”
方法是可以维护两个指针，p1和p2, 用p2来判断当前字符是否要删，不删则复制到p1，要删则p2++跳过
要删除的字符可以用hash表来存放和查找
*/
void delStr(string &str1, string str2)
{
	int isDel[256] = { 0 };
	int n = str1.size(), n2 = str2.size();
	int i,j;
	for (i = 0; i < n2; i++)
		isDel[str2[i]] = 1;
	i = j = 0;
	while (j<n)
	{
		if (isDel[str1[j]] == 0)
			str1[i++] = str1[j];
		++j;
	}
	str1 = str1.substr(0, i);
}
void testDelStr()
{
	string str1, str2;
	while (true)
	{
		cout << "输入字符串：";
		getline(cin, str1);
		if (str1 == "0") break;
		cout << "输入要剔除的字符集合：";

		cin >> str2;
		getchar();
		//关于这个位置为什么还要一个getchar()的原因：
		//		cin>> 这种输入方法是会忽略回车的，就是说你按回车后，回车符是留在输入流中了
		//		不论你输入的是字符，数字或是回车，空格符，getline()函数都接收,且它读取回车后返回,它读取的回车并
						//不会赋值给string


		cout << "删除指定字符后的结果为：";
		delStr(str1, str2);
		cout << str1 << "\n\n\n\n";
	}
}







/*
取得所有对称子串的最大长度
*/
//时间复杂度： O(n^2)的方法
void GetLongestSymmetricalLength(string str)
{
	int left, right, i, n = str.size();
	int len=0,tmp=0;
	int flag;
	for (int i = 0; i < n; i++)
	{
		//考虑奇数情况
		left = i - 1;
		right = i + 1;
		while (left>=0 && right<n && str[left]==str[right])
		{
			--left;
			++right;
		}
		tmp = right - left - 1;
		if (tmp > len)
		{
			len = tmp;
			flag = left + 1;
		}

		//考虑偶数情况
		left = i;
		right = i + 1;
		while (left >= 0 && right<n && str[left] == str[right])
		{
			--left;
			++right;
		}
		tmp = right - left - 1;
		if (tmp > len)
		{
			len = tmp;
			flag = left + 1;
		}
	}
	cout << "\n1最长的回文子串：" << str.substr(flag, len);
}
//时间复杂度为：O（n）的方法，维护一个max和id,mx是娶不到的
void GetLongestSymmetricalLength2(string s)
{
	int i=1, k=0,n =2*s.size()+2;
	string str(n, '$');  //开头加上一个特殊字符，防止判断的时候越界
	while (s[k])
	{
		str[i++] = '#';
		str[i++] = s[k++];
	}
	str[i] = '#';

	int id, mx = 0,ans=0;
	vector<int> len(n, 0);		//len[i]是以i为中心的最长半径（半径长度包括i自己）
	for (i = 1; i < n; i++)
	{
		if (i < mx)
			len[i] = min(len[2 * id - i], mx - i);  //这里注意理解mx是取不到的
		else
			len[i] = 1;
		while (str[i + len[i]] == str[i - len[i]])  //这里不用判断i<n，因为头尾都有‘$'和'\0'结束符肯定不等
			++len[i];
		if (i + len[i] > mx)	//从这里更新mx也知道，mx是取不到的
		{
			mx = i + len[i];
			id = i;
		}
		if (len[ans] < len[i])	//设置一个ans来记录最长的半径
			ans = i;
	}
							//这里注意str开头加了一个‘$', 然后len[i]-1 刚好是没加'#'的子串长度！！！！
	cout << "\n2最长的回文子串：" << s.substr(ans/2-len[ans]/2, len[ans]-1) << "\n\n\n";
}
void testLongestSymmetricalLength()
{
	string str;
	while (true)
	{
		cout << "请输入一个字符串：";
		cin >> str;
		if (str == "0")
			break;
		GetLongestSymmetricalLength(str);
		GetLongestSymmetricalLength2(str);
	}
}





/*
5. 全排列
不多说，递归
*/
bool isRepeat(string &str, int i, int cur)
{
	for (int j = cur; j < i; j++)
		if (str[j] == str[i])
			return true;
	return false;
}
void allSeq(string &str,int cur)
{
	if (cur == str.size() - 1)
		cout << str << endl;
	else
	{
		int i, j,n = str.size();
		char tmp;
		for (i = cur; i < n; i++)
		{
			if (!isRepeat(str, i, cur))
			{
				tmp = str[cur];
				str[cur] = str[i];
				str[i] = tmp;
				allSeq(str, cur + 1);
				tmp = str[cur];
				str[cur] = str[i];
				str[i] = tmp;
			}
		}
	}
}
void testAllSeq()
{
	string str;
	while (true)
	{
		cout << "请输入一个字符串：";
		cin >> str;
		if (str == "0")
			break;
		cout << "它的全排列为：\n";
		allSeq(str, 0);
		cout << "\n\n\n\n";
	}
}





/*
6. 全组合
采用二进制的形式，对每个元素用0或者1表示，表示选中或者没有选中
（1）如果是求出所有的组合，则直接用1-n，判断二进制位输出即可
（2）如果要求是取其中m个元素求其所有的组合，则建立一个m个1的和n-1个0的数组全排列再输出
*/
void combination(string str)
{
	int nbits = str.size();
	int n = pow(2, nbits);
	int i, j,tmp;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < nbits; j++)
		{
			tmp = pow(2, j);
			if (i&tmp)
				cout << str[j];
		}
		cout << endl;
	}
	cout << "一共有" << n - 1 << "个组合";
}

bool isRepeat(vector<int> &vec, int i, int cur)
{
	for (int j = cur; j < i; j++)
		if (vec[j] == vec[i])
			return true;
	return false;
}
void seqPrint(string &str, vector<int> &vec, int cur)
{
	int n = vec.size();
	if (cur == n - 1)
	{
		for (int i = 0; i < n; i++)
			if (vec[i] == 1)
				cout << str[i];
		cout << endl;
	}
	else
	{
		int i, tmp;
		for (i = cur; i < n; i++)
			if (!isRepeat(vec, i, cur))
			{
				tmp = vec[i];
				vec[i] = vec[cur];
				vec[cur] = tmp;
				seqPrint(str, vec, cur + 1);
				tmp = vec[i];
				vec[i] = vec[cur];
				vec[cur] = tmp;
			}
	}
}
void nCombination(string str, int m)  //求任意取m个元素所有的情况
{
	int n = str.size();
	vector<int> vec(n, 0);
	int i;
	for (i = 0; i < m; i++)
		vec[i] = 1;
	seqPrint(str, vec, 0);
}
void testCombination()
{
	string str;
	int m;
	while (true)
	{
		cout << "请输入字符串：";
		cin >> str;
		if (str == "0")
			break;
		cout << "请输入要提取的元素的个数：";
		cin >> m;
		cout << "全组合为: \n";
		combination(str);
		cout << "\n\n\n\n提取" << m << "个元素的所有情况为：\n";
		nCombination(str, m);
		cout << "\n\n\n\n\n";
	}
}




/*
7. 求一个字符串最长不重复的子串
	思想：用一个begin 和 len来记录最长不重复子串的起始位置和长度
			然后用  pre表示当前的不重复子串的起始位置

*/
int getLongestSubString1(const string s)
{
	int hash[256];
	memset(hash, -1, sizeof(hash));
	int i, n = s.size();
	int pre=0,len=0,begin=0;
	for (i = 0; i < n; i++)
	{
		//ejwfjwojfelk
		if (hash[s[i]] != -1 && hash[s[i]]+1>pre)		//这里一定要注意判断    hash[s[i]]+1>pre
			pre = hash[s[i]] + 1;
		hash[s[i]] = i;
		if (i - pre + 1 > len)
		{
			begin = pre;
			len = i - pre + 1;
			cout << s.substr(begin, len) << endl;
		}
	}

	cout << "长度是：" << len;
	cout << "\n子串是：" << s.substr(begin, len);
	return len;
}
void testGetLongestSubString()
{
	string s;
	while (true)
	{
		cout << "input the string: ";
		cin >> s;
		if (s == "0")
			break;
		getLongestSubString(s);
		cout << "\n\n\n\n";
	}
}