#define  _CRT_SECURE_NO_WARNINGS 1
//问题描述：
//编号为 1 到 n 的 n 个人围成一圈。从编号为 1 的人开始报数，报到 m 的人离开。
//下一个人继续从 1 开始报数。
//n - 1 轮结束以后，只剩下一个人，问最后留下的这个人编号是多少？
//数据范围：
//1≤n,m≤10000进阶：空间复杂度O(1)，时间复杂O(n)
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
//思路:创建一个环形链表，让指针pcur若干次遍历数组，每走m步就销毁节点内存
// 最后链表只剩一个节点时返回节点指针
//当然，还要一个指针prev来辅助pcur，帮助销毁后链表前后节点相连

//1.根据n创建带环链表
struct ListNode {
    int val;
    struct ListNode* next;
};
typedef struct ListNode ListNode;
//创建节点
ListNode* buyNode(int x)
{
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    if (node == NULL)
    {
        exit(1);
    }
    node->val = x;
    node->next = NULL;
    return node;
}
 // 创建带环链表
ListNode* createCircle(int n)
{
    //先创建第一个节点
    ListNode* phead = buyNode(1);
    ListNode* ptail = phead; //创建一个ptail指针，起到类似遍历链表的作用
    for (int i = 2; i <= n; i++) //创建由1到n的节点
    {
        ptail->next = buyNode(i);
        ptail = ptail->next; //尾指针继续往后走
    }
    //最重要的一步：最后的一个节点要指向头节点
    ptail->next = phead;
    //最夸张的一点来了，因为我们在后面报数时要知道它的前驱节点，所以不返回头节点而是尾节点，也就是头节点的前一个节点
    return ptail;
}
int ysf(int n, int m) 
{
    ListNode* prev = createCircle(n);
    ListNode* pcur = prev->next;
    int count = 1; //pcur开始已指向1号节点，先报数1
    while (pcur->next != pcur)
    {
        if (count == m) //先链接，后销毁
        {
            prev->next = pcur->next;
            free(pcur);
            pcur = prev->next;
            count = 1; //重新报数，而这个节点本身已经报了一次1了
        }
        else //此时不需要销毁节点 
        {
            prev = pcur; //走之前prev要走到pcur的位置，方便销毁节点后前连
            pcur = pcur->next;
            count++;
        }
    }
    return pcur->val;
}