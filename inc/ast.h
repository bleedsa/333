#ifndef __AST_H__
#define __AST_H__

#include <u.h>

typedef enum {
	X_I,   /* int */
	X_U,   /* unsigned int */
	X_F,   /* float */
	X_C,   /* char */
	X_STR, /* string */
	X_O,   /* lambda */
	X_FUN, /* named function */
	X_LET, /* let expr */
} ExprTy;

typedef struct {
	ExprTy ty;
	S attr;
} Expr;

typedef struct {
	union {
		i64 i;
		u64 u;
		F f;
		C c;
		C **str;
	};
	bool free;
} PrsAttr;

extern PrsAttr *PRS_ATTRS;

V ast_init(V);

S ast_add_attr_i(i64 x);
S ast_add_attr_str(C *);

#endif
