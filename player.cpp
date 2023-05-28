#include "player.h"
#include "splashkit.h"
#include "planets.h"
#include "cats.h"
#include "power_up.h"
#include "menu.h"

// global constants for game size and range
#define MIN_GAME_RANGE -1500
#define MAX_GAME_RANGE 1500
#define MAX_SCREEN_RANGE 3000

// The three ship types
bitmap ship_bitmap(ship_kind kind)
{
    switch (kind)
    {
    case CALYPSO:
        return bitmap_named("calypso");
    case ELECTRA:
        return bitmap_named("electra");
    default:
        return bitmap_named("lyra");
    }
}

player_data new_player() // add in all the necessary player data needed to record the player's progress
{
    player_data result;                        // The player data keeps track of all of the information related to the player.
    bitmap default_bitmap = ship_bitmap(LYRA); // The default bitmap for the player
    result.fuel_pct = 1;                       // The starting fuel percentage for the player
    result.health_pct = 1;                     // The starting health percentage for the player
    result.shield_pct = 0.5;                   // The starting shield percentage for the player
    result.timer_pct = 1;                      // The starting timer percentage for the player
    result.coins = 0;                          // The starting coins collected for the player
    result.stars = 0;                          // The starting stars collected for the player
    result.score = 0;                          // The starting score for the player
    result.cats = 0;                           // The starting cats collected for the player

    // Create the sprite with 3 layers - we can turn on and off based
    // on the ship kind selected
    result.player_sprite = create_sprite(default_bitmap);

    sprite_add_layer(result.player_sprite, ship_bitmap(CALYPSO), "calypso");
    sprite_add_layer(result.player_sprite, ship_bitmap(ELECTRA), "electra");

    // Default to layer 0 = Lyra so hide others
    sprite_hide_layer(result.player_sprite, 1);
    sprite_hide_layer(result.player_sprite, 2);

    result.spaceship_kind = LYRA;

    // Position in the centre of the initial screen
    sprite_set_x(result.player_sprite, ((screen_width() - sprite_width(result.player_sprite)) / 2));
    sprite_set_y(result.player_sprite, ((screen_height() - sprite_height(result.player_sprite)) / 2));

    // Setting the camera at 0 postion every time a new player is created
    set_camera_x(0);
    set_camera_y(0);

    return result;
}

void draw_player(const player_data &player_to_draw) // add in all the necessary player data needed to record the player's progress
{
    draw_sprite(player_to_draw.player_sprite);
}

void update_player(player_data &player_to_update) // update all the necessary player data needed to record the player's progress
{
    update_sprite(player_to_update.player_sprite); // Apply movement based on rotation and velocity in the sprite

    // Test edge of screen boundaries to adjust the camera
    double left_edge = camera_x() + SCREEN_BORDER;
    double right_edge = left_edge + screen_width() - 2 * SCREEN_BORDER;
    double top_edge = camera_y() + SCREEN_BORDER;
    double bottom_edge = top_edge + screen_height() - 2 * SCREEN_BORDER;

    point_2d sprite_center = center_point(player_to_update.player_sprite); // Get the center of the player

    if (sprite_center.y < top_edge) // Test top/bottom of screen
    {
        move_camera_by(0, sprite_center.y - top_edge);
    }
    else if (sprite_center.y > bottom_edge)
    {
        move_camera_by(0, sprite_center.y - bottom_edge);
    }
    if (sprite_center.x < left_edge) // Test left/right of screen
    {
        move_camera_by(sprite_center.x - left_edge, 0);
    }
    else if (sprite_center.x > right_edge)
    {
        if (sprite_center.x > MAX_GAME_RANGE)
        {
            sprite_set_x(player_to_update.player_sprite, (MAX_GAME_RANGE - MAX_SCREEN_RANGE)); // Wrap the player around to the left side of the game map
        }
        else
        {
            move_camera_by(sprite_center.x - right_edge, 0);
        }
    }

    // Update the player's fuel, health, and timer as the game goes on
    if (player_to_update.fuel_pct > 0)
    {
        player_to_update.fuel_pct -= 0.000278;
    }
    if (player_to_update.health_pct > 0)
    {
        player_to_update.health_pct -= 0.0001;
    }
    if (player_to_update.timer_pct > 0)
    {
        player_to_update.timer_pct -= 0.0001;
    }
}

void player_switch_to_ship(player_data &player, ship_kind target) // Switch the ship kind - will adjust which layer is hidden/shown
{

    if (player.spaceship_kind != target) // only do this if we're changing ship kind
    {
        sprite_show_layer(player.player_sprite, static_cast<int>(target));
        sprite_hide_layer(player.player_sprite, static_cast<int>(player.spaceship_kind));
        player.spaceship_kind = target; // remember what is currently shown
    }
}

void handle_input(player_data &player) // Add functions to allow the player to move and change characters
{
    // Allow the player to switch ships
    if (key_typed(NUM_1_KEY))
        player_switch_to_ship(player, LYRA);
    if (key_typed(NUM_2_KEY))
        player_switch_to_ship(player, CALYPSO);
    if (key_typed(NUM_3_KEY))
        player_switch_to_ship(player, ELECTRA);

    // Handle movement - rotating left/right and moving forward/back
    float dx = sprite_dx(player.player_sprite);
    float rotation = sprite_rotation(player.player_sprite);

    // Allow rotation with left/right keys
    if (key_down(LEFT_KEY))
        sprite_set_rotation(player.player_sprite, rotation - PLAYER_ROTATE_SPEED);
    if (key_down(RIGHT_KEY))
        sprite_set_rotation(player.player_sprite, rotation + PLAYER_ROTATE_SPEED);

    // Increase speed with up/down keys - typed to give step increases
    if (key_typed(DOWN_KEY))
        sprite_set_dx(player.player_sprite, dx - PLAYER_SPEED);
    if (key_typed(UP_KEY))
        sprite_set_dx(player.player_sprite, dx + PLAYER_SPEED);
}
