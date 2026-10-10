#ifndef TURING_H
#define TURING_H

#include <stddef.h>

typedef enum {
    LEFT,
    RIGHT
} Direction;

typedef enum {
    TRUE,
    FALSE
} Accepting;

typedef struct {
    Accepting accepting;
    char *name;
} State;

typedef struct {
    State *start_state;
    State *end_state;
    char input;
    char output;
    Direction direction;
} Transition;

typedef struct {
    char *tape;
    int head;
    State *current_state;
    State **states;
    size_t num_states;
    Transition **transitions;
    size_t num_transitions;
} Turing;

State *create_state(Accepting accepting, char *name);

Transition *create_transition(
    State *start_state,
    State *end_state,
    char input,
    char output,
    Direction direction
);

Turing *create_turing(
    char *tape,
    int head,
    State **states,
    size_t num_states,
    Transition **transitions,
    size_t num_transitions
);

void run_turing(Turing *turing);

void free_turing(Turing *turing);

#endif
