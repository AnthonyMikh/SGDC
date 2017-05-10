#ifndef SGDC_SIMPLE_DATATYPE
	#define data_node_t SGDC_QP(bintree_node)
#else
	#ifdef _SGDC_BINTREE_NODE_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on bintree more than once
	#endif
#endif

#ifndef _SGDC_BINTREE_NODE_H
#define _SGDC_BINTREE_NODE_H 1
#endif

#include "../qualify_macros/qualify_macros.h"
#include "bintree_node_types.h"

#ifndef _MALLOC_H
#include <malloc.h>
#endif

#if __STDC_VERSION__ >= 199901L /* if compiler supports C99 standart*/
	#include <stdbool> /* use built-in boolean type */
#else
	typedef enum {false, true} bool; /* emulate bool with enum*/
#endif

typedef struct _SGDC_QP(bintree_node){
    struct _SGDC_QP(bintree_node)* top;
    struct _SGDC_QP(bintree_node)* left;
    struct _SGDC_QP(bintree_node)* right;
    T  value;
} data_node_t;

bool SGDC_QP(bintree_node_isright) (data_node_t* node) {
	if (node == NULL || node->top == NULL)
		return false;
	if (node->top->right == node)
		return true;
	else
		return false;
}

bool SGDC_QP(bintree_node_isleft) (data_node_t* node) {
	if (node == NULL || node->top == NULL)
		return false;
	if (node->top->left == node)
		return true;
	else
		return false;
}

_SGDC_bintree_node_type SGDC_QP(bintree_node_type) (data_node_t* node) {
	if (node == NULL || node->top == NULL)
		return _SGDC_bintree_node_root;
	if (node->top->left == node)
		return _SGDC_bintree_node_left;
	else
		return _SGDC_bintree_node_right;
}

data_node_t* SGDC_QP(bintree_node_create) (T init) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return NULL;
	}
	
	newnode->top   = NULL;
	newnode->left  = NULL;
	newnode->right = NULL;
	newnode->value = init;
	return newnode;
}

/* it will be possibly removed */
static void SGDC_QP(bintree_node_cut) (data_node_t* node) {
	if (node == NULL) return;
	if (node->top == NULL) return;

	data_node_t* supernode = node->top;
	if (supernode->left == node) {
		supernode->left == NULL;
	} else {
		supernode->right == NULL;
	}

	node->top = NULL;
	return;
}

data_node_t* SGDC_QP(bintree_node_getroot) (data_node_t* node) {
	if (node == NULL) return NULL;

	data_node_t* root = node;

	while (root->top != NULL) {
		root = root->top;
	}

	return root;
}

data_node_t* SGDC_QP(bintree_node_rightest) (data_node_t* node) {
	if (node == NULL)
		return NULL;
	data_node_t* rightest = node;
	while (rightest->right != NULL) {
		rightest = rightest->right;
	}
	return rightest;
}

data_node_t* SGDC_QP(bintree_node_leftest) (data_node_t* node) {
	if (node == NULL)
		return NULL;
	data_node_t* leftest = node;
	while (leftest->left != NULL) {
		leftest = leftest->left;
	}
	return leftest;
}

void SGDC_QP(bintree_node_insright) (data_node_t* node, T insvalue) {
	if (node == NULL)
		return;
	data_node_t* inspoint = SGDC_QP(bintree_node_rightest) (node);
	data_node_t* newnode  = malloc(sizeof *newnode);
	if (newnode == NULL)
		return;
	inspoint->right = newnode;
	newnode->top    = inspoint;
	newnode->left   = NULL;
	newnode->right  = NULL;
	newnode->value  = insvalue;
	return;
}

void SGDC_QP(bintree_node_insleft) (data_node_t* node, T insvalue) {
	if (node == NULL)
		return;
	data_node_t* inspoint = SGDC_QP(bintree_node_leftest)(node);
	data_node_t* newnode  = malloc(sizeof *newnode);
	if (newnode == NULL)
		return;
	inspoint->left = newnode;
	newnode->top    = inspoint;
	newnode->left   = NULL;
	newnode->right  = NULL;
	newnode->value  = insvalue;
	return;
}

void SGDC_QP(bintree_node_free) (data_node_t* node) {
	if (node == NULL) {
		return;
	}

	SGDC_QP(bintree_node_cut) (node);
	SGDC_QP(bintree_node_free) (node->right);
	SGDC_QP(bintree_node_free) (node->left);
	free(node);
	return;
}
