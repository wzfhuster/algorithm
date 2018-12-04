#pragma once
#include<iostream>
using namespace std;


//���ֲ��Ҵ�ǰ��������������н�������ģ����Ӷ�Ϊ : O(logn)



//1.����ĳ�������±� (�ݹ�汾��
int binarySearch1(int *a, int left, int right, int k);
//1.����ĳ�������±� (�ǵݹ�汾��
int binarySearch2(int *a, int n, int k);



//2.���������в���ĳ��Ԫ�س��ֵĴ���
//  ��1����ͨ���ֲ��ҵ�һ��key��Ȼ��ֱ������߼��ȷ������
//	��2������һ��ȱ�������һ��Ԫ���ظ������ӽ�n����ô���Ӷ��˻��� O��n���ˣ�������ͷβ��key�����
//				����һ�Ƚϼ�����ʵ��һ�·�������
int getFirstKey(int *a, int n, int k);   //��ȡ����ظ�k�ĵ�һ��k���±�
int getLastKey(int *a, int n, int k);    //��ȡ����ظ�k�����һ��k���±�
int countTimes(int *a, int n, int k);




//3.���ҵ�һ������ĳ�������±꣨���ߴ��ڵ���ĳ�������±�˼��һ��һ���ģ�
int getFirstGreater(int *a, int n, int k);
//3.����������С��ĳ����������±꣬û�з���-1(���߼�һ���Ⱥţ�
int getLastLower(int *a, int n, int k);


