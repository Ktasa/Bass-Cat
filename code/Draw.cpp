#include "Engine.h"
#include <iostream>

void Engine::draw()
{
    //std::cout<<"Entering draw()" << endl;
	m_Window.clear(Color::Black);

    m_Window.setView(m_mainView);
    //m_Window.draw(m_cat.getSprite());
    Sprite catSprite = player1->getSprite();
    m_Window.draw(catSprite);

    //depending on game state,
    //set views and draw objects to those views

    //draw HUD (a lot of our hud might be in Battle.h which manages the battle scene)
    //m_Window.setView(m_HudView);

    m_Window.display();
}