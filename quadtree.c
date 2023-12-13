/* MANEA Andrei Iulian - 311CB */
#include "header.h"

int main(int argc, char const *argv[]) {
    if (strcmp(argv[1], "-c1") == 0) {     // cazul pentru cerinta 1
        FILE *input = fopen(argv[3], "rb"), *output = fopen(argv[4], "w");     // deschid fisierul de input si cel de out cu ajutorul parametrilor din linia de comanda
        if (input == NULL) {     // verific daca s-a realizat cu succes deschiderea fisierului
            printf("Nu s-a putut deschide fisierul!");
            return 0;     // daca fisierul nu s-a deschis, afisez un mesaj aferent
        }
        char file_type[3], space;
        fscanf(input, "%s\n", file_type);     // citesc primul rand din fisierul PPM, care contine tipul fisierului (P6)
        unsigned int width, height, max_value_for_pixel;
        fscanf(input, "%u %u\n", &width, &height);     // citesc al doilea rand din fisierul PPM, care contine dimensiunile imaginii
        fscanf(input, "%u", &max_value_for_pixel);     // citesc al treilea rand din fisierul PPM, care contine intensitatea maxima a culorilor 
        fscanf(input, "%c", &space);     // citesc endline-ul dinaintea imaginii in format binar separat
        RGB **Pixel_Matrix = malloc(width * sizeof(RGB*));     // aloc spatiu pentru matricea pixelilor
        for (int i = 0; i < height; i++) {
            Pixel_Matrix[i] = malloc(height * sizeof(RGB));     // aloc spatiu pentru fiecare linie din matricea pixelilor
            for (int j = 0; j < width; j++) {
                fread(&Pixel_Matrix[i][j].red, sizeof(unsigned char), 1, input);       // citesc valorile pentru ficare canal de culoare,
                fread(&Pixel_Matrix[i][j].green, sizeof(unsigned char), 1, input);     // pentru fiecare element din matricea pixelilor, 
                fread(&Pixel_Matrix[i][j].blue, sizeof(unsigned char), 1, input);      // din fisierul de input
            }
        }
        int factor = atoi(argv[2]), size = height;     // preiau din linia de comanda pragul impus pentru compararea combinatiei de culori
        TArb Tree = build_tree(0, 0, size, factor, 0, Pixel_Matrix);     // construiesc arborele cuaternar
        int levels = number_of_levels(Tree);     // calculez numarul de niveluri din arborele cuaternar
        int leaves = number_of_leaves(Tree);     // calculez numarul de blocuri nedivizate din arbore (numarul de frunze)
        int rez = biggest_square(Tree, 999, 0);     // calculez dimensiunea laturii celui mai mare patrat nedivizat din imagine
        int final = size;
        for (int i = 1; i <= rez; i++) {
            final = final / 2;
        }
        fprintf(output, "%d\n%d\n%d\n", levels, leaves, final);     // afisez in fisierul de output informatiile cerute
        for (int i = 0; i < height; i++) {     //
            free(Pixel_Matrix[i]);             //
        }                                      // eliberez memoria alocata
        free(Pixel_Matrix);                    // pe parcursul implementarii 
        destroy_tree(&Tree);                   // primei cerinte
        fclose(input);                         //
        fclose(output);                        //
    }

    if (strcmp(argv[1], "-c2") == 0) {     // cazul pentru cerinta 2
        FILE *input = fopen(argv[3], "rb"), *output = fopen(argv[4], "wb");     // deschid fisierul de input si cel de out cu ajutorul parametrilor din linia de comanda
        if (input == NULL) {     // verific daca s-a realizat cu succes deschiderea fisierului
            printf("Nu s-a putut deschide fisierul!");
            return 0;     // daca fisierul nu s-a deschis, afisez un mesaj aferent
        }
        char file_type[3], space;
        fscanf(input, "%s\n", file_type);     // citesc primul rand din fisierul PPM, care contine tipul fisierului (P6)
        unsigned int width, height, max_value_for_pixel;
        fscanf(input, "%u %u\n", &width, &height);     // citesc al doilea rand din fisierul PPM, care contine dimensiunile imaginii
        fscanf(input, "%u", &max_value_for_pixel);     // citesc al treilea rand din fisierul PPM, care contine intensitatea maxima a culorilor
        fscanf(input, "%c", &space);     // citesc endline-ul dinaintea imaginii in format binar separat
        RGB **Pixel_Matrix = malloc(width * sizeof(RGB*));     // aloc spatiu pentru matricea pixelilor
        for (int i = 0; i < height; i++) {
            Pixel_Matrix[i] = malloc(height * sizeof(RGB));     // aloc spatiu pentru fiecare linie din matricea pixelilor
            for (int j = 0; j < width; j++) {
                fread(&Pixel_Matrix[i][j].red, sizeof(unsigned char), 1, input);       // citesc valorile pentru ficare canal de culoare,
                fread(&Pixel_Matrix[i][j].green, sizeof(unsigned char), 1, input);     // pentru fiecare element din matricea pixelilor,
                fread(&Pixel_Matrix[i][j].blue, sizeof(unsigned char), 1, input);      // din fisierul de input
            }
        }
        int factor = atoi(argv[2]), size = height;     // preiau din linia de comanda pragul impus pentru compararea combinatiei de culori
        fwrite(&size, sizeof(int), 1, output);     // scriu in fisierul comprimat dimensiunea imaginii
        TArb Tree = build_tree(0, 0, size, factor, 0, Pixel_Matrix);     // construiesc arborele cuaternar
        write_in_compressed_file(Tree, output);     // scriu in fisierul comprimat informatiile necesare(tipurile nodurilor si, eventual, valorile din cele 3 canale de culoare)
        for (int i = 0; i < height; i++) {      //
            free(Pixel_Matrix[i]);              //
        }                                       // eliberez memoria alocata
        free(Pixel_Matrix);                     // pe parcursul implementarii
        destroy_tree(&Tree);                    // celei de-a doua cerinte
        fclose(input);                          //
        fclose(output);                         //
    }
    if (strcmp(argv[1], "-d") == 0) {     // cazul pentru cerinta 3
        FILE *input = fopen(argv[2], "rb"), *output = fopen(argv[3], "wb");     // deschid fisierul de input si cel de out cu ajutorul parametrilor din linia de comanda
        if (input == NULL) {     // verific daca s-a realizat cu succes deschiderea fisierului
            printf("Nu s-a putut deschide fisierul!");
            return 0;     // daca fisierul nu s-a deschis, afisez un mesaj aferent
        }
        char file_type[3] = "P6";
        int size, max_value = 255;
        fread(&size, sizeof(int), 1, input);     // citesc din fisierul de input dimensiunea imaginii
        fprintf(output, "%s\n", file_type);     // afisez in fisierul PPM tipul fisierului (P6)
        fprintf(output, "%d %d\n", size, size);     // afisez in fisierul PPM dimensiunile imaginii
        fprintf(output, "%d\n", max_value);     // afisez in fisierul PPM valoarea maxima pentru intensitatea maxima a culorilor
        TArb Tree = (TArb)malloc(sizeof(TNod));     // aloc spatiu pentru arborele cuaternar
        build_tree_from_compressed_file(input, Tree);     // contruiesc arborele pe baza informatiilor din fisierul comprimat
        RGB **Pixel_Matrix_new = malloc(size * sizeof(RGB*));     // aloc spatiu pentru matricea pixelilor
        for (int i = 0; i < size; i++) {
            Pixel_Matrix_new[i] = malloc(size * sizeof(RGB));     // aloc spatiu pentru fiecare linie din matricea pixelilor
        }
        put_elements_in_matrix(Pixel_Matrix_new, Tree, size, 0, 0);     // pun elementele de tip RGB in fiecare elemnt din matricea pixelilor
        for (int i = 0; i < size; i++) {
            for (int j = 0; j < size; j++) {
                fwrite(&Pixel_Matrix_new[i][j].red, sizeof(unsigned char), 1, output);       // scriu in fiiserul PPM
                fwrite(&Pixel_Matrix_new[i][j].green, sizeof(unsigned char), 1, output);     // elementele din canalele de culoare
                fwrite(&Pixel_Matrix_new[i][j].blue, sizeof(unsigned char), 1, output);      // din fiecare pixel din matrice
            }
        }
        for (int i = 0; i < size; i++) {  //
            free(Pixel_Matrix_new[i]);    //
        }                                 // eliberez memoria alocata
        free(Pixel_Matrix_new);           // pe parcursul implementarii 
        destroy_tree(&Tree);              // celei de-a treia cerinte
        fclose(input);                    //
        fclose(output);                   //
    }
    return 0;
}