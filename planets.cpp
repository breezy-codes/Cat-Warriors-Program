#include "splashkit.h"
#include "player.h"
#include "planets.h"
#include "cat_warriors.h"

using namespace std;

// The instructions for implementing a new planet to the game
// The planet is created with a random kind
// Selected from a random option of 6
bitmap planet_collision(planet_data_kind planet_kind)
{
    switch (planet_kind)
    {
    case NEPTUNE:
        return bitmap_named("neptune"); // The bitmap for the neptune planet
    case SATURN:
        return bitmap_named("saturn"); // The bitmap for the saturn planet
    case PLUTO:
        return bitmap_named("pluto"); // The bitmap for the pluto planet
    case MERCURY:
        return bitmap_named("mercury"); // The bitmap for the mercury planet
    case ASTEROID:
        return bitmap_named("asteroid"); // The bitmap for the asteroid
    case SPACE_ROCK:
        return bitmap_named("space_rock"); // The bitmap for the space rock
    default:
        return bitmap_named("neptune"); // The default bitmap
    }
};

planet_collision_data new_planet_added(double x, double y) // The instructions for implementing a new planet to the game
{
    planet_collision_data result;
    result.planet_kind = static_cast<planet_data_kind>(rnd(6)); // Assigning a random planet kind to the planet_kind
    result.planet_sprite = create_sprite(planet_collision(result.planet_kind)); // Creating the planet sprite with a random kind

    // Setting the postion for the planet sprite
    sprite_set_x(result.planet_sprite, x);
    sprite_set_y(result.planet_sprite, y);

    // Giving some velocity to the planet sprite so that it can move around
    sprite_set_dx(result.planet_sprite, rnd() * 4 - 2);
    sprite_set_dy(result.planet_sprite, rnd() * 4 - 2);

    return result;
}

void draw_planet(const planet_collision_data &draw_planet) // uses the instructions from new_planet to draw and output the planet
{
    draw_sprite(draw_planet.planet_sprite); // Drawing the planet sprite to the screen
}

void update_planet(planet_collision_data &update_planet) // uses the instructions from new_planet to update the planet
{
    update_sprite(update_planet.planet_sprite); // Updating the planet sprite
}
