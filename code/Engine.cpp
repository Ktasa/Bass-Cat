#include "Engine.h"
#include "Character.h"

Engine::Engine()
{
    std::cout << "Entering engine constructor" << endl;

    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    cat_ptr = new Character(CAT, Color::White, LEFT, 150);
    Vector2f player1Position = {resolution.x * float(0.1), resolution.y * float(0.8)};
    cat_ptr->setPosition(player1Position);
    
    //size of cat proportional to resolution
    float defaultSize = CHARACTER_SHEET_WIDTH / resolution.y;
    float goalSize = 0.50;
    float adjustScale = goalSize / defaultSize;
    //std::cout << "scale: " << catScaleXY << endl;
    Vector2f catScale = {adjustScale,adjustScale};
    cat_ptr->setScale(catScale);

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