#include "splashkit.h"
#include "player.h"
#include "power_up.h"
#include "cat_warriors.h"
#include "planets.h"
#include "cats.h"
#include "menu.h"

void load_resources() // loads the resources for the game
{
    load_resource_bundle("game_bundle", "lost_in_space.txt");
}

int main()
{

    open_window("Cat Warriors", 1000, 1200); // Create the window and load the resources
    load_resources();

    game_data my_game;    // the game data
    my_game = new_game(); // the new game

    /*
    This loop starts the game on the menu screen, it allows the user to press enter to then start the game
    once in the game, the player will either fail or win the game.
    If they fail, they get the game over screen and can press enter to restart the game
    If they win, they get the game finished screen showing their position for winning the game
    */
    while (not quit_requested())
    {
        process_events(); // Handle input to adjust player movement

        if (my_game.menu) // The menu is displayed when the game is first started
        {
            menu_screen(my_game);                // Display the menu screen
            my_game.menu = menu_select(my_game); // The game starts when the user presses enter
        }
        else // game
        {
            handle_input(my_game.player); // Handle the input the user enter and adjust players movement
            update_game(my_game);         // update the game with the player and the power up
            draw_game(my_game);           // draw the game

            // The game arrives at a game over screen if the players fuel or health runs out
            if (my_game.player.fuel_pct <= 0 or my_game.player.health_pct <= 0)
            {
                game_over_screen(my_game); // The game restarts when the user presses enter

                while (menu_select(my_game)) // handles user input to restart the game
                {
                    process_events();
                }
            }
            else if (my_game.player.timer_pct <= 0) // player wins if they run out of time
            {
                game_finished(my_game); // displays the winner screen
            }
        }
    }
    return 0;
}
