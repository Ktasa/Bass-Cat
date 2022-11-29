#include "Engine.h"
//
void Engine::input()
{
    Event event;
    while(m_Window.pollEvent(event))
    {
        //dont put events here that need to track key releases
        if (event.type == Event::KeyPressed)
        {
            // Quit game
            if (Keyboard::isKeyPressed(Keyboard::Escape))
            {
                m_Window.close();
            }
            //start game / unpause
            if (Keyboard::isKeyPressed(Keyboard::Return))
			{
				m_Playing = true;
			}
        }
        if(event.type == Event::Closed)
        {
            m_Window.close();
        }
        
        if(menu->isActive())
            menu->handleInput();
        else
            battle->handleInput();
    }
}