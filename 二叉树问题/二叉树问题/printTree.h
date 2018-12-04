#pragma once
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;

struct BinaryTreeNode
{
	int value;
	BinaryTreeNode *left;
	BinaryTreeNode *right;
};

//´òÓ¡Ò»¿Å¶þ²æÊ÷
void printTree(BinaryTreeNode *root);
int getDeep(BinaryTreeNode *root);
void printSpace(int n);
