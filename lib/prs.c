#include <prs.h>
#include <err.h>

static SXsEnt *PRS_SXENTS;
SX **PRS_SXS;

static S ent_cap = 8, ent_len = 0;

/* resize PRS_SXENTS */
inl V PRS_SXENTS_reZ(V) {
	if (ent_len >= ent_cap) {
		ent_cap *= 2;
		PRS_SXENTS = remk(PRS_SXENTS, SXsEnt, ent_cap);
	}
}

/* resize a SXsEnt */
inl V SXsEnt_reZ(SXsEnt *x) {
	if (x->len >= x->cap) {
		x->cap *= 2;
		x->ptr = remk(x->ptr, SX, x->cap);
	}
}

/* push a new SXsEnt to PRS_SXENTS and return a pointer to it */
inl SXsEnt *push_SXsEnt(V) {
	PRS_SXENTS_reZ();

	S cap = 8, len = 0;
	auto ptr = mk(SX, cap);
	PRS_SXENTS[ent_len++] = (SXsEnt) {
		.ptr = ptr,
		.cap = cap,
		.len = len,
	};

	return PRS_SXENTS + (ent_len - 1);
}

inl V push_SX(S i, SX x) {
	SXsEnt_reZ(PRS_SXENTS+i);
}

V SXsEnt_free(SXsEnt *x) {
	free((V*)x->ptr);
}

V prs_cpy_sxs(V) {
	S L = ent_len;
	PRS_SXS = mk(SX*, L);
	for (S i = 0; i < L; i++) PRS_SXS[i] = PRS_SXENTS[i].ptr;
}

V prs_init(V) {
	PRS_SXENTS = mk(SXsEnt, ent_cap);
}

V prs_deinit(V) {
	for (S i = 0; i < ent_len; i++) SXsEnt_free(PRS_SXENTS+i);
	free(PRS_SXENTS);
}

i64 parse(V) {
	auto en = push_SXsEnt();
	goto err;

err:
	err_prs((Pos){0, 0}, "PARSER NYI");
	return -1;
}
