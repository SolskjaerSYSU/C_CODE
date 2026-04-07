#define  _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
 struct ListNode {
    int val;
    struct ListNode* next;
    
};
typedef struct ListNode ListNode;
// 思路一：遍历原链表，将值为val的节点释放掉
struct ListNode* removeElements(struct ListNode* head, int val)
{
    // 1. 创建一个虚拟头节点，指向原链表的头
    // 这样可以将“删除头节点”和“删除中间节点”的操作统一起来
    ListNode* dummy = (ListNode*)malloc(sizeof(ListNode));
    dummy->next = head;

    // 2. 使用 prev 指针进行遍历，prev 始终指向待检查节点的前一个节点
    ListNode* prev = dummy;

    while (prev->next != NULL)
    {
        // 如果发现下一个节点的值等于 val
        if (prev->next->val == val)
        {
            // 记录要删除的节点
            ListNode* temp = prev->next;
            // 跳过该节点
            prev->next = prev->next->next;
            // 释放内存
            free(temp);
        }
        else
        {
            // 如果不相等，prev 向后移动
            prev = prev->next;
        }
    }

    // 3. 返回新的头节点（dummy->next 可能会变）
    struct ListNode* newHead = dummy->next;
    free(dummy); // 释放虚拟头节点
    return newHead;
}