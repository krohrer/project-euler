.PHONY: default all runtop clean clobber

OCAMLBUILD=ocamlbuild -use-ocamlfind
NAME=euler
TOP=$(NAME).top
ALL=$(shell ls p[0-9]*.ml)

default: $(TOP)

all: $(ALL:.ml=.native)

%.native: %.ml
	$(OCAMLBUILD) $@

%.top: *.ml
	$(OCAMLBUILD) $@

%: %.native
	./$<

runtop: $(TOP)
	./$(TOP) -I _build

clean:
	$(OCAMLBUILD) -clean

clobber: clean
	rm -f *~ *.annot *.native *.byte
