#include <prs.h>

S idx = 0;

static S cap = 8, len = 0;

inl Tok *peek() {
	return LEX_TOKS+idx;
}

C *Noun(S tok) {
	auto t = peek();
	switch (t->ty) {
	case TOK_I:

	}

	return NULL;
}
