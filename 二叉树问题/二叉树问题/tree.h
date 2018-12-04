#pragma once
#include<iostream>
#include<queue>
#include"printTree.h"
#include<assert.h>
#include<stack>

//序列化二叉树
void preSerialize(BinaryTreeNode* root, vector<int> &vec);
void midSerialize(BinaryTreeNode* root, vector<int> &vec);
void aftSerialize(BinaryTreeNode* root, vector<int> &vec);
void layerSerialize(BinaryTreeNode* root, vector<int> &vec);
void testSerialize();


//反序列化，似乎只能先序和按层才能反序列化
void dePreSerialize(BinaryTreeNode **root, vector<int> &vec, int &cur);
void deLayerSerialize(BinaryTreeNode** root, vector<int> &vec, int cur);
void testDeSerialize();


//根据前序和中序遍历序列来重建二叉树,为了方便递归，所以参数两个数组的头尾指针，返回值为构建好的二叉树的根节点
BinaryTreeNode* rebuild(int *preLeft, int *preRight, int *midLeft, int *midRight);
void testRebuild();



//递归和非递归求二叉树的深度
int depth(BinaryTreeNode *root);
int depthRecursion(BinaryTreeNode *root);
void testDepth();



//中序遍历的二叉树的下一个节点：(由下到上的去考虑情况）
//先看该节点有右子树否，有则下一个是右子树的最左节点；
//没有右子树的话，再看它是不是一个父节点的左节点，是的话，则下一个是其父节点
//若是一个右节点则找到其第一次为左节点的那个父节点就是下一个节点



//给出一个二叉树，求出它的镜像二叉树
BinaryTreeNode *mirrorTree(BinaryTreeNode *root);
void testMirrorTree();


//判断一个二叉树是否是对称的！！！
//一般的先序遍历是根节点之后再是左节点再是右节点，我们可以定义一种新的遍历方法就是根节点后先是右节点再是左节点
//然后同时判断这两者遍历过程中值是否是相等的
bool isSymmetric(BinaryTreeNode *root1, BinaryTreeNode *root2);
void testIsSymmetric();



//判断一个序列是否是二叉搜索树的后续遍历结果
//方法是序列最后一个数是根节点，是否它将序列分成小于它和大于它的两部分....
bool isBST(int *left, int *right);
void testIsBST();



//二叉树中和为某一值的路径
void findPath(BinaryTreeNode *root, vector<int> &vec, int curSum, int sum);
void testFindPath();



//将一个二叉搜索树变成双向链表,按中序遍历可以变成有序的双向链表
//方法就是保存一个结点表示已经转化好了的双向链表的最后一个结点
//然后按照中序遍历去处理当前结点，当前结点为中间节点，自然和那个最后一个结点互相指向
//然后双向链表的最后一个结点就变成了当前的中间节点，再去递归的处理右子树.......
void convert(BinaryTreeNode* root, BinaryTreeNode **lastNode);
void testConvert();



//二叉搜索树的第k大的节点
void kThNode(BinaryTreeNode* root, int k, int &cur);
void testKNode();



//判断是否是平衡二叉树,左右子树深度相差不超过1
//一般的从上到下的判断会重复判断，效率低下
//可以用后序遍历顺序判断，因为它从底向上，到达该节点前，它的左右子树已经遍历
bool isBalanceTree(BinaryTreeNode *root, int &deep);
void testIsBalanceTree();



//判断一棵树是否是另一颗树的子结构
//分为两步：首先找到a中与b根节点相同的节点，然后判断是否包含b
bool hasSubTree(BinaryTreeNode *root1, BinaryTreeNode *root2);
bool tree1HasTree2(BinaryTreeNode *root1, BinaryTreeNode *root2);
void testHasSubTree();



//非递归的方式实现二叉树的三种遍历
//方法是
void stackPreTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s);
void stackMidTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s);
void stackAftTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s);
void testStackTree();



//神级遍历二叉树的方法：要求时间复杂度为 O(n), 空间复杂度为 O(1)
//之前的递归(函数栈）和非递归方法（自己申请的栈）都用到了栈，所以他们的空间复杂度为 O(h)，h为树的高度
//之所以用栈是为了能从下层回到上层去
//我们可以利用叶子节点的null指向一些上层节点来实现





//利用后序遍历序列重建二叉搜索树
BinaryTreeNode *rebuildBST(int *left, int *right);
void testRebuildBst();
