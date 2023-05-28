#ifndef CAT_WARRIORS_PLANETS
#define CAT_WARRIORS_PLANETS

#include "splashkit.h"
#include <vector>

using namespace std;

enum planet_data_kind // The definitions for each planet that will be implemented within the game
{
    NEPTUNE,
    SATURN,
    PLUTO,
    MERCURY,
    ASTEROID,
    SPACE_ROCK,
};

struct planet_collision_data
{
    sprite planet_sprite;                  // The planet's sprite - used to track position and movement
    planet_data_kind planet_kind;          // Current kind of planet
    vector<planet_collision_data> planets; // The current planets collected for the player
};

planet_collision_data new_planet_added(double x, double y); // The instructions for implementing a new planet to the game

void draw_planet(const planet_collision_data &draw_planet); // The instructions for adding in new planets

void update_planet(planet_collision_data &update_planet); // Actions a step update of the planet - moving them and adjusting the camera.

#endif
