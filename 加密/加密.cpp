// 加密.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "asm.h"

#define enCryPtion 1
#define deCode 0


#define calcLen1(x) (*((int *)x)*4) 
#define calcLen2(x) (*((int *)x)/4) 


void *_decode(void *a, void * b, void * c);

//a source   b len  c key
void *_1(void *a, void * b, void * c)
{
	char * v1 = (char *)a;
	int v3 = *(int *)b;
	void *v4 = c;
	void *vv = (void *)_VirtualAlloc(v3);

	char *r = (char *)vv;
	int v2 = 0;

	while (v2 < v3)
	{
		_xorCore(v1, v4, r);
		v1++, r++, v2++;
	}
	return vv;
}
//a source b r
void _2_1_1(void **a, void **b)
{
	void * p1 = *a, *p2 = *b;

	DWORD v1 = (*(char *)p1) << 1;
	*(int *)p2 = v1;

	*((char *)a) += 1;
	*((char *)b) += 4;

}

//a ->source  b ->len
void *_2_1(void *a, void *b)
{
	int i1 = 0;
	int v1 = *(int *)b;
	void * v2 = _VirtualAlloc(v1 * 4);

	void *v3 = v2;
	while (i1 < v1)
	{
		_2_1_1(&a, &v3);
		i1++;
	}
	return v2;
}

//a source b r
void _2_2_1(void **a, void **b)
{
	void * p1 = *a, *p2 = *b;

	char v1 = (char)((*(int *)p1) >> 1);
	*((char *)p2) = v1;



	*((char *)a) += 4;
	*((char *)b) += 1;
}

//a ->source  b ->len
void *_2_2(void *a, void *b)
{
	int i1 = 0;
	int v1 = *(int *)b;
	void * v2 = _VirtualAlloc(v1 / 4);
	void * v3 = v2;
	while (i1 < v1)
	{
		_2_2_1(&a, &v3);
		i1++;
	}
	return v2;
}

//1.enCryPtion  2.deCode
//a ->source  b ->len c->falg
void *_2(void *a, void *b, int c)
{
	void * v1;
	if (c == enCryPtion)
	{
		v1 = _2_1(a, b);
	}


	if (c == deCode)
	{
		v1 = _2_2(a, b);
	}
	return v1;
}


//a->需要加密的数据 b->len  c->key
//return 加密后的数据
/*
1.a与c xor fn:_xor()
2.每一字节 分配4字节为单位  左移1位
3.xor c

*/
//a->开始地址 b->len c->key
void *_encryption(void *a, void * b, void * c)
{
	void *v1, *v2, *v3;

	/****************************************************************************************************1*********************************************************************************************************/
	v1 = _1(a, b, c);
	/****************************************************************************************************2*********************************************************************************************************/
	v2 = _2(v1, b, enCryPtion);
	/****************************************************************************************************3*********************************************************************************************************/
	void *v4 = _VirtualAlloc(4);
	*(int*)v4 = calcLen1(b);

	v3 = _1(v2, v4, c);



	return v3;

}


//a->需要解密的数据 b->len  c->key
//return 解密后的数据
/*
	1.xor c
	2.每四字节 右移一位 取第一个字节
	3.xor c
	*/
void *_decode(void *a, void * b, void * c)
{
	void *v1, *v2, *v3;
	/****************************************************************************************************1*********************************************************************************************************/
	v1 = _1(a, b, c);
	/****************************************************************************************************2*********************************************************************************************************/
	v2 = _2(v1, b, deCode);
	/****************************************************************************************************3*********************************************************************************************************/
	void *v4 = _VirtualAlloc(4);
	*(int*)v4 = calcLen2(b);


	v3 = _1(v2, v4, c);

	return v3;
}




void * _tmain(void * argc, _TCHAR* argv[])
{

	int * v1 = (int *)_VirtualAlloc(4);
	int * v2 = (int *)_VirtualAlloc(4);
	int * v2_2 = (int *)_VirtualAlloc(4);
	int * v3 = (int *)_VirtualAlloc(4);
	void *vv1, *vv2;

	char *n1 = "ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!ccc!cc";
	*v1 = strlen(n1);
	*v2 = 0x55;
	//加密测试
	vv1 = _encryption(n1, v1, v2);



	*v2_2 = 0x55;
	*v3 = strlen((char *)vv1);
	vv2 = _decode(vv1, v3, v2_2);


	printf("%s\n", (char *)vv2);
	getchar();
	return 0;
}

