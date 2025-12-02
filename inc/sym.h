#ifndef __SYM_H__
#define __SYM_H__

#include <u.h>
#include <mem.h>

typedef struct {
	Pos pos;
	C *ptr;
} Sym;

typedef struct {
	S len, cap;
	Sym *ptr;
} Syms;

extern Syms SYMS;

V syms_init(V);

i64 fnd_str(C *s);
i64 sym_add(Pos p, C *s);

#endif
