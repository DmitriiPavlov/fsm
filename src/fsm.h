typedef struct {
    //public
    uint32_t enum_id;
    void*    data;

    //opaque
    uint32_t internal_state_id;
    fsm_master_t* master_object;
} fsm_state_t;

typedef struct {
    uint32_t enum_id;
    void*    data;
} fsm_event_t;

typedef struct {
   void* fmap;
   void* stid_map;
   uint64_t flags;
} fsm_master_t;

#define _FSM_BEGIN_HANDLING(s, e) \
    fsm_master_t* ___fsm_internal_function_master_object = s->master_object; \
    fsm_state_t*  ___fsm_internal_function_state_object = s; \
    fsm_event_t*  ___fsm_internal_function_event_object = e;
#define FSM_BEGIN_HANDLING(s, e) _FSM_BEGIN_HANDLING((s), (e))

#define FSM_STATE_IS(state_enum_literal) (__fsm_internal_function_state_object->enum_id == (state_enum_literal))
#define FSM_EVENT_IS(event_enum_literal) (__fsm_internal_function_event_object->enum_id == (event_enum_literal))

#define FSM_STATE_TRANSITION(state_enum_literal) \
    (__fsm_internal_function_state_object->enum_id = state_enum_literal); \ 
    return 0; \


typedef void (*fsm_state_handler)(fsm_state_t* state, fsm_event_t* event); 


fsm_master_t* fsm_init();
fsm_state_t*  fsm_create_state(fsm_master_t* master, uint32_t state_enum_id, void* data);
void fsm_register_handler(fsm_master_t* master, uint32_t state_enum_id, uint32_t event_enum_id, fsm_state_handler handler);
void fsm_register_default_handler(fsm_master_t* m, uint32_t state_enum_id, fsm_state_handler handler);
void fsm_execute_one(fsm_state_t* state, uint32_t event_enum_id);
void fsm_execute_one(fsm_state_t* state, fsm_event_t* event);
