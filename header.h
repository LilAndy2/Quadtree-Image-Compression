/* MANEA Andrei Iulian - 311CB */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct RGB {
    unsigned char red, green, blue;
} RGB;

typedef struct nod {
    RGB rgb;
    unsigned int type, level;
    struct nod *celula1, *celula2, *celula3, *celula4;
} TNod, *TArb;

typedef struct cell {
    TArb Tree;
    struct cell *next;
} TCell, *TList;

typedef struct queue {
    TList first, last;
} TQueue;

unsigned long long calculate_red(int x, int y, int size, RGB **Matrix);
unsigned long long calculate_blue(int x, int y, int size, RGB **Matrix);
unsigned long long calculate_green(int x, int y, int size, RGB **Matrix);
unsigned long long calculate_mean(int x, int y, int size, unsigned long long red, unsigned long long green, unsigned long long blue, RGB **Matrix);
TArb build_tree(int x, int y, int size, int factor, int level, RGB **Matrix);
int number_of_levels (TArb Tree);
int number_of_leaves (TArb Tree);
int biggest_square (TArb Tree, int minim, int nivel);
void write_in_compressed_file(TArb Tree, FILE *file);
TQueue* InitQ();
void IntrQ(TQueue* q, TArb A);
TArb ExtrQ(TQueue* q);
void build_tree_from_compressed_file(FILE *input, TArb my_Tree);
void put_elements_in_matrix(RGB **Matrix, TArb Tree, int size, int x, int y);
void destroy(TArb Tree);
void destroy_tree(TArb *Tree);