#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "cat_warriors.h"
#include "planets.h"
#include "cats.h"
#include "menu.h"

// global constants for game size and range
#define MIN_GAME_RANGE -1500
#define MAX_GAME_RANGE 1500
#define MAX_SCREEN_RANGE 3000

game_data new_game()
{
    game_data game;             // Creating a new game
    game.menu = true;           // Setting the menu to true so that the menu screen is displayed
    game.player = new_player(); // Creating a new player
    return game;                // Returning the game
}

void add_power_up(game_data &game) // Adding a new power up to the display
{
    int value = rnd(MIN_GAME_RANGE, MAX_GAME_RANGE);
    // Adding the power up to the vector at any random position in the players area
    game.power_ups.push_back(new_power_up(value, value));
}

void add_planet(game_data &game) // Adding a new planet to the display
{
    int value = rnd(MIN_GAME_RANGE, MAX_GAME_RANGE);
    // Adding the power up to the vector at any random position in the players area
    game.planets.push_back(new_planet_added(value, value));
}

void add_cat(game_data &game) // Adding a new cat to the display
{
    int value = rnd(MIN_GAME_RANGE, MAX_GAME_RANGE);
    // Adding the power up to the vector at any random position in the players area
    game.cats.push_back(new_cat_added(value, value));
}

// Check for collision then apply power up and remove from screen
// Check for collision then apply planets and remove from screen
// Check for collision then apply cats and remove from screen
void check_collisions(game_data &game)
{
    for (int i = game.power_ups.size() - 1; i >= 0; i--) // Checking for collision between the player and power up
    {
        if (sprite_collision(game.player.player_sprite, game.power_ups[i].power_up_sprite))
        {
            // Apply the power up to the user and then remove from the screen
            apply_power_up(game, i);
            remove_power_up(game, i);
        }
    }
    for (int i = game.planets.size() - 1; i >= 0; i--) // Checking for collision between the player and planets
    {
        if (sprite_collision(game.player.player_sprite, game.planets[i].planet_sprite))
        {
            // Apply the power up to the user and then remove from the screen
            apply_planet(game, i);
            remove_planet(game, i);
        }
    }
    for (int i = game.cats.size() - 1; i >= 0; i--) // Checking for collision between the player and cats
    {
        if (sprite_collision(game.player.player_sprite, game.cats[i].cat_sprite))
        {
            // Apply the power up to the user and then remove from the screen
            apply_cat(game, i);
            remove_cat(game, i);
        }
    }
}

void apply_power_up(game_data &game, int index) // Apply the effects of the power ups
{
    if (game.power_ups[index].kind == POWER) // Increasing the value only if the percentage is less than 100% for the player
    {
        if (game.player.fuel_pct <= 1)
            game.player.fuel_pct += 0.20;
    }

    else if (game.power_ups[index].kind == HEALTH) // Increasing the value only if the percentage is less than 100% for the player
    {
        if (game.player.health_pct <= 1)
            game.player.health_pct += 0.20;
    }

    else if (game.power_ups[index].kind == SHIELD) // Increasing the value only if the percentage is less than 100% for the player
    {
        if (game.player.shield_pct <= 1)
            game.player.shield_pct += 0.10;
    }

    else if (game.power_ups[index].kind == COINS)
    {
        // Player collects one coin every time a coin power up is collected
        // Player has 1 pointed added to their score every time a coin power up is collected
        game.player.coins += 1;
        game.player.score += 1;
    }
    else if (game.power_ups[index].kind == STAR)
    {
        // Player collects one star every time a star power up is collected
        // Player has 3 points added to their score every time a star power up is collected
        game.player.stars += 1;
        game.player.score += 3;
    }
}

void remove_power_up(game_data &game, int index) // Removing the power up at the index from the vector
{
    int last_idx = game.power_ups.size() - 1;
    game.power_ups[index] = game.power_ups[last_idx];
    game.power_ups.pop_back();
}

// Apply the planet based on the different planets within the game
// The larger planets create more damage to the player, while the smaller planets create less damage
// If the player has more than 0% in their shield field, then the shield will go down
// Else if the player has less than 0% in their shield field, then the health will go down
void apply_planet(game_data &game, int index)
{

    if (game.planets[index].planet_kind == NEPTUNE)
    {
        // If player shield is greater than 0.25, then the shield is decreased by 0.25
        //  Else if player shield is less than 0.25, then health is decreased by 0.10
        if (game.player.shield_pct < 0.10)
        {
            game.player.shield_pct = 0;
            game.player.health_pct -= 0.10;
        }
        else if (game.player.shield_pct < 0.25)
            game.player.shield_pct -= 0.25;
        else
            game.player.shield_pct -= 0.25;
    }

    if (game.planets[index].planet_kind == SATURN)
    {
        // If player shield is greater than 0, then shield will go down by 0.25
        //  Else if player shield is less than 0, then health will go down by 0.25
        if (game.player.shield_pct < 0.10)
        {
            game.player.shield_pct = 0;
            game.player.health_pct -= 0.10;
        }
        else if (game.player.shield_pct < 0.25)
            game.player.shield_pct -= 0.25;
        else
            game.player.shield_pct -= 0.25;
    }

    if (game.planets[index].planet_kind == MERCURY)
    {
        // If player shield is greater than 0, then shield will go down by 0.20
        //  Else if player shield is less than 0, then health will go down by 0.20
        if (game.player.shield_pct < 0.10)
        {
            game.player.shield_pct = 0;
            game.player.health_pct -= 0.10;
        }
        else if (game.player.shield_pct < 0.20)
            game.player.shield_pct -= 0.20;
        else
            game.player.shield_pct -= 0.20;
    }

    if (game.planets[index].planet_kind == PLUTO)
    {
        // If player shield is greater than 0, then shield will go down by 0.10
        //  Else if player shield is less than 0, then health will go down by 0.10
        if (game.player.shield_pct < 0.05)
        {
            game.player.shield_pct = 0;
            game.player.health_pct -= 0.05;
        }
        else if (game.player.shield_pct < 0.10)
            game.player.shield_pct -= 0.10;
        else
            game.player.shield_pct -= 0.10;
    }

    if (game.planets[index].planet_kind == ASTEROID)
    {
        // If player shield is greater than 0, then shield will go down by 0.10
        //  Else if player shield is less than 0, then health will go down by 0.10
        if (game.player.shield_pct < 0.05)
        {
            game.player.shield_pct = 0;
            game.player.health_pct -= 0.05;
        }
        else if (game.player.shield_pct < 0.10)
            game.player.shield_pct -= 0.10;
        else
            game.player.shield_pct -= 0.10;
    }

    if (game.planets[index].planet_kind == SPACE_ROCK)
    {
        // If player shield is greater than 0, then shield will go down by 0.05
        //  Else if player shield is less than 0, then health will go down by 0.05
        if (game.player.shield_pct < 0.05)
        {
            game.player.shield_pct = 0;
            game.player.health_pct -= 0.03;
        }
        else if (game.player.shield_pct < 0.10)
            game.player.shield_pct -= 0.05;
        else
            game.player.shield_pct -= 0.05;
    }
}

void remove_planet(game_data &game, int index) // Removing the planet at the index from the vector
{
    int last_idx = game.planets.size() - 1;
    game.planets[index] = game.planets[last_idx];
    game.planets.pop_back();
}

// Once collision has been detected for a cat, remove the cat from the vector
// Then apply the value of the specific cat to the players score
// And apply the cat to the total collected score
void apply_cat(game_data &game, int index)
{
    if (game.cats[index].cat_kind == PHOEBE)
    {
        game.player.cats += 1;
        game.player.score += 14;
    }
    if (game.cats[index].cat_kind == MOLLY)
    {
        game.player.cats += 1;
        game.player.score += 16;
    }
    if (game.cats[index].cat_kind == NORMAN)
    {
        game.player.cats += 1;
        game.player.score += 18;
    }
    if (game.cats[index].cat_kind == CHESTER)
    {
        game.player.cats += 1;
        game.player.score += 20;
    }
}

void remove_cat(game_data &game, int index) // Removing the cat at the index from the vector
{
    int last_idx = game.cats.size() - 1;
    game.cats[index] = game.cats[last_idx];
    game.cats.pop_back();
}

void check_power_up_position(game_data &game) // Checking the position of the power up and removing it if it goes out of the playing area
{
    for (int i = 0; i < game.power_ups.size(); i++)
    {
        double power_up_x = sprite_x(game.power_ups[i].power_up_sprite);
        double power_up_y = sprite_y(game.power_ups[i].power_up_sprite);

        // Removing the power up if it goes out of the playing area
        if ((power_up_y > MAX_GAME_RANGE) || (power_up_y < MIN_GAME_RANGE))
        {
            remove_power_up(game, i);
        }
        if ((power_up_x > MAX_GAME_RANGE) || (power_up_x < MIN_GAME_RANGE))
        {
            remove_power_up(game, i);
        }
    }
}

void check_planet_position(game_data &game) // Checking the position of the planet and removing it if it goes out of the playing area
{
    for (int i = 0; i < game.planets.size(); i++)
    {
        double planet_x = sprite_x(game.planets[i].planet_sprite);
        double planet_y = sprite_y(game.planets[i].planet_sprite);

        // Removing the planet if it goes out of the playing area
        if ((planet_y > MAX_GAME_RANGE) || (planet_y < MIN_GAME_RANGE))
        {
            remove_planet(game, i);
        }
        if ((planet_x > MAX_GAME_RANGE) || (planet_x < MIN_GAME_RANGE))
        {
            remove_planet(game, i);
        }
    }
}

void check_cat_position(game_data &game) // Checking the position of the cat and removing it if it goes out of the playing area
{
    for (int i = 0; i < game.cats.size(); i++)
    {
        double cat_x = sprite_x(game.cats[i].cat_sprite);
        double cat_y = sprite_y(game.cats[i].cat_sprite);

        // Removing the cat if it goes out of the playing area
        if ((cat_y > MAX_GAME_RANGE) || (cat_y < MIN_GAME_RANGE))
        {
            remove_cat(game, i);
        }
        if ((cat_x > MAX_GAME_RANGE) || (cat_x < MIN_GAME_RANGE))
        {
            remove_cat(game, i);
        }
    }
}

void draw_hud(const game_data &game) // Create the HUD display to show the users data information
{
    // starting information for the HUD, the box size, score and the player location
    fill_rectangle(rgba_color(251, 88, 149, 255), 0, 0, 1000, 145, option_to_screen());
    draw_text("PLAYER: " + to_string(game.player.spaceship_kind), COLOR_WHITE, 40, 10, option_to_screen());
    draw_text("SCORE: " + to_string(game.player.score), COLOR_WHITE, 470, 10, option_to_screen());
    draw_text("LOCATION: " + point_to_string(center_point(game.player.player_sprite)), COLOR_WHITE, 600, 10, option_to_screen());

    // fuel status bar and its location, the bar is filled with the percentage of fuel left
    draw_text("POWER: ", COLOR_WHITE, 40, 25, option_to_screen());
    draw_bitmap("empty_bar", 25, 30, option_part_bmp(0, 0, bitmap_width("empty_bar"), bitmap_height("empty_bar"), option_to_screen()));
    int pink_bar_width = bitmap_width("pink_bar") * game.player.fuel_pct; // the width of the pink bar is the percentage of fuel left
    if (pink_bar_width > bitmap_width("pink_bar"))                        // Prevents the bar from going over the maximum width
        pink_bar_width = bitmap_width("pink_bar");
    draw_bitmap("pink_bar", 25, 30, option_part_bmp(0, 0, pink_bar_width, bitmap_height("pink_bar"), option_to_screen()));

    // health status bar and its location, the bar is filled with the percentage of health left
    draw_text("HEALTH: ", COLOR_WHITE, 600, 25, option_to_screen());
    draw_bitmap("empty_bar", 580, 30, option_part_bmp(0, 0, bitmap_width("empty_bar"), bitmap_height("empty_bar"), option_to_screen()));
    int lilac_bar_width = bitmap_width("lilac_bar") * game.player.health_pct; // the width of the lilac bar is the percentage of health left
    if (lilac_bar_width > bitmap_width("lilac_bar"))                          // Prevents the bar from going over the maximum width
        lilac_bar_width = bitmap_width("lilac_bar");
    draw_bitmap("lilac_bar", 580, 30, option_part_bmp(0, 0, lilac_bar_width, bitmap_height("lilac_bar"), option_to_screen()));

    // timer status bar and its location, the bar is filled with the percentage of time left
    draw_text("TIMER: ", COLOR_WHITE, 40, 85, option_to_screen());
    draw_bitmap("empty_bar", 25, 90, option_part_bmp(0, 0, bitmap_width("empty_bar"), bitmap_height("empty_bar"), option_to_screen()));
    int purple_bar_width = bitmap_width("purple_bar") * game.player.timer_pct; // the width of the purple bar is the percentage of time left
    if (purple_bar_width > bitmap_width("purple_bar"))                         // Prevents the bar from going over the maximum width
        purple_bar_width = bitmap_width("purple_bar");
    draw_bitmap("purple_bar", 25, 90, option_part_bmp(0, 0, purple_bar_width, bitmap_height("purple_bar"), option_to_screen()));

    // shield status bar and its location, the bar is filled with the percentage of shield left
    draw_text("SHIELD: ", COLOR_WHITE, 600, 85, option_to_screen());
    draw_bitmap("empty_bar", 580, 90, option_part_bmp(0, 0, bitmap_width("empty_bar"), bitmap_height("empty_bar"), option_to_screen()));
    int rose_bar_width = bitmap_width("rose_bar") * game.player.shield_pct; // the width of the rose bar is the percentage of shield left
    if (rose_bar_width > bitmap_width("rose_bar"))                          // Prevents the bar from going over the maximum width
        rose_bar_width = bitmap_width("rose_bar");
    draw_bitmap("rose_bar", 580, 90, option_part_bmp(0, 0, rose_bar_width, bitmap_height("rose_bar"), option_to_screen()));

    // Draw coin icon, show coin count and its location
    draw_text("COINS:" + to_string(game.player.coins), COLOR_WHITE, 430, 25, option_to_screen());
    draw_bitmap("coin_small", 440, 35, option_to_screen());

    // Draw star icon, show star count and its location
    draw_text("STARS:" + to_string(game.player.stars), COLOR_WHITE, 510, 25, option_to_screen());
    draw_bitmap("star_small", 523, 34, option_to_screen());

    // Draw the cats to collect their score
    draw_text("CATS SAVED:" + to_string(game.player.cats), COLOR_WHITE, 455, 80, option_to_screen());
    draw_bitmap("cat_menu", 472, 98, option_to_screen());
};

void update_game(game_data &game) // Updating the game
{
    check_collisions(game); // Checking for collision and applying the power up

    update_player(game.player); // Perform movement and update the camera

    if (0.04 > rnd()) // Adding a power up to the game at the random rate of 4%
    {
        add_power_up(game);
    }

    if (0.01 > rnd()) // Adding a planet to the game at the random rate of 1%
    {
        add_planet(game);
    }

    if (0.02 > rnd()) // Adding a cat to the game at the random rate of 2%
    {
        add_cat(game);
    }

    for (int i = 0; i < game.power_ups.size(); i++) // Updating and looping through the power ups
    {
        check_power_up_position(game);
        update_power_up(game.power_ups[i]);
    }

    for (int i = 0; i < game.planets.size(); i++) // Updating and looping through the planets
    {
        check_planet_position(game);
        update_planet(game.planets[i]);
    }

    for (int i = 0; i < game.cats.size(); i++) // Updating and looping through the cats
    {
        check_cat_position(game);
        update_cat(game.cats[i]);
    }
}

void draw_game(const game_data &game) // Redraw the game screen to show the new game state
{
    bitmap background = load_bitmap("background", "background.png"); // Loading the background
    clear_screen(COLOR_BLACK);                                       // Redrawing everything
    draw_bitmap(background, 0, 0, option_to_screen());               // Drawing the background

    draw_player(game.player); // Draw in the player

    for (int i = 0; i < game.power_ups.size(); i++) // Drawing the power ups on the screen
    {
        draw_power_up(game.power_ups[i]);
    }

    for (int i = 0; i < game.planets.size(); i++) // Drawing the planets on the screen
    {
        draw_planet(game.planets[i]);
    }

    for (int i = 0; i < game.cats.size(); i++) // Drawing the cats on the screen
    {
        draw_cat(game.cats[i]);
    }

    draw_hud(game); // Displaying the HUD on the screen

    refresh_screen(60);
}
