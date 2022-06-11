# include <stdlib.h>
# include "lib/read_save_codelib.h"
# include "lib/addword_codelib.h"

int main() {

    Code *code;
    int num = 3000;
    int order = 100;

    code = new_code(order);
    add_code_random_word(code, num);
    saveCode(code);
    return EXIT_SUCCESS;
}
