#include <u.h>
#include <sym.h>
#include <sx.h>
#include <err.h>
#include <prs.h>

V init(V) {
	sym_init();
	sx_init();
	prs_init();
}

V deinit(V) {
	sym_deinit();
	sx_deinit();
	prs_deinit();
	err_deinit();
}
