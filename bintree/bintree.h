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

data_t SGDC_QP(bintree_combine) (data_t ltree, T value, data_t rtree) {
	data_t newtree = SGDC_QP(bintree_create) (value);
	newtree.root->left  = ltree.root;
	newtree.root->left->top = newtree.root;
	newtree.root->right = rtree.root;
	newtree.root->right->top = newtree.root;
	return newtree;
}

void SGDC_QP(bintree_free) (data_t tree) {
	SGDC_QP(bintree_node_free) (tree.root);
	return;
}

data_iter_t SGDC_QP(bintree_it_make) (data_t tree) {
	data_iter_t newiter;
	newiter.current = tree.root;
	return newiter;
}

data_iter_t SGDC_QP(bintree_it_makeend) (data_t tree) {
    data_iter_t newiter;
    if (tree.root == NULL)
        newiter.current = NULL;
    else
        newiter.current = tree.root->top;
    return newiter;
}

data_iter_directed_t SGDC_QP(bintree_it_makeltr) (data_t tree) {
	data_iter_directed_t newiter;
	newiter.current = SGDC_QP(bintree_node_leftest) (tree.root);
	newiter.type = _SGDC_bintree_ltr;
	newiter.state = _SGDC_bintree_to_right;
	return newiter;
}

data_iter_directed_t SGDC_QP(bintree_it_makertl) (data_t tree) {
	data_iter_directed_t newiter;
	newiter.current = SGDC_QP(bintree_node_rightest) (tree.root);
	newiter.type = _SGDC_bintree_rtl;
	newiter.state = _SGDC_bintree_to_left;
	return newiter;
}

bool SGDC_QP(bintree_it_reached) (data_iter_directed_t currit, data_iter_t endit) {
    return currit.current == endit.current;
}

bool SGDC_QP(bintree_it_hasright) (data_iter_t it) {
	if (it.current->right != NULL)
		return true;
	else
		return false;
}

bool SGDC_QP(bintree_it_hasleft) (data_iter_t it) {
	if (it.current->left != NULL)
		return true;
	else
		return false;
}

void SGDC_QP(bintree_it_insright) (data_iter_t it, T insvalue) {
	SGDC_QP(bintree_node_insright) (it.current, insvalue);
}

void SGDC_QP(bintree_it_insleft) (data_iter_t it, T insvalue) {
	SGDC_QP(bintree_node_insleft) (it.current, insvalue);
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
		case _SGDC_bintree_ltr:
			SGDC_QP(bintree_it_ltr_gonext) (it);
			break;
		case _SGDC_bintree_rtl:
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
		switch (state) {
			case _SGDC_bintree_to_left:
				if (node->left == NULL) {
					state = _SGDC_bintree_to_right;
					stop = true;
				} else {
					node = node->left;
				}
				break;
			case _SGDC_bintree_to_right:
				if (node->right != NULL) {
					node = node->right;
					state = _SGDC_bintree_to_left;
				} else {
					switch (SGDC_QP(bintree_node_type) (node)) {
						case _SGDC_bintree_node_root:
							stop = true;
							break;
						case _SGDC_bintree_node_right:
							node = node->top;
							state = _SGDC_bintree_from_right;
							break;
						case _SGDC_bintree_node_left:
							node = node->top;
							state = _SGDC_bintree_to_right;
							stop = true;
							break;
					}
				}
				break;
			case _SGDC_bintree_from_right:
				switch (SGDC_QP(bintree_node_type) (node)) {
					case _SGDC_bintree_node_root:
						stop = true;
						break;
					case _SGDC_bintree_node_right:
						node = node->top;
						break;
					case _SGDC_bintree_node_left:
						node = node->top;
						state = _SGDC_bintree_to_right;
						stop = true;
						break;
				}
				break;
			case _SGDC_bintree_from_left:
				state = _SGDC_bintree_to_right;
				stop = true;
		} /* switch it->state */
	} while (!stop);
	
	it->current = node;
	it->state = state;
	
	return;
}

void SGDC_QP(bintree_it_rtl_gonext) (data_iter_directed_t* it) {
	if (it == NULL || it->current == NULL || it->type != _SGDC_bintree_rtl)
		return;

	data_node_t* node = it->current; SGDC_bintree_iter_state state = it->state;
	bool stop = false;

	do {
		switch (state) {
			case _SGDC_bintree_to_right:
				if (node->right == NULL) {
					state = _SGDC_bintree_to_left;
					stop = true;
				} else {
					node = node->right;
				}
				break;
			case _SGDC_bintree_to_left:
				if (node->left != NULL) {
					node = node->left;
					state = _SGDC_bintree_to_right;
				} else {
					switch (SGDC_QP(bintree_node_type) (node)) {
						case _SGDC_bintree_node_root:
							stop = true;
							break;
						case _SGDC_bintree_node_right:
							node = node->top;
							state = _SGDC_bintree_to_left;
							stop = true;
							break;
						case _SGDC_bintree_node_left:
							node = node->top;
							state = _SGDC_bintree_from_left;
							break;
					}
				}
				break;
			case _SGDC_bintree_from_left:
				switch (SGDC_QP(bintree_node_type) (node)) {
					case _SGDC_bintree_node_root:
						node = node->top;
						stop = true;
						break;
					case _SGDC_bintree_node_right:
						node = node->top;
						state = _SGDC_bintree_to_left;
						stop = true;
						break;
					case _SGDC_bintree_node_left:
						node = node->top;
						break;
				}
				break;
            case _SGDC_bintree_from_right:
                state = _SGDC_bintree_to_left;
                stop = true;
		} /* switch it->state */
	} while (!stop);

	it->current = node;
	it->state = state;

	return;
}

#include "../default_type/default_type_end.h"
