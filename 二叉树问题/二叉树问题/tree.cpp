#include"tree.h"


//4�����л��������ķ���
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
			for (i = 0; i < n; i++)		//�ų����һ��ȫΪNULL�Ĳ���
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
	cout << "\n\n\n";	//������һ�Ŷ�����


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




//4�ַ����л��ķ���
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
	*root = new BinaryTreeNode();	//ָ��Ҳ��һ����������洢�����������ڴ�ĵ�ַ������ void fun(int *p2); fun(p1);
	(*root)->value = vec[cur];		//����p1��p2���������������ӣ����Ǻ�������װ����ͬһ���ڴ��ַ�������Ǹı�p2��������ĵ�ַʱ��p1�����ڵ�ַ������
	dePreSerialize(&(*root)->left, vec, ++cur);		//������������ **root������fun(int **p2); p2��������װ����p1�ĵ�ַ�������Ϳ��Ըı�p1��������ĵ�ַ��
	dePreSerialize(&(*root)->right, vec, ++cur);	//����һ����� root->left = p; ���ǰ�p������������ݸ��Ƹ�left���ӡ�������
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
		//(*root)->left = NULL;			//�����Ĭ��ֵ��null
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
	cout << "\n\n\n";	//������һ�Ŷ�����


	vector<int> vec1 = { 1,2,3,4,-1,5,6,-1,-1,-1,-1,7,8,-1,-1 };
	BinaryTreeNode *root1;
	int cur1 = 0;
	deLayerSerialize(&root1, vec1, cur1);
	printTree(root1);
	cout << "\n\n\n";	//������һ�Ŷ�����
}
//****************************************************************************************************************//




//����ǰ�����������������ؽ�������,Ϊ�˷���ݹ飬���Բ������������ͷβָ�룬����ֵΪ�����õĶ������ĸ��ڵ�
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
		cout << "\n\n�����������: \n";
		cout << "ǰ���е� " << root->value << " ���������Ҳ�����Ӧ������ ! ! !\n\n\n";
		exit(-1);
	}
	root->left = rebuild(preLeft + 1, preLeft + (p - midLeft), midLeft, p - 1);
	root->right = rebuild(preLeft + (p - midLeft) + 1, preRight, p + 1, midRight);
	return root;
}
void testRebuild()
{
	vector<int> vec = { 1,2,3,4,-1,5,6,-1,7,-1,-1,-1,-1,8,-1 };
	cout << "�ȴ�ӡ�������: \n\n";
	BinaryTreeNode *root;
	deLayerSerialize(&root, vec, 0);
	printTree(root);


	int pre[8] = { 1,2,4,7,3,5,6,8 };
	int mid[8] = { 4,7,2,1,5,3,8,6 };
	BinaryTreeNode *root1 = rebuild(pre, pre + 7, mid, mid + 7);
	cout << "\n\n\n�ؽ���Ķ�����Ϊ: \n\n";
	printTree(root1);

}
//****************************************************************************************************************//




//�ݹ�ͷǵݹ�������������
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
	cout << "\n\n\n";	//������һ�Ŷ�����

	cout << "depth(non recursion): " << depth(root);
	cout << "\n\ndepth(recursion): " << depthRecursion(root);
}
//****************************************************************************************************************//



//����һ����������������ľ��������
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
	cout << "\n\n\n";	//������һ�Ŷ�����

	root = mirrorTree(root);
	cout << "\n\n�ö������ľ���Ϊ��\n\n\n";
	printTree(root);
}
//****************************************************************************************************************//




//�ж�һ���������Ƿ��ǶԳƵģ�����
//һ�����������Ǹ��ڵ�֮��������ڵ������ҽڵ㣬���ǿ��Զ���һ���µı����������Ǹ��ڵ�������ҽڵ�������ڵ�
//Ȼ��ͬʱ�ж������߱���������ֵ�Ƿ�����ȵ�
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
	cout << "\n\n\n";	//������һ�Ŷ�����

	cout << "��";
	if (isSymmetric(root, root))
		cout << "  ��  ";
	else
		cout << "  ����  ";
	cout << "�Գƶ�����������";
}
//****************************************************************************************************************//




//�ж�һ�������Ƿ��Ƕ����������ĺ����������
//�������������һ�����Ǹ��ڵ㣬�Ƿ��������зֳ�С�����ʹ�������������....
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




//�������к�Ϊĳһֵ��·��
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
	vec.pop_back();		//ע������������������֮���pop��������
	//curSum -= value;
}
void testFindPath()
{
	vector<int> vec = { 10,5,12,4,7,-1,-1 };
	BinaryTreeNode *root;
	int cur = 0;
	deLayerSerialize(&root, vec, cur);
	printTree(root);
	cout << "\n\n\n";	//������һ�Ŷ�����

	vector<int>v;
	int curSum = 0;
	findPath(root, v, curSum, 22);
}
//****************************************************************************************************************//




//��һ���������������һ�������˫������
//�����ǣ�ԭ��ָ�����ӽڵ��ָ�����Ϊָ��ǰһ���ڵ��ָ�룬ԭ��ָ���ҽڵ��ָ�����Ϊָ�����һ������ָ��
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
	cout << "\n\n\n";	//������һ�Ŷ�����

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




//�����������ĵ�k��Ľڵ�
//****************************************************************************************************************//
void kThNode(BinaryTreeNode* root, int k, int &cur)
{
	if (root == NULL || cur == k)
		return;
	kThNode(root->left, k, cur);
	++cur;				//��ν���������˵���״δ���Ľڵ�һ��������ڵ㣬ֻ��Ҫ��ע��ǰ��㴦���λ�ü���
	if (cur == k)		//ע���������� kThNode(root->left, k, cur); ֮�������״η��ʵ�һ��value֮ǰ��һ��������
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
	cout << "\n\n\n";	//������һ�Ŷ�����

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




//�ж��Ƿ���ƽ�������,�����������������1,�ú��������ж���root���������Ƿ�ƽ�⣬���ҷ���root�������
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
	cout << "\n\n\n";	//������һ�Ŷ�����

	int deep = 0;
	if (isBalanceTree(root, deep))
		cout << "\n is balanced ������";
	else
		cout << "\nnot balance ������";
}
//****************************************************************************************************************//




//�ж�һ�����Ƿ�����һ�������ӽṹ
//��Ϊ�����������ҵ�a����b���ڵ���ͬ�Ľڵ㣬Ȼ���ж��Ƿ����b
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
		cout << "��A������B";
	else
		cout << "��A��������B";

}
//****************************************************************************************************************//




//�ǵݹ�ķ�ʽʵ�ֶ����������ֱ���
//������
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
//ʵ�ֺ�������е��鷳��������ջ���Ƚ�headѹ��s1�У�Ȼ���s1�е���curѹ��s2�У�����cur���ҽڵ�һ��ѹ��s1��Ȼ���ظ��ò���
//ֱ��s1Ϊ�գ���ӡ��s2���Ǻ���������
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





//���ú�����������ؽ�����������
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

	int a[7] = { 2,4,3,6,7,5 };	//��������Ķ���������
	BinaryTreeNode *root1 = rebuildBST(a, a + 5);
	printTree(root1);
}
//****************************************************************************************************************//