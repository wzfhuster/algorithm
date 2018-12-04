#include"printTree.h"

int getDeep(BinaryTreeNode *root)
{
	if (root == NULL)
		return 0;
	else
		return max(getDeep(root->left), getDeep(root->right)) + 1;
}

void printSpace(int n)
{
	while (n--)
		cout << " ";
}

void printTree(BinaryTreeNode *root)
{
	if (root == NULL) return;
	queue<BinaryTreeNode*> q;
	vector<BinaryTreeNode*> v;
	q.push(root);
	BinaryTreeNode *node;
	int deep = getDeep(root);
	int num = pow(2, deep) - 1;
	while (true)
	{
		node = q.front();
		q.pop();
		v.push_back(node);
		if (node != NULL)
		{
			if (node->left != NULL)
				q.push(node->left);
			else
				q.push(NULL);
			if (node->right != NULL)
				q.push(node->right);
			else
				q.push(NULL);
		}
		else
		{
			q.push(NULL);
			q.push(NULL);
		}
		if (v.size() == num) break;
	}

	int i = 0;
	for (int d = 1; d <= deep; ++d)
	{
		int cnum = pow(2, d - 1);  //每一层的层数
		int gap1 = pow(2, deep - d) - 1; //两个间隙
		int gap2 = pow(2, deep - d + 1) - 1;
		printSpace(gap1 + 3);
		for (int j = 0; j < cnum; ++j)
		{
			if (v[i] == NULL)
				//cout << "nan";
				cout << 'N';
			else
				cout << v[i]->value;
			++i;
			printSpace(gap2);
		}
		cout << endl << endl;
	}
	cout << endl;
}