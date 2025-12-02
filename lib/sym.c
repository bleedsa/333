#include <sym.h>

Syms SYMS;

static V syms_reZ() {
	auto Y = &SYMS;
	if (Y->len >= Y->cap) {
		Y->cap *= 2;
		Y->ptr = remk(Y->ptr, Sym, Y->cap);
	}
}

V init(V) {
	S cap = 8;
	auto buf = mk(Sym, cap);
	SYMS = (Syms){0, cap, buf};
}

i64 fnd_str(C *s) {
	auto ptr = SYMS.ptr;
	S L = SYMS.len;

	for (S i = 0; i < L; i++) {
		if (strcmp(ptr[i].ptr, s) == 0) return i;
	}

	return -1;
}

/* NOTE: moves out of s Z(C)*(strlen(s)+1) */
i64 sym_add(Pos p, C *s) {
	i64 i = fnd_str(s);
	if (i < 0) {
		/* make the symbol string ptr */
		S L = strlen(s) + 1;
		C *buf = mk(C, L);
		memmove(buf, s, Z(C)*L);

		syms_reZ();
		SYMS.ptr[SYMS.len++] = (Sym){
			.pos = p,
			.ptr = buf,
		};

		return SYMS.len - 1;
	} else {
		return i;
	}
}
