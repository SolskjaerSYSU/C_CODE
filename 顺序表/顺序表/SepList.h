#pragma once
//#define
//typedef int SLDataType;
//typedef struct SeqList
//{
//	SLDataType* a;
//	int size;
//	int capacity;
//}SL;
//
//void SLInit(SL ps);
#include <stdio.h>
#include <stdlib.h> // 提供 malloc, realloc, free 等内存管理函数

//// ==========================================
//// 1. 定义顺序表的结构体
//// ==========================================
//typedef struct {
//    int* data;      // 指向动态分配的数组（储物柜本身）
//    int size;       // 当前已经存储的元素个数（已经用了多少个柜子）
//    int capacity;   // 当前的总容量（总共有多少个柜子）
//} SeqList;
//
//// ==========================================
//// 2. 初始化顺序表
//// ==========================================
//// 作用：为顺序表分配初始的内存空间
//void InitSeqList(SeqList* list) {
//    list->capacity = 5; // 我们一开始先准备 5 个空位
//    list->size = 0;     // 一开始没有任何元素，所以是 0
//    // 使用 malloc 向系统申请 5 个 int 大小的连续内存
//    list->data = (int*)malloc(list->capacity * sizeof(int));
//
//    if (list->data == NULL) {
//        printf("内存分配失败！\n");
//        return;
//    }
//    printf("顺序表初始化成功，初始容量为: %d\n", list->capacity);
//}
//
//// ==========================================
//// 3. 检查并扩容 (核心内部机制)
//// ==========================================
//// 作用：当发现柜子满了，自动买两倍的新柜子，把旧东西搬过去
//void CheckCapacity(SeqList* list) {
//    if (list->size >= list->capacity) { // 如果已用空间大于等于总容量
//        int newCapacity = list->capacity * 2; // 容量翻倍
//        // realloc 函数会自动分配新内存，并把旧数据拷贝过去，然后释放旧内存
//        int* newData = (int*)realloc(list->data, newCapacity * sizeof(int));
//
//        if (newData == NULL) {
//            printf("扩容失败！\n");
//            return;
//        }
//
//        list->data = newData;       // 让指针指向新房子
//        list->capacity = newCapacity; // 更新容量记录
//        printf("触发自动扩容！当前新容量为: %d\n", list->capacity);
//    }
//}
//
//// ==========================================
//// 4. 插入元素
//// ==========================================
//// 作用：在指定的位置 (index) 插入一个新数据 (value)
//void Insert(SeqList* list, int index, int value) {
//    // 错误检查：插入的位置不能小于0，也不能大于当前的元素总数（必须挨着放）
//    if (index < 0 || index > list->size) {
//        printf("插入位置不合法！\n");
//        return;
//    }
//
//    // 检查是否需要扩容
//    CheckCapacity(list);
//
//    // 核心步骤：将 index 及其之后的所有元素往后移动一位，腾出空间
//    // 注意：移动元素时必须【从后往前】移，否则会覆盖数据！
//    for (int i = list->size; i > index; i--) {
//        list->data[i] = list->data[i - 1];
//    }
//
//    // 把新元素放入腾出的空位
//    list->data[index] = value;
//    list->size++; // 元素总数加 1
//    printf("在索引 %d 处成功插入元素 %d\n", index, value);
//}
//
//// ==========================================
//// 5. 删除元素
//// ==========================================
//// 作用：删除指定位置 (index) 的元素
//void Delete(SeqList* list, int index) {
//    // 错误检查：不能删除不存在的位置
//    if (index < 0 || index >= list->size) {
//        printf("删除位置不合法！\n");
//        return;
//    }
//
//    // 核心步骤：将 index 之后的所有元素往前移动一位，覆盖掉要删除的元素
//    // 注意：移动元素时必须【从前往后】移！
//    for (int i = index; i < list->size - 1; i++) {
//        list->data[i] = list->data[i + 1];
//    }
//
//    list->size--; // 元素总数减 1
//    printf("成功删除索引 %d 处的元素\n", index);
//}
//
//// ==========================================
//// 6. 打印顺序表
//// ==========================================
//void PrintList(SeqList* list) {
//    printf("当前顺序表内容: [ ");
//    for (int i = 0; i < list->size; i++) {
//        printf("%d ", list->data[i]);
//    }
//    printf("] (Size: %d, Capacity: %d)\n", list->size, list->capacity);
//}
//
//// ==========================================
//// 7. 销毁顺序表
//// ==========================================
//// 作用：释放内存，防止内存泄漏
//void DestroySeqList(SeqList* list) {
//    if (list->data != NULL) {
//        free(list->data); // 把内存还给操作系统
//        list->data = NULL; // 指针置空，防止变成野指针
//        list->size = 0;
//        list->capacity = 0;
//        printf("顺序表已销毁，内存已释放。\n");
//    }
//}
//
//// ==========================================
//// 主函数：测试我们的顺序表
//// ==========================================
//int main() {
//    SeqList myList;
//
//    InitSeqList(&myList);
//
//    // 连续插入 6 个元素，这会触发我们的自动扩容机制！
//    Insert(&myList, 0, 10);
//    Insert(&myList, 1, 20);
//    Insert(&myList, 2, 30);
//    Insert(&myList, 3, 40);
//    Insert(&myList, 4, 50);
//    PrintList(&myList); // 此时满了
//
//    Insert(&myList, 2, 99); // 在中间插入，触发扩容，后面的元素后移
//    PrintList(&myList);
//
//    Delete(&myList, 1); // 删除索引为 1 的元素 (20)
//    PrintList(&myList);
//
//    DestroySeqList(&myList); // 用完一定要释放
//    return 0;
//}