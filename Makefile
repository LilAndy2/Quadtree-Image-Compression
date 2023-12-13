build:
	gcc -std=gnu11 -g -Wall -o quadtree quadtree.c functions.c -lm

clean:
	rm quadtree

run:
	./quadtree