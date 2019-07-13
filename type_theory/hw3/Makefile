.PHONY: pack all run clean
GENERATED=parser.mli parser.ml lexer.ml
OCAMLC=ocamlc # ocamlopt for speed
PACKAGE=hw3.zip

DEL=rm -f

all: main.exe

run:
	./main.exe

parser: data.cmi
	$(OCAMLC) -c $(GENERATED)

data.cmi:
	$(OCAMLC) -c data.ml

main.exe: $(GENERATED) data.cmi parser
	$(OCAMLC) data.ml $(GENERATED) main.ml -o main.exe

$(GENERATED): lexer.mll parser.mly
	ocamllex lexer.mll
	ocamlyacc parser.mly

pack: $(GENERATED)
	zip $(PACKAGE) parser.mly Makefile main.ml lexer.mll data.ml

clean:
	$(DEL) $(GENERATED:src/%=%) *.c* *.o*
	$(DEL) main.exe $(PACKAGE)
