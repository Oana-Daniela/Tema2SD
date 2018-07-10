#ifndef AVLTREE_H_
#define AVLTREE_H_

#include <stdlib.h>

#define MAX(a, b) (((a) >= (b))?(a):(b))

typedef struct node{
	void* elem;
	void* info;
	struct node *pt;
	struct node *lt;
	struct node *rt;
	struct node* next;
	struct node* prev;
	struct node* end;
	long height;
}TreeNode;

typedef struct TTree{
	TreeNode *root;
	TreeNode *nil;
	void* (*createElement)(void*);
	void (*destroyElement)(void*);
	void* (*createInfo)(void*);
	void (*destroyInfo)(void*);
	int (*compare)(void*, void*);
	long size;
}TTree;


TTree* createTree(void* (*createElement)(void*), void (*destroyElement)(void*),
		void* (*createInfo)(void*), void (*destroyInfo)(void*),
		int compare(void*, void*)){
	/* 
	 * TODO: 
	 * 1. Allocate tree
     * 2. Allocate sentinel
     * 3. Set sentinel
     * 4. Set all other fields
	 */
	TTree* newTree = (TTree*)malloc(sizeof(TTree));
	newTree->size = 0;
	newTree->createElement = createElement;
	newTree->destroyElement = destroyElement;
	newTree->createInfo = createInfo;
	newTree->destroyInfo = destroyInfo;
	newTree->compare = compare;

	TreeNode* sentinel = malloc(sizeof(TreeNode));
	sentinel->elem = 0;
	sentinel->info = 0;
	sentinel->pt = sentinel;
	sentinel->lt = sentinel;
	sentinel->rt = sentinel;
	sentinel->next = sentinel;
	sentinel->prev = sentinel;
	sentinel->end = sentinel;
	sentinel->height = 0;

	newTree->nil = sentinel;
	newTree->root = sentinel;
}

TreeNode* createTreeNode(TTree *tree, void* value, void* info) {
	TreeNode* newNode = malloc(sizeof(TreeNode));

	newNode->elem = tree->createElement(value);
	newNode->info = tree->createInfo(info);
	newNode->pt = tree->nil;
	newNode->lt = tree->nil;
	newNode->rt = tree->nil;
	newNode->next = tree->nil;
	newNode->prev = tree->nil;
	newNode->end = tree->nil;
	newNode->height = 1;

	return newNode;
}

void destroyTreeNode(TTree *tree, TreeNode* node){
	/* 
	 * TODO: 
	 * 1. Destroy fields
     * 2. De-allocate node
	 */
}

int isEmpty(TTree* tree){
	return (tree->root == tree->nil) ? 1: 0;
}

TreeNode* search(TTree* tree, TreeNode* x, void* elem) {
	if (x == tree->nil)
	{
		return x;
	}
	else
	{
		int comp_result = tree->compare(x->elem, elem);

		if (comp_result == 0)
		{
			return x;
		} 
		else
		if (comp_result < 0)
		{
			// Caut in partea dreapta
			return search(tree, x->rt, elem);
		}
		else
		if (comp_result > 0)
		{
			// Caut in partea stanga
			return search(tree, x->lt, elem);
		}
	}
}

TreeNode* minimum(TTree*tree, TreeNode* x) {
	if (x == tree->nil)
	{
		return x;
	}
	else
	{
		while (x->lt != tree->nil)
		{
			x = x->lt;
		}
		return x;
	}	
}

TreeNode* maximum(TTree* tree, TreeNode* x) {
	if (x == tree->nil)
	{
		return x;
	}
	else
	{
		while (x->rt != tree->nil)
		{
			x = x->rt;
		}
		return x;
	}
}

TreeNode* successor(TTree* tree, TreeNode* x) {
	if (x == tree->nil)
	{
		return tree->nil;
	}
	else
	{
		TreeNode* min = minimum(tree, x->rt);

		if (min == tree->nil && x->pt != tree->nil && x->pt->lt == x)
		{
			return x->pt;
		}
		else
		if (x->pt != tree->nil && x->pt->pt != tree->nil && x->pt->pt->lt->rt == x)
		{
			return x->pt->pt;
		} 
		else
		{
			return min;
		}
	}
}

TreeNode* predecessor(TTree* tree, TreeNode* x) {
	if (x == tree->nil)
	{
		return tree->nil;
	}
	else
	{
		TreeNode* max = maximum(tree, x->lt);
		if (max == tree->nil && x->pt != tree->nil && x->pt->rt == x)
		{
			return x->pt;
		}
		else
		if (x->pt != tree->nil && x->pt->pt != tree->nil && x->pt->pt->rt->lt == x)
		{
			return x->pt->pt;
		}
		else
		{
			return max;
		}
	}
}

void avlRotateLeft(TTree* tree, TreeNode* x){
	TreeNode *y = x->rt;
	x->rt = y->lt;

	if(y->lt != tree->nil)
		y->lt->pt = x; // the parent of the y left subtree is x
	y->pt = x->pt; // update parent for y

	if(x->pt == tree->nil)
		tree->root = y;
	else if(x->pt->lt == x)
		x->pt->lt = y;
	else
		x->pt->rt = y;

	y->lt = x; // x is to the left of y
	x->pt = y; // x parent is y

	// Update heights
	y->height = MAX(y->lt->height, y->rt->height) + 1;
	x->height = MAX(x->lt->height, x->rt->height) + 1;

}

void avlRotateRight(TTree* tree, TreeNode* y){
	TreeNode *x = y->lt;

	y->lt = x->rt;
	if(x->rt != tree->nil)
		x->rt->pt = y;

	x->pt = y->pt;

	if(y->pt == tree->nil)
		tree->root = x;
	else if(y->pt->lt == y)
		y->pt->lt = x;
	else
		y->pt->rt = x;

	x->rt = y;
	y->pt = x;

	// Update heights
	y->height = MAX(y->lt->height, y->rt->height) + 1;
	x->height = MAX(x->lt->height, x->rt->height) + 1;
}

/* Get AVL balance factor for node x */
int avlGetBalance(TTree* tree, TreeNode *x) {
	if (x == tree->nil)
	{
		return 0;
	}

	return x->lt->height - x->rt->height;
}


void avlFixUp(TTree* tree, TreeNode* y) {
	TreeNode* parent = y->pt;
	TreeNode* start = y; // start needs to be removed!

	while (parent != tree->nil)
	{
		parent->height = MAX(parent->lt->height, parent->rt->height) + 1;
		int balance = avlGetBalance(tree, parent);
		// Left left
		if (balance > 1 && parent->lt->lt != tree->nil && parent->rt == tree->nil)
		{
			avlRotateRight(tree, parent);
		}
		// Right right
		if (balance < -1 && parent->rt->rt != tree->nil && parent->lt == tree->nil)
		{
			avlRotateLeft(tree, parent);
		}
		// Left right
		if (balance > 1 && start == parent->lt->rt)
		{
			avlRotateLeft(tree, parent->lt);
			avlRotateRight(tree, parent);
		}
		// Right left
		if (balance < -1 && start == parent->rt->lt)
		{
			avlRotateRight(tree, parent->rt);
			avlRotateLeft(tree, parent);
		}
		parent = parent->pt;
	}
}

void insert(TTree* tree, void* elem, void* info) {
	/* 
	 * TODO: 
	 * 1. Create new node
     	 * 2. Iterate to down-wards to nil 
     	 *    (duplicates are added to the list for the search node)
      	 * 3. Update tree 
     	 * 4. Update linked list
     	 * 5. Update size of tree and call fix-up
	 */
	TreeNode* node = createTreeNode(tree, elem, info);
	if (tree->root == tree->nil)
	{
		tree->root = node;
		// Trebuie setat si size pe 1 
		tree->size = 1;
		// Nu este nevoie sa ma asigur ca este echilibrat arborele
	}
	else
	{
		TreeNode* current_node = tree->root;
		TreeNode* parent = tree->nil;
		int position = -1;

		while (current_node != tree->nil)
		{
			int comp_result = tree->compare(current_node->elem, elem);
			if (comp_result < 0)
			{
				//Nodul va fi inserat in pareta dreapta
				parent = current_node;
				position = -1;
				current_node = current_node->rt;
			}
			else
			if (comp_result > 0)
			{
				// Nodul va fi inserat in pareta stanga
				parent = current_node;
				position = 1;
				current_node = current_node->lt;
			}
			else
			{
				
				current_node = tree->nil;
			}
		}
		// Actualizare arbore + lista
		node->pt = parent;
		if (position == -1)
		{
			parent->rt = node;
		} else if (position == 1)
		{
			parent->lt = node;
		}
		// Actualizare size
		tree->size = tree->size + 1;
		// Trebuie fix-up
		avlFixUp(tree, node);
	}
}

void delete(TTree* tree, void* elem) {
	/* 
	 * TODO: 
	 * 1. Search for the node
     * 2. If duplicate delete from the list and exit
     * 3. Otherwise perform tree deletion and update linked list at the end
     * 4. Update size and call fix-up
     * 
     * Hints:
     * 1. If you MUST delete a node from the tree than it has no duplicates!
     *
     * 2. Changing the links with the splice out node is the way to GO,
     *    exchaning node fields does not work in this case,
          you might have duplicates for the splice-out node!!!! 
	 */

	TreeNode* node = search(tree, tree->root, elem);
	if (node == tree->nil)
	{
		return;	
	}
	
	if (node->lt == tree->nil && node->rt == tree->nil)
	{
		if (node->pt != tree->nil)
		{
			if (node->pt->rt == node)
			{
				node->pt->rt = tree->nil;
			}
			else
			if (node->pt->lt == node)
			{
				node->pt->lt = tree->nil;
			}
			avlFixUp(tree, node);
			free(node);
		}
		else
		{
			tree->root = tree->nil;
		}
	}
	
}

void destroyTree(TTree* tree){
	// TODO:

	// Hint: Can you use the list?
}


#endif /* AVLTREE_H_ */
