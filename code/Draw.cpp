#include "Engine.h"
#include <iostream>

void Engine::draw()
{
    displayBackground();

    m_Window.setView(m_mainView);

    if(battle->getState() == ENDSCREEN)
    {
        displayEndScreen();
    }
    else if(m_Playing)
    {
        displayEffects();
        displayCharacters();
        displayStatusBars();
        //displayRhythmTester();
        displayInterface();
    }

    if(menu->isActive())
    {
        menu->drawText(m_Window);
    }

    //depending on game state,
    //set views and draw objects to those views

    m_Window.display();
}

void Engine::displayBackground()
{
    m_Window.clear(Color::Black);
    if(battle->getState() != INACTIVE)
    {
        Display type = battle->getDisplay();
        if(type == GALAXY)
            m_Window.draw(*m_backgroundSprite);
        else
            m_Window.clear(battle->getBackground());
    }
}

void Engine::displayEffects()
{
    //not always displaying both effects
    if(battle->getIsEffectActive(P1, MAGIC))
    {
        Sprite* magicP1 = battle->getEffectSprite(P1);
        m_Window.draw(*magicP1);
    }
    if(battle->getIsEffectActive(P2, MAGIC))
    {
        Sprite* magicP2 = battle->getEffectSprite(P2);
        m_Window.draw(*magicP2);
    }
}

void Engine::displayCharacters()
{
    Sprite* p1Sprite;
    p1Sprite = battle->getCharacterSprite(P1);
    //Vector2f scale = p1Sprite->getScale();
    //p1Sprite->setScale(scale.x * 1.1, scale.y * 1.1);
    m_Window.draw(*p1Sprite);
    Sprite* p2Sprite;
    p2Sprite = battle->getCharacterSprite(P2);
    m_Window.draw(*p2Sprite);
}
void Engine::displayStatusBars()
{
    vector<RectangleShape*> statusBarsP1 = battle->getStatusBars(P1);
    vector<RectangleShape*> statusBarsP2 = battle->getStatusBars(P2);
    m_Window.draw(*statusBarsP1[0]);
    m_Window.draw(*statusBarsP2[0]);
    m_Window.draw(*statusBarsP1[1]);
    m_Window.draw(*statusBarsP2[1]);
}
void Engine::displayRhythmTester()
{
    if(battle->getIsInputActive() || battle->getIsInputDone())
    {
        //display red when recording
        RectangleShape* tester1 = battle->getRhythmTester(P1);
        RectangleShape* tester2 = battle->getRhythmTester(P2);

        Vector2f resolution;
        resolution.x = VideoMode::getDesktopMode().width;
        resolution.y = VideoMode::getDesktopMode().height;
        tester1->setPosition(resolution.x *float(0.28), resolution.y *float(0.3));
        tester2->setPosition(resolution.x *float(0.33), resolution.y *float(0.3));

        m_Window.draw(*tester1);
        m_Window.draw(*tester2);
    }
}
void Engine::displayInterface()
{
    if(battle->getState() == CALIBRATE)
    {
        Sprite* calibrationSprite = battle->getCalibrationSprite();
        m_Window.draw(*calibrationSprite);
    }
    else if(battle->getState() == MENU)
    {
        Sprite* combatMenuSprite = battle->getCombatMenuSprite();
        m_Window.draw(*combatMenuSprite);
    }
}
void Engine::displayEndScreen()
{
    //displayEffects();
    displayCharacters();
    Sprite* endscreen = battle->getEndScreenSprite();
    m_Window.draw(*endscreen);
    Sprite* victoryText = battle->getEndScreenText();
    m_Window.draw(*victoryText);
}