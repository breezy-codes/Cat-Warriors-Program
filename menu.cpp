#include "splashkit.h"
#include "cat_warriors.h"

bool menu_select(game_data &game) // Handle the user input in the menu
{
    if (key_down(RETURN_KEY)) // Enter key starts a new game
    {
        game = new_game();
        return false;
    }
    else
        return true;
}

void menu_screen(const game_data &game) // Display the menu screen
{
    clear_screen(COLOR_BLACK);
    draw_bitmap("menu", 0, 0, option_to_screen());
    refresh_screen(60);
}

void game_over_screen(const game_data &game) // Display the game over screen if the players fuel or health runs out
{
    clear_screen(COLOR_BLACK);
    draw_bitmap("game_over", 0, 0, option_to_screen());
    refresh_screen(60);
}

/*
In this function create 3 pages depending on total score,
each screen will display depending on how well the player did
*/
void game_finished(const game_data &game)
{
    clear_screen(COLOR_BLACK);
    if (game.player.score >= 1000)
        draw_bitmap("first_place", 0, 0, option_to_screen());
    else if (game.player.score >= 500)
        draw_bitmap("second_place", 0, 0, option_to_screen());
    else if (game.player.score >= 250)
        draw_bitmap("third_place", 0, 0, option_to_screen());
    refresh_screen(60);
}
