#define  _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>

// 辅助函数：用来打印数组内容，方便我们观察变化
void printArray(int arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void merge(int* nums1, int m, int* nums2, int n)
{
	int l1 = m - 1;       // nums1 的有效尾部
	int l2 = n - 1;       // nums2 的尾部
	int l3 = m + n - 1;   // nums1 的最终尾部（空位）

	// 1. 两人都在场时，比大小，大的往后放
	while (l1 >= 0 && l2 >= 0)
	{
		if (nums1[l1] < nums2[l2])
		{
			nums1[l3--] = nums2[l2--];
		}
		else
		{
			nums1[l3--] = nums1[l1--];
		}
	}

	// 2. 善后处理：如果二号选手 l2 还有剩余，说明还没搬完
	// 巧妙的处理：原本我们想用if来处理l2中还未搬运的元素，但是这里可以将 if 改为 while，确保全部搬运完
	while (l2 >= 0)
	{
		nums1[l3--] = nums2[l2--];
	}

	// 至于 l1 >= 0 的情况为什么不需要写 while 循环处理，这正是这道题的绝妙之处：本来就是把l2中的元素搬运到l1中实现新的数组，l2走到头了说明就是搬完了，不需要再去看l1走到哪了  
}

int main()
{
	// 准备测试数据
	// 注意：nums1 必须预留足够的空间 (m + n)。这里的 0 只是占位符，代表空位。
	int nums1[6] = { 1, 2, 3, 0, 0, 0 };
	int m = 3; // nums1 里面真正有用的数字是 3 个 (1, 2, 3)

	int nums2[3] = { 2, 5, 6 };
	int n = 3; // nums2 里面的数字也是 3 个 (2, 5, 6)

	// 打印合并前的状态，进行对比
	printf("合并前 nums1 状态: ");
	// nums1 的总长度是 m + n = 6
	printArray(nums1, m + n);

	printf("合并前 nums2 状态: ");
	printArray(nums2, n);

	printf("------------------------\n");

	// 调用你写好的合并函数
	merge(nums1, m, nums2, n);

	// 打印合并后的最终结果
	printf("合并后 nums1 结果: ");
	printArray(nums1, m + n);

	return 0;
}