#ifndef __PRS_H__
#define __PRS_H__

#include <u.h>
#include <err.h>
#include <lex.h>

extern S idx;

inl C *mtch(S tok) {
	auto x = LEX_TOKS+tok, y = LEX_TOKS+idx;
	if (tok_eq(x, y)) {
		idx++;
		return NULL;
	} else return err_prs(x->pos, "failed to match token");
}

C *Noun(S tok);

#endif
