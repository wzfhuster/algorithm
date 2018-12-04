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
		tmp = str.at(i) - 'a';		//��Ĭ���ַ�����Сд�ģ��ɸ�����������
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

//����һ���ֵ���
trieNode *createTrie(vector<string> vec)
{
	trieNode *root = createTrieNode();
	int n = vec.size();
	for (auto s : vec)
		insertTrie(root, s);
	return root;
}


//���Ѿ����ɵ��ֵ����в���һ���ַ����Ƿ���ڣ������ڷ��ش��ַ����ĸ�����ע�ⲻ����ǰ׺��
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


//���ѹ��ɵ��ֵ����У����� ��������� �ַ����������ǰ׺����������һ���ַ�����Ϊ���ӣ�����ǰ׺
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
//���� �����С� �ַ����������ǰ׺
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
	return str.substr(0, i);  //0��ʼ������Ϊi���Ӵ�
}


//�������ַ����������򣬲���ӡ�����������ȥ�غ������
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
//��ȥ�غ������
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



//�õ������ַ����г���Ƶ����ߵ�k����Top(k)����
//��ʼ����ʱ�� ��vec�г�ʼ��k�� pair<"",0> ���󣡣�������

//��index=0����ʼά����
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



//�ͷ��ֵ������ڴ�
void deleteTrie(trieNode *root)
{
	if (root == NULL)
		return;
	for (int i = 0; i < maxNum; i++)
		deleteTrie(root->next[i]);
	delete root;
}