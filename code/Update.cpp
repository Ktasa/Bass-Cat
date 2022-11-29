#include "Engine.h"
#include <SFML/Graphics.hpp>
#include "Character.h"
#include <iostream>

using namespace sf;
using namespace std;

void Engine::update(float dtAsSeconds)
{
	
	//cout << "before update\n";
	if(menu->isActive())
		menu->update();
	else
		m_Playing = true;
	//cout << "update good\n";

    if (m_Playing)
	{
		//cout << "entering updates\n";
		//m_cat.updateCharacter(dtAsSeconds);
		//player1->updateCharacter(dtAsSeconds);
		battle->update(dtAsSeconds);
		//cout << "exiting character updates\n";
	}// End if playing

    //update views, other objects depending on the game state


}