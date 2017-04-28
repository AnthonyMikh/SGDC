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

static void SGDC_QP(bintree_cut) (data_node_t* a) {
	if (a == NULL) return;
	if (a->top == NULL) return;

	data_node_t* atop = a->top;
	if (atop->left == a) {
		atop->left == NULL;
	} else {
		atop->right == NULL;
	}

	a->top = NULL;
}

data_node_t* SGDC_QP(bintree_getroot) (data_node_t* a) {
	if (a == NULL) return NULL;

	data_node_t* _a = a;

	while (_a->top != NULL) {
		_a = _a->top;
	}

	return _a;
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
