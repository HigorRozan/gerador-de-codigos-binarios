# include <stdlib.h>
# include "binary_code.h"

int main(int argc, char *argv[]) {

    int order = atoi(argv[1]);
    int length = atoi(argv[2]);
    HammingCode code;

    srand((unsigned) time(NULL));

    code = generate_code(order, length);
    code_save(&code);
    return EXIT_SUCCESS;
}
