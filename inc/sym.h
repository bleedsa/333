#ifndef __SYM_H__
#define __SYM_H__

#include <u.h>

typedef struct {
	Pos pos;
	C *ptr;
} StrSym;

typedef struct {
	S len, cap;
	StrSym *ptr;
} StrSyms;

extern StrSyms STR_SYMS;

V syms_init(void);

#endif
