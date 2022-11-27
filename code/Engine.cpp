#include "Engine.h"
#include "Character.h"

Engine::Engine()
{
    //Character m_cat(CAT, Color::Black, LEFT, 150);

    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Bass Cat", Style::Default);
    //not sure whether to use Fullscreen or Default

    View m_mainView;
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