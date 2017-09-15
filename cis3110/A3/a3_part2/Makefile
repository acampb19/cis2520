all: msh
msh: holes.o lex.yy.o
	gcc -o msh holes.o lex.yy.o -lfl  -lm

mshell.o: holes.c
	gcc -Wall -g -c holes.c -lm
lex.yy.o: lex.yy.c
	gcc -Wall -g -c lex.yy.c
lex.yy.c: lex.c
	flex lex.c
clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f msh
	
