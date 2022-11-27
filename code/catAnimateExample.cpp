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

    Texture nebulaTexture;
    nebulaTexture.loadFromFile("graphics/nebula 800.png");
    Sprite nebulaSprite;
    nebulaSprite.setTexture(nebulaTexture);
    nebulaSprite.setScale(2,2);
    nebulaSprite.setPosition(-200,0);
    nebulaSprite.setOrigin(0,0);

    Texture characterTexture;
    characterTexture.loadFromFile("graphics/cat.png");

    //VertexArray Character;
    //Character.setPrimitiveType(Quads);
    //Character.resize(4);

    const int CHARACTER_SHEET_WIDTH = 1000;
    const float FRAME_TIME_S = 0.2f;

    Vector2f player1Position = {resolution.x * float(0.1), resolution.y * float(0.8)};
    Vector2f player2Position = {resolution.x * float(0.6), resolution.y * float(0.8)};

    Sprite characterSprite;
    characterSprite.setTexture(characterTexture);
    float catScaleXY = resolution.y / 1500;
    Vector2f catScale = {catScaleXY,catScaleXY};
    characterSprite.setScale(catScale);
    //characterSprite.setScale(Vector2f{-1,1}); //make 1st argument negative to flip horizontal
    characterSprite.setOrigin(CHARACTER_SHEET_WIDTH/2,CHARACTER_SHEET_WIDTH/2);
    characterSprite.setPosition(player1Position);
    characterSprite.setColor(Color::White); //set color works with white sprites

    Texture auraTexture;
    auraTexture.loadFromFile("graphics/Aura.png");

    const int AURA_SHEET_WIDTH = 600;
    float auraScale = resolution.y / 700;
    float auraFlip = auraScale * 1.0;
    Sprite auraSprite;
    auraSprite.setTexture(auraTexture);
    auraSprite.setScale(Vector2f{auraFlip,auraScale});
    auraSprite.setPosition(player1Position);
    auraSprite.setColor(Color(0,100,255));
    auraSprite.setOrigin(AURA_SHEET_WIDTH/2,AURA_SHEET_WIDTH*float(0.6));

    Sprite c2Sprite;
    c2Sprite.setTexture(characterTexture);
    Vector2f c2Scale = {-catScaleXY,catScaleXY};
    c2Sprite.setScale(c2Scale);
    c2Sprite.setOrigin(CHARACTER_SHEET_WIDTH/2,CHARACTER_SHEET_WIDTH/2);
    c2Sprite.setPosition(player2Position);
    c2Sprite.setColor(Color::White);
    
    Sprite a2Sprite;
    a2Sprite.setTexture(auraTexture);
    a2Sprite.setScale(Vector2f{auraFlip,auraScale});
    a2Sprite.setPosition(player2Position);
    a2Sprite.setColor(Color(255,0,100));
    a2Sprite.setOrigin(AURA_SHEET_WIDTH/2,AURA_SHEET_WIDTH*float(0.6));


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
            auraFlip *= -1;
            auraSprite.setScale(auraFlip,auraScale);
            a2Sprite.setScale(auraFlip, auraScale);
        }

        // Set the texture coordinates of each vertex
        int frameOffset = CHARACTER_SHEET_WIDTH * characterFrame;

        //Character[0].texCoords = Vector2f(0 + frameOffset, 0);
        //Character[1].texCoords = Vector2f(CHARACTER_SHEET_WIDTH + frameOffset, 0);
        //Character[2].texCoords = Vector2f(CHARACTER_SHEET_WIDTH + frameOffset, CHARACTER_SHEET_WIDTH);
        //Character[3].texCoords = Vector2f(0 + frameOffset, CHARACTER_SHEET_WIDTH);

        IntRect rect(0 + frameOffset, 0, CHARACTER_SHEET_WIDTH, CHARACTER_SHEET_WIDTH);
        characterSprite.setTextureRect(rect);
        c2Sprite.setTextureRect(rect);

        window.clear(Color::Black);
        //window.draw(nebulaSprite);
        //window.draw(Character, &characterTexture);
        window.draw(auraSprite);
        window.draw(a2Sprite);
        window.draw(characterSprite);
        window.draw(c2Sprite);
        window.display();
    }
}
