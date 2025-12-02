#include <stdio.h>

#include <u.h>
#include <str.h>
#include <prs.h>

I main(I argc, C **argv) {
	C *err, *str;
	Tok t;
	S i;

	if (argc < 2) fatal("usage: %s [expr]", argv[0]);

	err = lex(argv[1]);
	if (!(err == NULL)) fatal("%s", err);

	for (i = 0, t = *LEX_TOKS; tok_is(&t); i++, t = LEX_TOKS[i]) {
		str = tok_tostr(&t);
		println("tok: %d %s", t.ty, str);
		free(str);
	}

	return 0;
}
