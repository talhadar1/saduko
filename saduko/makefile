CC = gcc
OBJS = main.o Main_aux.o Parser.o Solver.o Game.o 
EXEC = saduko
COMP_FLAG = -ansi -Wall -Wextra \
-Werror -pedantic-errors

$(EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@
main.o: main.c Game.h SPBufferset.h
	$(CC) $(COMP_FLAG) -c $*.c
Main_aux.o: Main_aux.c Main_aux.h
	$(CC) $(COMP_FLAG) -c $*.c
Parser.o: Parser.c Parser.h
	$(CC) $(COMP_FLAG) -c $*.c
Solver.o: Main_aux.h Solver.c Solver.h Parser.h Game.h 
	$(CC) $(COMP_FLAG) -c $*.c
Game.o: Game.c Main_aux.h Game.h Parser.h Solver.h 
	$(CC) $(COMP_FLAG) -c $*.c
clean:
	rm -f $(OBJS) $(EXEC)
