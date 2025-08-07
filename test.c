#include "src/fsm.h"

typedef enum{
    NEXT_LIGHT,
    AMBULANCE_HEADED_THIS_WAY,
    AMBULANCE_HEADED_OTHER_WAY
} traffic_event_t;

typedef enum{
    RED,
    GREEN,
    YELLOW
} light_color_t;

static void green_light_event_handler(fsm_state_t* state, fsm_event_t* event){
    FSM_BEGIN_HANDLING(state,event);   
    FSM_STATE_IS(GREEN);

    if (FSM_EVENT_IS(NEXT_LIGHT)){
        FSM_STATE_TRANSITION(YELLOW);
    }

    else if (FSM_EVENT_IS(AMBULANCE_HEADED_THIS_WAY)){
        FSM_STATE_TRANSITION(GREEN);
    }
    
    else if (FSM_EVENT_IS(AMBULANCE_HEADED_OTHER_WAY)){
        FSM_STATE_TRANSITION(YELLOW);
    }

}

static void red_light_event_handler(fsm_state_t* state, fsm_event_t* event){
    FSM_BEGIN_HANDLING(state,event);
    FSM_STATE_IS(RED);

    if (FSM_EVENT_IS(NEXT_LIGHT)){
        FSM_STATE_TRANSITION(GREEN);
    }

    else if (FSM_EVENT_IS(AMBULANCE_HEADED_THIS_WAY)){
        FSM_STATE_TRANSITION(GREEN);
    }
    
    else if (FSM_EVENT_IS(AMBULANCE_HEADED_OTHER_WAY)){
        FSM_STATE_TRANSITION(RED);
    }
}

static void yellow_light_event_handler(fsm_state_t* state, fsm_event_t* event){
    FSM_BEGIN_HANDLING(state,event);
    FSM_STATE_IS(YELLOW);

    if (FSM_EVENT_IS(NEXT_LIGHT)){
        FSM_STATE_TRANSITION(RED);
    }

    else if (FSM_EVENT_IS(AMBULANCE_HEADED_THIS_WAY)){
        FSM_STATE_TRANSITION(GREEN);
    }
    
    else if (FSM_EVENT_IS(AMBULANCE_HEADED_OTHER_WAY)){
        FSM_STATE_TRANSITION(RED);
    }
}

int main(){
    fsm_master_t* fsm = fsm_init();
    fsm_register_handler(GREEN, green_light_event_handler);
    fsm_register_handler(YELLOW,yellow_light_event_handler);
    fsm_register_handler(RED, red_light_event_handler);

    fsm_state_t* traffic_light = fsm_create_state(fsm, RED, NULL);
    fsm_execute_one(traffic_light,NEXT_LIGHT);
    return;
}