#include"tree.h"
using namespace std;




int *fun(int *a)
{
	cout << "p2: " << &a<<"---"<<*a<<endl;
	return a;
}

int main()
{
	//����ָ��Ҳ�Ǹ������ڲ���������������ڴ�ռ�ĵ�ַ
	//int a = 3;
	//int *p = &a;
	//cout << "p1: " << &p << "---" << *p << endl << endl;
	//int *p3 = fun(p);
	//cout << "p3: " << &p3 << "---" << *p3 << endl << endl;
	//

	//testSerialize();
	//testDeSerialize();
	//testDepth();
	//testRebuild();
	//testMirrorTree();
	//testIsSymmetric();
	//testIsBST();
	testFindPath();
	//testConvert();
	//testKNode();
	//testIsBalanceTree();
	//testHasSubTree();
	//testStackTree();
	//testRebuildBst();

	cout << "\n\n\n\n";
	return 0;
}