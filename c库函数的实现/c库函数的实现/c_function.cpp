#include"c_function.h"

int myStrlen(const char *str)
{
	assert(str!=NULL);
	int i = 0;
	while (*str++) ++i;
	return i;
}


//�������ڴ��ص������
char *myStrcpy1(char *dst, const char *src)
{
	assert(dst);
	assert(src);
	char *d = dst;
	while ((*d++ = *src++)!='\0');
	return dst;
}
//���ǵ��ڴ��ص���������� dst λ��src�ַ����м��ʱ���Ǵ���ģ�����null
char *myStrcpy2(char *dst, const char *src)
{
	assert(dst != src);
	assert(dst != NULL && src!=NULL);
	int n1=0, n2=0;
	char *d;
	const char *s;
	while (*d++) ++n1;
	while (*s++) ++n2;
	d = dst;
	if (dst > src && dst < src + n2)
		return NULL;
	else
		while ((*d++ = *src++) != '\0');
	return dst;
}

char *myStrncpy(char *dst, const char *src, size_t n)
{
	char *d = dst;
	int i = 0;
	while (i++ < n && (*d++ = *src++) != '\0');
	if ((*d)!='\0')
		*d = '\0';
	return dst;
}
//memû��memncpy��memncmp������
void *myMemcpy(void *dst,const void *src, size_t size)
{
	assert(dst != NULL && src != NULL);
	assert(dst != src);
	char *tmpd = (char*)dst;
	char *tmps = (char*)src;
	if (tmpd > tmps && tmpd < tmps + size)
	{
		tmpd += size;
		tmps += size;
		while (size--)
			*--tmpd = *--tmps;
	}
	else
		while (size--)
			*tmpd++ = *tmps++;
	return dst;
}
//�Ż�Ч�ʵ�myMemcpy
void *myMemcpy2(void *dst, const void *src, size_t size)
{
	int i = size / sizeof(int);
	int j = size % sizeof(int);
	int *int_dst = (int *)dst;
	int *int_src = (int *)src;
	char *ch_dst = (char *)dst;
	char *ch_src = (char*)src;
	if (ch_dst > ch_src && ch_dst < ch_src + size)
	{
		int_dst = (int *)(ch_dst + size);
		int_src = (int *)(ch_src + size);
		while (i--)
			*--int_dst = *--int_src;	//��������״�int��4���ֽ�һ�ο�����Ӧ���ȼ���С4�ֽڵ�ַ����������
		ch_dst = (char*)int_dst;
		ch_src = (char*)int_src;
		while (j--)
			*ch_dst-- = *ch_src--;
	}
	else
	{
		while (i--)
			*int_dst++ = *int_src++;
		ch_dst = (char*)int_dst;
		ch_src = (char*)int_src;
		while (j--)
			*ch_dst++ = *ch_src++;
	}
	return dst;
}




int myStrcmp(const char *str1, const char *str2)
{
	assert(str1 != NULL && str2 != NULL);
	while (*str1++ && *str2++)
		if (*str1 > *str2)
			return 1;
		else if (*str1 < *str2)
			return -1;
	return 0;
}

int memcmp(const void *buf1, const void *buf2, unsigned int count)
{
	char *ch1 = (char*)buf1;
	char *ch2 = (char*)buf2;
	while (count && (*ch1 == *ch2))
	{
		++ch1;
		++ch2;
		--count;	//����һ��Ҫע��count�����ڲ�������ֹ���ж����һ���ַ���ʱ���������
	}
	if (count == 0) return 0;
	if (*ch1 < *ch2)
		return -1;
	else
		return 1;
}




char *myStrcat(char *dst, const char *src)
{
	assert(dst != NULL && src != NULL);
	char *res = dst;
	while (*dst) ++dst;
	while ((*dst++ = *src++) != '\0');
	return res;
}