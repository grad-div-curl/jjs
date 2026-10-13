#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"

#include "jjsasm.h"

/*

Helpers
    static uint64_t ll_read_u64(long long ll);
    static uint64_t d_read_u64(double d);
    static long long u64_read_ll(uint64_t u64);
    static double u64_read_d(uint64_t u64);
Conversion to jjsasm types
    size_t jjsasm_argc_of(jjsasm_instr_e instruction);
String conversion and prints
    char *jjsasm_instr_e_to_a(jjsasm_instr_e instr_e);
    char *jjsasm_type_e_to_a(jjsasm_type_e type_e);
    void jjsasm_print_arg_t(jjsasm_arg_t arg_t);
    void jjsasm_print_instr_t(jjsasm_instr_t instr_t);
Parsing strings
    jjsasm_instr_e jjsasm_a_to_instr_e(char *str);
    jjsasm_type_e jjsasm_parsenum(char *str);
    vector_t *jjsasm_tokenize(char *str);

*/


// evil floating point bit level hacking
// what the fuck?

static uint64_t ll_readas_u64(long long ll){
    return *(uint64_t *)&ll;
}
static uint64_t d_readas_u64(double d){
    return *(uint64_t *)&d;
}
static long long u64_readas_ll(uint64_t u64){
    return *(long long *)&u64;
}
static double u64_readas_d(uint64_t u64){
    return *(double *)&u64;
}

size_t jjsasm_argc_of(jjsasm_instr_e instr_e){
    if (instr_e >= jjsasm_argc_size) return 0;
    return jjsasm_argc[(int)instr_e];
}

const char *jjsasm_type_e_to_a(jjsasm_type_e type_e){
    if (type_e >= jjsasm_type_strs_size) return NULL;
    return jjsasm_type_strs[(int)type_e];
}

const char *jjsasm_instr_e_to_a(jjsasm_instr_e instr_e){
    if (instr_e >= jjsasm_instr_strs_size) return NULL;
    return jjsasm_instr_strs[(int)instr_e];
}

const char *jjsasm_token_e_to_a(jjsasm_token_e token_e){
    if (token_e >= jjsasm_token_strs_size) return NULL;
    return jjsasm_token_strs[(int)token_e];
}

void jjsasm_print_arg_t(jjsasm_arg_t arg_t){
    printf("(%s : ", jjsasm_instr_e_to_a(arg_t.type_e));

    switch (arg_t.type_e){
        case JJSASM_TYPE_UNKNOWN:
            printf("%.16x", (uintptr_t)arg_t.data);
            break;
        case JJSASM_TYPE_INTEGER:
            printf("%ld", u64_readas_ll(arg_t.data));
            break;
        case JJSASM_TYPE_DECIMAL:
            printf("%lf", u64_readas_d(arg_t.data));
            break;
        case JJSASM_TYPE_STRING:
            printf("\"%s\"", (char *)arg_t.data);
            break;
        case JJSASM_TYPE_TAG:
            printf("%c%s", JJSASM_TAG_CHAR, (char *)arg_t.data);
            break;
        case JJSASM_TYPE_BAD:
            printf("%.16x", (uintptr_t)arg_t.data);
            break;
        default:
            printf("what the fuck?");
            break;
    }

    putchar(')');
}

void jjsasm_print_instr_t(jjsasm_instr_t instr_t){
    printf(jjsasm_instr_e_to_a(instr_t.instr_e));
    for (int i = 0; i < instr_t.argc; i++){
        putchar(' ');
        jjsasm_print_arg_t(instr_t.argv[i]);
    }
}

void jjsasm_print_token_t(jjsasm_token_t token_t){
    printf("[%s : ", jjsasm_token_e_to_a(token_t.token_e));

    switch (token_t.token_e){
        case JJSASM_TOKEN_UNKNOWN:
            printf("%.16x", (uintptr_t)token_t.data);
            break;
        case JJSASM_TOKEN_INSTRUCTION:
            jjsasm_print_instr_t(*(jjsasm_instr_t *)token_t.data);
            break;
        case JJSASM_TOKEN_COMMENT:
            printf((char *)token_t.data);
            break;
        case JJSASM_TOKEN_LABEL:
            printf((char *)token_t.data);
            break;
        case JJSASM_TOKEN_BAD:
            printf("%.16x", (uintptr_t)token_t.data);
            break;
    }

    putchar(']');
}

jjsasm_instr_e jjsasm_a_to_instr_e(char *str){
    if (strcmp(str, "NOP") == 0) return JJSASM_INSTR_NOP;
    if (strcmp(str, "MOV") == 0) return JJSASM_INSTR_MOV;
    if (strcmp(str, "ADD") == 0) return JJSASM_INSTR_ADD;
    if (strcmp(str, "SUB") == 0) return JJSASM_INSTR_SUB;
    if (strcmp(str, "CMP") == 0) return JJSASM_INSTR_CMP;
    if (strcmp(str, "JMP") == 0) return JJSASM_INSTR_JMP;
    if (strcmp(str, "JE") == 0)  return JJSASM_INSTR_JE;
    if (strcmp(str, "JL") == 0)  return JJSASM_INSTR_JL;
    if (strcmp(str, "JG") == 0)  return JJSASM_INSTR_JG;
    if (strcmp(str, "SKL") == 0) return JJSASM_INSTR_SKL;
    return JJSASM_INSTR_BAD;
}

jjsasm_type_e jjsasm_parsenum(char *str){
    int i = 0;
    int dec_used = 0;

    while (strchr(JJSASM_STR_WHITESPACE, str[i]) == NULL){
        if (str[i] == '.'){
            if (dec_used == 1) return JJSASM_TYPE_UNKNOWN;
            dec_used = 1;
        }
        else if ('0' <= str[i] && str[i] <= '9'){
            continue;
        }
        else {
            return JJSASM_TYPE_UNKNOWN;
            // wont add exponent support, maybe if i build a higher-level compiler into JJSASM?
        }
    }
}


vector_t *jjsasm_tokenize(char *str){
    if (str == NULL) return NULL; // note to self: strtok(NULL, {delim}) without 1st call is bad
    str = strtok(str, JJSASM_STR_LINEBREAK);

    vector_t *vec = vector_new(sizeof(jjsasm_token_t), 64);

    while (str != NULL){
        size_t len = strlen(str);
    }



    TOKENIZE_FAILURE: // this is a goto
    vector_free(vec);
    return EXIT_FAILURE;
}