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
		/*
		//current elapsed time in midi ticks
		int battleTicks = int(m_battleTime.asSeconds() * TICKS_PER_SECOND);
		if(battle->getIsCalibrated())
		{
			//cout << "inside update getiscalibrated" << endl;
			//calculate current time in ticks, update rhythm
			m_battleTimeActive = true;
			rhythm1->update(battleTicks);
			rhythm2->update(battleTicks);
			//cout << "battle ticks " << battleTicks << endl;
		}
		*/

		if(battle->getState() == INACTIVE) //set battle options one time
		{
			battle->setChoices(menu->getChoices());
			//battle->setState(CALIBRATE);

			//rhythm1->activate(battleTicks, 1920);
			//rhythm2->activate(battleTicks, 1920);
		}
		

		//cout << "entering updates\n";
		//update battle objects
		battle->update(dtAsSeconds);
		//BattleState state = battle->getState();
		//cout << state << endl;
		//cout << "exiting updates\n";
	}// End if playing

    //update views, other objects depending on the game state


}