# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <stdio.h>

typedef struct CodeList {
    short int *word;
    struct CodeList *next;
} CodeList;

typedef struct Code {
    CodeList *code;
    int order;
    double length;
    int minimum_hamming_distance;
} Code;


CodeList *addListCode(CodeList *list, short int word[]) {
    if (list == NULL) {
        CodeList *new_node = (CodeList *) malloc(sizeof(CodeList));
        new_node->word = word;
        new_node->next = NULL;

        return new_node;
    }

    list->next = addListCode(list->next, word);
    return list;
}


void code_save(Code* c) {
    int i;

    char name[20];
    char num[4];
    int ramdom;

    srand((unsigned) time(NULL)); //alimenta a semente

    ramdom = rand() % 1000;

    sprintf(name, "Code %d", ramdom);

    FILE *file;

    file = fopen(("%s", name), "w");

    fprintf(file, "SOF\n");

    CodeList *code = c->code;

    while (code != NULL) {

        for (i = 0; i < c->order; i++) {
            fprintf(file, "%u", code->word[i]);
        }
        fprintf(file, "\n");

        code = code->next;

    }
    fprintf(file, "EOF");

    fclose(file);

    strcat(name, "_Doc");

    file = fopen(("%s", name), "w");

    fprintf(file, "Codigo:\n-----------------------\n");
    fprintf(file, "Ordem:              [%d]\n", c->order);
    fprintf(file, "Numero de palavras: [%0.0lf]\n", c->length);
    fprintf(file, "Distancia Minima:   [%d]\n", c->minimum_hamming_distance);
    fprintf(file, "-----------------------\n\n");

    fclose(file);

}

void calcDistMin(Code *code) {

    int dist = 0, distMin = code->order;
    int i;
    CodeList *w1 = code->code;
    CodeList *w2 = code->code->next;

    while (w1 != NULL) {
        while (w2 != NULL) {

            for (i = 0; i < code->order; i++)
                dist += (w1->word[i] + w2->word[i]) % 2;

            distMin = (dist < distMin && dist != 0) ? dist : distMin;

            dist = 0;
            w2 = w2->next;
        }
        w2 = w1->next;
        w1 = w1->next;
    }


    code->minimum_hamming_distance = distMin;


}


Code generate_code(int order, int length) {

    Code *c = (Code *) malloc(sizeof(Code));

    c->code = NULL;
    c->order = order;
    c->length = 0;
    c->minimum_hamming_distance = -1;

    int o = c->order;
    CodeList *code = c->code;
    short int *newWord = NULL;
    int i, t, aux, dist = 0;

    srand((unsigned) time(NULL)); //alimenta a semente



    for (t = 0; t < length; t++) {

        newWord = (short int *) calloc(o, sizeof(short int));

        aux = 1;

        while (aux) {

            aux = 0;

            for (i = 0; i < o; i++)        //cria palavra randomica
                newWord[i] = (rand() % 2);


            while (code != NULL) {

                for (i = 0; i < o; i++) //calcula  a distancia da palavra com o enésima do codico
                    dist += (code->word[i] + newWord[i]) % 2;

                if (dist == 0) { // se a distancia for 0 significa q ela esta repetida
                    aux = 1; // executa o laço novamente
                    code = c->code;// volta ao inicio do codigo
                    dist = 0;
                    break;
                }
                dist = 0;

                code = code->next;
            }
        }

        c->code = addListCode(c->code, newWord); // adiciona palavra ao codigo;
        c->length++;


    }

    calcDistMin(c); // calcula nova distancia minima

    return *c;
}







