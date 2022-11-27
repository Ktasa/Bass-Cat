//This will be the final main file

#include "Engine.h"
#include "Character.h"

int main()
{
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y),
        "Animate Cat", Style::Default);

    sf::Clock clock;
    Time dt;

    Character cat(CAT, Color::White, LEFT, 150);
    Vector2f player1Position = {resolution.x * float(0.1), resolution.y * float(0.8)};
    cat.setPosition(Vector2f(300,300));

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        dt = clock.restart();
        cat.updateCharacter(dt.asSeconds());

        window.clear(Color::Black);
        window.draw(cat.getSprite());
        window.display();
    }

    //Engine engine;

    //engine.run();

    return 0;
}
