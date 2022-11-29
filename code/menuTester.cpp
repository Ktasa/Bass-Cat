#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include "Battle.h"

using namespace sf;
using namespace std;

void menuTest()
{

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y),
        "MenuTester", Style::Default);

    View mainView;
    mainView.setSize(resolution);
    //window.setView(mainView);

    sf::Clock clock;

    //Player 1 text
    ostringstream p1Select;
    p1Select << "Player1 Character Select:" << endl
               << "1. Cat" << endl << "2. Dog" << endl;
    //display these at the same time with separate inputs?
    ostringstream p2Select;
    p2Select << "Player2 Character Select:" << endl
               << "1. Cat" << endl << "2. Dog" << endl;

    ostringstream displaySelect;
    displaySelect << "Select Display Mode: " << endl
                  << "1. Light" << endl << "2. Dark" << endl;

    Font font;
    font.loadFromFile("fonts/DanmarkURWTDem.ttf");

    Text menuText;

    menuText.setCharacterSize(80);
    menuText.setFillColor(Color::White);
    menuText.setFont(font);
    menuText.setOutlineColor(Color::Black);
    menuText.setOutlineThickness(1);

    menuText.setString(p1Select.str());

    menuText.setPosition(resolution.x * float(0.5), resolution.y * float(0.5));
    FloatRect textRect = menuText.getLocalBounds();
    menuText.setOrigin(textRect.width / 2, textRect.height / 2);
    //menuText.setOrigin(textRect.left,textRect.top);


    

    Time dt;

    bool done = false;

    int choices[3] = {0,0,0};

    bool validInput = false;

    int currChoice = 0;
    while (window.isOpen() && !done)
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (Keyboard::isKeyPressed(Keyboard::Num1) && validInput)
            {
                choices[currChoice] = 1;
                currChoice++;
            }
            else if (Keyboard::isKeyPressed(Keyboard::Num2) && validInput)
            {
                choices[currChoice] = 2;
            }
            if( !(Keyboard::isKeyPressed(Keyboard::Num1)) && !Keyboard::isKeyPressed(Keyboard::Num1))
            {validInput = true;}
            else
            {validInput = false;}
        }

        //dt = clock.restart();
        //character_animate_time += dt;

        string current;
        if(choices[0]==0)
        {current = p1Select.str();}
        else if(choices[1]==0)
        {current = p2Select.str();}
        else if(choices[2]==0)
        {current = displaySelect.str();}
        else
        {done = true;}

        menuText.setString(current);

        window.clear(Color::Black);
        window.draw(menuText);
        window.display();
    }
}