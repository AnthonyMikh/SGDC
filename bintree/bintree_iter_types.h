#ifndef _SGDC_BINTREE_ITER_TYPES_H
#define _SGDC_BINTREE_ITER_TYPES_H 1

typedef enum {
	  _SGDC_bintree_to_left
	, _SGDC_bintree_to_right
	, _SGDC_bintree_from_left
	, _SGDC_bintree_from_right
} SGDC_bintree_iter_state;

typedef enum {
	_SGDC_bintree_ltr,
	_SGDC_bintree_rtl
} SGDC_bintree_iter_type;

#endif /* _SGDC_BINTREE_ITER_TYPES_H */
