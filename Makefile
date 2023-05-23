build:
	gcc -Wall -o tema3 tema3.c operations.c -lm && touch tema3.out
run:
	./tema3
clean:
	rm tema3
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./tema3