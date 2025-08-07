#ifndef STID_HEADER_GUARD_H
#define STID_HEADER_GUARD_H

void*        stid_init();
uint64_t     stid_provision_id(void* stid_map, fsm_state_t* state);
fsm_state_t* stid_lookup(uint64_t);

#endif
