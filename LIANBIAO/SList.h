#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int SLTDataType;
typedef struct SListNode
{
	SLTDataType	data;
	struct SListNode* next;
}SLTNode;

void SLTPrint(SLTNode* phead);
void SLTPushBack(SLTNode** pphead, SLTDataType x);
void SLTPushFront(SLTNode** pphead, SLTDataType x);
void SLTPopBack(SLTNode** pphead);
void SLTPopFront(SLTNode** pphead);
SLTNode* SLTFind(SLTNode* phead, SLTDataType x);
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x);
void SLTInsertAfter(SLTNode* pos, SLTDataType x);
void SLTErase(SLTNode** pphead, SLTNode* pos);
void SLTDestroy(SLTNode** pphead);