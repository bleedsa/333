#ifndef __PRS_H__
#define __PRS_H__

#include <u.h>
#include <sx.h>

typedef struct {
	SX *ptr;
	S cap, len;
} SXsEnt;

extern SX **PRS_SXS;

V SXsEnt_free(SXsEnt *x);

V prs_init(V);
V prs_deinit(V);
V prs_cpy_sxs(V);
i64 parse(V);


#endif
