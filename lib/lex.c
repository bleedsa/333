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

	/* identifier */
	LEX_ID, 
} LexState;

Tok TOK_EOF = {0, {0, 0}, 0, 0};
Tok *LEX_TOKS;

/* the chars that can be in an identifier */
static CC *ID_CHRS =
	"qwertyuiopasdfghjklzxcvbnm"
	"QWERTYUIOPASDFGHJKLZXCVBNM"
	"!@#$%^&*_+|\\:'<,>.?/~";

/* is c a valid identifier char? */
inl bool isid(C c) {
	return !!(strchr(ID_CHRS, c));
}

bool tok_eq(Tok *x, Tok *y) {
	return x->ty == y->ty
		&& pos_eq(&x->pos, &y->pos)
		&& strcmp(x->ptr, y->ptr)
		&& x->len == y->len;
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
	/* 
	 * boolean conditions that change `push:` behavior.
	 * sometimes a lexer state adds a symbol on push.
	 */
	bool add_sym;
	/* lexer buffer capacity, length. the current token length. */
	S cap = 8, len = 0, tlen = 0;
	/* the current lexer position and the position of this token's start */
	Pos p = pos_mk(), thisp = p;
	/* the type of the current token */
	TokTy ty;
	/* the state of the lexer */
	LexState state = LEX_UNK;

	/* make the return vector */
	LEX_TOKS = mk(Tok, cap);
	memset(LEX_TOKS, 0, Z(Tok)*cap);

	/* state machine hot loop is here */
	for (c = *src; true; src++, c = *src, pos_inc(&p)) {
	start:
		println("%c %d", c, state);
		switch (state) {
		/* unknown state. switch based on char type to set new state */
		case LEX_UNK: {
			if (c == EOF || !c) goto eof;
			else if (c == '\n') pos_nl(&p);
			else if (isspace(c)) continue;
			else if (isid(c)) {state = LEX_ID;   goto init;}
			else if (isdigit(c)) {state = LEX_INT;  goto init;}
			else if (c == '"')   {state = LEX_QUOTE;goto init;}
			else if (c == '-' && isdigit(*(src + 1))) {
				state = LEX_NEG; goto init;
			} else {
				/* check for single char tokens */
				switch (c) {
				case '(': ty = TOK_LPRN, ptr = src; goto push_c;
				case ')': ty = TOK_RPRN, ptr = src; goto push_c;
				default:
					return err_lex(
						p, "invalid char: %c", c
					);
				}
			}
			break;

		init:
			ptr = src, tlen = 0, thisp = p;
			add_sym = false;
			goto start;
		}

		/* identifiers start with alpha but can contain alnum */
		case LEX_ID: {
			if (isid(c)||isdigit(c)) tlen++;
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
			ty = TOK_STR, add_sym = true;
			goto push;

		/* should be unreachable */
		default:
			fatal("ICE: unknown state %d", state);

		/* jump here to finish lexing a tok and add it to the vec.
		 * setting certain variables before the push changes the
		 * behavior here. */
		push:
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

			/* jump somewhere else */
			if (!c) goto eof;
			/* goto start doesn't inc the lexer */
			goto start;

		/* jump here to push a single char token */
		push_c:
			state = LEX_UNK;

			/* add the tok to LEX_TOKS */
			lex_toks_reZ(&cap, &len);
			LEX_TOKS[len++] = (Tok){
				.ty = ty,
				.pos = p,
				.ptr = ptr,
				.len = 1,
			};

			if (!c) goto eof;
			continue;
		}
	}

eof:
	return NULL;
}
