#pragma once
#include<iostream>
#include<assert.h>

int myStrlen(const char *str);

//不考虑内存重叠的情况
char *myStrcpy1(char *dst, const char *src);
//考虑到内存重叠的情况，当 dst 位于src字符串中间的时候，需要从后向前复制
char *myStrcpy2(char *dst, const char *src);
char *myStrncpy(char *dst, const char *src, size_t n);
void *myMemcpy(void *dst, const void *src, size_t size);
//优化效率的myMemcpy
void *myMemcpy2(void *dst, const void *src, size_t size);


char *myStrcat(char *dst, const char *src);


int myStrcmp(const char *str1, const char *str2);
int memcmp(const void *buf1, const void *buf2, unsigned int count);
