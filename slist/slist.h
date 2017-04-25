
#ifndef SGDC_SIMPLE_DATATYPE
	#define data_node_t SGDC_QP(slist)
#else
	#ifdef _SGDC_SLIST_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on single-linked list more than once
#endif

#ifndef _SGDC_SLIST_H
#define _SGDC_SLIST_H 1
#endif

#include "../qualify_macros/qualify_macros.h"
#include "../default_type/default_type_begin.h"

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct _SGDC_QP(slist) {
	struct _SGDC_QP(slist)* next;
	T value;
} data_node_t;

data_node_t* SGDC_QP(slist_create) (T init) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return NULL;
	}
	
	newnode->value = init;
	newnode->next  = NULL;
	return newnode;
}

void SGDC_QP(slist_insert) (data_node_t* node, T insertvalue) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return;
	}
	
	newnode->next  = node->next;
	newnode->value = insertvalue;
	node->next     = newnode;
	return;
}

void SGDC_QP(slist_delnext) (data_node_t* node) {
	if (node->next == NULL)
		return;

	data_node_t* nextnode = node->next;
	node->next = nextnode->next;
	free(nextnode);
	return;
}

void SGDC_QP(slist_deltail) (data_node_t* node) {
	if (node == NULL)
		return;
	
	while(node->next != NULL) {
		SGDC_QP(slist_delnext) (node);
	}
	return;
}

#include "../default_type/default_type_end.h"
