# include <stdlib.h>
# include <time.h>
# include <string.h>
# include <stdio.h>

struct Word {
    short int *value;
    struct Word *next;
};

struct HammingCode {
    struct Word *code;
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

    Word *word_i = code->code;
    Word *word_j = code->code->next;

    while (word_i != NULL) {
        while (word_j != NULL) {
            int current_distance = 0;

            for (int i = 0; i < code->order; i++){
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


HammingCode generate_code(int order, int length) {

    HammingCode *c = (HammingCode *) malloc(sizeof(HammingCode));
    c->code = NULL;
    c->order = order;
    c->length = 0;
    c->minimum_hamming_distance = -1;


    Word *code = c->code;
    int code_order = c->order;


    for (int i = 0; i < length; i++) {
        short int *new_word = NULL;
        new_word = (short int *) calloc(code_order, sizeof(short int));


        // Generate new random value
        for (int j = 0; j < code_order; j++)
            new_word[j] = (rand() % 2);

        while (code != NULL) {
            // Calculate hamming distance
            int hamming_distance = 0;
            for (int k = 0; k < code_order; k++)
                hamming_distance += (code->value[k] + new_word[k]) % 2;

            if (hamming_distance == 0) {
                code = c->code;// volta ao inicio do codigo
                hamming_distance = 0;
                break;
            }
            hamming_distance = 0;

            code = code->next;
        }

        c->code = append_new_word(c->code, new_word); // adiciona palavra ao codigo;
        c->length++;


    }

    calculate_minimum_hamming_distance(c); // calcula nova distancia minima

    return *c;
}


void code_save(HammingCode *c) {
    int i;
    int code_prefix;
    // todo: check possible array overflow
    char file_name[20];
    FILE *file;

    code_prefix = rand() % 1000;
    sprintf(file_name, "hamming_code_%d.txt", code_prefix);
    file = fopen(("%s", file_name), "w");
    fprintf(file, "SOF\n");
    fprintf(file, "order:%d\nlength%d\nminimum_hamming_distance:%d", c->order, c->length, c->minimum_hamming_distance);


    Word *code = c->code;
    while (code != NULL) {
        for (i = 0; i < c->order; i++) {
            fprintf(file, "%u\n", code->value[i]);
        }
        code = code->next;
    }

    fprintf(file, "EOF");
    fclose(file);
}





