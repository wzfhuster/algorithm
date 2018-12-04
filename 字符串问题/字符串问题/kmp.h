//#pragma once
#include<iostream>
using namespace std;

//kmp�㷨�ؼ��������� next[]
//next Ҳ���Կ�������״̬�Զ�����״̬
//����ı����ĳ���Ϊn��ģʽ���ĳ���Ϊm��
//��ôƥ����̵�ʱ�临�Ӷ�ΪO(n)�����ϼ���next��O(m)ʱ�䣬KMP������ʱ�临�Ӷ�ΪO(m + n)


void getNext(char *p,int *next);

//�Ż��汾����next
//���� abab����ģʽ���е�bƥ��ʧ�ܵ�ʱ��j = next[j],aba��ǰ��׺����Ϊ1������j = 1����ȥ�жϣ�����p[j]=b,�϶�ʧ�ܡ�����
void getOptNext(char *p, int *next);

int kmpSearch(char *s, char *p, int *next);  //ʧ�ܷ���-1