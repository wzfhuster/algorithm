#include<iostream>
#include<map>

using namespace std;

struct ListNode
{
	int value;
	struct ListNode* next;
};


void reverseList(ListNode **head);   //翻转链表
ListNode* reverseList2(ListNode *head, ListNode **newHead);   //翻转链表, 递归版本,函数返回反转后的头结点

void testListBubbleSort();	//链表冒泡排序
void testMergeList();		//合并两个链表
void testListMergeSort();   //链表归并排序
void printList(ListNode *head);


int main()
{
	ListNode *a[5];
	for (int i = 0; i < 5; i++)
	{
		a[i] = new ListNode();
		a[i]->value = i + 1;
	}
	a[0]->next = a[1];
	a[1]->next = a[2];
	a[2]->next = a[3];
	a[3]->next = a[4];
	a[4]->next = NULL;

	printList(a[0]);

	reverseList(&a[0]);
	printList(a[0]);
	reverseList2(a[0], &a[0]);

	printList(a[0]);

	return 0;
}



void reverseList(ListNode **head)
{
	ListNode *p1 = *head;
	if (p1 == NULL || p1->next == NULL)
		return;
	ListNode *p2 = p1->next;
	ListNode *p3 = p2->next;
	p1->next = NULL;
	while (p2)
	{
		p2->next = p1;
		p1 = p2;
		p2 = p3;
		if(p2)
			p3 = p2->next;
	}
	*head = p1;
}

ListNode* reverseList2(ListNode *head, ListNode **newHead)
{
	if (head == NULL || head->next == NULL)
	{
		*newHead = head;
		if (head)
			head->next = NULL;
		return head;
	}
	ListNode *tail = reverseList2(head->next, newHead);
	tail->next = head;
	head->next = NULL;
	return head;
}

void printList(ListNode *head)
{
	cout << endl;
	while (head)
	{
		cout << head->value << "---->";
		head = head->next;
	}
	cout << "NULL" << endl;
}