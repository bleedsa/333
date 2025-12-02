#ifndef __VEC_H__
#define __VEC_H__

#include <u.h>

typedef struct {
	S z, len, cap;
	void *ptr;
} Vec;

Vec vec_mk(S z, S cap);
V vec_free(Vec *v);

#endif
