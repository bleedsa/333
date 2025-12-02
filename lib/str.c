#include <str.h>

Str str_mk(void) {
	S cap = 8;
	C *ptr = mk(C, cap);
	memset(ptr, 0, Z(C)*cap);
	return (Str){0, 8, ptr};
}

V str_append(Str *str, C *x) {
	for (; *x; x++) str_push(str, *x);
}

V str_free(Str *str) {
	free(str->ptr);
}
