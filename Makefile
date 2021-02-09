all: minishell

minishell: main.o parser.o cmdline.o processus.o builtin.o utils.o
	gcc -o minishell main.o parser.o cmdline.o processus.o builtin.o utils.o

main.o: main.c cmdline.h parser.h
	gcc -o main.o -c main.c

parser.o: parser.c
	gcc -o parser.o -c parser.c

cmdline.o: cmdline.c processus.h utils.h
	gcc -o cmdline.o -c cmdline.c

utils.o: utils.c
	gcc -o utils.o -c utils.c

processus.o: processus.c builtin.h
	gcc -o processus.o -c processus.c

builtin.o: builtin.c
	gcc -o builtin.o -c builtin.c

clean:
	rm -rf *.o

mrproper: clean
	rm -rf minishell
