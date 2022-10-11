all: bminor-parser

bminor-parser: parser.o scanner.o bminor.o token_map.o
	gcc -o bminor scanner.o bminor.o parser.o token_map.o

bminor-scanner: token.h scanner.o bminor.o token_map.o
	gcc -o bminor scanner.o bminor.o token_map.o

token.h: parser.c

parser.o: parser.c
	gcc -c parser.c

parser.c: parser.bison
	bison -v --defines=token.h --output=parser.c parser.bison

scanner.o:	scanner.c
	gcc -c scanner.c

scanner.c: 
	flex -o scanner.c scanner.flex

bminor.o:
	gcc -c bminor.c

token_map.o:
	gcc -c token_map.c

clean:
	rm bminor bminor.o scanner.c scanner.o token_map.o parser.c token.h parser.output parser.o

sgood:
	./bminor -scanner good_test.bminor

good:
	./bminor -parser good_test.bminor

bad:
	./bminor -parser bad_test.bminor
