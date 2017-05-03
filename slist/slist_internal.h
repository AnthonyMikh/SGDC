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

typedef struct _SGDC_QP(slist_node) {
	struct _SGDC_QP(slist_node)* next;
	T value;
} data_node_t;

typedef char _SGDC_was_modified;

data_node_t* SGDC_QP(slist_node_create) (T init) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return NULL;
	}
	
	newnode->value = init;
	newnode->next  = NULL;
	return newnode;
}

_SGDC_was_modified SGDC_QP(slist_node_insert) (data_node_t* node, T insertvalue) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return 0;
	}
	
	newnode->next  = node->next;
	newnode->value = insertvalue;
	node->next     = newnode;
	return 1;
}

_SGDC_was_modified SGDC_QP(slist_node_delnext) (data_node_t* node) {
	if (node == NULL)
		return 0;
	if (node->next == NULL)
		return 0;

	data_node_t* nextnode = node->next;
	node->next = nextnode->next;
	free(nextnode);
	return 1;
}

_SGDC_was_modified SGDC_QP(slist_node_deltail) (data_node_t* node) {
	if (node == NULL)
		return 0;
	
	while(node->next != NULL) {
		SGDC_QP(slist_delnext) (node);
	}
	return 1;
}

_SGDC_was_modified SGDC_QP(slist_node_free) (data_node_t* node) {
	if (node == NULL)
		return 0;
	
	free(node);
	return 1;
}
