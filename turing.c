#include "turing.h"
#include <stdlib.h>
#include <stdio.h>

State *create_state(Accepting accepting, char *name) {
    State *state = malloc(sizeof(State));

    if (state == NULL) {
        return NULL;
    }

    state->accepting = accepting;
    state->name = name;

    return state;
}

Transition *create_transition(
    State *start_state,
    State *end_state,
    char input,
    char output,
    Direction direction
) {
    Transition *transition = malloc(sizeof(Transition));

    if (transition == NULL) {
        return NULL;
    }

    transition->start_state = start_state;
    transition->end_state = end_state;
    transition->input = input;
    transition->output = output;
    transition->direction = direction;

    return transition;
}

Turing *create_turing(
    char *tape,
    int head,
    State **states,
    size_t num_states,
    Transition **transitions,
    size_t num_transitions
) {
    if (tape == NULL || states == NULL || num_states == 0) {
        return NULL;
    }

    Turing *turing = malloc(sizeof(Turing));

    if (turing == NULL) {
        return NULL;
    }

    turing->tape = tape;
    turing->head = head;
    turing->current_state = states[0];
    turing->states = states;
    turing->num_states = num_states;
    turing->transitions = transitions;
    turing->num_transitions = num_transitions;

    return turing;
}
void run_turing(Turing *turing) {
    if (turing == NULL || turing->tape == NULL ||
        turing->current_state == NULL) {
        return;
    }

    size_t tape_length = 0;

    while (turing->tape[tape_length] != '\0') {
        tape_length++;
    }

    while (1) {
        if (turing->current_state->accepting == TRUE) {
            printf("Final Tape: %s\n", turing->tape);
            printf("Machine accepted.\n");
            return;
        }

        if (turing->head < 0 ||
            (size_t)turing->head >= tape_length) {
            printf("Head moved outside the tape.\n");
            return;
        }

        char symbol = turing->tape[turing->head];

        Transition *matched = NULL;

        for (size_t i = 0; i < turing->num_transitions; i++) {
            Transition *transition = turing->transitions[i];

            if (transition != NULL &&
                transition->start_state == turing->current_state &&
                transition->input == symbol) {
                matched = transition;
                break;
            }
        }

        if (matched == NULL) {
            printf("Machine halted: no matching transition.\n");
            return;
        }

        turing->tape[turing->head] = matched->output;

        if (matched->direction == LEFT) {
            turing->head--;
        } else if (matched->direction == RIGHT) {
            turing->head++;
        }

        turing->current_state = matched->end_state;
    }
}
void free_turing(Turing *turing) {
    if (turing == NULL) {
        return;
    }

    free(turing);
}
