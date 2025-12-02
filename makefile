all: o o/src o/lib o/src/0.c.o o/lib/str.c.o o/lib/vec.c.o o/lib/prs.c.o o/333.com o/lib333.a
o/src/0.c.o: src/0.c
	clang -c -std=gnu23 -Iinc -g -DDBG -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/str.c.o: lib/str.c
	clang -c -std=gnu23 -Iinc -g -DDBG -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/vec.c.o: lib/vec.c
	clang -c -std=gnu23 -Iinc -g -DDBG -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o/lib/prs.c.o: lib/prs.c
	clang -c -std=gnu23 -Iinc -g -DDBG -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function $^ -o $@
o o/src o/lib:
	mkdir -p $@
o/lib333.a: o/lib/str.c.o o/lib/vec.c.o o/lib/prs.c.o
	ar rcs $@ $^
o/333.com: o/src/0.c.o o/lib/str.c.o o/lib/vec.c.o o/lib/prs.c.o
	clang -std=gnu23 -Iinc -g -DDBG -fno-omit-frame-pointer -Wall -Wextra -Wno-unused-parameter -Wno-unused-variable -mno-omit-leaf-frame-pointer -Wno-unused-function  $^ -o $@
clean:
	rm -rf o
