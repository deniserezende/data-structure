//
//  red-black_tree.c
//  
//
//  Created by Denise F. de Rezende on 24/08/21.
//

#include <stdio.h>
#include <stdlib.h>
#include "red-black_tree.h"

typedef struct red_black_tree_node {
	type_rbtitems item;
	int color; // 1-red, 0-black
	struct red_black_tree_node* parent;
	struct red_black_tree_node* right; // right-child
	struct red_black_tree_node* left; // left child
}NODE;


type_rbtree create_red_black_tree(){
    return NULL;
}


type_rbtree create_new_node_rbt_aux(type_rbtitems item){
    NODE *temp = malloc(sizeof(NODE));
    temp->item = item;
    temp->left = NULL;
    temp->right = NULL;
    temp->parent = NULL;
	temp->color = 0;
    return temp;
}

type_rbtree insert_item_in_red_black_tree(type_rbtree tree, type_rbtitems item, type_rbtptrf_twoitems compare){
	NODE *rb_tree = tree;

	if(rb_tree == NULL) return create_new_node_rbt_aux(item);

	long value_of_comparison = (long)compare(item, rb_tree->item);

	if(value_of_comparison < 0){
		rb_tree->left = insert_item_in_red_black_tree(rb_tree->left, item, compare);
		(rb_tree->left)->parent = rb_tree;
	}
	else if(value_of_comparison > 0){
		rb_tree->right = insert_item_in_red_black_tree(rb_tree->right, item, compare);
		(rb_tree->right)->parent = rb_tree;
	}

	return rb_tree;
}


// This function fixes violations
// caused by BST insertion
void fixup(struct node* root, struct node* pt)
{
	struct node* parent_pt = NULL;
	struct node* grand_parent_pt = NULL;

	while ((pt != root) && (pt->c != 0)
		&& (pt->p->c == 1))
	{
		parent_pt = pt->p;
		grand_parent_pt = pt->p->p;

		/* Case : A
			Parent of pt is left child
			of Grand-parent of
		pt */
		if (parent_pt == grand_parent_pt->l)
		{

			struct node* uncle_pt = grand_parent_pt->r;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if (uncle_pt != NULL && uncle_pt->c == 1)
			{
				grand_parent_pt->c = 1;
				parent_pt->c = 0;
				uncle_pt->c = 0;
				pt = grand_parent_pt;
			}

			else {

				/* Case : 2
					pt is right child of its parent
					Left-rotation required */
				if (pt == parent_pt->r) {
					leftrotate(parent_pt);
					pt = parent_pt;
					parent_pt = pt->p;
				}

				/* Case : 3
					pt is left child of its parent
					Right-rotation required */
				rightrotate(grand_parent_pt);
				int t = parent_pt->c;
				parent_pt->c = grand_parent_pt->c;
				grand_parent_pt->c = t;
				pt = parent_pt;
			}
		}

		/* Case : B
			Parent of pt is right
			child of Grand-parent of
		pt */
		else {
			struct node* uncle_pt = grand_parent_pt->l;

			/* Case : 1
				The uncle of pt is also red
				Only Recoloring required */
			if ((uncle_pt != NULL) && (uncle_pt->c == 1))
			{
				grand_parent_pt->c = 1;
				parent_pt->c = 0;
				uncle_pt->c = 0;
				pt = grand_parent_pt;
			}
			else {
				/* Case : 2
				pt is left child of its parent
				Right-rotation required */
				if (pt == parent_pt->l) {
					rightrotate(parent_pt);
					pt = parent_pt;
					parent_pt = pt->p;
				}

				/* Case : 3
					pt is right child of its parent
					Left-rotation required */
				leftrotate(grand_parent_pt);
				int t = parent_pt->c;
				parent_pt->c = grand_parent_pt->c;
				grand_parent_pt->c = t;
				pt = parent_pt;
			}
		}
	}

	root->c = 0;
}

// Function to print inorder traversal
// of the fixated tree
void inorder(struct node* trav)
{
	if (trav == NULL)
		return;
	inorder(trav->l);
	printf("%d ", trav->d);
	inorder(trav->r);
}

// driver code
int main()
{
	int n = 7;
	int a[7] = { 7, 6, 5, 4, 3, 2, 1 };

	for (int i = 0; i < n; i++) {

		// allocating memory to the node and initializing:
		// 1. color as red
		// 2. parent, left and right pointers as NULL
		// 3. data as i-th value in the array
		struct node* temp
			= (struct node*)malloc(sizeof(struct node));
		temp->r = NULL;
		temp->l = NULL;
		temp->p = NULL;
		temp->d = a[i];
		temp->c = 1;

		// calling function that performs bst insertion of
		// this newly created node
		root = bst(root, temp);

		// calling function to preserve properties of rb
		// tree
		fixup(root, temp);
	}

	printf("Inoder Traversal of Created Tree\n");
	inorder(root);

	return 0;
}
