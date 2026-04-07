#define  _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
#include <stdio.h> // 建议加上 stdio.h 以便后续测试打印

struct ListNode {
    int val;
    struct ListNode* next;
};
typedef struct ListNode ListNode;

// 思路一：创建一个“新链表”（逻辑上的空链表），遍历原链表节点，将原链表中的节点不断头插
struct ListNode* reverseList(struct ListNode* head)
{
    // 1. 定义一个“新链表”的头指针，初始为空
    ListNode* newHead = NULL;

    // 2. pcur 用于遍历原链表
    ListNode* pcur = head;

    // 3. 当 pcur 不为空时，说明还有节点没有搬运完
    while (pcur != NULL)
    {
        // 【关键防御】提前记住原链表的下一个节点，防止修改 next 后迷路！
        ListNode* nextNode = pcur->next;

        // 【执行头插】让当前节点指向新链表的头
        pcur->next = newHead;

        // 【更新新头】新链表的头往前移动，变成了当前节点
        newHead = pcur;

        // 【继续遍历】pcur 回到原链表，准备搬运下一个节点
        pcur = nextNode;
    }

    // 4. 循环结束时，原链表被拆空了，newHead 就是反转后链表的新头节点
    return newHead;
}