#ifndef CAT_WARRIORS_CATS
#define CAT_WARRIORS_CATS

#include "splashkit.h"
#include <vector>

using namespace std;

enum cat_data_kind // The definitions for each cat that will be implemented within the game
{
    PHOEBE,
    MOLLY,
    NORMAN,
    CHESTER,
};

struct cat_data // The cat data keeps track of all of the information related to the cat.
{
    sprite cat_sprite;      // The cat's sprite - used to track position and movement
    cat_data_kind cat_kind; // Current kind of cat
    vector<cat_data> cats;  // The current cats collected for the player
};

cat_data new_cat_added(double x, double y); // The instructions for implementing a new cat to the game

void draw_cat(const cat_data &draw_cat); // uses the instructions from new_cat to draw and output the cat

void update_cat(cat_data &update_cat); // uses the instructions from new_cat to update the cat

#endif
