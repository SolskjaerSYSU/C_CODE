#define  _CRT_SECURE_NO_WARNINGS 1
#include <string.h>
//给你一个链表的头节点 head 和一个特定值 x ，请你对链表进行分隔，使得所有 小于 x 的节点都出现在 大于或等于 x 的节点之前。
//你不需要 保留 每个分区中各节点的初始相对位置。

//思路一：在原链表上进行修改，若pcur节点的值大于等于x，尾插在原链表，而且还要定义一个prev来删除节点，ptail来判断走没走完，newPtail来尾插节点
struct ListNode {
    int val;
    struct ListNode* next;
    
};
typedef struct ListNode ListNode;
struct ListNode* partition(struct ListNode* head, int x)
{
    // 1. 处理空链表或只有一个节点的极端情况
    if (head == NULL || head->next == NULL) {
        return head;
    }

    // 2. 找原链表的尾巴 ptail，把它当作“停止哨”
    ListNode* ptail = head;
    while (ptail->next != NULL) 
    {
        ptail = ptail->next;
    }
    // 3. 初始化你的四个得力助手
    ListNode* newPtail = ptail; // 新尾巴初始等于老尾巴
    ListNode* stop = ptail;     // 记录循环必须停止的位置（非常关键！）

    ListNode dummy;             // 哨兵节点：因为头节点可能大于等于 x 被搬走，所以必须用哨兵
    dummy.next = head;

    ListNode* prev = &dummy;
    ListNode* pcur = head;  //把哨兵头插在原链表前面

    // 4. 开始遍历
    while (pcur != NULL)
    {
        // 【防死循环的核心】：提前记录当前 pcur 是不是原链表的最后一个节点
        // 必须在拆解 pcur 之前记录，不然等会儿 pcur 被移走就乱了
        int isStop = (pcur == stop);

        // 情况 A：发现大于等于 x 的节点，准备“逮捕”并流放到尾部
        if (pcur->val >= x)
        {
            // 第一步：从原位置“删除”（让 prev 跳过 pcur）
            prev->next = pcur->next;
            
            // 第二步：尾插到新尾巴 newPtail 后面
            pcur->next = NULL;          // 先把自己的尾巴斩断
            newPtail->next = pcur;      // 挂到新尾巴后面
            newPtail = pcur;            // 更新新尾巴的身份

            // 第三步：pcur 走向下一个节点（注意！此时 prev 不需要动，因为它已经指着下一个新节点了）
            pcur = prev->next;
        }
        // 情况 B：小于 x，是安全的节点，放行
        else
        {
            prev = pcur;       // prev 正常跟进
            pcur = pcur->next; // pcur 正常往下走
        }

        // 【检查停止哨】：如果刚才处理的节点就是原链表的最后一个节点，立刻结束战斗！
        if (isStop) 
        {
            break;
        }
    }

    return dummy.next;
}