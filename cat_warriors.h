#ifndef CAT_WARRIORS_GAME
#define CAT_WARRIORS_GAME

#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "planets.h"
#include "cats.h"

#include <vector>
using std::vector;
using namespace std;

/* The game data keeps track of all of the information related to the game.
 * This includes the player
 * This includes the power ups
 * This includes the planets
 * This includes the cats
 */
struct game_data
{
    // data for the player
    player_data player;
    timer game_timer;
    ship_kind spaceship_kind;

    // data for the power ups
    power_up_data power_up;
    power_up_kind kind;
    vector<power_up_data> power_ups;

    // data for the planets
    planet_collision_data planet;
    planet_data_kind planet_kind;
    vector<planet_collision_data> planets;

    // Data for the cats
    cat_data cat;
    cat_data_kind cat_kind;
    vector<cat_data> cats;

    bool menu;
};

// Loads the resources for the game
void load_resources();

// Creates a new game for the player
game_data new_game();

// Updates the game by updating the player, power ups, adding power ups and checking
void update_game(game_data &game);

// Draws the game to the screen by drawing the hud, player and power ups
void draw_game(const game_data &game);

// Adds a power up to the dynamic array of the game's power up by calling the new_power_up function
void add_power_up(game_data &game);

// Adds a planet to the dynamic array of the game's planet by calling the new_planet function
void add_planet(game_data &game);

// Adds a cat to the dynamic array of the game's cat by calling the new_cat function
void add_cat(game_data &game);

// Checks the collision between the player and power up to call the respective procedures to
void check_collisions(game_data &game);

// Applies the power up to the player by calling the respective procedures to
void apply_power_up(game_data &game, int index);

// Removes the power up from the dynamic array of the game's power up
void remove_power_up(game_data &game, int index);

// Applies the planet to the player by calling the respective procedures to
void apply_planet(game_data &game, int index);

// Removes the planet from the dynamic array of the game's planet
void remove_planet(game_data &game, int index);

// Applies the cat to the player by calling the respective procedures to
void apply_cat(game_data &game, int index);

// Removes the cat from the dynamic array of the game's cat
void remove_cat(game_data &game, int index);

// Checks the position of the power up and moves it back into the game range if it is out of bounds
void check_power_up_position(game_data &game);

// Checks the position of the planet and moves it back into the game range if it is out of bounds
void check_planet_position(game_data &game);

// Checks the position of the cat and moves it back into the game range if it is out of bounds
void check_cat_position(game_data &game);

// Draws the hud to the screen by drawing the timer and the score
void draw_hud(const game_data &game);

#endif
