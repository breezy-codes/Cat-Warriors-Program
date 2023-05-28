#ifndef CAT_WARRIORS_POWER_UP
#define CAT_WARRIORS_POWER_UP

#include "splashkit.h"
#include <vector>

using namespace std;

// The definitions for each power up that will be implemented within the game
// The power up kind is used to determine which power up is being used
enum power_up_kind
{
    POWER,
    HEALTH,
    SHIELD,
    COINS,
    STAR,
};

// The power up data keeps track of all of the information related to the power up.
struct power_up_data
{
    sprite power_up_sprite;          // The power up's sprite - used to track position and movement
    power_up_kind kind;              // Current kind of power up
    vector<power_up_data> power_ups; // The current power ups collected for the player
};

power_up_data new_power_up(double x, double y); // The instructions for implementing a new power up to the game

void draw_power_up(const power_up_data &power_to_draw); // The instructions for implementing a new power up to the game

void update_power_up(power_up_data &power_to_update); // Actions a step update of the power up - moving them and adjusting the camera

#endif
