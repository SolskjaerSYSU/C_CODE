#define  _CRT_SECURE_NO_WARNINGS 1
//将两个升序链表合并为一个新的 升序 链表并返回。新链表是通过拼接给定的两个链表的所有节点组成的(有点像合并两个有序数组)
//设置list1和list2两个指针分别去比较，让它们遍历数组，小的那个尾插到一个新的链表里，然后搬过去的那个指针往后走
//创建新链表的作用：不用让插进来的指针首尾相连，直接尾插即可
//而且发现遍历的情况只有两种：要么list1走到空，要么list2走到空  所以最后别忘了把剩下的那个链表的剩余节点存放到新链表里来   
#include <string.h>

 struct ListNode {
    int val;
    struct ListNode* next;
    
};
 typedef struct ListNode ListNode;
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) 
{
    // 1. 处理极端情况：如果其中一个是空，直接返回另一个
    if (list1 == NULL) return list2;
    if (list2 == NULL) return list1;
    // 2. 召唤“哨兵节点”（随便给个值，我们不需要用到它的值）
    // 注意：这里我们直接在局部变量里建一个哨兵，不用 malloc，运行速度更快，离开函数自动销毁
    ListNode dummy;
    dummy.next = NULL;

    // 3. 准备一个 tail 指针，它负责不断往后连珠子。初始时它站在哨兵的位置
    ListNode* tail = &dummy;
    // 4.开始比较
    while (list1 && list2)
    {
        if (list1->val <= list2->val)
        {
            tail->next = list1;      // 接在 tail 后面
            list1 = list1->next;     // list1 往后走
        }
        else
        {
            tail->next = list2;
            list2 = list2->next;     //list2往后走
        }
        tail = tail->next;  //  极其关键的一步：tail 接完人之后，自己也要往后走一步，准备接下一个人！
    }
    //5. 循环结束后，一定有一个链表里的节点没有完
    // 我们把还没走到 NULL 的那个链表剩下的“尾巴”，一整串接在 tail 后面
    if (list1 != NULL)
    {
        tail->next = list1;
    }
    else
    {
        tail->next = list2;
    }

    // 6. 哨兵节点 dummy 后面的才是真正的新链表头！
    return dummy.next;

}

//最后总结一下困惑：为什么最后不用循环来一个个处理剩下的节点？（像数组那样？）
//假设我们拼接好的新链表（tail 目前站在最后）：[1] ->[2] ->[3]
//list1 已经全部走完，变成了 NULL。
//list2 还有一长串没有处理：[4] ->[5] ->[6] ->[7]->NULL
//此时，list2 这个指针指在哪里？它指向的是节点[4]。
//请注意！虽然 list2 只指向了[4]，但是[4] 的后面已经死死地连着[5]、[6] 和[7] 了！它们本身就是一根完整的绳子上的蚂蚱。
//你在物理上做的事情是：把 tail（也就是[3]）的挂钩，直接挂到了[4] 上。
//一旦[3] 抓住了[4]，因为[4] 本来就牵着[5]，[5] 牵着[6]…… 那么整串 list2 就被瞬间、一次性地拖到了新链表的后面
