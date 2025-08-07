#include "fsm.h"
#include "fmap_array.h"
#include <stdlib.h>

fsm_master_t* fsm_init(){
    fsm_master_t* fsm = (fsm_master_t*) malloc(sizeof(fsm_master_t));
    fsm->fmap = fmap_init(10,10);
    fsm->stid_map = stid_init();
}


fsm_state_t* fsm_create_state(fsm_master_t* master, uint32_t state_enum_id, void* data){
    fsm_state_t* state = (fsm_state_t*) malloc(sizeof(fsm_state_t));
    state->enum_id = state_enum_id;
    state->data = data;
    state->master_object = master;
    state->internal_state_id = stid_provision_id(master->stid_map, state);
}

void fsm_register_handler(fsm_master_t* master, uint32_t state_enum_id, uint32_t event_enum_id, fsm_state_handler handler){
    //ignoring error handling.. for now
    (void) fmap_add_event_handler(master->fmap, state_enum_id, event_enum_id, handler);
}

void fsm_register_default_handler(fsm_master_t* m, uint32_t state_enum_id, fsm_state_handler handler){
    //ignoring error handling.. for now
    (void) fmap_add_default_handler(master->fmap, state_enum_id, handler);
}

void fsm_execute_one(fsm_state_t* state, uint32_t enum_id){
    fsm_event_t e = {enum_id, NULL};
    fsm_execute_one(state, &e);
}

void fsm_execute_one(fsm_state_t* state, fsm_event_t* event){
    fsm_state_handler handler = fmap_get_handler(state->master->fmap, state->enum_id, event->enum_id);
    if (handler != NULL) handler(state, event);
}



