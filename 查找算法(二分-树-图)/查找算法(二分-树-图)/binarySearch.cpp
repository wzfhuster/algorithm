#include"binarySearch.h"





//这里的left和right分别是数组的 [left,right], 考虑一下最终的情况即可，挺简单的
int binarySearch1(int *a, int left, int right, int k)
{
	if (a == NULL || left>right)
		return -1;
	int mid = (left + right)/2;
	if (a[mid] > k)
		return binarySearch1(a, left, mid - 1, k);
	else if (a[mid] < k)
		return binarySearch1(a, mid + 1, right, k);
	else
		return mid;
}


//一般递归的形式函数参数都会有left，right等，这里是非递归就只传入一个n即可
int binarySearch2(int *a, int n, int k)
{
	if (a == NULL)
		return -1;
	int left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] == k)
			return mid;
		else if (k < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}



//主要在于找到第一个和最后一个key，增加一个判断即可
int getFirstKey(int *a, int n, int k)
{
	if (a == NULL) return -1;
	int left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] == k)
		{
			if (mid > 0 && a[mid - 1] == k) //在这里增加一层判断
				right = mid - 1;
			else
				return mid;
		}
		else if (k < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
int getLastKey(int *a, int n, int k)
{
	if (a == NULL) return -1;
	int left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] == k)
		{
			if (mid < n - 1 && a[mid + 1] == k)
				left = mid + 1;
			else
				return mid;
		}
		else if (k < a[mid])
			right = mid - 1;
		else
			left = mid + 1;
	}
	return -1;
}
int countTimes(int *a, int n, int k)
{
	if (a == NULL) return -1;
	int left = getFirstKey(a, n, k);
	if (left == -1) return -1;
	int right = getLastKey(a, n, k);
	return right - left + 1;
}


//得到第一个大于某个数的数下标，思想就是在大于的时候多个判断即可
int getFirstGreater(int *a, int n, int k)
{
	if (a == NULL) return -1;
	int left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] > k)
		{
			if (mid > 0 && a[mid - 1] > k)
				right = mid - 1;
			else
				return mid;
		}
		else if (a[mid] <= k)
			left = mid + 1;
	}
	return -1;
}

//查找数组中小于某个数的最大下标，没有返回-1(或者加一个等号）
int getLastLower(int *a, int n, int k)
{
	if (a == NULL) return -1;
	int left = 0, right = n - 1, mid;
	while (left <= right)
	{
		mid = (left + right) / 2;
		if (a[mid] < k)
		{
			if (mid < n - 1 && a[mid + 1] < k)
				left = mid + 1;
			else
				return mid;
		}
		else if (a[mid] >= k)
			right = mid - 1;
	}
	return -1;
}