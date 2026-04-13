#define  _CRT_SECURE_NO_WARNINGS 1
#include  "List.h"

LTNode* LTBuyNode(LTDataType x) //申请节点
{
	LTNode* newNode = (LTNode*)malloc(sizeof(LTNode));
	if (newNode == NULL)
	{
		perror("malloc fail!");
		exit(1);
	}
	newNode->data = x;
	newNode->next = newNode;
	newNode->prev = newNode;

	return newNode;
}

//初始化
void LTInit(LTNode** pphead) //传入一个地址（二级指针），里面存储了一个节点指针的地址，通过我们传入要初始化的链表的地址来修改phead，给它创建一个哨兵位
{
	//给双向链表创建一个哨兵位
	*pphead = LTBuyNode(-1);
}
//哨兵位的节点不能被删除，节点的地址也不能被改变!!(所以我们不改变哨兵位的地址，因此传一级指针即可——顺着这个指针修改哨兵位的前后指向)
//打印
void LTPrint(LTNode* phead)
{
	LTNode* pcur = phead->next; //把遍历链表的指针放在哨兵位下一位（第一个有效节点），这很重要！
	while (pcur !=phead) //避免陷入死循环，只打印有效节点
	{
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("\n");
}
//尾插
void LTPushBack(LTNode* phead,LTDataType x) //插入数据之前，链表必须初始化到只有一个头结点(哨兵位)的情况
{
	assert(phead); //不能没有哨兵位
	LTNode* newnode = LTBuyNode(x);
    //思路：为了不改变原链表里的节点，我们先改变newnode里的指向 尾节点
	newnode->prev = phead->prev; //妙手：用phead->prev来表示原链表的尾节点！
	newnode->next = phead; //指向phead本身即可，不用指向它（头节点）的prev或next

	phead->prev->next = newnode; //这句话相当于让尾节点的next指向newnode
	phead->prev = newnode;  //尾节点改为newnode 注意这两句顺序不能改变！

}
//头插 :注意是往第一个有效节点头插，不是往哨兵位头插！——往哨兵位尾插！
void LTPushFront(LTNode* phead, LTDataType x)
{
	assert(phead);
	LTNode* newnode = LTBuyNode(x);
	//思路：先让新节点指向哨兵位和原首节点
	newnode->prev = phead;
	newnode->next = phead->next;
	//然后我们先改newnode与原首节点，因为原首节点叫phead->next，不可改变顺序
	phead->next->prev = newnode;
	phead->next = newnode;

}

//尾删
void LTPopBack(LTNode* phead)
{
	//链表必须有效且链表不能为空  （链表为空时，只有一个哨兵位，若phead==NULL，则malloc初始化失败，它不是一个有效的双向链表）
	assert(phead && phead->next != phead); //前面是说链表有效，后面是说链表不为空，这很重要！
	LTNode* del = phead->prev;
	//如果我们销毁尾节点，会影响到尾节点的前一个节点和头节点   尾节点：del 
	del->prev->next= phead; //尾节点的前一个节点改为指向头节点
	phead->prev = del->prev; //头节点的prev改为指向尾节点的前一个节点
	//删除
	free(del);
	del = NULL;

}
//头删
void LTPopFront(LTNode* phead)
{
	assert(phead && phead->next != phead);
	LTNode* del = phead->next; //原第一个节点：del
	//如果我们删除第一个有效节点，会影响到del->next和哨兵位phead
	phead->next = del->next;
	del->next->prev = phead;
	//删除
	free(del);
	del = NULL;
}
//总结：删除不同于插入函数，删除只要改变两个指针的指向，删除的节点指向不需要改变，总共2次；而插入函数要改变原位置前后两个节点的指向和新节点的两边指向，总共4次

//查找值为x的节点
LTNode* LTFind(LTNode* phead, LTDataType x)
{
	LTNode* pcur = phead->next; //从第一个有效节点开始查找
	while (pcur != phead)
	{
		if (pcur->data == x)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	//没有找到
	return NULL;
}

//在pos位置之后插入数据 ---与Find函数一起搭配使用（得找到pos地址才好插入）
void LTInsert(LTNode* pos, LTDataType x)
{
	LTNode* newnode = LTBuyNode(x);
	newnode->prev = pos;
	newnode->next = pos->next;
	//一定要先修改原pos的下一个节点的prev
	pos->next->prev = newnode;
	pos->next = newnode;

}
//删除pos位置的节点
void LTErase(LTNode* pos)
{
	assert(pos);
	// 理论上还应该 assert(pos != phead)，因为哨兵位绝对不能删！
	// 但因为这里没传 phead，我们需要在调用时自己注意。

	LTNode* posPrev = pos->prev; // 提取出 pos 前面的节点
	LTNode* posNext = pos->next; // 提取出 pos 后面的节点

	// 1. 让前面的节点指向后面的节点
	posPrev->next = posNext;

	// 2. 让后面的节点指向前面的节点
	posNext->prev = posPrev;

	// 3. 抹杀 pos
	free(pos);
	// pos = NULL; // 注意：由于这里传的是一级指针，置空只在函数内部有效，但这依然是个好习惯。
}
