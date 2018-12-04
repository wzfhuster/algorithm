#pragma once
#include<iostream>
#include<queue>
#include"printTree.h"
#include<assert.h>
#include<stack>

//���л�������
void preSerialize(BinaryTreeNode* root, vector<int> &vec);
void midSerialize(BinaryTreeNode* root, vector<int> &vec);
void aftSerialize(BinaryTreeNode* root, vector<int> &vec);
void layerSerialize(BinaryTreeNode* root, vector<int> &vec);
void testSerialize();


//�����л����ƺ�ֻ������Ͱ�����ܷ����л�
void dePreSerialize(BinaryTreeNode **root, vector<int> &vec, int &cur);
void deLayerSerialize(BinaryTreeNode** root, vector<int> &vec, int cur);
void testDeSerialize();


//����ǰ�����������������ؽ�������,Ϊ�˷���ݹ飬���Բ������������ͷβָ�룬����ֵΪ�����õĶ������ĸ��ڵ�
BinaryTreeNode* rebuild(int *preLeft, int *preRight, int *midLeft, int *midRight);
void testRebuild();



//�ݹ�ͷǵݹ�������������
int depth(BinaryTreeNode *root);
int depthRecursion(BinaryTreeNode *root);
void testDepth();



//��������Ķ���������һ���ڵ㣺(���µ��ϵ�ȥ���������
//�ȿ��ýڵ�����������������һ����������������ڵ㣻
//û���������Ļ����ٿ����ǲ���һ�����ڵ����ڵ㣬�ǵĻ�������һ�����丸�ڵ�
//����һ���ҽڵ����ҵ����һ��Ϊ��ڵ���Ǹ����ڵ������һ���ڵ�



//����һ����������������ľ��������
BinaryTreeNode *mirrorTree(BinaryTreeNode *root);
void testMirrorTree();


//�ж�һ���������Ƿ��ǶԳƵģ�����
//һ�����������Ǹ��ڵ�֮��������ڵ������ҽڵ㣬���ǿ��Զ���һ���µı����������Ǹ��ڵ�������ҽڵ�������ڵ�
//Ȼ��ͬʱ�ж������߱���������ֵ�Ƿ�����ȵ�
bool isSymmetric(BinaryTreeNode *root1, BinaryTreeNode *root2);
void testIsSymmetric();



//�ж�һ�������Ƿ��Ƕ����������ĺ����������
//�������������һ�����Ǹ��ڵ㣬�Ƿ��������зֳ�С�����ʹ�������������....
bool isBST(int *left, int *right);
void testIsBST();



//�������к�Ϊĳһֵ��·��
void findPath(BinaryTreeNode *root, vector<int> &vec, int curSum, int sum);
void testFindPath();



//��һ���������������˫������,������������Ա�������˫������
//�������Ǳ���һ������ʾ�Ѿ�ת�����˵�˫����������һ�����
//Ȼ�����������ȥ����ǰ��㣬��ǰ���Ϊ�м�ڵ㣬��Ȼ���Ǹ����һ����㻥��ָ��
//Ȼ��˫����������һ�����ͱ���˵�ǰ���м�ڵ㣬��ȥ�ݹ�Ĵ���������.......
void convert(BinaryTreeNode* root, BinaryTreeNode **lastNode);
void testConvert();



//�����������ĵ�k��Ľڵ�
void kThNode(BinaryTreeNode* root, int k, int &cur);
void testKNode();



//�ж��Ƿ���ƽ�������,�����������������1
//һ��Ĵ��ϵ��µ��жϻ��ظ��жϣ�Ч�ʵ���
//�����ú������˳���жϣ���Ϊ���ӵ����ϣ�����ýڵ�ǰ���������������Ѿ�����
bool isBalanceTree(BinaryTreeNode *root, int &deep);
void testIsBalanceTree();



//�ж�һ�����Ƿ�����һ�������ӽṹ
//��Ϊ�����������ҵ�a����b���ڵ���ͬ�Ľڵ㣬Ȼ���ж��Ƿ����b
bool hasSubTree(BinaryTreeNode *root1, BinaryTreeNode *root2);
bool tree1HasTree2(BinaryTreeNode *root1, BinaryTreeNode *root2);
void testHasSubTree();



//�ǵݹ�ķ�ʽʵ�ֶ����������ֱ���
//������
void stackPreTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s);
void stackMidTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s);
void stackAftTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s);
void testStackTree();



//�񼶱����������ķ�����Ҫ��ʱ�临�Ӷ�Ϊ O(n), �ռ临�Ӷ�Ϊ O(1)
//֮ǰ�ĵݹ�(����ջ���ͷǵݹ鷽�����Լ������ջ�����õ���ջ���������ǵĿռ临�Ӷ�Ϊ O(h)��hΪ���ĸ߶�
//֮������ջ��Ϊ���ܴ��²�ص��ϲ�ȥ
//���ǿ�������Ҷ�ӽڵ��nullָ��һЩ�ϲ�ڵ���ʵ��





//���ú�����������ؽ�����������
BinaryTreeNode *rebuildBST(int *left, int *right);
void testRebuildBst();
