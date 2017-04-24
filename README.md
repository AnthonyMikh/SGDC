# What is SGDC
SGDC stands for "student's general data collection". SGDC is a collection of abstract data structures written in pure C. Unlike many other similar libraries, it doesn't mess around casting from and to `void*`. SGDC also isn't built upon `typedef`s so it lets you have several SGDC data structures in one program holding values of different types.

# Usage
Suppose you want to have binary tree holding `double`s. In order to do it, put `sgdc` directory along with your sources and write in the beginning od code file:
```C
#define T double
#include "sgdc/bintree/bintree.h"
...
/* code stuff */
```
Now you're able to do things like this:
```C
SGDC_bintree_double* mytree = SGDC_bintree_create_double(0.5d);
SGDC_bintree_insertr_double(mytree, 0.888d);
```
As you can see, T defines the type of data stucture. All SGDC functions begin with `SGDC_` and tailed by underscore followed by type name in order to escape name collisions.

## More features
* Of course, you can have more than one typed binary trees. Just define `T` before including header file:

  ````C
  #define T char
  #include "sgdc/bintree/bintree.h"

  #define T float
  #include "sgdc/bintree/bintree.h"

  #define T long
  #include "sgdc/bintree/bintree.h"
  ...
  /* working with trees of chars, floats and longs*/
  ````

* You can also not to define any T. In this case data structure will hold `int` values:

  ````C
  #undef T
  #include "sgdc/bintree/bintree.h"
  ...
  /* works with "SGDC_bintree_create_int" etc. */
  ````

* In case you find constant `SGDC_` too noisy, you can change it:

  ````C
  #define SGDC_PREFIX S
  #include "sgdc/bintree/bintree.h"
  ...
  /* now work with "S_bintree_create_int" */
  ````

    Or even remove it completely:

  ````C
  #define SGDC_PREFIX
  /* now functions have no prefix*/
  ````

* If you find typing `bintree_char` too tiring (esspecially if you have only one instance of structure), you can cut the corners:

  ````C
  #define SGDC_SIMPLE_DATATYPE
  #define T char
  #include "sgdc/bintree/bintree.h"
  ...
  //now you're able to write stuff like this:
  data_node_t* tree = SGCD_bintree_create_char('☺');
  ````
  
  Note that if you try to use this option more than once, you will get an error during compilation.

* You can ease typing long names using qualify macros:

  ````C
  #define T char
  #include "sgdc/bintree/bintree.h"
  ...
  SGDC_QP(bintree)* tree = SGDC_QP(bintree_create)('A');
  ````

    You can type even less if you enable simple qualifiers:
    
  ````C
  #define SGDC_SIMPLE_QUALIFIERS
  #include "sgdc/bintree/bintree.h"
  ...
  QP(bintree)* tree = QP(bintree_create)('A');
  ````

# Known limitations
Since name qualifying is done via macros, you can't use names containg `*` or spaces. Use `typedef` in order to solve this issue.
