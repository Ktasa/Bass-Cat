#include "Engine.h"

void Engine::draw()
{
	m_Window.clear(Color::White);

    //depending on game state,
    //set views and draw objects to those views

    //draw HUD (a lot of our hud might be in Battle.h which manages the battle scene)
    //m_Window.setView(m_HudView);

    m_Window.display();
}