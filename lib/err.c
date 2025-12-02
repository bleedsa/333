#include <stdarg.h>

#include <err.h>
#include <str.h>

C *err_lex(Pos p, CC *fmt, ...) {
	va_list args;
	C *buf;
	Str str;

	va_start(args, fmt);
	str = str_mk();

	str_append(&str, "err: 'lex: ");
	if (0 > asprintf(&buf, "%zu, %zu", p.line, p.col)) fatal("asprintf!!");
	str_append(&str, buf);
	free(buf);

	str_append(&str, " \n\t");
	if (0 > vasprintf(&buf, fmt, args)) fatal("asprintf!!");
	str_append(&str, buf);
	free(buf);

	return str.ptr;
}
