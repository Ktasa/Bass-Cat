//EXAMPLE PROGRAM FOR ANIMATING SPRITE SHEETS
/*
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
        "Animate Face", Style::Default);

    sf::Clock clock;

    Texture faceTexture;
    faceTexture.loadFromFile("Talking.png");

    VertexArray talkingFace;
    talkingFace.setPrimitiveType(Quads);
    talkingFace.resize(4);

    const int FACE_SHEET_WIDTH = 200;
    const float FRAME_TIME_S = 0.2f;

    Vector2f facePosition = { resolution.x / 2, resolution.y / 2 };

    talkingFace[0].position = facePosition + Vector2f(0, 0);
    talkingFace[1].position = facePosition + Vector2f(FACE_SHEET_WIDTH, 0);
    talkingFace[2].position = facePosition + Vector2f(FACE_SHEET_WIDTH, FACE_SHEET_WIDTH);
    talkingFace[3].position = facePosition + Vector2f(0, FACE_SHEET_WIDTH);

    Time face_animate_time;
    int faceFrame = 0;

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
        face_animate_time += dt;

        if (face_animate_time >= seconds(FRAME_TIME_S))
        {
            faceFrame++;
            faceFrame %= 4;
            face_animate_time = Time::Zero;
        }

        // Set the texture coordinates of each vertex
        int frameOffset = FACE_SHEET_WIDTH * faceFrame;

        talkingFace[0].texCoords = Vector2f(0, 0 + frameOffset);
        talkingFace[1].texCoords = Vector2f(FACE_SHEET_WIDTH, 0 + frameOffset);
        talkingFace[2].texCoords = Vector2f(FACE_SHEET_WIDTH, FACE_SHEET_WIDTH + frameOffset);
        talkingFace[3].texCoords = Vector2f(0, FACE_SHEET_WIDTH + frameOffset);

        window.clear(Color::Magenta);
        window.draw(talkingFace, &faceTexture);
        window.display();
    }
}
*/