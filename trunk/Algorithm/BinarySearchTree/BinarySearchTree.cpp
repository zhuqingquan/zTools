// BinarySearchTree.cpp : 定义 DLL 应用程序的导出函数。
//

#include "BinarySearchTree.h"
#include <tchar.h>
#include <assert.h>

using namespace Algorithm;

int Algorithm::treeset_init(TreeSet* binaryTree, cmp_val_func cmp_less_func)
{
	if (!binaryTree)  return -1;
	binaryTree->cmp_func = cmp_less_func;
	binaryTree->root = NULL;
	binaryTree->nodeCount = NULL;
	return 0;
}

int Algorithm::treeset_free(TreeSet* binaryTree, tree_node_free_func free_func)
{
	assert(!_T("Not implement."));
	return -1;
}

int Algorithm::treeset_add(TreeSet* binaryTree, int val)
{
	TreeNode* treenode = (TreeNode*)malloc(sizeof(TreeNode));
	treenode->val = val;
	treenode->left = NULL;
	treenode->right = NULL;
	int ret = 0;
	if (0 != (ret = treeset_add(binaryTree, treenode)))
		free(treenode);
	return ret;
}

int Algorithm::treeset_add(TreeSet* binaryTree, TreeNode* node)
{
	TreeNode* pRoot = binaryTree ? binaryTree->root : NULL;
	if (pRoot)
		return -1;
	TreeNode* pCur = pRoot;
	if (binaryTree->cmp_func == NULL)	return -2;
	if (NULL == node)	return -3;
	while (pCur)
	{
		int cmpResult = binaryTree->cmp_func(pCur->val, node->val);
		if (cmpResult == 0)
			return -4;
		else if (cmpResult < 0)
		{
			if (pCur->left == NULL)
			{
				pCur->left = node;
				return 0;
			}
			pCur = pCur->left;
		}
		else if (cmpResult > 0)
		{
			if (pCur->left == NULL)
			{
				pCur->right = node;
				return 0;
			}
			pCur = pCur->right;
		}
	}
	return -5;
}

int Algorithm::treeset_walk_rec(TreeSet* binaryTree, printf_val_func printfFunc)
{
	return inorder_treeset_walk_rec(binaryTree, printfFunc);
}

int _inorder_treeset_walk_rec(TreeNode* pCur, printf_val_func printfFunc)
{
	if (!pCur)
		return 0;
	_inorder_treeset_walk_rec(pCur->left, printfFunc);
	printfFunc(pCur->val);
	_inorder_treeset_walk_rec(pCur->right, printfFunc);
	return 0;
}
int Algorithm::inorder_treeset_walk_rec(TreeSet* tree, printf_val_func printfFunc)
{
	if (!tree)	return -1;
	return _inorder_treeset_walk_rec(tree->root, printfFunc);
}
