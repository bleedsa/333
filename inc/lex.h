#ifndef __LEX_H__
#define __LEX_H__

#include <str.h>

typedef enum {
	TOK_I,    /* int */
	TOK_U,    /* unsigned */
	TOK_F,    /* float */
	TOK_C,    /* char */
	TOK_STR,  /* string */
	TOK_ID,   /* identifier */
	TOK_LPRN, /* ( */
	TOK_RPRN, /* ) */
} TokTy;

typedef struct {
	TokTy ty;
	Pos pos;
	C *ptr;
	S len;
} Tok;

extern Tok TOK_EOF;
extern Tok *LEX_TOKS;

bool tok_eq(Tok *x, Tok *y);
C *tok_tostr(Tok *t);

C *lex(C *src);

/* check if tok != 0 */
inl bool tok_is(Tok *t) {
	return memcmp(t, &TOK_EOF, Z(Tok)) != 0;
}

#endif
