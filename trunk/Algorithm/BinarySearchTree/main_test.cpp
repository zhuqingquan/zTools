#include "BinarySearchTree.h"
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

using namespace Algorithm;

int int_compare(int lVal, int rVal)
{
	return lVal - rVal;
}

void int_printf_func(const int& val)
{
	printf("%d ", val);
}

void free_node_func(TreeNode* node)
{
	free(node);
}

// 用于测试的数值  
static int VALS[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

int main(int argc, char* argv[])
{
	int n;
	// 定义一个树结构  
	TreeSet set;

#ifdef DEBUG  
	// 在程序结束时显示内存报告  
	atexit(show_block);
#endif // DEBUG  

	// 设置随机数种子  
	srand(time(0));

	// 利用随机数打乱数组内容  
	for (n = 0; n < 1000; n++)
	{
		int a = rand() % (sizeof(VALS) / sizeof(VALS[0]));
		int b = rand() % (sizeof(VALS) / sizeof(VALS[0]));
		if (a != b)
		{
			VALS[a] ^= VALS[b];
			VALS[b] ^= VALS[a];
			VALS[a] ^= VALS[b];
		}
	}

	// 初始化树结构  
	treeset_init(&set, (cmp_val_func)int_compare);

	// 存储元素  
	printf("测试元素存储\n");
	for (n = 0; n < sizeof(VALS) / sizeof(VALS[0]); n++)
		treeset_add(&set, VALS[n]);
	printf("    二叉树中存放了%d个元素\n", set.nodeCount);
	treeset_walk_rec(&set, (printf_val_func)int_printf_func);

	puts("");

	// 查找元素  
	/*printf("测试元素查询：\n");
	for (n = 0; n < 10; n++)
	{
		int a = rand() % 50;
		if (treeset_contain(&set, &a))
			printf("    元素%d已存在\n", a);
		else
			printf("    元素%d不存在\n", a);
	}

	puts("");

	// 测试元素删除  
	printf("测试元素删除\n");
	n = rand() % 20 + 1;
	printf("    删除前元素%d%s\n", n, treeset_contain(&set, &n) ? "存在" : "不存在");
	treeset_remove(&set, &n);
	printf("    删除后元素%d%s\n", n, treeset_contain(&set, &n) ? "存在" : "不存在");

	n = rand() % 20 + 1;
	printf("    删除前元素%d%s\n", n, treeset_contain(&set, &n) ? "存在" : "不存在");
	treeset_remove(&set, &n);
	printf("    删除后元素%d%s\n", n, treeset_contain(&set, &n) ? "存在" : "不存在");
	show_tree(&set);*/

	// 释放树结构  
	treeset_free(&set, (tree_node_free_func)free_node_func);

	return 0;
	return 0;
}