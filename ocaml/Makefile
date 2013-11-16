.PHONY: default all top clean clobber

OCAMLBUILD=ocamlbuild -use-ocamlfind
TOP=euler
ALL=$(shell ls p[0-9]*.ml)

default: $(ALL:.ml=.native)

%.native: %.ml
	$(OCAMLBUILD) $@

%: %.native
	./$<

top:
	$(OCAMLBUILD) $(TOP).top
	./$(TOP).top -I _build

clean:
	$(OCAMLBUILD) -clean

clobber: clean
	rm -f *~ *.annot *.native *.byte
