#include <stdio.h>

#include <err.h>
#include <lex.h>
#include <sym.h>

typedef enum {
	LEX_UNK,

	/* ints */
	LEX_NEG,
	LEX_INT,

	/* floats */
	LEX_FLT_DOT,
	LEX_FLT_DEC, /* decimal */

	/* strings */
	LEX_QUOTE,
	LEX_STR,
	LEX_QUOTE_R,

	/* verbs */
	LEX_VERB,
	LEX_VERB2,

	/* identifier */
	LEX_ID, 
} LexState;

Tok TOK_EOF = {0, {0, 0}, 0, 0};
Tok *LEX_TOKS;

static CC *VERB_CHRS = "!@#$%^&*_+~-=|:'<>?/.,\\";

inl bool isverb(C c) {
	return !!(strchr(VERB_CHRS, c));
}

static CC *VERB2_CHRS = ".:";

inl bool isverb2(C c) {
	return !!(strchr(VERB2_CHRS, c));
}

C *tok_tostr(Tok *t) {
	auto L = t->len;
	auto buf = mk(C, L+1);
	memcpy(buf, t->ptr, Z(C)*L);
	buf[L] = 0;
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
	bool add_sym;
	S cap = 8, len = 0, tlen = 0;
	Pos p = pos_mk(), thisp = p;
	TokTy ty;
	LexState state = LEX_UNK;

	/* make the return vector */
	LEX_TOKS = mk(Tok, cap);
	memset(LEX_TOKS, 0, Z(Tok)*cap);

	for (c = *src; true; src++, c = *src, pos_inc(&p)) {
	start:
		println("%c %d", c, c, state);
		switch (state) {
		/* unknown state. switch based on char type to set new state */
		case LEX_UNK: {
			if (c == EOF || !c) goto eof;
			else if (c == '\n') pos_nl(&p);
			else if (isspace(c)) continue;
			else if (isalpha(c)) {state = LEX_ID;   goto init;}
			else if (isdigit(c)) {state = LEX_INT;  goto init;}
			else if (isverb(c))  {state = LEX_VERB; goto init;}
			else if (c == '"')   {state = LEX_QUOTE;goto init;}
			else if (c == '-' && isdigit(*(src + 1))) {
				state = LEX_NEG; goto init;
			} else return err_lex(
				p, "invalid char during lexer pass: %c", c
			);
			break;

		init:
			ptr = src, tlen = 0, thisp = p, add_sym = false;
			goto start;
		}

		/* identifiers start with alpha but can contain alnum */
		case LEX_ID: {
			if (isalnum(c)) tlen++;
			else {
				ty = TOK_ID, add_sym = true;
				goto push;
			}
			break;
		}

		/* an integer with or without a negative sign */
		case LEX_INT: {
			if (isdigit(c)) tlen++;
			else {
				ty = TOK_I;
				goto push;
			}
			break;
		}

		/* the negative sign on a negative number */
		case LEX_NEG: {
			if (c == '-') {
				tlen++;
				state = LEX_INT;
			} else fatal("ICE: LEX_NEGINT on non-negative %c", c)
			break;
		}

		/* verb 1 */
		case LEX_VERB: {
			tlen++;
			if (isverb2(*(src + 1))) {
				state = LEX_VERB2;
				continue;
			}
			ty = TOK_OPR;
			goto push;
		}

		/* verb 2 */
		case LEX_VERB2: {
			tlen++;
			ty = TOK_OPR;
			goto push;
		}

		/* start a string */
		case LEX_QUOTE:
			state = LEX_STR;
			ptr++;
			break;

		/* a string body */
		case LEX_STR:
			if (c == '"') state = LEX_QUOTE_R;
			else if (!c) return err_lex(p, "unclosed string");
			else tlen++;
			break;

		/* rhs string quote */
		case LEX_QUOTE_R:
			ty = TOK_STR;
			goto push;

		/* should be unreachable */
		default:
			fatal("ICE: unknown state %d", state);

		/* finish lexing a tok and add it to the vec */
		push: {
			/* reset state */
			state = LEX_UNK;
			
			/* add the tok to LEX_TOKS */
			lex_toks_reZ(&cap, &len);
			LEX_TOKS[len++] = (Tok){
				.ty = ty,
				.pos = p,
				.ptr = ptr,
				.len = tlen,
			};

			/* optionally add symbol */
			if (add_sym) {
				C *sym = tok_tostr(LEX_TOKS+len-1);
				sym_add(thisp, sym);
				free(sym);
			}

			if (!c) goto eof;
		}
		}
	}

eof:
	return NULL;
}
