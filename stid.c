#include "stid.h"
#include "fsm.h"
#include "fmap_array.h"

typedef struct{
    uint64_t id;
    fsm_state_t* state;
} stid_map_entry_t;

typedef struct{
    fmap_array_t* ids;
    uint64_t curr_id;
} stid_map_t;

void* stid_init(){
    stid_map_t* stid_map = (stid_map_t*) malloc(sizeof(stid_map_t));
    stid_map->ids = fmap_array_create(sizeof(stid_map_entry_t), 1000);
    stid_map->curr_id = 0;
}
uint64_t stid_provision_id(void* stid_map, fsm_state_t* state){
    stid_map_t* stmap = (stid_map_t*) stid_map;
    stid_map_entry_t entry = {stmap->curr_id, state};
    stmap->curr_id++;
    stmap->state = state;
    fmap_array_push(stmap->ids, &entry);
}

fsm_state_t* stid_lookup(uint64_t id){
    return (stid_map_entry_t*)(ids->elements[id])->state;
}