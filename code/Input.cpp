#include "Engine.h"

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

        //player1->handleInput(); //character class based input
        battle->handleInput();

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