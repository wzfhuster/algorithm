#include"kmp.h"


//普通的next
void getNext(char *p, int *next)
{
	int n = strlen(p);
	memset(next, 0, n);
	next[0] = -1;
	int i = -1, j = 0;
	while (j<n-1)
	{
		if (i == -1 || p[i] == p[j])
		{
			++i;
			++j;
			next[j] = i;
		}
		else
			i = next[i];
	}
}



//优化版本的求next
void getOptNext(char *p, int *next)
{
	int n = strlen(p);
	memset(next, 0, n);
	next[0] = -1;
	int i = -1, j = 0;
	while (j<n-1)
	{
		if (i == -1 || p[i] == p[j])
		{
			++i;
			++j;
			if (p[i] != p[j])
				next[j] = i;
			else
				next[j] = next[i];
		}
		else
			i = next[i];
	}
}



//失败返回-1
int kmpSearch(char *s, char *p, int *next)
{
	int sn = strlen(s);
	int pn = strlen(p);
	int i = 0, j = 0;
	while (i<sn && j<pn)
	{
		if (j == -1 || s[i] == p[j])
		{
			++i;
			++j;
		}
		else
			j = next[j];
	}
	if (j == pn)
		return i - j;
	return -1;
}