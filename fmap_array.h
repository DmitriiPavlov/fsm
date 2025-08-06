typedef struct{
    void* elements;
    size_t element_size;
    uint32_t length;
    uint32_t max_length;
} fmap_array_t;

static inline fmap_array_t* fmap_array_create(size_t element_size, uint32_t length);

// replaces the old array with the new array, then frees the old array
static inline fmap_array_replace(fmap_array_t* old_array, fmap_array_t* new_array);