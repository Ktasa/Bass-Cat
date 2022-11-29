#include "Engine.h"
#include <iostream>

void Engine::draw()
{
    //std::cout<<"Entering draw()" << endl;
	m_Window.clear(Color::Black);

    m_Window.setView(m_mainView);

    //CHARACTER CLASS BASED DRAWING [TESTING]
    //m_Window.draw(m_cat.getSprite());
    //Sprite catSprite = player1->getSprite();
    //m_Window.draw(catSprite);

    //BATTLE CLASS BASED DRAWING
    Sprite p1Sprite;
    p1Sprite = battle->getCharacterSprite(P1);
    m_Window.draw(p1Sprite);
    Sprite p2Sprite;
    p2Sprite = battle->getCharacterSprite(P2);
    m_Window.draw(p2Sprite);

    //depending on game state,
    //set views and draw objects to those views

    //draw HUD (a lot of our hud might be in Battle.h which manages the battle scene)
    //m_Window.setView(m_HudView);

    m_Window.display();
}