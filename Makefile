# Makefile

tic-tac-toe: tic-tac-toe.c
	clang -ggdb3 -O0 -std=c11 -Wall -Werror -o tic-tac-toe tic-tac-toe.c -lm

clean:
	rm -f *.o a.out core tic-tac-toet
