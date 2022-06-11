# include <stdio.h>
# include <stdlib.h>

typedef struct List {
    short int num;
    struct List *next;
} List;

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

List *addListWord(List *list, short int num) {
    if (list == NULL) {
        List *new_node = (List *) malloc(sizeof(List));
        new_node->num = num;
        new_node->next = NULL;

        return new_node;
    }

    list->next = addListWord(list->next, num);
    return list;
}

void removeLastWord(Code *c) {
    CodeList *aux = c->code;
    CodeList *aux_ant = NULL;


    while (aux->next != NULL) { // caminha ate o final da lista;
        aux_ant = aux;
        aux = aux->next;
    }

    if (aux_ant != NULL) { // nao eh o primeiro
        aux_ant->next = NULL;
        free(aux);
    } else { // eh o primeiro 
        free(aux);
        c->code = NULL;
    }
}


void list_print(List *l) {
    if (l != NULL) {
        printf("[%u]", l->num);
        list_print(l->next);
    }
}

double countNode(CodeList *l) {
    if (l != NULL)
        return 1 + countNode(l->next);
    else
        return 0;
}

void convertListtoArray(List *l, short int array[], int i) {
    if (l != NULL) {

        array[i] = l->num;
        convertListtoArray(l->next, array, i + 1);

    }
}


List *freeList(List *l) {
    if (l != NULL) {
        List *aux;

        while (l->next != NULL) {
            aux = l->next;
            free(l);
            l = aux;

        }

        return NULL;

    }

}


