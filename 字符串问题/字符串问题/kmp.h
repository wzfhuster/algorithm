//#pragma once
#include<iostream>
using namespace std;

//kmp算法关键是在求其 next[]
//next 也可以看作有限状态自动机的状态
//如果文本串的长度为n，模式串的长度为m，
//那么匹配过程的时间复杂度为O(n)，算上计算next的O(m)时间，KMP的整体时间复杂度为O(m + n)


void getNext(char *p,int *next);

//优化版本的求next
//比如 abab，当模式串中的b匹配失败的时候，j = next[j],aba中前后缀长度为1，所以j = 1，再去判断，但是p[j]=b,肯定失败。。。
void getOptNext(char *p, int *next);

int kmpSearch(char *s, char *p, int *next);  //失败返回-1