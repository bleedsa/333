#include <sx.h>

static S A_len = 0, A_cap = 8;
SXAttrs *SXATTRS;

static V SXATTRS_reZ(V) {
	if (A_len >= A_cap) {
		A_cap *= 2;
		SXATTRS = remk(SXATTRS, SXAttrs, A_cap);
	}
}

V sx_init() {
	SXATTRS = mk(SXAttrs, A_cap);
}

V sx_deinit() {
	free(SXATTRS);
}

S sx_add_attrs(SXAttrs a) {
	SXATTRS_reZ();
	SXATTRS[A_len++] = a;
	return A_len - 1;
}

SXAttr *sx_getx(SX *x) {
	auto as = SXATTRS + x->attrs;
	return &as->x;
}

SXAttr *sx_gety(SX *x) {
	auto as = SXATTRS + x->attrs;
	return &as->y;
}
