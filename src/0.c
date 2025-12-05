#include <stdio.h>

#include <u.h>
#include <str.h>
#include <lex.h>
#include <sym.h>
#include <sx.h>
#include <prs.h>
#include <err.h>

I main(I argc, C **argv) {
	C *err, *str;
	Tok t;
	Sym *sym;
	S i;

	if (argc < 2) fatal("usage: %s [expr]", argv[0]);
	init();

	err = lex(argv[1]);
	if (err != NULL) {
		eprintln("%s", err);
		free(err);
		return -1;
	}

	for (i = 0, t = *LEX_TOKS; tok_is(&t); i++, t = LEX_TOKS[i]) {
		str = tok_tostr(&t);
		println("tok: %d %s", t.ty, str);
		free(str);
	}

	for (
		i = 0, sym = SYMS.ptr;
		i < SYMS.len;
		i++, sym = SYMS.ptr + i
	) {
		println(
			"sym: %zu, %zu\t%s",
			sym->pos.line, sym->pos.col, sym->ptr
		);
	}

	auto idx = parse();
	if (idx < 0) {
		eprintln("%s", prs_error());
		return idx;
	}

	println("%d", PRS_SXS[i]->ty);

	free(LEX_TOKS);
	return 0;
}
