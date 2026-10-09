#include "vector.h"

#include <stdlib.h>
#include <stdint.h>
#include <string.h>

vector_t *vector_new(size_t element_size, size_t capacity){
    vector_t *vec = malloc(sizeof(vector_t));

    vec->element_size = element_size;
    vec->size = 0;
    vec->capacity = capacity;
    vec->data = malloc(element_size * capacity);

    return vec;
}

void *vector_get(vector_t *vec, uint64_t i){
    if (i >= vec->size) return NULL;
    return vec->data + vec->element_size * i;
}

void vector_push(vector_t *vec, void *element){
    if (vec->size == vec->capacity){
        vec->capacity *= 2;
        vec->data = realloc(vec->data, vec->capacity);
    }
    memcpy(vec->data + vec->element_size * vec->size, element, vec->element_size);
    vec->size++;
}

// returns out if successful, NULL if failed
void *vector_pop(vector_t *vec, void *out){
    if (vec->size == 0) return NULL;
    vec->size--;
    // data[size] now points to the former last element
    memcpy(out, vec->data + vec->size * vec->element_size, vec->element_size);
    return out;
}

void vector_free(vector_t *vec){
    free(vec->data);
    free(vec);
}