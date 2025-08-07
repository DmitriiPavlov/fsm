#include "fmap_array.h"

typedef struct {
    uint32_t enum_event_id;
    fsm_state_handler handler;
} fmap_event_handler_pair;

typedef struct {
    uint32_t            enum_state_id;
    fsm_state_handler   default_handler;
    fmap_array_t* event_handler_pairs;
} fmap_entry_t;

typedef struct {
    //function map entry array
    fmap_array_t* function_map_entries;
} fmap_t;

static inline int fmap_entry_create_pair(fmap_entry_t* entry, uint32_t enum_event_id, fsm_state_handler handler);
static inline fmap_event_handler_pair* fmap_entry_locate_pair(fmap_entry_t* entry, uint32_t enum_event_id);
static inline fmap_entry_t* fmap_create_entry(fmap_t* mapper, uint32_t enum_state_id);
static inline fmap_entry_t* fmap_locate_entry(fmap_t* mapper, uint32_t enum_state_id);

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
}

int fmap_add_event_handler(fmap_t* mapper,uint32_t enum_state_id, uint32_t enum_event_id, fsm_state_handler handler){
    fmap_entry_t* map_entry = fmap_locate_or_create_entry(mapper, enum_state_id);
    if (!map_entry){
        return -1;
    }

    fmap_event_handler_pair pair = {enum_event_id, handler};
    if (fmap_array_push(event_handler_pairs, &pair)){
        return -1;
    }
}

//falls through to default handler if no normal handler
fsm_state_handler fmap_get_handler(fmap_t* mapper, uint32_t enum_state_id, uint32_t enum_event_id){
    fmap_entry_t* fmap_entry = fmap_locate_entry(mapper, enum_state_id);
    if (fmap_entry == NULL){
        return NULL;
    }

    fmap_event_handler_pair* pair = fmap_entry_locate_pair(fmap_entry, enum_event_id);

    if (pair != NULL){
        return pair->handler;
    }

    return fmap_entry->default_handler;
}
