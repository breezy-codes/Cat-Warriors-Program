#include "splashkit.h"
#include "power_up.h"
#include "player.h"
#include "cat_warriors.h"

using namespace std;

bitmap power_up_bitmap(power_up_kind kind) // The definitions for each power up that will be implemented within the game
{
    switch (kind)
    {
    case POWER:
        return bitmap_named("power"); // the bitmap for the fuel power up
    case HEALTH:
        return bitmap_named("heart"); // the bitmap for the health power up
    case SHIELD:
        return bitmap_named("shield"); // the bitmap for the shield power up
    case COINS:
        return bitmap_named("coin"); // the bitmap for the coins power up
    case STAR:
        return bitmap_named("star"); // the bitmap for the star power up
    default:
        return bitmap_named("fuel"); // the default bitmap
    }
};

power_up_data new_power_up(double x, double y) // The instructions for implementing a new power up to the game
{
    power_up_data result;

    // Assigning a random power up kind to the power_up_kind
    result.kind = static_cast<power_up_kind>(rnd(5));

    // Creating the power up sprite with a random kind
    result.power_up_sprite = create_sprite(power_up_bitmap(result.kind));

    // Setting the postion for the power up sprite
    sprite_set_x(result.power_up_sprite, x);
    sprite_set_y(result.power_up_sprite, y);

    // Giving some velocity to the power up sprite so that it can move around
    sprite_set_dx(result.power_up_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.power_up_sprite, rnd() * 4 - 2);

    return result;
}

void draw_power_up(const power_up_data &draw_power) // uses the instructions from new_power_up to draw and output the power up
{
    draw_sprite(draw_power.power_up_sprite); // Drawing the power up sprite to the screen
}

void update_power_up(power_up_data &update_power) // Uses the instructions from new_power_up to update the power up
{
    update_sprite(update_power.power_up_sprite); // Updating the power up sprite
}
