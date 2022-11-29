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
    FloatRect textRect = m_menuText.getLocalBounds();
    m_menuText.setOrigin(textRect.width / 2, textRect.height / 2);
}

void Menu::handleInput()
{
    //prevent extra values from being added
    if(m_current >= NUM_OPTIONS)
        m_validInput = false;
    if (Keyboard::isKeyPressed(Keyboard::Num1) && m_validInput)
    {
        m_choices.push_back(1);
        m_current++;
        //cout << "Num 1 entered" << endl;
    }
    else if (Keyboard::isKeyPressed(Keyboard::Num2) && m_validInput)
    {
        m_choices.push_back(2);
        m_current++;
        //cout << "num 2 entered" << endl;
    }
    if( !(Keyboard::isKeyPressed(Keyboard::Num1)) && !(Keyboard::isKeyPressed(Keyboard::Num1)))
    {m_validInput = true;}
    else
    {m_validInput = false;} //only allow new input for unique key presses
}
void Menu::update()
{
    if (m_current >= NUM_OPTIONS)
        m_isActive = false;
    string currentString;
    if(m_current < NUM_OPTIONS)
    {
        currentString = m_prompts.at(m_current);
        m_menuText.setString(currentString);
    }
}

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