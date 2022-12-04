#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <iostream>

using namespace sf;
using namespace std;

void Engine::update(float dtAsSeconds)
{
	
	//cout << "before update\n";
	//cout << boolalpha << menu->isActive() << m_Playing << endl;
	if(menu->isActive())
		menu->update();
	else
		m_Playing = true;

    if (m_Playing)
	{
		//current elapsed ticks in battle
		int battleTicks = int(m_battleTime.asSeconds() * TICKS_PER_SECOND);
		//cout << "battle as seconds: " << m_battleTime.asSeconds() << endl;
		//cout << "battle ticks: " << battleTicks << endl;
		rhythm->update(battleTicks);

		if(battle->getState() == INACTIVE) //set battle options one time
		{
			battle->setChoices(menu->getChoices());
			//battle->setState(CALIBRATE);

			//rhythm->activate(P1, battleTicks, 1920);
		}
		

		//cout << "entering updates\n";
		//currently updates characters, CombatMenu
		battle->update(dtAsSeconds);
		//cout << "exiting updates\n";
	}// End if playing

    //update views, other objects depending on the game state


}