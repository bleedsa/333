#include <ast.h>
#include <mem.h>

static S A_len = 0, A_cap = 8;
PrsAttr *PRS_ATTRS;

V ast_init() {
	PRS_ATTRS = mk(PrsAttr, A_cap);
}
