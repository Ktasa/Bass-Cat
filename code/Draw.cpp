#include "Engine.h"
#include <iostream>

void Engine::draw()
{
    //std::cout<<"Entering draw()" << endl;
	m_Window.clear(Color::Black);
    if(battle->getState() != INACTIVE)
    {
        m_Window.clear(battle->getBackground());
        //cout << "battle background active\n";
    }

    m_Window.setView(m_mainView);

    //BATTLE CLASS BASED DRAWING
    if(m_Playing)
    {
        //cout << "in draw if playing\n";
        Sprite magicP1 = battle->getEffectSprite(P1);
        Sprite magicP2 = battle->getEffectSprite(P2);
        m_Window.draw(magicP1);
        m_Window.draw(magicP2);

        Sprite p1Sprite;
        p1Sprite = battle->getCharacterSprite(P1);
        m_Window.draw(p1Sprite);
        Sprite p2Sprite;
        p2Sprite = battle->getCharacterSprite(P2);
        m_Window.draw(p2Sprite);

        vector<RectangleShape*> statusBarsP1 = battle->getStatusBars(P1);
        vector<RectangleShape*> statusBarsP2 = battle->getStatusBars(P2);
        m_Window.draw(*statusBarsP1[0]);
        m_Window.draw(*statusBarsP2[0]);
        m_Window.draw(*statusBarsP1[1]);
        m_Window.draw(*statusBarsP2[1]);
        
        //put into separate function? (not in battle class)
        if(rhythm->getIsActive())
        {
            //display red when recording
            RectangleShape* tester = rhythm->getTester();
            tester->setFillColor(Color::Red);
            m_Window.draw(*tester);
        }
        if(rhythm->getIsDone())
        {
            //display rhythm playback via flashing rectangle
            RectangleShape* tester = rhythm->getTester();
            m_Window.draw(*tester);
        }
        else if(!rhythm->getIsActive())
        {
            RectangleShape* tester = rhythm->getTester();
            tester->setFillColor(Color::Black);
            m_Window.draw(*tester);
        }

        if(battle->getState() == MENU)
        {
            Sprite combatMenuSprite = battle->getCombatMenuSprite();
            //m_Window.draw(combatMenuSprite);
        }

        if(rhythm->getIsDone())
        {
            //playback rhythm by flashing rectangle
            //RectangleShape* rhythmTest = rhythm->getTester();
            //m_Window.draw(*rhythmTest);
        }
    }
//cout << "exiting battle draw()\n";
    //
    //cout << "entering draw menu\n";
    if(menu->isActive())
    {
        menu->drawText(m_Window);
        //cout << "draw good \n";
    }

    //depending on game state,
    //set views and draw objects to those views

    //draw HUD (a lot of our hud might be in Battle.h which manages the battle scene)
    //m_Window.setView(m_HudView);

    m_Window.display();
}