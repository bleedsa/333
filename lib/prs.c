#include <stdio.h>

#include <prs.h>

typedef enum {
	LEX_UNK,

	/* ints */
	LEX_NEG,
	LEX_INT,

	/* floats */
	LEX_FLT_DOT,
	LEX_FLT_DEC, /* decimal */

	/* strings */
	LEX_QUOTE_L,
	LEX_STR,
	LEX_QUOTE_R,

	/* verbs */
	LEX_VERB,
	LEX_VERB2,

	/* identifier */
	LEX_ID, 
} LexState;

Tok TOK_EOF = {0, {0, 0}, 0, 0};
C *LEX_ERR = 0;
Tok *LEX_TOKS;

static CC *VERB_CHRS = "!@#$%^&*_+~-=|:'<>?/.,\\";

inl bool isverb(C c) {
	return !!(strchr(VERB_CHRS, c));
}

static CC *VERB2_CHRS = ".:";

inl bool isverb2(C c) {
	return !!(strchr(VERB2_CHRS, c));
}

#define ERR(f...) { \
	if (!asprintf(&LEX_ERR, "error: 'lex: " f)) {fatal("asprintf()!!");} \
	else return LEX_ERR; \
}

C *tok_tostr(Tok *t) {
	auto L = t->len;
	auto buf = mk(C, L);
	memcpy(buf, t->ptr, Z(C)*L);
	return buf;
}

/* conditionally resize lexer return buffer based on capacity and length */
inl V lex_toks_reZ(S *cap, S *len) {
	if (*len >= *cap) {
		*cap *= 2;
		LEX_TOKS = remk(LEX_TOKS, Tok, *cap);
	}
}

C *lex(C *src) {
	C c, *ptr;
	S cap = 8, len = 0, tlen = 0;
	Pos p = pos_mk();
	TokTy ty;
	LexState state = LEX_UNK;

	/* make the return vector */
	LEX_TOKS = mk(Tok, cap);
	memset(LEX_TOKS, 0, Z(Tok)*cap);

	for (c = *src; true; src++, c = *src, pos_inc(&p)) {
	start:
		println("%c %d %d", c, c, state);
		switch (state) {
		/* unknown state. switch based on char type to set new state */
		case LEX_UNK: {
			if (c == EOF || !c) goto eof;
			else if (c == '\n') pos_nl(&p);
			else if (isspace(c)) continue;
			else if (isalpha(c)) {state = LEX_ID;   goto init;}
			else if (isdigit(c)) {state = LEX_INT;  goto init;}
			else if (isverb(c))  {state = LEX_VERB; goto init;}
			else if (c == '-' && isdigit(*(src + 1))) {
				state = LEX_NEG; goto init;
			} else ERR("invalid char during lexer pass: %c", c)
			break;

		init:
			ptr = src, tlen = 0;
			goto start;
		}

		case LEX_ID: {
			if (isalnum(c)) tlen++;
			else {
				ty = TOK_ID;
				goto push;
			}
			break;
		}

		case LEX_INT: {
			if (isdigit(c)) tlen++;
			else {
				ty = TOK_I;
				goto push;
			}
			break;
		}

		case LEX_NEG: {
			if (c == '-') {
				tlen++;
				state = LEX_INT;
			} else fatal("ICE: LEX_NEGINT on non-negative %c", c)
			break;
		}

		case LEX_VERB: {
			tlen++;
			if (isverb2(*(src + 1))) {
				tlen++;
				state = LEX_VERB2;
				continue;
			}
			ty = TOK_OPR;
			goto push;
		}

		case LEX_VERB2: {
			tlen++;
			ty = TOK_OPR;
			goto push;
		}

		/* should be unreachable */
		default:
			fatal("ICE: unknown state %d", state);

		/* finish lexing a tok and add it to the vec */
		push: {
			state = LEX_UNK;
			lex_toks_reZ(&cap, &len);
			LEX_TOKS[len++] = (Tok){
				.ty = ty,
				.pos = p,
				.ptr = ptr,
				.len = tlen,
			};
			if (!c) goto eof;
		}
		}
	}

eof:
	return NULL;
}
