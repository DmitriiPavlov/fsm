#include "fsm.h"
#include <stdlib.h>

typedef struct {
    uint32_t event_state_id
    fsm_state_handler* event_specific_handlers;
} event_handler_pair;

typedef struct {
    uint32_t            enum_state_id;
    fsm_state_handler   default_handler;
    event_handler_pair* event_handler_pairs;
} function_map_entry_t;

typedef struct{
    //for each state id we want a function map entry object
    function_map_entry_t* entries;
} function_mapper_t;

static inline function_map_entry_t* fmap_locate_entry(function_mapper_t* mapper, uint32_t enum_state_id);
static inline function_map_entry_t* fmap_locate_or_create_entry(function_mapper_t* mapper, uint32_t enum_state_id);

static inline void fmap_add_default_handler(function_mapper_t* mapper, uint32_t enum_state_id, fsm_state_handler handler){
    function_map_entry_t* map_entry = fmap_locate_or_create_entry(mapper,enum_state_id);
    assert(map_entry->default_handler == NULL);
    map_entry->default_handler = handler;
}

static inline void fmap_add_event_handler(function_mapper_t* mapper,uint32_t enum_state_id, uint32_t event_state_id, fsm_state_handler handler){
    function_map_entry_t* map_entry = fmap_locate_or_create_entry(mapper, enum_state_id);
}




