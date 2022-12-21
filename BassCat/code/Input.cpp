#include "Engine.h"
//
void Engine::input()
{
    //cout << "in input" << endl;
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
        //NOTE: change to test activity inside the handler
        //cout << "entering menu is active" << endl;
        if(menu->isActive())
            menu->handleInput();
        else
        {
            //cout << "entering handle input" << endl;
            battle->handleInput();
            //rhythm1->handleInput(); //record user input 
            //rhythm2->handleInput();
        }
    }
}