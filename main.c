# include <stdlib.h>
# include "binary_code.h"

int main(int argc, char *argv[]) {

    srand((unsigned) time(NULL));
    int order = atoi(argv[1]);
    int length = atoi(argv[2]);

    HammingCode code = generate_code(order, length);
    code_save(&code);
    return EXIT_SUCCESS;
}
