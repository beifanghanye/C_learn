#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "kmp.h"

// 获取 next 数组
int* get_next(char* s)
{
	if (!s)
	{
		printf("Parameter error: s cannot be NULL\n");
		return NULL;
	}

	int len = strlen(s);
	int* next = (int*)malloc(sizeof(int) * len);
	if (!next)
	{
		printf("Memory allocation failed\n");
		return NULL;
	}

	int i = 0;
	int j = -1;
	next[0] = -1;

	while (i < len)
	{
		if (j == -1 || s[j] == s[i])
		{
			i++;
			j++;
			next[i] = j;
		}
		else
		{
			j = next[j];
		}
	}

	return next;
}

// kmp 算法
int kmp(char* s, char* t, int pos)
{
	int ret = -1;

	if (!s || !t)
	{
		printf("Parameter error: s and t cannot be NULL\n");
		return -1;
	}

	int* next = get_next(t);

	int i = pos;
	int j = 0;

	while (s[i] != '\0' && t[j] != '\0')
	{
		if (s[i] == t[j])
		{
			i++;
			j++;
		}
		else
		{
			j = next[j];
			if (j == -1)
			{
				i++;
				j++;
			}
		}
	}

	if (t[j] == '\0')
	{
		ret = i - j;
	}
	else
	{
		ret = -1;
	}
	
	return ret;
}

// 字符串输入
char* get_s()
{
	int buffer = 8;		// 缓冲区长度
	int len = 0;			// 字符串长度

	// 初始化缓冲区
	char* ret = (char*)malloc(sizeof(char) * buffer);
	if (!ret)
	{
		printf("Memory allocation failed\n");
		return NULL;
	}

	// 用于读取字符
	char c;


	while ((c = fgetc(stdin)) && (c != '\n' && c != EOF))
	{
		// 逐个读取字符，当输入回车或遇到终止符时结束输入
		ret[len++] = c;

		if (len + 1 > buffer)
		{
			//缓冲区满， 扩充缓冲区
			buffer *= 2;
			char* newRet = (char*)realloc(ret, sizeof(char) * buffer);
			if (!newRet)
			{
				printf("Memory reallocation failed, the result has been return\n");
				ret[len] = '\0';
				return ret;
			}

			ret = newRet;
		}
	}
	ret[len] = '\0';

	return ret;
}

