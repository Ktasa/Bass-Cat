//EXAMPLE PROGRAM FOR ANIMATING SPRITE SHEETS

#include <iostream>
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

int main()
{
    // Get the screen resolution and create an SFML window
    Vector2f resolution;
    resolution.x = VideoMode::getDesktopMode().width;
    resolution.y = VideoMode::getDesktopMode().height;

    RenderWindow window(VideoMode(resolution.x, resolution.y),
        "Animate Cat", Style::Default);

    View mainView;
    mainView.setSize(resolution);
    window.setView(mainView);

    sf::Clock clock;

    Texture characterTexture;
    characterTexture.loadFromFile("graphics/spritesheet cat B.png");

    VertexArray Character;
    Character.setPrimitiveType(Quads);
    Character.resize(4);

    Sprite characterSprite;
    characterSprite.setTexture(characterTexture);
    characterSprite.setScale(Vector2f{0.5,0.5});
    characterSprite.setPosition(Vector2f(0,200));

    const int CHARACTER_SHEET_WIDTH = 1000;
    const float FRAME_TIME_S = 0.2f;

    //Vector2f characterPosition = {0,0};

    //Character[0].position = characterPosition + Vector2f(0, 0);
    //Character[1].position = characterPosition + Vector2f(CHARACTER_SHEET_WIDTH, 0);
    //Character[2].position = characterPosition + Vector2f(CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
    //Character[3].position = characterPosition + Vector2f(0, CHARACTER_SHEET_WIDTH);

    Time character_animate_time;
    int characterFrame = 0;

    Time dt;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        dt = clock.restart();
        character_animate_time += dt;

        if (character_animate_time >= seconds(FRAME_TIME_S))
        {
            characterFrame++;
            characterFrame %= 4;
            //std::cout << "Frame: " << characterFrame << endl;
            character_animate_time = Time::Zero;
        }

        // Set the texture coordinates of each vertex
        int frameOffset = CHARACTER_SHEET_WIDTH * characterFrame;

        //Character[0].texCoords = Vector2f(0 + frameOffset, 0);
        //Character[1].texCoords = Vector2f(CHARACTER_SHEET_WIDTH + frameOffset, 0);
        //Character[2].texCoords = Vector2f(CHARACTER_SHEET_WIDTH + frameOffset, CHARACTER_SHEET_WIDTH);
        //Character[3].texCoords = Vector2f(0 + frameOffset, CHARACTER_SHEET_WIDTH);

        IntRect rect(0 + frameOffset, 0, CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
        characterSprite.setTextureRect(rect);

        window.clear(Color::White);
        //window.draw(Character, &characterTexture);
        window.draw(characterSprite);
        window.display();
    }
}
