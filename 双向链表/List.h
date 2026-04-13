#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

typedef int LTDataType;
//定义双向链表节点的结构
typedef struct ListNode
{
	LTDataType data;
	struct ListNode* next;
	struct ListNode* prev;
}LTNode;

//声明双向链表中提供的方法

//初始化
void LTInit(LTNode** pphead);

void LTPushBack(LTNode* phead, LTDataType x); //插入数据之前，链表必须初始化到只有一个头结点(哨兵位)的情况
void LTPrint(LTNode* phead);
void LTPushFront(LTNode* phead, LTDataType x);
void LTPopBack(LTNode* phead);   //尾删函数
void LTPopFront(LTNode* phead);  //头删函数
void LTInsert(LTNode* pos, LTDataType x); //在指定位置插入
void LTErase(LTNode* pos); //在指定位置删除
LTNode* LTFind(LTNode* phead, LTDataType x);  //查找函数