#include "Engine.h"
//#include "Character.h"
#include "Rhythm.h"
////////////////////////
Engine::Engine()
{
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    //set up battle manager
    battle = new Battle();

    menu = new Menu();

    rhythm = new Rhythm();
    //cout << "rhythm constructor success" << endl;
    //midiTime = 0;


    m_Playing = false;

    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Bass Cat", Style::Default);
    
    //m_Window.setFramerateLimit(30);
    //not sure whether to use Fullscreen or Default

    m_mainView.setSize(resolution);
    //set up HudView

    //get background texture from texture holder, set to m_BackgroundSprite
}

void Engine::run()
{
    Clock clock;
    cout << "in run" << endl;
    while(m_Window.isOpen())
    {  
        Time dt = clock.restart();
        m_GameTimeTotal += dt;
        float dtAsSeconds = dt.asSeconds();

        input();
        cout << "input done" << endl;
        update(dtAsSeconds);
        cout << "update done" << endl;
        draw();
        cout << "draw done" << endl;
    }
}