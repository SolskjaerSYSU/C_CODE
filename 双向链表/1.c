#define  _CRT_SECURE_NO_WARNINGS 1
#include  "List.h"

void ListTest01()
{
	LTNode* plist = NULL;
	LTInit(&plist);
	printf("%d\n", plist->data);
}
void ListTest02()
{
	LTNode* plist = NULL;
	LTInit(&plist);
	LTPushBack(plist, 1);
	LTPrint(plist);
	LTPushBack(plist, 2);
	LTPrint(plist);
	LTPushBack(plist, 3);
	LTPrint(plist);
}
void ListTest03()
{
	LTNode* plist = NULL;
	LTInit(&plist);

	printf("开始头插测试：\n");
	LTPushFront(plist, 10);
	LTPrint(plist); // 预期：哨兵位 <-> 10 <-> (回到哨兵位)

	LTPushFront(plist, 20);
	LTPrint(plist); // 预期：哨兵位 <-> 20 <-> 10 <-> (回到哨兵位)

	LTPushFront(plist, 30);
	LTPrint(plist); // 预期：哨兵位 <-> 30 <-> 20 <-> 10 <-> (回到哨兵位)
}

void ListTest05()
{
	printf("=== 开始测试头删 (LTPopFront) ===\n");
	LTNode* plist = NULL;
	LTInit(&plist); // 初始化，产生哨兵位

	// 1. 先尾插 3 个数据：10, 20, 30
	LTPushBack(plist, 10);
	LTPushBack(plist, 20);
	LTPushBack(plist, 30);
	printf("准备数据 (尾插 10, 20, 30)：\n");
	LTPrint(plist); // 预期：哨兵位 <-> 10 <-> 20 <-> 30 <-> 哨兵位

	// 2. 测试头删 1 个节点
	LTPopFront(plist);
	printf("\n执行一次头删后 (应该删掉10)：\n");
	LTPrint(plist); // 预期：哨兵位 <-> 20 <-> 30 <-> 哨兵位

	// 3. 继续头删，直到链表只剩哨兵位
	LTPopFront(plist);
	LTPopFront(plist);
	printf("\n再执行两次头删后 (链表应该为空)：\n");
	LTPrint(plist); // 预期：哨兵位 <-> 哨兵位

	// 4. 边界测试：如果这时候再头删，程序应该报错 (触发 assert)
	//LTPopFront(plist); 
	//printf("解开上一行注释，程序会断言失败！\n");
}
void ListTest06()
{
	printf("=== 开始测试查找 (LTFind) ===\n");
	LTNode* plist = NULL;
	LTInit(&plist);

	// 先准备点数据：尾插 10, 20, 30, 40
	LTPushBack(plist, 10);
	LTPushBack(plist, 20);
	LTPushBack(plist, 30);
	LTPushBack(plist, 40);
	printf("当前链表数据：\n");
	LTPrint(plist);

	// 测试 1：查找存在的节点 (比如找 30)
	printf("\n查找数据为 30 的节点...\n");
	LTNode* pos = LTFind(plist, 30);
	if (pos != NULL)
	{
		printf("-> 找到了！节点地址：%p，值为：%d\n", pos, pos->data);

		// 炫技时刻：利用找到的指针，直接修改数据！
		pos->data = 300;
		printf("-> 将找到的节点值修改为 300 后链表变为：\n");
		LTPrint(plist); // 预期：... 10 <-> 20 <-> 300 <-> 40 ...
	}
	else
	{
		printf("-> 没找到\n");
	}

	// 测试 2：查找不存在的节点 (比如找 99)
	printf("\n查找数据为 99 的节点...\n");
	pos = LTFind(plist, 99);
	if (pos != NULL)
	{
		printf("-> 找到了！值为：%d\n", pos->data);
	}
	else
	{
		printf("-> 查找失败：链表中不存在值为 99 的节点。\n");
	}
}
void Test07()
{
	printf("=== 开始测试任意位置插入 (LTInsert) ===\n");
	LTNode* plist = NULL;
	LTInit(&plist);

	// 用我们刚才推导的“新·尾插法”加入数据 (你可以试试把原来的 LTPushBack 里面改成直接调用 LTInsert)
	LTInsert(plist->prev, 10);
	LTInsert(plist->prev, 20);
	LTInsert(plist->prev, 30);
	printf("初始数据：\n");
	LTPrint(plist); // 预期：哨兵位 <-> 10 <-> 20 <-> 30 <-> 哨兵位

	// 连招测试：找到 20，并在 20 的后面插入 99
	printf("\n查找 20 并插入 99...\n");
	LTNode* pos = LTFind(plist, 20);
	if (pos != NULL)
	{
		LTInsert(pos, 99);
	}
	LTPrint(plist); // 预期：哨兵位 <-> 10 <-> 20 <-> 99 <-> 30 <-> 哨兵位
}
void TestUltimate()
{
	printf("===========================================\n");
	printf("        双向带环链表：终极通关大考         \n");
	printf("===========================================\n\n");

	LTNode* plist = NULL;
	LTInit(&plist);
	printf("[初始化成功] 此时只有哨兵位。\n\n");

	// --- 第一阶段：四大金刚基础测试 ---
	printf("【第一阶段：头尾插删测试】\n");
	LTPushBack(plist, 10);
	LTPushBack(plist, 20);
	printf("连续尾插 10, 20：\n");
	LTPrint(plist); // 预期: 哨兵位 <-> 10 <-> 20

	LTPushFront(plist, 0);
	LTPushFront(plist, -10);
	printf("连续头插 0, -10：\n");
	LTPrint(plist); // 预期: 哨兵位 <-> -10 <-> 0 <-> 10 <-> 20

	LTPopBack(plist);
	printf("执行一次尾删 (删掉 20)：\n");
	LTPrint(plist); // 预期: 哨兵位 <-> -10 <-> 0 <-> 10

	LTPopFront(plist);
	printf("执行一次头删 (删掉 -10)：\n");
	LTPrint(plist); // 预期: 哨兵位 <-> 0 <-> 10 
	printf("\n");


	// --- 第二阶段：精准打击测试 ---
	printf("【第二阶段：查找与任意位置操作测试】\n");

	// 查找并插入 (注意：你的 LTInsert 是在 pos *之后* 插入)
	LTNode* pos1 = LTFind(plist, 0);
	if (pos1 != NULL)
	{
		printf("找到节点 0，在其后插入 5：\n");
		LTInsert(pos1, 5);
	}
	LTPrint(plist); // 预期: 哨兵位 <-> 0 <-> 5 <-> 10

	// 查找并删除
	LTNode* pos2 = LTFind(plist, 5);
	if (pos2 != NULL)
	{
		printf("找到节点 5，并将其残忍抹杀 (LTErase)：\n");
		LTErase(pos2);
	}
	LTPrint(plist); // 预期: 哨兵位 <-> 0 <-> 10
	printf("\n");


	// --- 第三阶段：极限抗压测试 ---
	printf("【第三阶段：清空链表极限测试】\n");
	LTPopFront(plist); // 删掉 0
	LTPopBack(plist);  // 删掉 10
	printf("删空所有有效节点后：\n");
	LTPrint(plist); // 预期: 哨兵位 <-> (回到哨兵位)

	printf("\n恭喜！所有逻辑全部完美运行！\n");
	printf("===========================================\n");
}
int main()
{
	//ListTest01();
	//ListTest02();
	//ListTest03();
	//ListTest05();
	//ListTest06();
	//Test07();
	TestUltimate();

	return 0;
}