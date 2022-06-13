# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <stdio.h>

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


// todo: optimize comparator
void calculate_minimum_hamming_distance(HammingCode *code) {
    int dist = 0, distMin = code->order;
    int minimum_distance = code->minimum_hamming_distance;

    Word *word_i = code->head_word;
    Word *word_j = code->head_word->next;

    while (word_i != NULL) {
        while (word_j != NULL) {
            int current_distance = 0;

            for (int i = 0; i < code->order; i++) {
                current_distance += (word_i->value[i] + word_j->value[i]) % 2;
            }

            dist = 0;
            word_j = word_j->next;
        }
        word_j = word_i->next;
        word_i = word_i->next;
    }

    code->minimum_hamming_distance = distMin;
}

short int *generate_random_word(int code_order) {
    short int *new_word = (short int *) calloc(code_order, sizeof(short int));
    for (int j = 0; j < code_order; j++) {
        new_word[j] = (rand() % 2);
    }
    return new_word;
}

HammingCode *new_hamming_code(int order, int length) {
    HammingCode *c = (HammingCode *) malloc(sizeof(HammingCode));
    c->head_word = NULL;
    c->order = order;
    c->length = length;
    c->minimum_hamming_distance = -1;
    return c;
}

HammingCode generate_code(int order, int length) {

    HammingCode *code = new_hamming_code(order, length);

    for (int i = 0; i < length; i++) {
        short int *new_word = generate_random_word(order);

        Word *aux = code->head_word;
        while (aux != NULL) {
            // Calculate hamming distance
            int hamming_distance = 0;
            for (int j = 0; j < code->order; j++){
               int bit_a = aux->value[j];
               int bit_b = new_word[j];

                hamming_distance += (bit_a + bit_b) % 2;
            }

            if (hamming_distance == 0) {
                aux = code->head_word;// volta ao inicio do codigo
                hamming_distance = 0;
                break;
            }
            hamming_distance = 0;

            aux = aux->next;
        }

        code->head_word = append_new_word(code->head_word, new_word);
        code->length++;


    }

    calculate_minimum_hamming_distance(code);

    return *code;
}


void code_save(HammingCode *c) {
    int i;
    FILE *file;

    file = fopen(("%s","hamming_code.txt"), "w");
    fprintf(file, "(order = %d, length = %d, minimum_hamming_distance = %d)", c->order, c->length, c->minimum_hamming_distance);

    Word *code = c->head_word;
    while (code != NULL) {
        fprintf(file, "\n");
        for (i = 0; i < c->order; i++) {
            fprintf(file, "%u", code->value[i]);
        }
        code = code->next;
    }
    fclose(file);
}





