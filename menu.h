#ifndef MENU
#define MENU

#include "splashkit.h"
#include "cat_warriors.h"

#include <vector>
using std::vector;
using namespace std;

void menu_screen(const game_data &game); // Loads the resources for the game to display the welcome menu

bool menu_select(game_data &game); // Handle the user input in the menu

void game_over_screen(const game_data &game); // Display the game over screen if the players fuel or health runs out

void game_finished(const game_data &game); // Display the game finished screen if the player wins the game

#endif
