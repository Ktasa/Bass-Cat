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
    //m_midiTime = 0;
    m_battleTime = Time::Zero;
    m_battleTimeActive = false;


    m_Playing = false;

    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Bass Cat", Style::Default);
    //not sure whether to use Fullscreen or Default
    
    //m_Window.setFramerateLimit(30); //looks cleaner but less responsive animations

    m_mainView.setSize(resolution);
    //set up HudView

    //get background texture from texture holder, set to m_BackgroundSprite
    string fileName = "graphics/nebula.png";
    m_backgroundSprite = new Sprite(TextureHolder::GetTexture(fileName));
    m_backgroundSprite->setPosition(Vector2f{0,0});

}

void Engine::run()
{
    Clock clock;

    while(m_Window.isOpen())
    {  
        //Store game time as seconds to avoid loss of precision
        //only convert to ticks at the point of calculation

        Time dt = clock.restart();
        m_GameTimeTotal += dt;
        float dtAsSeconds = dt.asSeconds();

        if(m_Playing && m_battleTimeActive)
            m_battleTime += dt;
        else
        {
            m_battleTimeActive = false;
            m_battleTime = Time::Zero; //reset upon every recalibration
        }
        /*
        double dtAsTicksDouble = dt.asSeconds() * TICKS_PER_SECOND;
        int dtAsTicks = int(dtAsTicksDouble);
        if(m_GameTimeTotal < seconds(5))
        {
            cout << "dt seconds: " << dtAsSeconds << endl;
            cout << "dt ticks double: " << dtAsTicksDouble << endl;
            cout << "dt ticks int: " << dtAsTicks << endl;
        }
        */

        input();
        //cout << "input done" << endl;
        update(dtAsSeconds);
        //cout << "update done" << endl;
        draw();
        //cout << "draw done" << endl;
    }
}