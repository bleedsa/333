#!/usr/bin/env -S rlwrap etc/k.com

/ utils
has:{~0N~y?x}

/ filters
ext:{x~|#[x]#|y} / y has ext x?
(c;h):ext@'(".",)'"ch"
srcs:{[fil;dir](dir,"/",)'d@&fil'd:0:dir}

/ get files
(srcc;srch):srcs[;"src"]'(c;h)
(libc;libh):srcs[;"lib"]'(c;h)
inch:srcs[h;"inc"]

/ flags
A:|/has[;`argv[]]'
rel:A("--release";"--rel")
lnx:A("--linux";"--lnx")
nat:A("--native";"--nat")

/ set config vars
NAME:"333"
CC:$[nat;"clang";"ape/bin/cosmocc"]
AR:$[nat;"ar";   "ape/bin/ar.ape"]
CFLAGS:" "/("-std=gnu23 -Iinc",$[nat;"";" -mcosmo -mclang"]
            $[rel;$[nat;"";"-mtiny "],"-O3";$[nat;"";"-mdbg "],"-g -DDBG"]
            $[lnx&~nat;"-moptlinux -fomit-frame-pointer";"-fno-omit-frame-pointer"]
            "-Wall -Wextra -Wno-unused-parameter -Wno-unused-variable"
            "-mno-omit-leaf-frame-pointer -Wno-unused-function")

/ files
outof:{"o/",x}
(exeof;objof):{outof y,".",x}@'("com";"o")
libof:{outof "lib/lib",y,".",x}@"a"
srcof:{outof "src/",x}

/ make
bld:{[cmd;out;in]out,": ",(" "/in),"\n\t",cmd}

/ rules
ar:bld@AR," rcs $@ $^"
cc:bld@CC," -c ",CFLAGS," $^ -o $@"
lnk:bld@" "/(CC;CFLAGS;" $^ -o $@")

/ builders
bldc:{cc[objof x;,x]}

/ targets
exe:exeof NAME

/ objs
`0:"all: "," "/("o o/src o/lib";" "/objs:objof'srcc,libc;exe;lib333:"o/lib333.a");
`0:'bldc'srcc;
`0:'bldc'libc;

/ out
`0:"o o/src o/lib:\n\tmkdir -p $@"
`0:ar[lib333;objof'libc]
`0:lnk[exe;objs]
`0:"clean:\n\trm -rf o"
