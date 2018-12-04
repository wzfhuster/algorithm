#pragma once
#include<iostream>
using namespace std;


//二分查找大前提是针对有序数列进行排序的，复杂度为 : O(logn)



//1.查找某个数的下标 (递归版本）
int binarySearch1(int *a, int left, int right, int k);
//1.查找某个数的下标 (非递归版本）
int binarySearch2(int *a, int n, int k);



//2.有序数组中查找某个元素出现的次数
//  （1）普通二分查找到一个key，然后分别向两边检查确定次数
//	（2）方法一的缺点是如果一个元素重复次数接近n，那么复杂度退化成 O（n）了，可以找头尾的key再相减
//				方法一比较简单这里实现一下方法二：
int getFirstKey(int *a, int n, int k);   //获取多个重复k的第一个k的下标
int getLastKey(int *a, int n, int k);    //获取多个重复k的最后一个k的下标
int countTimes(int *a, int n, int k);




//3.查找第一个大于某个数的下标（或者大于等于某个数的下标思想一样一样的）
int getFirstGreater(int *a, int n, int k);
//3.查找数组中小于某个数的最大下标，没有返回-1(或者加一个等号）
int getLastLower(int *a, int n, int k);


