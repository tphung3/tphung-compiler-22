all: bminor-codegen

bminor-codegen: parser.o scanner.o bminor.o token_map.o decl.o expr.o param_list.o stmt.o type.o scope.o symbol.o hash_table.o codegen_helpers.o
	gcc -g -o bminor scanner.o bminor.o parser.o token_map.o decl.o expr.o param_list.o stmt.o type.o scope.o symbol.o hash_table.o codegen_helpers.o

bminor-typecheck: parser.o scanner.o bminor.o token_map.o decl.o expr.o param_list.o stmt.o type.o scope.o symbol.o hash_table.o
	gcc -g -o bminor scanner.o bminor.o parser.o token_map.o decl.o expr.o param_list.o stmt.o type.o scope.o symbol.o hash_table.o

bminor-resolve: parser.o scanner.o bminor.o token_map.o decl.o expr.o param_list.o stmt.o type.o scope.o symbol.o hash_table.o
	gcc -g -o bminor scanner.o bminor.o parser.o token_map.o decl.o expr.o param_list.o stmt.o type.o scope.o symbol.o hash_table.o


bminor-printer: parser.o scanner.o bminor.o token_map.o decl.o expr.o param_list.o stmt.o type.o
	gcc -g -o bminor scanner.o bminor.o parser.o token_map.o decl.o expr.o param_list.o stmt.o type.o

bminor-parser: parser.o scanner.o bminor.o token_map.o decl.o expr.o param_list.o stmt.o type.o
	gcc -g -o bminor scanner.o bminor.o parser.o token_map.o decl.o expr.o param_list.o stmt.o type.o

bminor-scanner: token.h scanner.o bminor.o token_map.o
	gcc -g -o bminor scanner.o bminor.o token_map.o

token.h: parser.c

parser.o: parser.c 
	gcc -g -c parser.c

parser.c: parser.bison
	bison -v -t --defines=token.h --output=parser.c parser.bison

decl.o: decl.c
	gcc -g -c decl.c

expr.o: expr.c
	gcc -g -c expr.c

param_list.o: param_list.c
	gcc -g -c param_list.c

stmt.o: stmt.c
	gcc -g -c stmt.c

type.o: type.c
	gcc -g -c type.c

scope.o: scope.c
	gcc -g -c scope.c

symbol.o: symbol.c
	gcc -g -c symbol.c

hash_table.o: hash_table.c
	gcc -g -c hash_table.c

scanner.o:	scanner.c
	gcc -g -c scanner.c

scanner.c: 
	flex -o scanner.c scanner.flex

bminor.o:
	gcc -g -c bminor.c

token_map.o:
	gcc -g -c token_map.c

codegen_helpers.o:
	gcc -g -c codegen_helpers.c

clean:
	rm -f bminor bminor.o scanner.c scanner.o token_map.o parser.c token.h parser.output parser.o decl.o expr.o param_list.o stmt.o type.o scope.o symbol.o hash_table.o codegen_helpers.o

sgood:
	./bminor -scan good_test.bminor

good:
	./bminor -parse good_test.bminor

bad:
	./bminor -parse bad_test.bminor

cleanmk: clean all
