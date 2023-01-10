#include "Engine.h"
#include "Character.h"
#include "Rhythm.h"
#include "Battle.h"
////////////////////////
Engine::Engine()
{
    Vector2f resolution;
	resolution.x = VideoMode::getDesktopMode().width;
	resolution.y = VideoMode::getDesktopMode().height;

    //set up battle manager
    battle = new Battle();

    menu = new Menu();

    m_Playing = false;

    m_Window.create(VideoMode(resolution.x, resolution.y),
        "Bass Cat", Style::Fullscreen);
    
    //m_Window.setFramerateLimit(30); //looks cleaner but less responsive animations

    m_mainView.reset(FloatRect(0, 0, 1920, 1080));
    //m_mainView.setSize(resolution);

    //get background texture from texture holder, set to m_BackgroundSprite
    string fileName = "graphics/nebula.png";
    m_backgroundSprite = new Sprite(TextureHolder::GetTexture(fileName));
    m_backgroundSprite->setPosition(Vector2f{0,0});
    Uint8 shade = 200;
    m_backgroundSprite->setColor(Color(shade,shade,shade));
}

void Engine::run()
{
    Clock clock;

    while(m_Window.isOpen())
    {  
        //Store game time as seconds to avoid loss of precision
        //only convert to ticks at the point of calculation

        Time dt = clock.restart();
        float dtAsSeconds = dt.asSeconds();

        if(m_Playing && battle->m_activeTime)
            battle->m_battleTime += dt;
        else
        {
            battle->m_activeTime = false;
            battle->m_battleTime = Time::Zero; //reset upon every recalibration
        }

        input();
        update(dtAsSeconds);
        draw();
    }
}