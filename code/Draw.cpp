#include "Engine.h"
#include <iostream>

void Engine::draw()
{
    //std::cout<<"Entering draw()" << endl;
	m_Window.clear(Color::Black);
    if(battle->getState() != INACTIVE)
        m_Window.clear(battle->getBackground());

    m_Window.setView(m_mainView);

    //CHARACTER CLASS BASED DRAWING [TESTING]
    //Sprite catSprite = player1->getSprite();
    //m_Window.draw(catSprite);
//cout << "entering battle draw()\n";
    //BATTLE CLASS BASED DRAWING
    if(m_Playing)
    {
        Sprite p1Sprite;
        p1Sprite = battle->getCharacterSprite(P1);
        m_Window.draw(p1Sprite);
        Sprite p2Sprite;
        p2Sprite = battle->getCharacterSprite(P2);
        m_Window.draw(p2Sprite);
    }
//cout << "exiting battle draw()\n";
    //
    //cout << "entering draw\n";
    if(menu->isActive())
    {
        menu->drawText(m_Window);
        //cout << "draw good \n";
    }

    //depending on game state,
    //set views and draw objects to those views

    //draw HUD (a lot of our hud might be in Battle.h which manages the battle scene)
    //m_Window.setView(m_HudView);

    m_Window.display();
}