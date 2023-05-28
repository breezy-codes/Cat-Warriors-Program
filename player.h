#ifndef LOST_IN_SPACE_PLAYER
#define LOST_IN_SPACE_PLAYER

#include "splashkit.h"
#include <vector>

using namespace std;

#define PLAYER_SPEED 1.5
#define PLAYER_ROTATE_SPEED 3
#define SCREEN_BORDER 100

//space ship types
enum ship_kind
{
    CALYPSO,
    ELECTRA,
    LYRA
};

struct player_data
{
    sprite player_sprite;     // The player's sprite - used to track position and movement
    ship_kind spaceship_kind; // Current kind of player ship
    int score;                // The current score for the player
    double fuel_pct;          // The current fuel percentage for the player
    double health_pct;        // The current health percentage for the player
    double shield_pct;        // The current shield percentage for the player
    double timer_pct;         // The current timer percentage for the player
    int coins;                // The current coins collected for the player
    int stars;                // The current stars collected for the player
    int cats;                 // The current cats collected for the player
};

player_data new_player(); // Adds in a new player to the screen with the default ship

void draw_player(const player_data &player_to_draw); // draws player to screen

void update_player(player_data &player_to_update); // updates the player's position and movement

void handle_input(player_data &player); // handles the player's input

#endif
