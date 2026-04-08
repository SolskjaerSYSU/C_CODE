#define  _CRT_SECURE_NO_WARNINGS 1
//给你单链表的头结点 head ，请你找出并返回链表的中间结点。
//如果有两个中间结点，则返回第二个中间结点。
//思路一：遍历，count计节点数，直接返回第（count/2）节点的next节点
#include <string.h>
 struct ListNode {
    int val;
    struct ListNode* next;
    
};
 typedef struct ListNode ListNode;

struct ListNode* middleNode(struct ListNode* head) 
{
    //分两种情况，空链表和非空链表
    if (head == NULL)
    {
        return head;//空链表直接返回空指针
    }
    else
    {
        int count = 0;
        ListNode* pcur1 = head;
        ListNode* pcur2 = head;
        while (pcur1) //遍历数组，直至pcur1走完链表
        {
            count++;
            pcur1 = pcur1->next; //这步别忘了，让指针往前走，避免陷入死循环
        }
        //现在我们要找到第(count/2)的节点
        for (int i = 0; i < (count / 2); i++) //让pcur2走（count/2）次，它就会来到第第（count/2）节点的next节点
        {
            pcur2 = pcur2->next;
        }
        return pcur2;
    }
}