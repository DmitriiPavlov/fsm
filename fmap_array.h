#ifndef FMAP_ARRAY_HEADER_GUARD_H
#define FMAP_ARRAY_HEADER_GUARD_H

#include <stdlib.h>

typedef struct{
    void* elements;
    size_t element_size;
    uint32_t length;
    uint32_t max_length;
} fmap_array_t;

static inline fmap_array_t* fmap_array_create(size_t element_size, uint32_t max_length){
    fmap_array_t* obj = (fmap_array_t*) malloc(sizeof(fmap_array_t));
    obj->elements = (fmap_array_t*) malloc(max_length * element_size);
    obj->max_length = max_length;
}

//currently thread unsafe, invalidates previous elements length (use RCU for safety if important)
static inline int fmap_array_resize(fmap_array_t* fmap_array, uint32_t new_max_length){
    assert(new_max_length > fmap_array->max_length);

    void* new_elements = (fmap_array_t*) realloc(elements, new_max_length * (fmap_array->element_size));
    if (new_elements == NULL){
        return -1;
    }

    fmap_array->elements = new_elements;
    fmap_array->max_length = new_max_length;
    return 0;
}

static inline int fmap_array_push(fmap_array_t* fmap_array, void* object){
    if (length == max_length && fmap_array_resize(fmap_array, fmap_array->max_length*2)){
        return -1;
    }
    memcpy(&(fmap_array->elements[fmap_array->length]), object, fmap_array->element_size);
    fmap_array->length++;
    return 0;
}

#endif
