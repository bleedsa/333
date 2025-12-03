#include <u.h>
#include <sym.h>
#include <ast.h>

V init(V) {
	sym_init();
	ast_init();
}

V deinit(V) {
	sym_deinit();
}
