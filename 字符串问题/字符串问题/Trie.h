#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<utility>
#define maxNum 26    //这里默认是传入的都是小写字母，若是大小写则改为 52
using namespace std;


typedef struct _trie
{
	int count;
	bool exit;	//记录此处是否构成一个单词, 可以用当前count减去子节点count之和
	struct _trie *next[maxNum];
}trieNode;




trieNode *createTrieNode();

void insertTrie(trieNode *root, string str);

//构造一个字典树
trieNode *createTrie(vector<string> vec);


//在已经构成的字典树中查找一个字符串是否存在，若存在返回此字符串的个数（注意不包括前缀）
int findString(trieNode *root, string str);


//在已构成的字典树中，查找部分字符串的最长公共前缀，返回前缀，由root下next[]数组中最大count决定
string getLongestComPrefix(trieNode *root);
//查找 “所有” 字符串的最长公共前缀
string getLongestComPrefix(trieNode *root, string str, int size);



//对所有字符串进行排序，并打印出来
void trieSort(trieNode *root, vector<char> &vec);
//不去重的排序
void allTrieSort(trieNode *root, vector<char> &vec);


//得到所有字符串中出现频率最高的k个，Top(k)问题
void getTopK(trieNode *root, vector<char> &c, vector<pair<string, int>> &vec);


//释放字典树的内存
void deleteTrie(trieNode *root);

