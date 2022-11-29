#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

//Would the start menu work better as a function?
class Menu
{
public:
    Menu();
    Text& getText();

private:
    Text text;
    vector<int> input;

};

//Menu options necessary to start the game
//1. pick light or dark mode
//2. each player picks a character
//


#endif