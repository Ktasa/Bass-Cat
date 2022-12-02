#include "Engine.h"
//#include "Character.h"
//////////////
Engine::Engine()
{
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    //set up battle manager
    //battle = new Battle(DARK, CAT, CAT, "fileName.wav");
    battle = new Battle();

    menu = new Menu();

    //noteTest = new Tapper(480);
    //vector<Note*> NV;
    //NV.push_back(noteTest);


    m_Playing = false;

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