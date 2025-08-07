#include "fmap_array.h"

fmap_t* fmap_init(int num_expected_states, int num_expected_events_per_state);
int fmap_add_default_handler(fmap_t* mapper, uint32_t enum_state_id, fsm_state_handler handler);
int fmap_add_event_handler(fmap_t* mapper,uint32_t enum_state_id, uint32_t event_state_id, fsm_state_handler handler);
fsm_state_handler fmap_get_handler(fmap_t* mapper, uint32_t enum_state_id, uint32_t event_state_id);