#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Character.h"

using namespace sf;

void Engine::update(float dtAsSeconds)
{
	//m_cat.updateCharacter(dtAsSeconds);
	cat_ptr->updateCharacter(dtAsSeconds);

    if (m_Playing)
	{
        /* //Example CH15
		// Update Thomas
		m_Thomas.update(dtAsSeconds);

		// Update Bob
		m_Bob.update(dtAsSeconds);

		// Count down the time the player has left
		m_TimeRemaining -= dtAsSeconds;

		// Have Thomas and Bob run out of time?
		if (m_TimeRemaining <= 0)
		{
			m_NewLevelRequired = true;
		}
        */
	}// End if playing

    //update views, other objects depending on the game state


}