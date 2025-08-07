#include "fmap_array.h"

typedef struct {
    uint32_t enum_event_id;
    fsm_state_handler handler;
} fmap_entry_pair_t;

typedef struct {
    uint32_t            enum_state_id;
    fsm_state_handler   default_handler;
    fmap_array_t* event_handler_pairs;
} fmap_entry_t;

typedef struct {
    uint32_t num_of_prealloc_event_entries;
    //function map entry array
    fmap_array_t* function_map_entries;
} fmap_t;

static int fmap_entry_pair_compare(const void* pair1,const void* pair2){
    const uint32_t id1 = ((fmap_entry_pair_t*) pair1)->enum_event_id;
    const uint32_t id2 = ((fmap_entry_pair_t*) pair2)->enum_event_id
    return (id1 > id2) - (id1 < id2);
}

static inline int fmap_entry_create_pair(fmap_entry_t* entry, uint32_t enum_event_id, fsm_state_handler handler){
    //push back then sort
    fmap_entry_pair_t pair = {enum_event_id, handler};
    fmap_array_push(fmap_entry_t->event_handler_pairs, &pair);
    qsort(entry->event_handler_pairs->elements, entry->event_handler_pairs->length, sizeof(pair), fmap_entry_pair_compare);
}
static inline fmap_entry_pair_t* fmap_entry_locate_pair(fmap_entry_t* entry, uint32_t enum_event_id){
    fmap_entry_pair_t key = {enum_event_id, NULL};
    return bsearch(&key, entry->event_handler_pairs->elements, entry->event_handler_pairs->length, sizeof(key), fmap_entry_pair_compare);
}

static int fmap_entry_compare(const void* entry1, const void* entry2){
    const uint32_t id1 = ((fmap_entry_t*) pair1)->state_event_id;
    const uint32_t id2 = ((fmap_entry_t*) pair2)->state_event_id
    return (id1 > id2) - (id1 < id2);
}

static inline fmap_entry_t* fmap_create_entry(fmap_t* mapper, uint32_t enum_state_id){
    fmap_array_t* event_handler_pairs = fmap_array_create(sizeof(fmap_entry_pair_t), mapper->num_of_prealloc_event_entries);
    fmap_entry_t entry = {enum_state_id, NULL, event_handler_pairs};
    fmap_array_push(mapper->function_mapper_entries, &entry);
    qsort(mapper->function_mapper_entries, mapper->function_mapper_entries->length, sizeof(entry), fmap_entry_compare);
}

static inline fmap_entry_t* fmap_locate_entry(fmap_t* mapper, uint32_t enum_state_id){
    fmap_entry_t key = {enum_state_id, NULL, NULL};
    return bsearch(&key, mapper->function_map_entries->elements, mapper->function_map_entries->length, sizeof(key), fmap_entry_compare);
}

static inline fmap_entry_t* fmap_locate_or_create_entry(fmap_t* mapper, uint32_t enum_state_id){
    fmap_entry_t* fmap_entry = fmap_locate_entry(mapper, enum_state_id);
    if (fmap_entry){
        return fmap_entry;
    }
    else{
        return fmap_create_entry(mapper, enum_state_id);
    }
}

int fmap_add_default_handler(fmap_t* mapper, uint32_t enum_state_id, fsm_state_handler handler){
    fmap_entry_t* map_entry = fmap_locate_or_create_entry(mapper,enum_state_id);
    if (!map_entry){
        return -1;
    }
    assert(map_entry->default_handler == NULL);
    map_entry->default_handler = handler;
    return 0;
}

int fmap_add_event_handler(fmap_t* mapper,uint32_t enum_state_id, uint32_t enum_event_id, fsm_state_handler handler){
    fmap_entry_t* map_entry = fmap_locate_or_create_entry(mapper, enum_state_id);
    if (!map_entry){
        return -1;
    }

    fmap_entry_pair_t pair = {enum_event_id, handler};
    if (fmap_array_push(event_handler_pairs, &pair)){
        return -1;
    }

    return 0;
}

//falls through to default handler if no normal handler
fsm_state_handler fmap_get_handler(fmap_t* mapper, uint32_t enum_state_id, uint32_t enum_event_id){
    fmap_entry_t* fmap_entry = fmap_locate_entry(mapper, enum_state_id);
    if (fmap_entry == NULL){
        return NULL;
    }

    fmap_entry_pair_t* pair = fmap_entry_locate_pair(fmap_entry, enum_event_id);

    if (pair != NULL){
        return pair->handler;
    }

    return fmap_entry->default_handler;
}

fmap_t* fmap_init(int num_expected_states, int num_expected_events_per_state){
    fmap_t* fmap = (fmap_t*) malloc(sizeof(fmap));
    fmap->num_of_prealloc_event_entries = num_expected_events_per_state;
    fmap->function_map_entries = fmap_array_create(sizeof(fmap_entry_t), num_expected_states);
    return fmap;
}
