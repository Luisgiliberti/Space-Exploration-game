#include "space_explorer.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

// define the ship state structure
typedef struct {
    unsigned int crt_planet;
    double distance_from_mixer;
    unsigned int next_planet;
    unsigned int action_count;
} ShipState;

ShipAction space_hop(unsigned int crt_planet,
                     const unsigned int *connections,
                     int num_connections,
                     double distance_from_mixer,
                     void *ship_state)

{
    // create a new ship state if NULL was passed
    if (ship_state == NULL) {
        // allocate memory for the ship state
        ShipState *state = malloc(sizeof(ShipState));
        // initialize the state with the current planet and distance from mixer
        state->crt_planet = crt_planet;
        state->distance_from_mixer = distance_from_mixer;
        // set the ship state in the return value
        ShipAction action;
        action.ship_state = state;
        // randomly select the next planet
        action.next_planet = connections[rand() % num_connections];
        // return the action
        return action;
    }

    // get the current ship state
    ShipState *state = (ShipState *) ship_state;

    // check if we have already visited this planet
    if (state->crt_planet == crt_planet) {
        // randomly select the next planet
        state->action_count++;
        if (state->action_count > num_connections) {
            // if action_count > num_conn, reset the action count
            state->action_count = 0;
            // and select a random planet
            state->next_planet = connections[rand() % num_connections];
        }
    }

    // we have jumped to a new planet
    else {
        // update the distance from mixer
        state->distance_from_mixer = distance_from_mixer;
        // set the current planet
        state->crt_planet = crt_planet;
        // randomly select the next planet
        state->action_count = 0;
        state->next_planet = connections[rand() % num_connections];
    }

    // create the return value
    ShipAction action;
    action.ship_state = state;
    action.next_planet = state->next_planet;
    // return the action
    return action;
}