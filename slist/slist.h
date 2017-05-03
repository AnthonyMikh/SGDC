#ifndef SGDC_SIMPLE_DATATYPE
	#define data_t SGDC_QP(slist)
#else
	#ifdef _SGDC_SLIST_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on same slist more than once
	#endif
#endif

#define data_iter_t SGDC_QP(slist_iter)

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
} data_iter_t;

data_t SGDC_QP(slist_create) (T init) {
	data_node_t* newnode = SGDC_QP(slist_node_create) (init);
	
	data_t newlist;
	newlist.head = newnode;
	newlist.last = newnode;
	newlist.size = 1;
	
	return newlist;
}

void SGDC_QP(slist_append) (data_t list, T tailvalue) {
	data_node_t* newnode = SGDC_QP(slist_node_insert) (list.last, tailvalue);
	if (newnode == NULL) {
		return;
	}
	list.last = newnode;
	++list.size;
	return;
}

data_iter_t SGDC_QP(slist_it_make) (data_t list) {
	data_iter_t newiter;
	newiter.current = list.head;
	newiter.head = list;
	return newiter;
}

void SGDC_QP(slist_it_gonext) (data_iter_t* iter) {
	if (iter->current == NULL)
		return;
	iter->current = iter->current.next;
	return;
}

void SGDC_QP(slist_it_rewind) (data_iter_t* iter) {
	iter->current = iter->head.head;
	return;
}

#include "../default_type/default_type_end.h"
