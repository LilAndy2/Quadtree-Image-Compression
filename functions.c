/* MANEA Andrei Iulian - 311CB */
#include "header.h"

unsigned long long calculate_red(int x, int y, int size, RGB **Matrix) {
    unsigned long long red = 0, sum = 0;
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            sum = sum + Matrix[i][j].red;
        }
    }
    red = sum / (size * size);
    red = floor(red);
    return red;
}     /* functia primeste ca parametri coordonatele punctului din care se incepe cautarea in matrice, dimensiunea laturii imaginii si
matricea pixelilor si returneaza valoarea canalului de culoare rosie, efectuand suma prezentata in cerinta si aplicarea operatiei de 
parte intreaga */

unsigned long long calculate_blue(int x, int y, int size, RGB **Matrix) {
    unsigned long long blue = 0, sum = 0;
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            sum = sum + Matrix[i][j].blue;
        }
    }
    blue = sum / (size * size);
    blue = floor(blue);
    return blue;
}     /* functia primeste ca parametri coordonatele punctului din care se incepe cautarea in matrice, dimensiunea laturii imaginii si
matricea pixelilor si returneaza valoarea canalului de culoare albastra, efectuand suma prezentata in cerinta si aplicarea operatiei de 
parte intreaga */

unsigned long long calculate_green(int x, int y, int size, RGB **Matrix) {
    unsigned long long green = 0, sum = 0;
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            sum = sum + Matrix[i][j].green;
        }
    }
    green = sum / (size * size);
    green = floor(green);
    return green;
}     /* functia primeste ca parametri coordonatele punctului din care se incepe cautarea in matrice, dimensiunea laturii imaginii si
matricea pixelilor si returneaza valoarea canalului de culoare verde, efectuand suma prezentata in cerinta si aplicarea operatiei de 
parte intreaga */

unsigned long long calculate_mean(int x, int y, int size, unsigned long long red, unsigned long long green, unsigned long long blue, RGB **Matrix) {
    unsigned long long mean = 0, sum = 0;
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            sum = sum + (red - Matrix[i][j].red) * (red - Matrix[i][j].red) + (green - Matrix[i][j].green) * (green - Matrix[i][j].green)+ (blue - Matrix[i][j].blue) * (blue - Matrix[i][j].blue);
        }
    }
    mean = sum / (3 * size * size);
    mean = floor(mean);
    return mean;
}     /* functia primeste ca parametri coordonatele punctului din care se incepe cautarea in matrice, dimensiunea laturii imaginii, valorile
canalelor de culoare rosie, verde si albastra calculate anterior, si matricea pixelilor si returneaza valoarea medie a canalelor de culoare, 
efectuand suma prezentata in cerinta si aplicarea operatiei de parte intreaga */

TArb build_tree(int x, int y, int size, int factor, int level, RGB **Matrix) {
    TArb node = (TArb)malloc(sizeof(TNod));
    if (node == NULL) return NULL;
    unsigned long long red = calculate_red(x, y, size, Matrix);
    unsigned long long green = calculate_green(x, y, size, Matrix);
    unsigned long long blue = calculate_blue(x, y, size, Matrix);
    unsigned long long mean = calculate_mean(x, y, size, red, green, blue, Matrix);
    if (mean <= factor) {
        (node->rgb).red = red;
        (node->rgb).green = green;
        (node->rgb).blue = blue;
        node->type = 1;
        node->level = level;
        node->celula1 = NULL;
        node->celula2 = NULL;
        node->celula3 = NULL;
        node->celula4 = NULL;
        return node;
    } else {
        (node->rgb).red = red;
        (node->rgb).green = green;
        (node->rgb).blue = blue;
        node->type = 0;
        node->level = level;
        node->celula1 = build_tree(x, y, size / 2, factor, level + 1, Matrix);
        node->celula2 = build_tree(x, y + size / 2, size / 2, factor, level + 1, Matrix);
        node->celula3 = build_tree(x + size / 2, y + size / 2, size/2, factor, level + 1, Matrix);
        node->celula4 = build_tree(x + size / 2, y, size/2, factor, level + 1, Matrix);
        return node;
    }
    free(node);
}     /* functia primeste ca parametri coordonatele punctului din care se incepe cautarea in matrice, dimensiunea laturii imaginii,
pragul cu care se compara valoarea medie si matricea de pixeli; in functie se calculeaza valoarea medie a canalelor de culoare si,
in caz ca este mai mica decat pragul furnizat (nodul respectiv este o frunza), se atribuie fiecarui camp din structura de arbore
valorile corespunzatoare (tipul nodului va fi 1), iar cei 4 fii vor fi nuli; in caz ca valoarea medie este mai mare decat pragul
furnizat (nodul respectiv este intermediar), se atribuie fiecarui camp din structura de arbore valorile corespunzatoare (tipul nodului
va fi 0), iar pentru fiecare din cei 4 fii este apelata recursiv functia, modificandu-se coordonatele de inceput ale matricei, in
functie de care cadran este vorba, si dimensiunea fiecarei submatrice (jumatate din dimensiunea apelului precedent); in final este 
returnat arborele creat */

int number_of_levels (TArb Tree) {
    if (Tree == NULL) return 0;
    int max_depth = 0, child_depth;
    child_depth = number_of_levels(Tree->celula1);
    if (child_depth > max_depth) max_depth = child_depth;
    child_depth = number_of_levels(Tree->celula2);
    if (child_depth > max_depth) max_depth = child_depth;
    child_depth = number_of_levels(Tree->celula3);
    if (child_depth > max_depth) max_depth = child_depth;
    child_depth = number_of_levels(Tree->celula4);
    if (child_depth > max_depth) max_depth = child_depth;
    return 1 + max_depth;
}     /* functia primeste ca parametru arborele cuaternar si cauta, recursiv, numarul de niveluri din arbore (se apeleaza functia
recursiv pentru fiecare din cei 4 fii si se cauta numarul maxim de niveluri din fiecare subarbore) */

int number_of_leaves (TArb Tree) {
    if (Tree == NULL) return 0;
    if (Tree->celula1 == NULL && Tree->celula2 == NULL && Tree->celula3 == NULL && Tree->celula4 == NULL) return 1;
    return number_of_leaves(Tree->celula1) + number_of_leaves(Tree->celula2) + number_of_leaves(Tree->celula3) + number_of_leaves(Tree->celula4);
}     /* functia primeste ca parametru arborele cuaternar si returneaza numarul de frunze  din acesta, cautand recursiv pe fiecare 
subarbore aferent celor 4 fii */

int biggest_square(TArb Tree, int minim, int nivel) {
    if (Tree == NULL) return minim;
    if (Tree->celula1 == NULL && Tree->celula2 == NULL && Tree->celula3 == NULL && Tree->celula4 == NULL) {
        if(minim > nivel) {
            minim = nivel;
            return minim;
        }
    }
    minim = biggest_square(Tree->celula1, minim, nivel + 1);
    minim = biggest_square(Tree->celula2, minim, nivel + 1);
    minim = biggest_square(Tree->celula3, minim, nivel + 1); 
    minim = biggest_square(Tree->celula4, minim, nivel + 1); 
    return minim;
}     /* functia primeste ca parametri arborele cuaternar, o valoare de minim (care in main este luata 0) si nivelul la care ma aflu
in arbore si intoare primul nivel din arbore la care se intalneste o frunza; la fiecare intalnire a unei frunze este comparat nivelul
din apelul functiei cu minimul; daca nu intalnim o frunza, apelam functia recursiv pentru fiecare subarbore aferent celor 4 fii si cautam
primul nivel din arbore la care gasim o frunza */

TQueue* InitQ() {
    TQueue* q = (TQueue*)malloc(sizeof(TQueue));
    if(q == NULL) return NULL;
    q->first = q->last = NULL;
    return q;
}     /* functia creeaza o coada vida, atribuind primului si ultimului element valoarea NULL*/

void IntrQ(TQueue* q, TArb A) {
    TList aux = (TList)malloc(sizeof(TCell));
    if(aux == NULL) return;
    aux->Tree = A;
    aux->next = NULL;
    if(q->last != NULL) {
        q->last->next = aux;
    } else {
        q->first = aux;
    }
    q->last = aux;
}     /* functia primeste ca parametri o coada si un arbore, pe care il insereaza la finalul cozii*/

TArb ExtrQ(TQueue* q) {
    TList aux;
    TArb A;
    if(q->first == NULL) {
        return NULL;
    } else {
        if(q->first == q->last) {
            A = q->first->Tree;
            aux = q->first;
            q->first = NULL;
            q->last = NULL;
            free(aux);
        } else {
            A = q->first->Tree;
            aux = q->first;
            q->first = q->first->next;
            free(aux);
        }
    }
    return A;
}     /* functia primeste ca parametru o coada din care extrage primul element si dezaloca memoria pe care acesta o ocupa */

void write_in_compressed_file(TArb Tree, FILE *file) {
    if(Tree == NULL) {
        return;
    }
    TQueue *q = InitQ();
    IntrQ(q, Tree);
    while (q->first != NULL) {
        TArb current_node = ExtrQ(q);
        if (current_node == NULL) break;
        if (current_node->type == 0) {
            fwrite(&(current_node->type), sizeof(unsigned char), 1, file);
            IntrQ(q, current_node->celula1);
            IntrQ(q, current_node->celula2);
            IntrQ(q, current_node->celula3);
            IntrQ(q, current_node->celula4);
        } else {
            fwrite(&(current_node->type), sizeof(unsigned char), 1, file);
            fwrite(&(current_node->rgb.red), sizeof(unsigned char), 1, file);
            fwrite(&(current_node->rgb.green), sizeof(unsigned char), 1, file);
            fwrite(&(current_node->rgb.blue), sizeof(unsigned char), 1, file);
        }
    }
    free(q);
}     /* functia primeste ca parametrii un arbore cuaternar si un fisier in care se vor scrie informatii legate de nodurile acetuia;
se initializeaza o coada in care este adaugata radacina arborelui, apoi, cat timp exista elemente in coada, extragem un element; daca 
este de tip 0 (nod intermediar), se scrie in fisier tipul nodului si se pun in coada cei 4 fii; in caz contrat, daca tipul este unu 
(frunza) se scriu in fisier tipul nodului si valorile pentru fiecare canal de culoare aferent acestui nod; la final, este eliberata 
memoria ocupata de coada */

void build_tree_from_compressed_file(FILE *input, TArb my_Tree) {
    if (my_Tree == NULL) return;
    TQueue *q = InitQ();
    IntrQ(q, my_Tree);
    while (q->first != NULL) {
        char node_type;
        fread(&node_type, sizeof(char), 1, input);
        TArb current_node = ExtrQ(q);
        if (current_node == NULL) break;
        if (node_type == 1) {
            current_node->type = node_type;
            unsigned char red, green, blue;
            fread(&red, sizeof(unsigned char), 1, input);
            fread(&green, sizeof(unsigned char), 1, input);
            fread(&blue, sizeof(unsigned char), 1, input);
            current_node->rgb.red = red;
            current_node->rgb.green = green;
            current_node->rgb.blue = blue;
            current_node->celula1 = NULL;
            current_node->celula2 = NULL;
            current_node->celula3 = NULL;
            current_node->celula4 = NULL;
        } else {
            current_node->type = node_type;
            current_node->celula1 = malloc(sizeof(TNod));
            current_node->celula2 = malloc(sizeof(TNod));
            current_node->celula3 = malloc(sizeof(TNod));
            current_node->celula4 = malloc(sizeof(TNod));
            IntrQ(q, current_node->celula1);
            IntrQ(q, current_node->celula2);
            IntrQ(q, current_node->celula3);
            IntrQ(q, current_node->celula4);
        }
    }
    free(q);
}     /* functia primeste ca parametri un fisier din care sunt citite date si un arbore care va fi creat pe baza acestor informatii;
se initalizeaza o coada in care este introdusa radacina arborelui si, cat timp exista elemente in coada, se extrage din coada urmatorul
element si se citeste din fisier tipul urmatorului nod din arbore; daca este de tip 1 (frunza), se citesc din fisier inca 3 valori,
aferente fiecarui canal de culoare, care se atribuie frunzei din arbore, si se atribuie valoarea NULL celor 4 fii; in caz contrar, cand
tipul nodului este 0 (nod intermediar), se aloca spatiu pentru fiecare din cei 4 fii si se apeleaza recursiv functia pentru fiecare din
acestia; la final, este dezalocata memoria ocupata de coada */

void put_elements_in_matrix(RGB **Matrix, TArb Tree, int size, int x, int y) {
    if (Tree == NULL) return;
    if (Tree->type == 0) {
        put_elements_in_matrix(Matrix, Tree->celula1, size / 2, x, y);
        put_elements_in_matrix(Matrix, Tree->celula2, size / 2, x, y + size / 2);
        put_elements_in_matrix(Matrix, Tree->celula3, size / 2, x + size / 2, y + size / 2);
        put_elements_in_matrix(Matrix, Tree->celula4, size / 2, x + size / 2, y);
    } else {
        for (int i = x; i < x + size; i++) {
            for (int j = y; j < y + size; j++) {
                Matrix[i][j].red = Tree->rgb.red;
                Matrix[i][j].green = Tree->rgb.green;
                Matrix[i][j].blue = Tree->rgb.blue;
            }
        }
    }
}     /* functia primeste ca parametri matricea de pixeli, arborele cuaternar, dimensiunea imaginii si coordonatele de la care se incepe
scrierea in matrice si scrie in aceasta elementele de tip RBG; in caz ca nodul curent este de tip 0 (nod intermediar), se apeleaza recursiv
functia pentru fiecare din cei 4 fii, cu dimensiunea imaginii injumatatita si coordonatele ajustate in functie de cadranul in care ma mut*/ 

void destroy(TArb Tree) {
    if (Tree == NULL) return;
    destroy(Tree->celula1);
    destroy(Tree->celula2);
    destroy(Tree->celula3);
    destroy(Tree->celula4);
    free(Tree);
}     /* functia primeste ca parametru un arbore cuaternar si distruge toate nodurile acestuia */

void destroy_tree(TArb *Tree) {
    if (*Tree == NULL) return;
    destroy(*Tree);
    *Tree = NULL;
}     /* functia primeste ca parametru un arbore cuaternar si ii distruge nodurile, dupa care il face nul */