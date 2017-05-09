#ifndef SGDC_SIMPLE_DATATYPE
	#define data_node_t SGDC_QP(bintree)
#else
	#ifdef _SGDC_BINTREE_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on bintree more than once
	#endif
#endif

#ifndef _SGDC_BINTREE_H
#define _SGDC_BINTREE_H 1
#endif

#include "../qualify_macros/qualify_macros.h"
#include "../default_type/default_type_begin.h"

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct _SGDC_QP(bintree){
    struct _SGDC_QP(bintree)* top;
    struct _SGDC_QP(bintree)* left;
    struct _SGDC_QP(bintree)* right;
    T  value;
} data_node_t;

data_node_t* SGDC_QP(bintree_create) (T init) {
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

static void SGDC_QP(bintree_cut) (data_node_t* node) {
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

data_node_t* SGDC_QP(bintree_getroot) (data_node_t* a) {
	if (a == NULL) return NULL;

	data_node_t* _a = a;

	while (_a->top != NULL) {
		_a = _a->top;
	}

	return _a;
}

data_node_t* SGDC_QP(bintree_rightest) (data_node_t* node) {
	if (node == NULL)
		return NULL;
	data_node_t* rightest = node;
	while (rightest->right != NULL) {
		rightest = rightest->right;
	}
	return rightest;
}

data_node_t* SGDC_QP(bintree_leftest) (data_node_t* node) {
	if (node == NULL)
		return NULL;
	data_node_t* leftest = node;
	while (leftest->left != NULL) {
		leftest = leftest->left;
	}
	return leftest;
}

void SGDC_QP(bintree_insright) (data_node_t* node, T insvalue) {
	if (node == NULL)
		return;
	data_node_t* inspoint = rightest(node);
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

void SGDC_QP(bintree_insleft) (data_node_t* node, T insvalue) {
	if (node == NULL)
		return;
	data_node_t* inspoint = leftest(node);
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

void SGDC_QP(bintree_free) (data_node_t* a) {
    if (a == NULL) {
        return;
    }

    SGDC_QP(bintree_cut)  (a);
    SGDC_QP(bintree_free) (a->left);
    SGDC_QP(bintree_free) (a->right);

    free(a);
    return;
}

#include "../default_type/default_type_end.h"
