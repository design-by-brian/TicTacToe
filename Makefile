CC=gcc
CFLAGS= -g -Wall -pedantic -ansi -Werror -std=c89
EXEC=TestHarness TicTacToe
OBJ=LinkedList.o LinkedListTest.o TicTacToe.o UserInterface.o BoardDisplay.o

ifdef SECRET
CFLAGS += -D SECRET
SECRET : clean $(EXEC)
endif

ifdef EDITOR
CFLAGS += -D EDITOR
EDITOR : clean $(EXEC)
endif

all : $(EXEC)

TicTacToe : LinkedList.o TicTacToe.o UserInterface.o BoardDisplay.o 
			$(CC) -o TicTacToe LinkedList.o TicTacToe.o UserInterface.o BoardDisplay.o

LinkedList.o : LinkedList.c LinkedList.h
			$(CC) $(CFLAGS) -c LinkedList.c

TicTacToe.o : TicTacToe.c TicTacToe.h UserInterface.h BoardDisplay.h
			$(CC) $(CFLAGS) -c TicTacToe.c

UserInterface.o : UserInterface.c UserInterface.h BoardDisplay.h LinkedList.h TicTacToe.h
			$(CC) $(CFLAGS) -c UserInterface.c

BoardDisplay.o : BoardDisplay.c BoardDisplay.h LinkedList.h TicTacToe.h UserInterface.h
			$(CC) $(CFLAGS) -c BoardDisplay.c
	
TestHarness : LinkedListTest.o LinkedList.o
			$(CC) -o TestHarness LinkedListTest.o LinkedList.o

LinkedListTest.o : LinkedListTest.c 
			$(CC)	$(CFLAGS) -c LinkedListTest.c

clean:
	rm -f $(EXEC) $(OBJ)

runTTT:
	valgrind --leak-check=full --track-origins=yes ./TicTacToe settings.txt

runTest:
	valgrind --leak-check=full --track-origins=yes ./TestHarness 
