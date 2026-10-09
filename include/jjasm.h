#ifndef JJSASM_H
#define JJSASM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"

#define JJSASM_TAG_CHAR '#'

#define JJSASM_STR_NOP "NOP"
#define JJSASM_STR_SET "SET"
#define JJSASM_STR_MOV "MOV"
#define JJSASM_STR_ADD "ADD"
#define JJSASM_STR_SUB "SUB"
#define JJSASM_STR_CMP "CMP"
#define JJSASM_STR_JMP "JMP"
#define JJSASM_STR_JE  "JE"
#define JJSASM_STR_JL  "JL"
#define JJSASM_STR_JG  "JG"
#define JJSASM_STR_SKL "SKL"
#define JJSASM_STR_BAD "BAD"

/*

Types
    Enums
        jjsasm_type_e
        jjsasm_instr_e
        jjsasm_token_e
    Structs
        jjsasm_arg_t
        jjsasm_instr_t
        jjsasm_token_t
Functions
    Conversion to jjsasm types
        jjsasm_instr_e jjsasm_a_to_instr_e(char *str);
        size_t jjsasm_argc(jjsasm_instr_e instruction);
    String conversion and prints
        char *jjsasm_instr_e_to_a(jjsasm_instr_e instr_e);
        char *jjsasm_type_e_to_a(jjsasm_type_e type_e);
        void jjsasm_print_arg_t(jjsasm_arg_t arg_t);
        void jjsasm_print_instr_t(jjsasm_instr_t instr_t);
    Parsing strings
        size_t jjsasm_argc(jjsasm_instr_e instruction);
        jjsasm_instr_e jjsasm_a_to_instr_e(char *str);
        jjsasm_type_e jjsasm_parsenum(char *str);
        vector_t *jjsasm_tokenize(char *str);
    


*/

typedef enum jjsasm_type_e {
    JJSASM_TYPE_UNKNOWN = 0,
    JJSASM_TYPE_INTEGER,
    JJSASM_TYPE_DECIMAL,
    JJSASM_TYPE_STRING,
    JJSASM_TYPE_TAG,
    JJSASM_TYPE_BAD = 255
} jjsasm_type_e;

typedef enum jjsasm_instr_e {
    JJSASM_INSTR_NOP = 0,
    JJSASM_INSTR_SET,
    JJSASM_INSTR_MOV,
    JJSASM_INSTR_ADD,
    JJSASM_INSTR_SUB,
    JJSASM_INSTR_CMP,
    JJSASM_INSTR_JMP,
    JJSASM_INSTR_JE,
    JJSASM_INSTR_JL,
    JJSASM_INSTR_JG,
    JJSASM_INSTR_SKL,
    JJSASM_INSTR_BAD = 255
} jjsasm_instr_e;

typedef enum jjsasm_token_e {
    JJSASM_BAD,
    JJSASM_INSTRUCTION,
    JJSASM_COMMENT,
    JJSASM_LABEL
} jjsasm_token_e;

typedef struct jjsasm_arg_t {
    jjsasm_type_e type_e;
    uint64_t data;
} jjsasm_arg_t;

// if i decide to set `argv` to a vector_t, it contains jjs_arg_t's
typedef struct jjsasm_instr_t {
    jjsasm_instr_e instr_e;
    jjsasm_arg_t *argv;
    uint8_t argc;
} jjsasm_instr_t;

typedef struct jjsasm_token_t {
    jjsasm_token_e asm_token_e;
    void *data;
} jjasm_token_t;

char *jjsasm_instr_e_to_a(jjsasm_instr_e instr_e);
char *jjsasm_type_e_to_a(jjsasm_type_e type_e);
void jjsasm_print_arg_t(jjsasm_arg_t arg_t);
void jjsasm_print_instr_t(jjsasm_instr_t instr_t);

size_t jjsasm_argc(jjsasm_instr_e instruction);
jjsasm_instr_e jjsasm_a_to_instr_e(char *str);
jjsasm_type_e jjsasm_parsenum(char *str);
vector_t *jjsasm_tokenize(char *str);

#endif