#include "fmap_array.h"

int fmap_add_default_handler(fmap_t* mapper, uint32_t enum_state_id, fsm_state_handler handler);
int fmap_add_event_handler(fmap_t* mapper,uint32_t enum_state_id, uint32_t event_state_id, fsm_state_handler handler);
fsm_state_handler fmap_get_handler(fmap_t* mapper, uint32_t enum_state_id, uint32_t event_state_id);