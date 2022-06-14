# include <stdlib.h>
# include "binary_code.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Not enough parameters\n");
        return EXIT_FAILURE;
    }

    srand((unsigned) time(NULL));
    int order = atoi(argv[1]);
    int length = atoi(argv[2]);

    HammingCode *code = generate_hamming_code(order, length);
    calculate_minimum_hamming_distance(code);
    save_hamming_code_to_file(code);

    free(code);

    return EXIT_SUCCESS;
}
