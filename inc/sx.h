#ifndef __SX_H__
#define __SX_H__

/*
 * S expressions
 */

#include <u.h>
#include <mem.h>

/* a parser attribute */
typedef struct {
	union {
		i64 i;
		u64 u;
		F f;
		C c;
		C **str;
	};
} SXAttr;

/* parse attributes stored by a S expr */
typedef struct {
	SXAttr x;
	SXAttr y;
} SXAttrs;

#define mkattrsx(x) ((SXAttrs){*(SXAttr*)&x, {0}})
#define mkattrsxy(x, y) ((SXAttrs){(SXAttr)x, (SXAttr)y})

/* the parse attributes table */
extern SXAttrs *SXATTRS;

/* the type of an S expr */
typedef enum {
	SX_I,    /* int */
	SX_U,    /* unsigned */
	SX_F,    /* float */
	SX_C,    /* char */
	SX_STR,  /* string */
	SX_X,    /* identifier */
	SX_CONS, /* conseq */
	SX_LET,  /* let in */
} SXTy;

/* an S expression */
typedef struct {
	SXTy ty;
	S attrs;
} SX;

V sx_init(V);
V sx_deinit(V);

S sx_add_attrs(SXAttrs a);

SXAttr *sx_getx(SX *x); /* get x arg */
SXAttr *sx_gety(SX *x); /* get y arg */

inl SX mkI(i64 x) {
	auto a = mkattrsx(x);
	return (SX){SX_I, sx_add_attrs(a)};
}

inl SX mkF(F x) {
	auto a = mkattrsx(x);
	return (SX){SX_F, sx_add_attrs(a)};
}

#endif
