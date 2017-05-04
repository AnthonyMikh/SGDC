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

void SGDC_QP(slist_append) (data_t* list, T tailvalue) {
	if (list == NULL)
		return;
	if (list->last == NULL)
		return;
	
	size_t inscount = SGDC_QP(slist_node_insert) (list->last, tailvalue);
	if (inscount == 0) { //no nodes actually inserted
		return;
	}
	list->last = newnode;
	++(list->size);
	return;
}

T SGDC_QP(slist_pophead) (data_t* list, T default_value) {
	if (list == NULL)
		return default_value;
	if (list->size == 0)
		return 0;
	data_node_t* oldfirst = list->head;
	T headvalue = oldfirst->value;
	list->head = list->head->next;
	SGDC_QP(slist_node_free) (oldfirst);
	return headvalue;
}

data_iter_t SGDC_QP(slist_it_make) (data_t list) {
	data_iter_t newiter;
	newiter.current = list.head;
	newiter.head = list;
	return newiter;
}

void SGDC_QP(slist_it_gonext) (data_iter_t* iter) {
	if (iter == NULL)
		return;	
	if (iter->current == NULL)
		return;
	iter->current = iter->current.next;
	return;
}

void SGDC_QP(slist_it_rewind) (data_iter_t* iter) {
	if (iter == NULL)
		return;
	iter->current = iter->head.head;
	return;
}

void SGDC_QP(slist_it_insert) (data_iter_t iter, T insertvalue) {
	if (iter.current == NULL)
		return;
	data_node_t oldnext = iter.current->next;
	if (0 != SGDC_QP(slist_node_insert) (iter.current, T insertvalue)) { //if node was succesfully inserted
		++(iter.head.size);
		if (oldnext == NULL) //iterator was at last node
			iter.head.last = iter.current->next;
	}
	return;
}

void SGDC_QP(slist_it_delnext) (data_iter_t iter) {
	if (0 != SGDC_QP(slist_node_delnext) (iter.current)) { //if node was succesfully deleted
		--(iter.head.size);
		if (iter.current->next == NULL) //iterator is on last node
			iter.head.last = iter.current;
	}
	return;
}

void SGDC_QP(slist_it_deltail) (data_iter_t iter) {
	size_t deleted = 0;
	while (SGDC_QP(slist_node_delnext) (iter.current))
		++deleted;
	iter.head.size -= deleted;
	iter.head.last  = iter.current;
}

#include "../default_type/default_type_end.h"
