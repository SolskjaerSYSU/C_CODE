#define  _CRT_SECURE_NO_WARNINGS 1
#include "SList.h"
void SLTPrint(SLTNode* phead)
{
	SLTNode* pcur = phead;
	while (pcur)//pcur != NULL
	{
		printf("%d->", pcur->data);
		pcur = pcur->next;
	}
	printf("NULL\n");
}


//申请新节点
SLTNode* SLTBuyNode(SLTDataType x)
{
	SLTNode* newnode = (SLTNode*)malloc(sizeof(SLTNode));
	if (newnode == NULL)
	{
		perror("malloc fail");
		exit(1);
	}
	newnode->data = x;
	newnode->next = NULL;

	return newnode;
}

//尾插
void SLTPushBack(SLTNode** pphead, SLTDataType x)
{
	assert(pphead);
	//要分成空链表和非空两种情况
	SLTNode* newnode = SLTBuyNode(x);//你要插入含x变量的节点，我把这个含有x的信息给申请新节点函数,帮我申请一个内存，生成新节点，这个节点里含有了x信息并拥有了内存地址
	if (*pphead == NULL) //空链表——此时我们申请过来的新节点，就是链表的第一个节点
	{
		*pphead = newnode;//传过来plist的地址，我们把这个地址解引用，把newnode的值塞给解引用后的*plist
	}
	else  //非空链表
	{
		//先找尾
		SLTNode* ptail = *pphead;
		while (ptail->next) //让ptail指针慢慢走，走到让它的下一个指针为空指针时，它所处的位置就是最后一个节点
		{
			ptail = ptail->next;
		}//现在我们要让ptail（原最后一个节点）不再指向NULL，而是指向我们新生成的节点newnode，这里包含了x变量信息
		//ptail指向尾节点
		ptail->next = newnode;//但是这样空链表不行（ptail为空），因为NULL不能解引用
	}
}
//头插
void SLTPushFront(SLTNode** pphead, SLTDataType x)
{
	assert(pphead); 
	SLTNode* newnode = SLTBuyNode(x);
	newnode->next = *pphead;//让新的节点next指向原第一个节点
	*pphead = newnode;//改完后，新生成的节点要成为第一个节点(通过*pphead修改原来plist，plist现在成为了首节点)
}
//尾删
void SLTPopBack(SLTNode** pphead)
{
	//链表不能为空
	assert(pphead&&* pphead);//先找尾
	SLTNode* ptail = *pphead;
	if ((*pphead)->next == NULL)//第一种情况，链表里只有一个节点，这个首节点指向NULL，那么直接释放这个节点就可以了
	{
		free(*pphead);
		*pphead = NULL;//将头指针置空，通过*pphead修改外面plist的值，不修改的话，外面的plist就会变成野指针(它原来指向NULL，但在传入之后就改变了)
	}
	else //正常情况下:链表有两个及以上的节点
	{
		SLTNode* prev = NULL;//充当ptail的"跟班"指针
		SLTNode* ptail = *pphead;//探路指针,从头开始走

		while (ptail->next)//让ptail指针慢慢走，走到让它的下一个指针为空指针时，他所处的位置就是最后一个节点
		{
			prev = ptail;//小跟班prev先来到ptail的位置跟住它
			ptail = ptail->next;//ptail再往后跨一步
		}
		//循环结束时：ptail指向最后一个节点，prev指向倒数第二个节点
		//现在我们要让ptail(原最后一个指针)释放，并且让ptail的前一个指针的next指向空指针

		free(ptail);  //直接释放内存
		ptail = NULL;  //释放后置空防止野指针(习惯)

		prev->next = NULL; //将现任最后一个节点(原倒数第二个)的next指向空指针
	}
}
//头删
void SLTPopFront(SLTNode** pphead)
{
	//链表不能为空
	assert(pphead && *pphead);
	SLTNode* phead1 = *pphead;//创建一个指向SLTNode*类型的变量phead1，它等于pphead解引用，即代表phead，不然*pphead是没办法的直接通过箭头修改phead里指向next类型的变量的
	SLTNode* pnext = phead1->next;//将原第一个节点指向的节点地址存储到pnext这个指针里
	free(*pphead);
	*pphead = NULL;//释放后指控防止野指针

	*pphead = pnext;//最后，将原第一个节点指向的节点地址重新赋给phead，这样phead又是新的链表的第一个节点了
}
//查找
SLTNode* SLTFind(SLTNode* phead, SLTDataType x)
{
	SLTNode* pcur = phead; //我们希望在函数结束时phead值不变
	while (pcur) 
	{
		if (pcur->data == x)
		{
			return pcur;
		}
		pcur = pcur->next;
	}
	
	return NULL; //找不到，返回空指针
}

// 在指定位置 pos 之前插入数据
void SLTInsert(SLTNode** pphead, SLTNode* pos, SLTDataType x)
{
	assert(pphead && *pphead); // 确保传了有效的链表地址，且链表非空
	assert(pos);               // 确保插入的位置是有效的

	//特殊情况：如果 pos 刚好是第一个节点，相当于头插
	if (pos == *pphead)
	{
		// 如果你之前写了头插函数，可以直接调用：SLTPushFront(pphead, x);
		// 如果不调用，就手动头插：
		SLTNode* newnode = SLTBuyNode(x);
		newnode->next = *pphead;
		*pphead = newnode;
	}
	else // 正常情况：pos 不是第一个节点
	{
		// 找 pos 的前一个节点
		SLTNode* prev = *pphead;
		while (prev->next != pos) //让prev走到pos前一个节点
		{
			prev = prev->next;
			// 加上这个断言更安全，防止传入的 pos 根本就不在这个链表里
			assert(prev != NULL);
		}

		// 执行插队逻辑
		SLTNode* newnode = SLTBuyNode(x);
		prev->next = newnode;
		newnode->next = pos;
	}
}
//在指定位置之后插入节点
void SLTInsertAfter(SLTNode* pos, SLTDataType x) //不需要头节点来找pos的前一个节点
{
	assert(pos);
	SLTNode* newnode = SLTBuyNode(x);
	// 顺序非常关键：必须先让新节点抓住后面的节点，pos 才能放手！ 不然就找不到
	// 步骤 1：新节点的 next 指向 pos 原来后面的节点
	newnode->next = pos->next;

	// 步骤 2：pos 的 next 改为指向新节点
	pos->next = newnode;
}
//删除pos节点
void SLTErase(SLTNode** pphead, SLTNode* pos)
{
	assert(pphead && *pphead);
	assert(pos);
	if (*pphead == pos)//第一种情况：pos就是头节点
	{
		//相当于头删，把第二个节点设为头节点，然后释放旧头节点
		*pphead = pos->next;
		free(pos);
		pos = NULL;
	}
	else //第二种情况：pos不是头节点
	{
		//为了使删除pos之后pos前后两个节点能连起来，我们需要找到pos前后两个节点
		SLTNode* prev = *pphead;
		while (prev->next != pos)//找到pos前一个节点
		{
			prev = prev->next;
		}
		prev->next = pos->next;
		free(pos);
		pos = NULL;
	}
}

void SLTDestroy(SLTNode** pphead)//销毁链表(一个个销毁节点)
{
	assert(pphead && *pphead);
	SLTNode* pcur = *pphead;
	while (pcur)
	{
		SLTNode* next = pcur->next;
		free(pcur);
		pcur = next;
	}
	*pphead = NULL;
}
