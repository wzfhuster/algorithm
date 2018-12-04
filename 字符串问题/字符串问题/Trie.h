#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#define maxNum 26    //����Ĭ���Ǵ���Ķ���Сд��ĸ�����Ǵ�Сд���Ϊ 52
using namespace std;


typedef struct _trie
{
	int count;
	bool exit;	//��¼�˴��Ƿ񹹳�һ������, �����õ�ǰcount��ȥ�ӽڵ�count֮��
	struct _trie *next[maxNum];
}trieNode;




trieNode *createTrieNode();

void insertTrie(trieNode *root, string str);

//����һ���ֵ���
trieNode *createTrie(vector<string> vec);


//���Ѿ����ɵ��ֵ����в���һ���ַ����Ƿ���ڣ������ڷ��ش��ַ����ĸ�����ע�ⲻ����ǰ׺��
int findString(trieNode *root, string str);


//���ѹ��ɵ��ֵ����У����Ҳ����ַ����������ǰ׺������ǰ׺����root��next[]���������count����
string getLongestComPrefix(trieNode *root);
//���� �����С� �ַ����������ǰ׺
string getLongestComPrefix(trieNode *root, string str, int size);



//�������ַ����������򣬲���ӡ����
void trieSort(trieNode *root, vector<char> &vec);
//��ȥ�ص�����
void allTrieSort(trieNode *root, vector<char> &vec);


//�õ������ַ����г���Ƶ����ߵ�k����Top(k)����
void getTopK(trieNode *root, vector<char> &c, vector<pair<string, int>> &vec);


//�ͷ��ֵ������ڴ�
void deleteTrie(trieNode *root);

