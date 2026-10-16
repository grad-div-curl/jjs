// Code by graddivcurl

#ifndef JJSASM_H
#define JJSASM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "vector.h"

/*

Defines
    JJSASM_TAG_CHAR
Types
    Enums
        jjsasm_type_e
        jjsasm_instr_e
        jjsasm_token_e
    Structs
        jjsasm_arg_t
        jjsasm_instr_t
        jjsasm_token_t
Variables
    static const int jjsasm_argc[]
    static const char *jjsasm_type_strs
    static const char *jjsasm_instr_strs
    static const char *jjsasm_token_strs

    static const size_t jjsasm_argc_size
    static const size_t jjsasm_instr_strs_size
Functions
    Helpers
        static uint64_t ll_read_u64(long long ll);
        static uint64_t d_read_u64(double d);
        static long long u64_read_ll(uint64_t u64);
        static double u64_read_d(uint64_t u64);
    Conversion to jjsasm types
        size_t jjsasm_argc_of(jjsasm_instr_e instruction);
    String conversion and prints
        const char *jjsasm_type_e_to_a(jjsasm_type_e type_e);
        const char *jjsasm_instr_e_to_a(jjsasm_instr_e instr_e);
        const char *jjsasm_token_e_to_a(jjsasm_token_e token_e);

        void jjsasm_print_arg_t(jjsasm_arg_t arg_t);
        void jjsasm_print_instr_t(jjsasm_instr_t instr_t);
        void jjasm_print_token_t(jjsasm_token_t token_t);
        void jjsasm_print_token_vector(vector_t *vec);
    Parsing strings
        jjsasm_instr_e jjsasm_a_to_instr_e(const char *str);
        jjsasm_instr_e jjsasm_a_to_instr_e_N(const char *str);
        jjsasm_type_e jjsasm_parsenum(const char *str);
        vector_t *jjsasm_tokenize(char *str);

*/

#define JJSASM_TAG_CHAR '#'
#define JJSASM_STR_WHITESPACE "\n\r\t\0 "
#define JJSASM_STR_LINEBREAK "\n\r"

static const int jjsasm_argc[] = {0, 2, 2, 2, 2, 1, 1, 1, 1, 1};
static const char *jjsasm_type_strs[] = {"UNKNOWN", "INTEGER", "DECIMAL", "STRING", "TAG", "BAD"};
static const char *jjsasm_instr_strs[] = {"NOP", "MOV", "ADD", "SUB", "CMP", "JMP", "JE", "JL", "JG", "SKL", "BAD"};
static const char *jjsasm_token_strs[] = {"UNKNOWN", "INSTRUCTION", "COMMENT", "LABEL", "BAD"};

static const size_t jjsasm_argc_size = sizeof(jjsasm_argc) / sizeof(int); // resolved at compile-time! like the others
static const size_t jjsasm_type_strs_size = sizeof(jjsasm_type_strs) / sizeof(char *);
static const size_t jjsasm_instr_strs_size = sizeof(jjsasm_instr_strs) / sizeof(char *);
static const size_t jjsasm_token_strs_size = sizeof(jjsasm_token_strs) / sizeof(char *);

typedef enum jjsasm_type_e {
    JJSASM_TYPE_UNKNOWN,
    JJSASM_TYPE_INTEGER,
    JJSASM_TYPE_DECIMAL,
    JJSASM_TYPE_STRING,
    JJSASM_TYPE_TAG,
    JJSASM_TYPE_BAD,
} jjsasm_type_e;

typedef enum jjsasm_instr_e {
    JJSASM_INSTR_NOP,
    JJSASM_INSTR_MOV,
    JJSASM_INSTR_ADD,
    JJSASM_INSTR_SUB,
    JJSASM_INSTR_CMP,
    JJSASM_INSTR_JMP,
    JJSASM_INSTR_JE,
    JJSASM_INSTR_JL,
    JJSASM_INSTR_JG,
    JJSASM_INSTR_SKL,
    JJSASM_INSTR_BAD
} jjsasm_instr_e;

typedef enum jjsasm_token_e {
    JJSASM_TOKEN_UNKNOWN,
    JJSASM_TOKEN_INSTRUCTION,
    JJSASM_TOKEN_COMMENT,
    JJSASM_TOKEN_LABEL,
    JJSASM_TOKEN_BAD
} jjsasm_token_e;

typedef struct jjsasm_arg_t {
    jjsasm_type_e type_e;
    uint64_t data;
} jjsasm_arg_t;

typedef struct jjsasm_instr_t {
    jjsasm_instr_e instr_e;
    uint8_t argc;
    jjsasm_arg_t *argv;
} jjsasm_instr_t;

typedef struct jjsasm_token_t {
    jjsasm_token_e token_e;
    void *data;
} jjsasm_token_t;

static uint64_t ll_readas_u64(long long ll);
static uint64_t d_readas_u64(double d);
static long long u64_readas_ll(uint64_t u64);
static double u64_readas_d(uint64_t u64);

size_t jjsasm_argc_of(jjsasm_instr_e instr_e);

const char *jjsasm_type_e_to_a(jjsasm_type_e type_e);
const char *jjsasm_instr_e_to_a(jjsasm_instr_e instr_e);
const char *jjsasm_token_e_to_a(jjsasm_token_e token_e);

void jjsasm_print_arg_t(jjsasm_arg_t arg_t);
void jjsasm_print_instr_t(jjsasm_instr_t instr_t);
void jjsasm_print_token_t(jjsasm_token_t token_t);
void jjsasm_print_token_vector(vector_t *vec);

jjsasm_instr_e jjsasm_a_to_instr_e(const char *str);
jjsasm_instr_e jjsasm_a_to_instr_e_N(const char *str);
jjsasm_type_e jjsasm_parsenum(const char *str);
vector_t *jjsasm_tokenize(char *str); // vector_t elements are of type jjsasm_token_t

#endif // JJSASM_H