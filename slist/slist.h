#ifndef SGDC_SIMPLE_DATATYPE
	#define data_t SGDC_QP(slist)
#else
	#ifdef _SGDC_SLIST_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on same slist more than once
	#endif
#endif

#ifndef _SGDC_SLIST_H
#define _SGDC_SLIST_H 1
#endif

#include "../qualify_macros/qualify_macros.h"
#include "../default_type/default_type_begin.h"

#include "slist_internal.h"

typedef struct _SGDC_QP(slist) {
	data_node_t* head;
	data_node_t* last;
	size_t size;
} data_t;

typedef struct _SGCD_QP(slist_iter) {
	data_node_t* current;
	data_t* head;
}

data_t SGDC_QP(slist_init) (T init) {
	data_node_t* newnode = malloc(sizeof *newnode);
	if (newnode == NULL) {
		return NULL;
	}
	
	newnode->value = init;
	newnode->next  = NULL;
	
	data_t newlist;
	newlist.head = newnode;
	newlist.last = newnode;
	newlist.size = 1;
	
	return newlist;
}

/* code goes here */

#include "../default_type/default_type_end.h"
