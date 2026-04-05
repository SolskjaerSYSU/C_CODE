#define  _CRT_SECURE_NO_WARNINGS 1
#include "SList.h"

void SListTest01()
{
	//创建几个节点
	SLTNode* node1 = (SLTNode*)malloc(sizeof(SLTNode));
	node1->data = 1;

	SLTNode* node2 = (SLTNode*)malloc(sizeof(SLTNode));
	node2->data = 2;

	SLTNode* node3 = (SLTNode*)malloc(sizeof(SLTNode));
	node3->data = 3;

	SLTNode* node4 = (SLTNode*)malloc(sizeof(SLTNode));
	node4->data = 4;
	//将四个节点连接起来
	node1->next = node2;
	node2->next = node3;
	node3->next = node4;
	node4->next = NULL;
	
	//调用链表的打印
	SLTNode* plist = node1;
	SLTPrint(plist);
	//实现链表的尾删并检验
	SLTPopBack(&plist);//必须要传入plist的地址！
	SLTPrint(plist);
	//实现链表的头删并检验
	SLTPopFront(&plist);
	SLTPrint(plist);
}
void SListTest02()
{
	SLTNode* plist = NULL;//我们现在想让plist从一一个空指针变为指向头节点的指针，也就是指向我们生成的新节点newnode的指针
	SLTPushBack(&plist, 1);// 要传入的是plist的指针而不是plist！因为我们必须传指针调用,这样才能在函数中通过形参来改变实参
	//不然形参在函数中改变后就销毁了，根本无法影响到原来的plist，我们要把plist的地址传过去，让函数顺着这个地址修改plist里的值(原来plist指向NULL，修改后我们想让它指向newnode)
	SLTPrint(plist);
}
void SListTest03()
{
	/*SLTNode* plist = NULL;*/
	//
}
void SListTest01_Pro()
{
	SLTNode* plist = NULL;

	// 使用亲手写的尾插函数，快速构建链表
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);

	printf("初始链表: ");
	SLTPrint(plist); // 预期: 1->2->3->4->NULL

	printf("尾删一次: ");
	SLTPopBack(&plist);
	SLTPrint(plist); // 预期: 1->2->3->NULL

	printf("再尾删一次: ");
	SLTPopBack(&plist);
	SLTPrint(plist); // 预期: 1->2->NULL
}

int main()
{
	//SListTest01();
	//SListTest02();
	SListTest01_Pro();

	return 0;
}