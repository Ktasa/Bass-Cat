#include "Engine.h"

void Engine::input()
{
    Event event;
    while(m_Window.pollEvent(event))
    {
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

    }
    //Example from CH15
    //Not sure why this works outside the while loop?
    /*
    //Handle input specific to Thomas
	if (m_Thomas.handleInput())
	{
		// Play a jump sound
	}
    */
}