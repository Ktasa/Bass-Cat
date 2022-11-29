#include "Engine.h"
#include "Character.h"

Engine::Engine()
{
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    //set up new battle() instead of character here
    player1 = new Character(P1, CAT, Color::White, 150);
    //player2 = new Character(P2, CAT, Color::White, 150);  
    Vector2f player1Position = {resolution.x * float(0.1), resolution.y * float(0.8)};
    player1->setPosition(player1Position);
    
    //size of cat proportional to resolution
    float defaultSize = CHARACTER_SHEET_WIDTH / resolution.y;
    float goalSize = 0.50;
    float adjustScale = goalSize / defaultSize;
    //std::cout << "scale: " << catScaleXY << endl;
    Vector2f catScale = {adjustScale,adjustScale};
    player1->setScale(catScale);

    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Bass Cat", Style::Default);
    //not sure whether to use Fullscreen or Default

    m_mainView.setSize(resolution);
    //set up HudView

    //get background texture from texture holder, set to m_BackgroundSprite
}

void Engine::run()
{
    Clock clock;

    while(m_Window.isOpen())
    {  
        Time dt = clock.restart();
        m_GameTimeTotal += dt;
        float dtAsSeconds = dt.asSeconds();

        input();
        update(dtAsSeconds);
        draw();
    }
}