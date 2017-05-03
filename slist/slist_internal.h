#ifndef SGDC_SIMPLE_DATATYPE
	#define data_node_t SGDC_QP(slist_node)
#else
	#ifdef _SGDC_SLIST_NODE_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on single-linked list more than once
	#endif
#endif

#ifndef _SGDC_SLIST_NODE_H
#define _SGDC_SLIST_NODE_H 1
#endif

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct _SGDC_QP(slist) {
	struct _SGDC_QP(slist)* next;
	T value;
} data_node_t;

data_node_t* SGDC_QP(slist_node_create) (T init) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return NULL;
	}
	
	newnode->value = init;
	newnode->next  = NULL;
	return newnode;
}

void SGDC_QP(slist_node_insert) (data_node_t* node, T insertvalue) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return;
	}
	
	newnode->next  = node->next;
	newnode->value = insertvalue;
	node->next     = newnode;
	return;
}

void SGDC_QP(slist_node_delnext) (data_node_t* node) {
	if (node->next == NULL)
		return;

	data_node_t* nextnode = node->next;
	node->next = nextnode->next;
	free(nextnode);
	return;
}

void SGDC_QP(slist_node_deltail) (data_node_t* node) {
	if (node == NULL)
		return;
	
	while(node->next != NULL) {
		SGDC_QP(slist_delnext) (node);
	}
	return;
}

void SGDC_QP(slist_free) (data_node_t* node) {
	if (node == NULL)
		return;
	
	SGDC_QP(slist_deltail) (node);
	free(node);
	return;
}
