
#ifndef SGDC_SIMPLE_DATATYPE
	#define data_t SGDC_QP(bintree)
#else
	#ifdef _SGDC_BINTREE_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on same data structure more than once
	#endif
#endif

#define data_iter_directed_t SGDC_QP(bintree_iter_directed)
#define data_iter_t SGDC_QP(bintree_iter)

#ifndef _SGDC_BINTREE_H
#define _SGDC_BINTREE_H 1
#endif

#include "../qualify_macros/qualify_macros.h"
#include "../default_type/default_type_begin.h"
#include "bintree_internal.h"
#include "bintree_iter_types.h"

typedef struct {
	data_node_t* root;
} data_t;

typedef struct {
	data_node_t* current;
	SGDC_bintree_iter_state state;
	SGDC_bintree_iter_type  type;
} data_iter_directed_t;

typedef struct {
	data_node_t* current;
} data_iter_t;

void SGDC_QP(bintree_create) (T init) {
	data_t newtree;
	newtree.root = SGDC_QP(bintree_node_create) (init);
	return newtree;
}

void SGDC_QP(bintree_free) (data_t tree) {
	SGDC_QP(bintree_node_free) (tree.root);
	return;
}

data_iter_directed_t SGDC_QP(bintree_it_makeltr) (data_t tree) {
	data_iter_directed_t newiter;
	newiter.current = tree.root;
	newiter.type = _SGDC_bintree_ltr;
	newiter.state = _SGDC_bintree_to_left;
	return newiter;
}

data_iter_directed_t SGDC_QP(bintree_it_makertl) (data_t tree) {
	data_iter_directed_t newiter;
	newiter.current = tree.root;
	newiter.type = _SGDC_bintree_rtl;
	newiter.state = _SGDC_bintree_to_right;
	return newiter;
}

data_iter_t SGDC_QP(bintree_it_make) (data_t tree) {
	data_iter_t newiter;
	newiter.current = tree.root;
	return newiter;
}

void SGDC_QP(bintree_it_goright) (data_iter_t* it) {
	if (it == NULL || it->current == NULL || it->current->right == NULL)
		return;
	it->current = it->current->right;
	return;
}

void SGDC_QP(bintree_it_goleft) (data_iter_t* it) {
	if (it == NULL || it->current == NULL || it->current->left == NULL)
		return;
	it->current = it->current->left;
	return;
}

void SGDC_QP(bintree_it_gonext) (data_iter_directed_t* it) {
	if (it == NULL || it->current == NULL)
		return;
	switch (it->type) {
		_SGDC_bintree_ltr:
			SGDC_QP(bintree_it_ltr_gonext) (it);
			break;
		_SGDC_bintree_rtl:
			/* SGDC_QP(bintree_it_rtl_gonext) -- not implemented yet*/
			break;
		default:
			break; /* TODO: return error on this case*/
	}
}

void SGDC_QP(bintree_it_ltr_gonext) (data_iter_directed_t* it) {
	if (it == NULL || it->current == NULL || it->type != _SGDC_bintree_ltr)
		return;

	data_node_t* node = it->current; SGDC_bintree_iter_state state = it->state;
	bool stop = false;
	
	do {
		switch (it->state) {
			_SGDC_bintree_to_left:
				if (node->left == NULL) {
					state = _SGDC_bintree_to_right;
					stop = true;
				} else {
					node = node->left;
				}
				break;
			_SGDC_bintree_to_right:
				if (node->right != NULL) {
					node = node->right;
					state = _SGDC_bintree_to_left;
				} else {
					switch (SGDC_QP(bintree_node_type) (node)) {
						_SGDC_bintree_node_root:
							stop = true;
							break;
						_SGDC_bintree_node_right:
							node = node->top;
							state = _SGDC_bintree_from_right;
							break;
						_SGDC_bintree_node_left:
							node = node->top;
							state = _SGDC_bintree_to_right;
							stop = true;
							break;
					}
				}
				break;
			_SGDC_bintree_from_right:
				switch (SGDC_QP(bintree_node_type) (node)) {
					_SGDC_bintree_node_root:
						stop = true;
						break;
					_SGDC_bintree_node_right:
						node = node->top;
						break;
					_SGDC_bintree_node_left:
						node = node->top;
						state = _SGDC_bintree_to_right;
						stop = true;
						break;
				}
				break;
		} /* switch it->state */
	} while (!stop)
	
	it->current = node;
	it->state = state;
	
	return;
}

#include "../default_type/default_type_end.h"
