.PHONY: pack all run clean src/parcer src/sources
GENERATED=src/parser.mli src/parser.ml src/lexer.ml
SOURCE=check.ml deduct.ml
OCAMLC=ocamlc # ocamlopt for speed
PACKAGE=hw3.zip

ifeq ($(OS),Windows_NT)
	DEL=del /f
else
	DEL=rm -f
endif

all: main.exe

run: main.exe
	./main.exe

src/parser: src/data.cmi
	cd src && $(OCAMLC) -c $(GENERATED:src/%=%)

src/data.cmi:
	cd src && $(OCAMLC) -c data.ml

src/sources: src/parser
	cd src && $(OCAMLC) -c $(SOURCE:src/%=%)

main.exe: $(GENERATED) src/data.cmi src/sources
	cd src && $(OCAMLC) data.ml $(GENERATED:src/%=%) $(SOURCE:src/%=%) main.ml -o ../main.exe

pack: $(GENERATED)
	zip $(PACKAGE) -r Makefile src proofs

$(GENERATED): src/lexer.mll src/parser.mly
	ocamllex src/lexer.mll 
	ocamlyacc src/parser.mly

clean:
	cd src && $(DEL) $(GENERATED:src/%=%) *.c* *.o*
	$(DEL) main.exe $(PACKAGE)
