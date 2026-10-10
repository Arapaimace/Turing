#include "turing.h"
#include <stdio.h>
#include <stdlib.h>

int main(void) {
    char tape[] = "101";

    State *q0 = create_state(FALSE, "q0");
    State *q1 = create_state(TRUE, "q1");

    if (q0 == NULL || q1 == NULL) {
        free(q0);
        free(q1);
        return EXIT_FAILURE;
    }

    Transition *transition = create_transition(
        q0,
        q1,
        '1',
        '0',
        RIGHT
    );

    if (transition == NULL) {
        free(q0);
        free(q1);
        return EXIT_FAILURE;
    }

    State *states[] = { q0, q1 };
    Transition *transitions[] = { transition };

    Turing *turing = create_turing(
        tape,
        0,
        states,
        2,
        transitions,
        1
    );

    if (turing == NULL) {
        free(transition);
        free(q0);
        free(q1);
        return EXIT_FAILURE;
    }

    printf("Initial tape: %s\n", turing->tape);
    printf("Initial head: %d\n", turing->head);
    printf("Initial state: %s\n", states[0]->name);

    run_turing(turing);

    free_turing(turing);
    free(transition);
    free(q0);
    free(q1);

    return EXIT_SUCCESS;
}
