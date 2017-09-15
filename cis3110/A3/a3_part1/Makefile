all: msh
msh: philosophers.o lex.yy.o
	gcc -pthread -o msh philosophers.o lex.yy.o -lfl  -lm
mshell.o: philosopophers.c
	gcc -Wall -g -c philosophers.c -lm
lex.yy.o: lex.yy.c
	gcc -Wall -g -c lex.yy.c
lex.yy.c: lex.c
	flex lex.c
clean:
	rm -f *.o
	rm -f lex.yy.c
	rm -f msh
	
