#ifndef __SYM_H__
#define __SYM_H__

#include <u.h>
#include <mem.h>

typedef struct {
	Pos pos;
	C *ptr;
} Sym;

V sym_free(Sym *x);

typedef struct {
	S len, cap;
	Sym *ptr;
} Syms;

extern Syms SYMS;

V sym_init(V);
V sym_deinit(V);

i64 fnd_str(C *s);
i64 sym_add(Pos p, C *s);

#endif
