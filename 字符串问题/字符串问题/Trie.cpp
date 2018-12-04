#include"Trie.h"


trieNode *createTrieNode()
{
	trieNode *node = new trieNode;
	node->count = 1;
	node->exit = false;
	for (int i = 0; i < maxNum; i++)
		node->next[i] = NULL;
	return node;
}


void insertTrie(trieNode *root, string str)
{
	trieNode *p = root;
	trieNode *node;
	int i, tmp,n = str.size();
	for (i = 0; i < n; i++)
	{
		tmp = str.at(i) - 'a';		//这默认字符都是小写的，可根据题意来改
		if (p->next[tmp] == NULL)
		{
			node = createTrieNode();
			p->next[tmp] = node;
			p = node;
		}
		else
		{
			p = p->next[tmp];
			p->count++;
		}
		if (i == n - 1)
			p->exit = true;
	}
}

//构造一个字典树
trieNode *createTrie(vector<string> vec)
{
	trieNode *root = createTrieNode();
	int n = vec.size();
	for (auto s : vec)
		insertTrie(root, s);
	return root;
}


//在已经构成的字典树中查找一个字符串是否存在，若存在返回此字符串的个数（注意不包括前缀）
int findString(trieNode *root, string str)
{
	trieNode *p = root;
	int i, tmp,res,n = str.size();
	for (i = 0; i < n; i++)
	{
		tmp = str.at(i) - 'a';
		if (p->next[tmp] == NULL)
			return 0;
		p = p->next[tmp];
	}
	res = p->count;
	for (i = 0; i < maxNum; i++)
		if(p->next[i]!=NULL)
			res -= p->next[i]->count;
	return res;
}


//在已构成的字典树中，查找 ”大多数“ 字符串的最长公共前缀，传入其中一个字符串作为引子，返回前缀
string getLongestComPrefix(trieNode *root)
{
	trieNode* p = root;
	string str = "";
	int i, tmp, res=0;
	for (i = 0; i < maxNum; i++)
		if (root->next[i] != NULL && root->next[i]->count > res)
			res = root->next[i]->count;
	int flag;
	while (true)
	{
		flag = 0;
		for (i = 0; i < maxNum; i++)
			if (p->next[i] != NULL && p->next[i]->count == res)
			{
				str += (i + 'a');
				p = p->next[i];
				flag = 1;
				break;
			}
		if (flag == 0)
			break;
	}

	return str;
}
//查找 “所有” 字符串的最长公共前缀
string getLongestComPrefix(trieNode *root, string str, int size)
{
	trieNode* p = root;
	int i, tmp, res, n = str.size();
	res = p->next[str[0] - 'a']->count;
	for (i = 0; i < n; i++)
	{
		tmp = str[i] - 'a';
		if (p->next[tmp]->count < res || p->next[tmp]->count!=size)
			break;
		p = p->next[tmp];
	}
	return str.substr(0, i);  //0开始，长度为i的子串
}


//对所有字符串进行排序，并打印出来，这个是去重后的排序
void trieSort(trieNode *root, vector<char> &vec)
{
	int i;
	for(i=0;i<maxNum;i++)
		if (root->next[i] != NULL)
		{
			vec.push_back(i + 'a');
			if (root->next[i]->exit)
			{
				for (auto &c : vec)
					cout << c;
				cout << "  ";
			}
			trieSort(root->next[i], vec);
			vec.pop_back();
		}
}
//不去重后的排序
void allTrieSort(trieNode *root, vector<char> &vec)
{
	int i;
	for (i = 0; i < maxNum; i++)
	{
		if (root->next[i] != NULL)
		{
			vec.push_back(i + 'a');
			if (root->next[i]->exit)
			{
				int times = root->next[i]->count;
				for (int j = 0; j < maxNum; j++)
					if (root->next[i]->next[j] != NULL)
						times -= root->next[i]->next[j]->count;
				while (times--)
				{
					for (auto &c : vec)
						cout << c;
					cout << "  ";
				}
			}
			allTrieSort(root->next[i], vec);
			vec.pop_back();
		}
	}
}



//得到所有字符串中出现频率最高的k个，Top(k)问题
//初始化的时候 将vec中初始化k个 pair<"",0> 对象！！！！！

//从index=0处开始维护堆
void maintainHeap(vector<pair<string, int>> &vec)
{
	int n = vec.size();
	int cur=0,less=0;
	int left = 1, right;
	pair<string, int> pTmp;
	while (cur<n)
	{
		left = 2 * cur + 1;
		right = left + 1;
		if (left<n && vec[left].second < vec[less].second)
			less = left;
		if (right < n && vec[right].second < vec[less].second)
			less = right;
		if (less == cur)
			break;
		pTmp = vec[cur];
		vec[cur] = vec[less];
		vec[less] = pTmp;
		cur = less;
	}
}

void getTopK(trieNode *root, vector<char> &c, vector<pair<string, int>> &vec)
{
	int i, tmp;
	pair<string, int> pa;
	for(i=0;i<maxNum;i++)
		if (root->next[i] != NULL)
		{
			c.push_back(i + 'a');
			if (root->next[i]->exit)
			{
				tmp = root->next[i]->count;
				for (int j = 0; j < maxNum; j++)
					if (root->next[i]->next[j] != NULL)
						tmp -= root->next[i]->next[j]->count;
				if (tmp > vec[0].second)
				{
					string str = "";
					str.assign(c.begin(), c.end());
					pa = make_pair(str, tmp);
					vec[0] = pa;
					maintainHeap(vec);
				}
			}
			getTopK(root->next[i], c, vec);
			c.pop_back();
		}
}



//释放字典树的内存
void deleteTrie(trieNode *root)
{
	if (root == NULL)
		return;
	for (int i = 0; i < maxNum; i++)
		deleteTrie(root->next[i]);
	delete root;
}