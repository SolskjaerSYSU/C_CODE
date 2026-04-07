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
void SListTest02_Pro()//综合测试 插入 删除 寻找函数
{
	SLTNode* plist = NULL;

	// 1. 构建初始链表
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);

	printf("初始链表: ");
	SLTPrint(plist); // 预期: 1->2->3->4->NULL

	// 2. 测试查找存在的节点
	printf("\n--- 测试查找 ---\n");
	int search_val = 3;
	SLTNode* ret = SLTFind(plist, search_val);

	if (ret != NULL)
	{
		printf("成功找到节点，其值为: %d\n", ret->data);

		// 查找函数最强大的地方：找到后可以直接修改它！
		printf("尝试将找到的节点值修改为 300...\n");
		ret->data = 300;

		printf("修改后的链表: ");
		SLTPrint(plist); // 预期: 1->2->300->4->NULL
	}
	else
	{
		printf("未找到值为 %d 的节点\n", search_val);
	}

	// 3. 测试查找不存在的节点
	printf("\n--- 测试查找不存在的节点 ---\n");
	SLTNode* ret_none = SLTFind(plist, 99);
	if (ret_none == NULL)
	{
		printf("查找 99 失败：返回了空指针，符合预期！\n");
	}
}
void SListTest03_Pro()
{
	SLTNode* plist = NULL;

	// 1. 构建初始链表
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);

	printf("初始链表: ");
	SLTPrint(plist); // 预期: 1->2->3->4->NULL

	// 2. 测试正常情况：在节点 '3' 之前插入 '30'
	printf("\n--- 测试在中间插入 ---\n");
	SLTNode* pos3 = SLTFind(plist, 3); // 先用Find函数找到值为3的节点
	if (pos3 != NULL)
	{
		SLTInsert(&plist, pos3, 30);
		printf("在3之前插入30后: ");
		SLTPrint(plist); // 预期: 1->2->30->3->4->NULL
	}

	// 3. 测试特殊情况：在节点 '1' (头节点) 之前插入 '10'
	printf("\n--- 测试在头节点前插入 (极限测试) ---\n");
	SLTNode* pos1 = SLTFind(plist, 1); // 找到第一个节点
	if (pos1 != NULL)
	{
		SLTInsert(&plist, pos1, 10);
		printf("在1之前插入10后: ");
		SLTPrint(plist); // 预期: 10->1->2->30->3->4->NULL
	}
	SLTNode* pos2 = SLTFind(plist, 30);
	SLTInsertAfter(pos2, 40);
	printf("在30之后插入40后：");
	SLTPrint(plist);
}
void SListTest04_Pro()
{
	SLTNode* plist = NULL;

	// 1. 构建初始链表
	SLTPushBack(&plist, 1);
	SLTPushBack(&plist, 2);
	SLTPushBack(&plist, 3);
	SLTPushBack(&plist, 4);

	printf("初始链表: ");
	SLTPrint(plist); // 预期: 1->2->3->4->NULL

	// 2. 测试正常情况：删除中间的节点 '3'
	printf("\n--- 测试删除中间节点 ---\n");
	SLTNode* pos3 = SLTFind(plist, 3); // 先找到值为3的节点地址
	if (pos3 != NULL)
	{
		SLTErase(&plist, pos3);
		printf("删除节点3之后: ");
		SLTPrint(plist); // 预期: 1->2->4->NULL
	}

	// 3. 测试极限情况：删除头节点 '1'
	printf("\n--- 测试删除头节点 ---\n");
	SLTNode* pos1 = SLTFind(plist, 1); // 找到第一个节点
	if (pos1 != NULL)
	{
		SLTErase(&plist, pos1);
		printf("删除头节点1之后: ");
		SLTPrint(plist); // 预期: 2->4->NULL
	}
}
void SListTest05_Pro()
{
	SLTNode* plist = NULL;

	// 1. 构建一个有点长度的链表
	SLTPushBack(&plist, 10);
	SLTPushBack(&plist, 20);
	SLTPushBack(&plist, 30);
	SLTPushBack(&plist, 40);

	printf("销毁前的链表: ");
	SLTPrint(plist); // 预期: 10->20->30->40->NULL

	// 2. 调用销毁函数
	printf("\n执行销毁操作...\n");
	SLTDestroy(&plist);

	// 3. 验证销毁结果
	printf("销毁后的链表: ");
	SLTPrint(plist); // 预期: 打印出类似 "NULL" 或什么都不打印 (取决于你的 SLTPrint 实现)

	// 这里可以加一个判断来彻底证明头指针已经被安全置空
	if (plist == NULL)
	{
		printf("-> 测试通过：链表已彻底销毁，且 plist 被安全置为空指针！\n");
	}
}
//至此，关于链表的所有初步知识已学习完毕

int main()
{
	//SListTest01();
	//SListTest02();
	//SListTest01_Pro();
	//SListTest02_Pro();
	//SListTest03_Pro();
	//SListTest04_Pro();
	SListTest05_Pro();

	return 0;
}