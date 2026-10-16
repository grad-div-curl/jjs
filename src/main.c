#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"
#include "jjsasm.h"

int main(int argc, char **argv){
    char str[] = "ADD 1 2";
    jjsasm_print_token_vector(jjsasm_tokenize(str));
    
    return EXIT_SUCCESS;
}