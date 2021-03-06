#include "../qualify_macros/qualify_macros.h"

#ifndef SGDC_SIMPLE_DATATYPE
	#define data_node_t SGDC_QP( __name__ )
#else
	#ifdef _SGDC_NAME_H /* simple datatype enabled but header is included more than once*/
	#error SGDC: cannot use SGDC_SIMPLE_DATATYPE on same data structure more than once
	#endif
#endif

#ifndef _SGDC_NAME_H
#define _SGDC_NAME_H 1
#endif

#include "../default_type/default_type_begin.h"

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct _SGDC_QP( __name__ ) {
	/* internals */
	T value;
} data_node_t;

/* code goes here */

#ifndef SGDC_SIMPLE_DATATYPE
	#undef data_node_t
#endif

#include "../default_type/default_type_end.h"
