#pragma ide diagnostic ignored "cert-msc50-cpp"
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"
#pragma ide diagnostic ignored "misc-no-recursion"

#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

struct Word {
    short int *value;
    struct Word *next;
};

struct HammingCode {
    struct Word *head_word;
    int order;
    double length;
    int minimum_hamming_distance;
};

typedef struct Word Word;

typedef struct HammingCode HammingCode;

HammingCode *generate_hamming_code(int order, int length);

short int *generate_random_word(int order);

Word *append_new_word(Word *word, short int *value);

void calculate_minimum_hamming_distance(HammingCode *code);


HammingCode *generate_hamming_code(int order, int length) {
    HammingCode *code = (HammingCode *) malloc(sizeof(HammingCode));
    code->head_word = NULL;
    code->order = order;
    code->length = length;
    code->minimum_hamming_distance = -1;

    for (int i = 0; i < code->length; i++) {
        short int *new_word = generate_random_word(order);

        // Iterate over all words of the code
        Word *aux = code->head_word;
        while (aux != NULL) {
            // Calculate hamming distance
            int hamming_distance = 0;
            for (int j = 0; j < code->order; j++) {
                int a = aux->value[j];
                int b = new_word[j];

                hamming_distance += (a + b) % 2;
            }

            // the word is already in the code
            if (hamming_distance == 0) {
                break;
            }

            aux = aux->next;
        }

        code->head_word = append_new_word(code->head_word, new_word);
        code->length++;
    }

    return code;
}

short int *generate_random_word(int order) {
    short int *new_word = (short int *) calloc(order, sizeof(short int));
    for (int i = 0; i < order; i++) {
        new_word[i] = rand() % 2;
    }
    return new_word;
}

Word *append_new_word(Word *word, short int *value) {
    if (word == NULL) {
        Word *node = (Word *) malloc(sizeof(Word));
        node->value = value;
        node->next = NULL;
        return node;
    }

    word->next = append_new_word(word->next, value);
    return word;
}


void calculate_minimum_hamming_distance(HammingCode *code) {
    int minimum_distance = code->order;

    Word *aux_i = code->head_word;
    Word *aux_j = code->head_word->next;

    while (aux_i != NULL) {
        while (aux_j != NULL) {
            int current_distance = 0;

            for (int i = 0; i < code->order; i++) {
                current_distance += (aux_i->value[i] + aux_j->value[i]) % 2;
            }

            if (current_distance < code->order) {
                minimum_distance = current_distance;
            }

            aux_j = aux_j->next;
        }
        aux_j = aux_i->next;
        aux_i = aux_i->next;
    }

    code->minimum_hamming_distance = minimum_distance;
}


void save_hamming_code_to_file(HammingCode *code) {
    FILE *file = fopen("hamming_code.txt", "w");

    fprintf(file, "(%d, %d, %d)", code->order, code->length, code->minimum_hamming_distance);

    Word *aux = code->head_word;
    while (aux != NULL) {
        fprintf(file, "\n");

        for (int i = 0; i < code->order; i++) {
            fprintf(file, "%u", aux->value[i]);
        }
        aux = aux->next;
    }

    fclose(file);
}

