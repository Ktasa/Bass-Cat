#include <SFML/Graphics.hpp>
#include <sstream>
#include <vector>
#include "Menu.h"

Menu::Menu()
{
    m_current = 0;
    m_validInput = false;
    m_isActive = true;

    //set up prompts
    ostringstream p1Select;
    p1Select << "Player1 Character Select:" << endl
               << "1. Cat" << endl << "2. Dog" << endl;
    ostringstream p2Select;
    p2Select << "Player2 Character Select:" << endl
               << "1. Cat" << endl << "2. Dog" << endl;
    ostringstream displaySelect;
    displaySelect << "Select Display Mode: " << endl
                  << "1. Light" << endl << "2. Dark" << endl;

    m_prompts.push_back(p1Select.str());
    m_prompts.push_back(p2Select.str());
    m_prompts.push_back(displaySelect.str());
    //cout << "Testing vector" << endl;
    //cout << m_prompts[0] << endl;

    Font font;
    font.loadFromFile("fonts/DanmarkURWTDem.ttf");

    m_menuText.setCharacterSize(80);
    m_menuText.setFillColor(Color::White);
    m_menuText.setFont(font);
    m_menuText.setOutlineColor(Color::Black);
    m_menuText.setOutlineThickness(1);
    m_menuText.setString(p1Select.str());

    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    m_menuText.setPosition(resolution.x * float(0.5), resolution.y * float(0.5));
    m_textRect = m_menuText.getLocalBounds();
    m_menuText.setOrigin(m_textRect.width / 2, m_textRect.height / 2);
}

void Menu::handleMenuInput()
{
    if (Keyboard::isKeyPressed(Keyboard::Num1) && m_validInput)
    {
        m_choices.push_back(1);
        m_current++;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Num2) && m_validInput)
    {
        m_choices.push_back(2);
        m_current++;
    }
    if( !(Keyboard::isKeyPressed(Keyboard::Num1)) && !(Keyboard::isKeyPressed(Keyboard::Num1)))
    {m_validInput = true;}
    else
    {m_validInput = false;}
}
void Menu::update()
{
    //cout << "inside inner update\n";
    if (m_current == NUM_OPTIONS-1)
        m_isActive = false;
    string currentString;
    if(m_current < m_prompts.size())
    {
        currentString = m_prompts.at(m_current);
    //cout << "access vector success\n";
        m_menuText.setString(currentString);
    //cout << "exiting inner update\n";
    }
}

//better to do this with Text*?
void Menu::drawText(RenderWindow &window)
{
    Font menuFont;
    menuFont.loadFromFile("fonts/DanmarkURWTDem.ttf");
    m_menuText.setFont(menuFont);

    window.setView(window.getDefaultView()); //prevent view slicing errors
    window.draw(m_menuText);
}

bool Menu::isActive()
{
    return m_isActive;
}

vector<int> Menu::getChoices()
{
    return m_choices;
}

//////////