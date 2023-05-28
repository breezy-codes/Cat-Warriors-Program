#include "splashkit.h"
#include "player.h"
#include "cats.h"
#include "cat_warriors.h"

using namespace std;

// The definitions for each cat that will be implemented within the game
bitmap cat_collections(cat_data_kind cat_kind)
{
    switch (cat_kind)
    {
    case PHOEBE:
        return bitmap_named("phoebe");
    case MOLLY:
        return bitmap_named("molly");
    case NORMAN:
        return bitmap_named("norman");
    case CHESTER:
        return bitmap_named("chester");
    default:
        return bitmap_named("phoebe");
    }
};

// The instructions for implementing a new cat to the game
cat_data new_cat_added(double x, double y)
{
    cat_data result;

    // Assigning a random cat kind to the cat_kind
    result.cat_kind = static_cast<cat_data_kind>(rnd(4));

    // Creating the cat sprite with a random kind
    result.cat_sprite = create_sprite(cat_collections(result.cat_kind));

    // Setting the postion for the cat sprite
    sprite_set_x(result.cat_sprite, x);
    sprite_set_y(result.cat_sprite, y);

    // Giving some velocity to the cat sprite so that it can move around
    sprite_set_dx(result.cat_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.cat_sprite, rnd() * 4 - 2);

    return result;
}

// uses the instructions from new_cat to draw and output the cat
void draw_cat(const cat_data &draw_cat)
{
    // Drawing the cat sprite to the screen
    draw_sprite(draw_cat.cat_sprite);
}

// uses the instructions from new_cat to update the cat
void update_cat(cat_data &update_cat)
{
    // Moving the cat sprite
    update_sprite(update_cat.cat_sprite);
}
