#pragma once
#include<iostream>
#include<assert.h>

int myStrlen(const char *str);

//�������ڴ��ص������
char *myStrcpy1(char *dst, const char *src);
//���ǵ��ڴ��ص���������� dst λ��src�ַ����м��ʱ����Ҫ�Ӻ���ǰ����
char *myStrcpy2(char *dst, const char *src);
char *myStrncpy(char *dst, const char *src, size_t n);
void *myMemcpy(void *dst, const void *src, size_t size);
//�Ż�Ч�ʵ�myMemcpy
void *myMemcpy2(void *dst, const void *src, size_t size);


char *myStrcat(char *dst, const char *src);


int myStrcmp(const char *str1, const char *str2);
int memcmp(const void *buf1, const void *buf2, unsigned int count);
