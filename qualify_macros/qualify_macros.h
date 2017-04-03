#ifndef SGDC_PREFIX
#define SGDC_PREFIX SGDC_
#endif

#ifdef  SGDC_SIMPLE_QUALIFIERS
	#define Q SGDC_Q
	#define QP SGDC_QP
#endif

#define SGDC_Q(f) QUALIFY_WITH_T(f,T)
#define QUALIFY_WITH_T (f,T) QUALIFY_WITH_T_(f,T)
#define QUALIFY_WITH_T_(f,T) f ## _ ## T

#define SGDC_QP(f) SGDC_QP_(SGDC_PREFIX, f, T)
#define SGDC_QP_(p, f, T) QUALIFY_WITH_PREFIX_T (p, f, T)
#define QUALIFY_WITH_PREFIX_T(p, f, T) p ## f ## _ ## T

#define _SGDC_QP(f) _SGDC_QP_(SGDC_PREFIX, f, T)
#define _SGDC_QP_(p, f, T) _QUALIFY_WITH_PREFIX_T (p, f, T)
#define _QUALIFY_WITH_PREFIX_T(p, f, T) _ ## p ## f ## _ ## T
