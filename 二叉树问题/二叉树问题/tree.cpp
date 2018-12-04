#include"tree.h"


//4种序列化二叉树的方法
//****************************************************************************************************************//
void preSerialize(BinaryTreeNode* root, vector<int> &vec)
{
	if (root == NULL)
	{
		vec.push_back(-1);
		return;
	}
	vec.push_back(root->value);
	preSerialize(root->left, vec);
	preSerialize(root->right, vec);
}
void midSerialize(BinaryTreeNode* root, vector<int> &vec)
{
	if (root == NULL)
	{
		vec.push_back(-1);
		return;
	}
	midSerialize(root->left, vec);
	vec.push_back(root->value);
	midSerialize(root->right, vec);
}
void aftSerialize(BinaryTreeNode* root, vector<int> &vec)
{
	if (root == NULL)
	{
		vec.push_back(-1);
		return;
	}
	aftSerialize(root->left, vec);
	aftSerialize(root->right, vec);
	vec.push_back(root->value);
}
void layerSerialize(BinaryTreeNode* root, vector<int> &vec)
{
	queue<BinaryTreeNode*> que;
	que.push(root);
	int i, n;
	BinaryTreeNode *node;
	int flag = 1;
	while (!que.empty())
	{
		flag = 1;
		n = que.size();
		for (i = 0; i < n; i++)
		{
			node = que.front();
			que.pop();
			if (node == NULL)
			{
				vec.push_back(-1);
				que.push(NULL);
				que.push(NULL);
			}
			else
			{
				flag = 0;
				vec.push_back(node->value);
				que.push(node->left);
				que.push(node->right);
			}
		}
		if (flag)
		{
			for (i = 0; i < n; i++)		//排除最后一排全为NULL的部分
				vec.pop_back();
			break;
		}
	}
}
void testSerialize()
{
	vector<int> vec = { 1,2,4,-1,-1,-1,3,5,7,-1,-1,8,-1,-1,6,-1,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	dePreSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树


	cout << "preSerialize: ";
	vector<int> v;
	preSerialize(root, v);
	for (int &i : v)
		cout << i << "  ";
	cout << "\n\n";


	cout << "MidSerialize: ";
	vector<int> v1;
	midSerialize(root, v1);
	for (int &i : v1)
		cout << i << "  ";
	cout << "\n\n";


	cout << "aftSerialize: ";
	vector<int> v2;
	aftSerialize(root, v2);
	for (int &i : v2)
		cout << i << "  ";
	cout << "\n\n";

	cout << "layerSerialize: ";
	vector<int> v3;
	layerSerialize(root, v3);
	for (int &i : v3)
		cout << i << "   ";
	cout << "\n\n\n";
}
//****************************************************************************************************************//




//4种反序列化的方法
//****************************************************************************************************************//
void dePreSerialize(BinaryTreeNode** root, vector<int> &vec, int &cur)
{
	if (cur >= vec.size())    //	{ 1,2,4,-1,-1,-1,3,5,7,-1,-1,8,-1,-1,6,-1,-1 };
		return;
	else if (vec[cur] == -1)
	{
		*root = NULL;
		return;
	}
	*root = new BinaryTreeNode();	//指针也是一个对象，里面存储的是所开辟内存的地址，比如 void fun(int *p2); fun(p1);
	(*root)->value = vec[cur];		//这里p1和p2就像两个独立盒子，但是盒子里面装的是同一个内存地址，当我们改变p2盒子里面的地址时候，p1盒子内地址并不变
	dePreSerialize(&(*root)->left, vec, ++cur);		//所以这里用了 **root，就像fun(int **p2); p2盒子里面装的是p1的地址，这样就可以改变p1盒子里面的地址了
	dePreSerialize(&(*root)->right, vec, ++cur);	//还有一点就是 root->left = p; 就是把p盒子里面的内容复制给left盒子。。。。
}

void deLayerSerialize(BinaryTreeNode** root, vector<int> &vec, int cur)
{
	int n = vec.size();
	if (cur >= n)
		return;
	if (vec[cur] != -1)
	{
		*root = new BinaryTreeNode();
		(*root)->value = vec[cur];
		//(*root)->left = NULL;			//这里会默认值是null
		//(*root)->right = NULL;
		deLayerSerialize(&(*root)->left, vec, 2 * cur + 1);
		deLayerSerialize(&(*root)->right, vec, 2 * cur + 2);
	}
	else
		*root = NULL;
}
void testDeSerialize()
{
	vector<int> vec = { 1,2,4,-1,-1,-1,3,5,7,-1,-1,8,-1,-1,6,-1,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	dePreSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树


	vector<int> vec1 = { 1,2,3,4,-1,5,6,-1,-1,-1,-1,7,8,-1,-1 };
	BinaryTreeNode *root1;
	int cur1 = 0;
	deLayerSerialize(&root1, vec1, cur1);
	printTree(root1);
	cout << "\n\n\n";	//构建了一颗二叉树
}
//****************************************************************************************************************//




//根据前序和中序遍历序列来重建二叉树,为了方便递归，所以参数两个数组的头尾指针，返回值为构建好的二叉树的根节点
//****************************************************************************************************************//
BinaryTreeNode* rebuild(int *preLeft, int *preRight, int *midLeft, int *midRight)
{
	if (preLeft > preRight || midLeft > midRight)
		return NULL;
	BinaryTreeNode *root = new BinaryTreeNode();
	root->value = *preLeft;
	int *p = midLeft;
	for (; p <= midRight; p++)
		if (*p == *preLeft)
			break;
	if (p > midRight)
	{
		cout << "\n\n输入参数错误: \n";
		cout << "前序中的 " << root->value << " 在中序中找不到对应的数字 ! ! !\n\n\n";
		exit(-1);
	}
	root->left = rebuild(preLeft + 1, preLeft + (p - midLeft), midLeft, p - 1);
	root->right = rebuild(preLeft + (p - midLeft) + 1, preRight, p + 1, midRight);
	return root;
}
void testRebuild()
{
	vector<int> vec = { 1,2,3,4,-1,5,6,-1,7,-1,-1,-1,-1,8,-1 };
	cout << "先打印出这棵树: \n\n";
	BinaryTreeNode *root;
	deLayerSerialize(&root, vec, 0);
	printTree(root);


	int pre[8] = { 1,2,4,7,3,5,6,8 };
	int mid[8] = { 4,7,2,1,5,3,8,6 };
	BinaryTreeNode *root1 = rebuild(pre, pre + 7, mid, mid + 7);
	cout << "\n\n\n重建后的二叉树为: \n\n";
	printTree(root1);

}
//****************************************************************************************************************//




//递归和非递归求二叉树的深度
//****************************************************************************************************************//
int depth(BinaryTreeNode *root)
{
	if (root == NULL)
		return 0;
	int d = 0, i, n;
	queue<BinaryTreeNode*> que;
	BinaryTreeNode* node;
	que.push(root);
	while (!que.empty())
	{
		n = que.size();
		for (i = 0; i < n; i++)
		{
			node = que.front();
			que.pop();
			if (node->left != NULL)
				que.push(node->left);
			if (node->right != NULL)
				que.push(node->right);
		}
		++d;
	}
	return d;
}
int depthRecursion(BinaryTreeNode *root)
{
	if (root == NULL)
		return 0;
	int d1 = depthRecursion(root->left);
	int d2 = depthRecursion(root->right);
	return d1 > d2 ? d1 + 1 : d2 + 1;
}
void testDepth()
{
	vector<int> vec = { 1,2,4,-1,-1,-1,3,5,7,-1,-1,8,-1,-1,6,-1,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	dePreSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树

	cout << "depth(non recursion): " << depth(root);
	cout << "\n\ndepth(recursion): " << depthRecursion(root);
}
//****************************************************************************************************************//



//给出一个二叉树，求出它的镜像二叉树
//****************************************************************************************************************//
BinaryTreeNode *mirrorTree(BinaryTreeNode *root)
{
	if (root == NULL)
		return root;
	if (root->left == NULL && root->right == NULL)
		return root;
	BinaryTreeNode *tmp = root->left;
	root->left = root->right;
	root->right = tmp;
	if (root->left)
		mirrorTree(root->left);
	if (root->right)
		mirrorTree(root->right);
	return root;
}
void testMirrorTree()
{
	vector<int> vec = { 1,2,3,4,-1,5,6,-1,7,-1,-1,-1,-1,8,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树

	root = mirrorTree(root);
	cout << "\n\n该二叉树的镜像为：\n\n\n";
	printTree(root);
}
//****************************************************************************************************************//




//判断一个二叉树是否是对称的！！！
//一般的先序遍历是根节点之后再是左节点再是右节点，我们可以定义一种新的遍历方法就是根节点后先是右节点再是左节点
//然后同时判断这两者遍历过程中值是否是相等的
//****************************************************************************************************************//
bool isSymmetric(BinaryTreeNode *root1, BinaryTreeNode *root2)
{
	if (root1 == NULL && root2 == NULL)
		return true;
	else if (root1 == NULL || root2 == NULL)
		return false;
	if (root1->value != root2->value)
		return false;
	return isSymmetric(root1->left, root2->right) && isSymmetric(root1->right, root2->left);
}
void testIsSymmetric()
{
	//vector<int> vec = { 8,6,6,5,7,7,5 };
	vector<int> vec = { 7,7,7,7,5,5,7 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树

	cout << "它";
	if (isSymmetric(root, root))
		cout << "  是  ";
	else
		cout << "  不是  ";
	cout << "对称二叉树！！！";
}
//****************************************************************************************************************//




//判断一个序列是否是二叉搜索树的后续遍历结果
//方法是序列最后一个数是根节点，是否它将序列分成小于它和大于它的两部分....
//****************************************************************************************************************//
bool isBST(int *left, int *right)
{
	if (right <= left)
		return true;
	int root = *right;
	int *p = left, *tmp;
	for (; p < right; p++)
		if (*p > root)
			break;
	tmp = p;
	for (; tmp < right; tmp++)
		if (*tmp < root)
			return false;
	return isBST(left, p - 1) && isBST(p, right - 1);
}
void testIsBST()
{
	int a[7] = { 5,7,6,9,14,10,8 };
	int aa[7] = { 5,7,6,8 };
	int aaa[7] = { 9,14,10,8 };
	int b[] = { 7,4,5 };
	cout << isBST(a, a + 6) << "\n\n";
	cout << isBST(aa, aa + 6) << "\n\n";
	cout << isBST(aaa, aaa + 6) << "\n\n";
	cout << isBST(b, b + 2);
}
//****************************************************************************************************************//




//二叉树中和为某一值的路径
//****************************************************************************************************************//
void findPath(BinaryTreeNode *root, vector<int> &vec, int curSum, int sum)
{
	if (root == NULL)
		return;
	int value = root->value;
	vec.push_back(value);
	curSum += value;
	if (curSum == sum)
	{
		for (int &i : vec)
			cout << i << "--->";
		cout << "null" << "\n\n\n";
	}
	findPath(root->left, vec, curSum, sum);
	findPath(root->right, vec, curSum, sum);
	vec.pop_back();		//注意这里是在两个函数之后才pop处理！！！
	//curSum -= value;
}
void testFindPath()
{
	vector<int> vec = { 10,5,12,4,7,-1,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树

	vector<int>v;
	int curSum = 0;
	findPath(root, v, curSum, 22);
}
//****************************************************************************************************************//




//将一个二叉搜索树变成一个排序的双向链表
//方法是：原先指向左子节点的指针调整为指向前一个节点的指针，原先指向右节点的指针调整为指向最后一个结点的指针
//****************************************************************************************************************//
void convert(BinaryTreeNode* root, BinaryTreeNode **lastNode)
{
	if (root == NULL)
		return;
	convert(root->left, lastNode);
	root->left = *lastNode;
	if (*lastNode != NULL)
		(*lastNode)->right = root;
	*lastNode = root;
	convert(root->right, lastNode);
}
void testConvert()
{
	vector<int> vec = { 10,6,14,4,8,12,16 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树

	BinaryTreeNode *lastNode = NULL;
	convert(root, &lastNode);
	while (lastNode->left)
	{
		cout << lastNode->value << "<---";
		lastNode = lastNode->left;
	}
	cout << lastNode->value << endl;
	while (lastNode->right)
	{
		cout << lastNode->value << "--->";
		lastNode = lastNode->right;
	}
	cout << lastNode->value;
}
//****************************************************************************************************************//




//二叉搜索树的第k大的节点
//****************************************************************************************************************//
void kThNode(BinaryTreeNode* root, int k, int &cur)
{
	if (root == NULL || cur == k)
		return;
	kThNode(root->left, k, cur);
	++cur;				//所谓中序遍历，说明首次处理的节点一定是最左节点，只需要关注当前结点处理的位置即可
	if (cur == k)		//注意这里是在 kThNode(root->left, k, cur); 之后处理，在首次访问第一个value之前加一！！！！
	{
		cout << root->value << "  ";
		return;
	}
	kThNode(root->right, k, cur);
}
void testKNode()
{
	vector<int> vec = { 5,3,7,2,4,6,8 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树

	for (int i = 1; i <= 7; i++)
	{
		cur = 0;
		kThNode(root, i, cur);
	}

	int k;
	while (true)
	{
		cout << "\n\ninput k: ";
		cin >> k;
		if (k == -1)
			break;
		cur = 0;
		cout << "kth: ";
		kThNode(root, k, cur);
	}
}
//****************************************************************************************************************//




//判断是否是平衡二叉树,左右子树深度相差不超过1,该函数可以判断其root左右子树是否平衡，并且返回root所在深度
//****************************************************************************************************************//
bool isBalanceTree(BinaryTreeNode *root, int &deep)
{
	if (root == NULL)
		return true;
	int left = 0, right = 0;
	if (isBalanceTree(root->left, left) && isBalanceTree(root->right, right))
	{
		deep = left > right ? left + 1 : right + 1;
		cout << root->value << "  :  deep=" << deep << "   left-deep=" << left << "   right-deep=" << right << endl;
		if (abs(left - right) > 1)
			return false;
		return true;
	}
	return false;

}
void testIsBalanceTree()
{
	vector<int> vec = { 5,3,7,2,4,-1,9 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//构建了一颗二叉树

	int deep = 0;
	if (isBalanceTree(root, deep))
		cout << "\n is balanced ！！！";
	else
		cout << "\nnot balance ！！！";
}
//****************************************************************************************************************//




//判断一棵树是否是另一颗树的子结构
//分为两步：首先找到a中与b根节点相同的节点，然后判断是否包含b
//****************************************************************************************************************//
bool hasSubTree(BinaryTreeNode *root1, BinaryTreeNode *root2)
{
	if (root2 == NULL)
		return true;
	bool res = false;
	if (root1 != NULL && root2 != NULL)
	{
		if (root1->value == root2->value)
			res = tree1HasTree2(root1, root2);
		if (!res)
			res = hasSubTree(root1->left, root2);
		if (!res)
			res = hasSubTree(root1->right, root2);
	}
	return res;
}
bool tree1HasTree2(BinaryTreeNode *root1, BinaryTreeNode *root2)
{
	if (root2 == NULL)
		return true;
	if (root1 == NULL)
		return false;
	if (root1->value != root2->value)
		return false;
	return tree1HasTree2(root1->left, root2->left) && tree1HasTree2(root1->right, root2->right);
}
void testHasSubTree()
{
	vector<int> vec = { 8,8,7,9,2,-1,-1,-1,-1,4,7,-1,-1,-1,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n";

	vector<int> vec1 = { 8,9,2 };
	BinaryTreeNode *root1;
	int cur1 = 0;
	deLayerSerialize(&root1, vec1, cur1);
	printTree(root1);
	cout << "\n\n\n";

	if (hasSubTree(root, root1))
		cout << "树A包含树B";
	else
		cout << "树A不包含树B";

}
//****************************************************************************************************************//




//非递归的方式实现二叉树的三种遍历
//方法是
//****************************************************************************************************************//
void stackPreTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s)
{
	if (root == NULL)
		return;
	BinaryTreeNode *node = root;
	s.push(root);
	while (!s.empty())
	{
		node = s.top();
		s.pop();
		cout << node->value << "  ";
		if (node->right != NULL)
			s.push(node->right);
		if (node->left != NULL)
			s.push(node->left);
	}
}
void stackMidTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s)
{
	if (root == NULL)
		return;
	BinaryTreeNode *node = root;
	while (!s.empty() || node)
	{
		if (node != NULL)
		{
			s.push(node);
			node = node->left;
		}
		else
		{
			node = s.top();
			s.pop();
			cout << node->value << "   ";
			node = node->right;
		}
	}
}
//实现后序遍历有点麻烦，用两个栈，先将head压入s1中，然后从s1中弹出cur压入s2中，并将cur左右节点一次压入s1，然后重复该操作
//直到s1为空，打印出s2即是后序遍历结果
void stackAftTree(BinaryTreeNode *root, stack<BinaryTreeNode*> &s)
{
	if (root == NULL)
		return;
	BinaryTreeNode *node = root;
	s.push(root);
	stack<BinaryTreeNode*> s2;
	while (!s.empty())
	{
		node = s.top();
		s.pop();
		s2.push(node);
		if (node->left != NULL)
			s.push(node->left);
		if (node->right != NULL)
			s.push(node->right);
	}
	while (!s2.empty())
	{
		cout << s2.top()->value << "   ";
		s2.pop();
	}
}
void testStackTree()
{
	vector<int> vec = { 1,2,3,4,5,6,7 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";

	stack<BinaryTreeNode*> s;
	cout << "prePrint: ";
	stackPreTree(root, s);

	cout << "\n\nmidPrint: ";
	stackMidTree(root, s);

	cout << "\n\naftPrint: ";
	stackAftTree(root, s);
}
//****************************************************************************************************************//





//利用后序遍历序列重建二叉搜索树
//****************************************************************************************************************//
BinaryTreeNode *rebuildBST(int *left, int *right)
{
	if (right < left)
		return NULL;
	BinaryTreeNode *node = new BinaryTreeNode();
	node->value = *right;
	int *tmp = left;
	for (; tmp < right; tmp++)
		if (*tmp > *right)
			break;
	node->left = rebuildBST(left, tmp - 1);
	node->right = rebuildBST(tmp, right - 1);
	return node;
}
void testRebuildBst()
{
	vector<int> vec = { 5,3,7,2,4,6,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";

	int a[7] = { 2,4,3,6,7,5 };	//后序遍历的二叉搜索树
	BinaryTreeNode *root1 = rebuildBST(a, a + 5);
	printTree(root1);
}
//****************************************************************************************************************//