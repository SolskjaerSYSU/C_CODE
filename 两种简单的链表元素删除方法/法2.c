#define  _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
struct ListNode {
    int val;
    struct ListNode* next;

};
typedef struct ListNode ListNode;
//思路二：找值为不为val的节点，尾插到新链表中 （好处：只需要定义一个pcur，不必前后衔接，遇一搬一即可）
struct ListNode* removeElements(struct ListNode* head, int val)
{
    //创建一个空链表
    ListNode* newHead, * newTail;
    newHead = newTail = NULL;
    //遍历原链表
    ListNode* pcur = head;
    while (pcur != NULL)
    {
        //找值不为val的节点，尾插到链表中
        if (pcur->val != val)
        {
            //但是新链表分两种情况
            if (newHead == NULL) //链表为空时 找到这么一个一个符合条件的节点就直接插入新链表
            {
                newHead = newTail = pcur;
            }
            else //链表不为空 我们的新节点就应该往尾部去插
            {
                // 如果是 val，直接跳过，并释放该节点（如果题目要求释放内存的话）
                // 这里为了逻辑简单，暂不释放，实际工程中建议 free(pcur)
                newTail->next = pcur;
                newTail = newTail->next;
            }
        }
        pcur = pcur->next; //pcur继续在旧链表中往下走

    }
    //我们要把最后一个搬过来的节点的next置空，避免它带过来的next还不符合题意（注意新链表如果为空是不能解引用的哈）
    if (newTail != NULL)
    {
        newTail->next = NULL; //不为空才能解引用！
    }
    return newHead;//pcur遍历完整一个链表之后，我们拿到了一个新链表，直接返回这个链表的首节点即可
}