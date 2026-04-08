#define  _CRT_SECURE_NO_WARNINGS 1
//给你单链表的头结点 head ，请你找出并返回链表的中间结点。
//如果有两个中间结点，则返回第二个中间结点。
//思路二：快慢指针法  (妙处在于空间复杂度更小，不用像方法一一样遍历一个半链表，而且可以和判断链表是否有环联系起来)
//想象一下，有两个人（A和B）在跑道上同时起跑。A 的速度是 B 的两倍。那么，当 A 跑到终点时，B 一定刚好跑到跑道的中点！
//代码逻辑：
//  1.定义两个指针，slow（慢指针）和 fast（快指针），初始都指向 head
// 
//  2.每次让 slow 走一步（slow = slow->next），让 fast 走两步（fast = fast->next->next）
// 
//  3.当 fast 走到链表末尾（fast == NULL 或 fast->next == NULL）时，slow 所指的节点就是中间节点！
#include <string.h>
struct ListNode {
    int val;
    struct ListNode* next;

};
typedef struct ListNode ListNode;

struct ListNode* middleNode(ListNode* head)
{
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != NULL && fast->next != NULL)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    return slow;
}