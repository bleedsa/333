all: o o/src o/lib o/src/0.c.o o/lib/str.c.o o/lib/err.c.o o/lib/sx.c.o o/lib/u.c.o o/lib/sym.c.o o/lib/prs.c.o o/lib/lex.c.o o/333.com o/lib333.a
o/src/0.c.o: src/0.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/str.c.o: lib/str.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/err.c.o: lib/err.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/sx.c.o: lib/sx.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/u.c.o: lib/u.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/sym.c.o: lib/sym.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/prs.c.o: lib/prs.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/lex.c.o: lib/lex.c
	ape/bin/cosmocc -c -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o o/src o/lib:
	mkdir -p $@
o/lib333.a: o/lib/str.c.o o/lib/err.c.o o/lib/sx.c.o o/lib/u.c.o o/lib/sym.c.o o/lib/prs.c.o o/lib/lex.c.o
	ape/bin/ar.ape rcs $@ $^
o/333.com: o/src/0.c.o o/lib/str.c.o o/lib/err.c.o o/lib/sx.c.o o/lib/u.c.o o/lib/sym.c.o o/lib/prs.c.o o/lib/lex.c.o
	ape/bin/cosmocc -std=gnu23 -Iinc -mcosmo -mclang -mtiny -O3 -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function  $^ -o $@
clean:
	rm -rf o
