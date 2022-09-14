all: exe_bminor

exe_bminor: bminor
	./bminor -scan test.bminor

bminor: scanner.o bminor.o token_map.o
	gcc -o bminor scanner.o bminor.o

scanner.o:	scanner.c
	gcc -c scanner.c

scanner.c: 
	flex -o scanner.c scanner.flex

bminor.o:
	gcc -c bminor.c

token_map.o:
	gcc -c token_map.c

clean:
	rm bminor bminor.o scanner.c scanner.o token_map.o
