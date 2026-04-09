#define  _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
//给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
//你不需要 保留 每个分区中各节点的初始相对位置。

//思路二：双哨兵链表拼接法
struct ListNode {
    int val;
    struct ListNode* next;

};
typedef struct ListNode ListNode;
struct ListNode* partition(struct ListNode* head, int x)
{
    // 两个假车头（哨兵）
    ListNode smallDummy;
    ListNode* small = &smallDummy; // small 专门负责串联小于 x 的节点

    ListNode bigDummy;
    ListNode* big = &bigDummy;     // big 专门负责串联大于等于 x 的节点

    ListNode* pcur = head;
    // 1. 开始分发节点（把红豆绿豆分到两个碗里）
    while (pcur != NULL)
    {
        if (pcur->val < x)
        {
            small->next = pcur;  // 挂到 small 链表后面
            small = small->next; // small 尾巴往后挪
        }
        else
        {
            big->next = pcur;    // 挂到 big 链表后面
            big = big->next;     // big 尾巴往后挪
        }

        pcur = pcur->next;       // pcur 正常往下遍历原链表
    }
    // 2.斩断大链表的尾巴（极其关键！防止链表成环）
    big->next = NULL;

    // 3. 将小链表的尾巴，连上大链表的第一个“真人”节点
    small->next = bigDummy.next;

    // 4. 返回小链表假车头后面的第一个“真人”节点，这就是新链表的头
    return smallDummy.next;
}