/*
 *	@author		zhuqingquan
 *	@date		2015-07-06
 *	@brief		Binary Search Tree
 */

#pragma once
#ifndef _ALGORITHM_BINARY_SEARCH_TREE_H_
#define _ALGORITHM_BINARY_SEARCH_TREE_H_

#include <stdlib.h>

namespace Algorithm
{
	struct TreeNode
	{
		int val;		//fixme replace int by template
		TreeNode* left;
		TreeNode* right;

		TreeNode() : val(0), left(NULL), right(NULL) {};
		~TreeNode() { val = 0; left = NULL; right = NULL; };
	};

	typedef int (*cmp_val_func)(int leftval, int rightval);
	struct TreeSet
	{
		struct TreeNode* root;
		size_t	nodeCount;
		cmp_val_func cmp_func;

		TreeSet() : root(NULL), nodeCount(0), cmp_func(NULL) {};
		~TreeSet() { root = NULL; nodeCount = 0; cmp_func = NULL; };
	};

	typedef void(*printf_val_func)(const int& val);
	typedef void(*tree_node_free_func)(TreeNode* treenode);

	int treeset_init(TreeSet* binaryTree, cmp_val_func cmp_less_func);
	int treeset_free(TreeSet* binaryTree, tree_node_free_func free_func);
	int treeset_add(TreeSet* binaryTree, int val);
	int treeset_add(TreeSet* binaryTree, TreeNode* node);
	int treeset_remove(TreeSet* binaryTree, int val);
	//walk through the binary tree
	int treeset_walk_rec(TreeSet* binaryTree, printf_val_func printfFunc);
	int treeset_walk_iter(TreeSet* binaryTree, printf_val_func printfFunc);

	//walk through the binary tree by recursion algorithm
	int inorder_treeset_walk_rec(TreeSet* tree, printf_val_func printfFunc);
	int preorder_treeset_walk_rec(TreeSet* tree, printf_val_func printfFunc);
	int postorder_treeset_walk_rec(TreeSet* tree, printf_val_func printfFunc);

	//walk through the binary tree by iteractive algorithm
	int inorder_treeset_walk_iter(TreeSet* tree, printf_val_func printfFunc);
	int preorder_treeset_walk_iter(TreeSet* tree, printf_val_func printfFunc);
	int postorder_treeset_walk_iter(TreeSet* tree, printf_val_func printfFunc);

	//find a tree node of the val
	TreeNode* treeset_find(TreeSet* binaryTree, int val);
	TreeNode* treeset_find_rec(TreeSet* binaryTree, int val);
	TreeNode* treeset_find_iter(TreeSet* binaryTree, int val);

	TreeNode* treeset_minimum(TreeSet* binaryTree);
	TreeNode* treeset_maximum(TreeSet* binaryTree);

	TreeNode* treeset_successor(TreeSet* binaryTree, TreeNode* node);
	TreeNode* treeset_successor(TreeSet* binaryTree, int nodeVal);
	TreeNode* treeset_predecessor(TreeSet* binaryTree, TreeNode* node);
	TreeNode* treeset_predecessor(TreeSet* binaryTree, int nodeVal);
	
}

#endif //_ALGORITHM_BINARY_SEARCH_TREE_H_
