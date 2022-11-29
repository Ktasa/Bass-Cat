#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>

using namespace sf;
using namespace std;

const int NUM_OPTIONS = 3;

class Menu
{
public:
    Menu();
    void handleInput(); //use in input()
    void update(); //use in update()
    void drawText(RenderWindow &window); //use in draw()
    bool isActive();
    vector<int> getChoices();

private:
    Text m_menuText;
    vector<string> m_prompts;
    //vector<int> m_choices[NUM_OPTIONS]; //store user input
    vector<int> m_choices;
    int m_current;
    bool m_validInput; //only allow input from unique key presses
    bool m_isActive; //is the menu active or done
};

//Menu options necessary to start the game
//1. pick light or dark mode
//2. each player picks a character


#endif