#ifndef _SGDC_NAME_H
#define _SGDC_NAME_H 1
#endif

#include "../qualify_macros/qualify_macros.h"
#include "../default_type/default_type_begin.h"

#ifndef SGDC_SIMPLE_DATATYPE
#define data_node_t SGDC_Q( __name__ )
#endif

#ifndef _MALLOC_H
#include <malloc.h>
#endif

typedef struct _SGDC_QP( __name__ ){
	/* internals */
} data_node_t;

/* code goes here */

#include "../default_type/default_type_end.h"
