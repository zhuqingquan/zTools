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

// ���ڲ��Ե���ֵ  
static int VALS[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };

int main(int argc, char* argv[])
{
	int n;
	// ����һ�����ṹ  
	TreeSet set;

#ifdef DEBUG  
	// �ڳ������ʱ��ʾ�ڴ汨��  
	atexit(show_block);
#endif // DEBUG  

	// �������������  
	srand(time(0));

	// ���������������������  
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

	// ��ʼ�����ṹ  
	treeset_init(&set, (cmp_val_func)int_compare);

	// �洢Ԫ��  
	printf("����Ԫ�ش洢\n");
	for (n = 0; n < sizeof(VALS) / sizeof(VALS[0]); n++)
		treeset_add(&set, VALS[n]);
	printf("    �������д����%d��Ԫ��\n", set.nodeCount);
	treeset_walk_rec(&set, (printf_val_func)int_printf_func);

	puts("");

	// ����Ԫ��  
	/*printf("����Ԫ�ز�ѯ��\n");
	for (n = 0; n < 10; n++)
	{
		int a = rand() % 50;
		if (treeset_contain(&set, &a))
			printf("    Ԫ��%d�Ѵ���\n", a);
		else
			printf("    Ԫ��%d������\n", a);
	}

	puts("");

	// ����Ԫ��ɾ��  
	printf("����Ԫ��ɾ��\n");
	n = rand() % 20 + 1;
	printf("    ɾ��ǰԪ��%d%s\n", n, treeset_contain(&set, &n) ? "����" : "������");
	treeset_remove(&set, &n);
	printf("    ɾ����Ԫ��%d%s\n", n, treeset_contain(&set, &n) ? "����" : "������");

	n = rand() % 20 + 1;
	printf("    ɾ��ǰԪ��%d%s\n", n, treeset_contain(&set, &n) ? "����" : "������");
	treeset_remove(&set, &n);
	printf("    ɾ����Ԫ��%d%s\n", n, treeset_contain(&set, &n) ? "����" : "������");
	show_tree(&set);*/

	// �ͷ����ṹ  
	treeset_free(&set, (tree_node_free_func)free_node_func);

	return 0;
	return 0;
}