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
   void* function_mapper_object;
} fsm_master_t;

typedef void (*fsm_state_handler)(fsm_state_t* state, fsm_event_t* event); 


fsm_master_t* fsm_init();
fsm_state_t*  fsm_init_state(fsm_master_t* master, uint32_t state_enum_id, void* data);
void fsm_register_handler(fsm_master_t* master, uint32_t state_enum_id, uint32_t event_enum_id, fsm_state_handler handler);
void fsm_register_default_handler(fsm_master_t* m, uint32_t state_enum_id, fsm_state_handler handler);
int  fsm_execute_one(fsm_state_t* state, fsm_event_t* event);
