
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "cat.h"

using namespace sf;
using namespace std;

int main()
{
	int resolutionWidth = VideoMode::getDesktopMode().width;
    int resolutionHeight = VideoMode::getDesktopMode().height;
    //double aspectRatio = resolutionHeight * 1.0 / resolutionWidth;

    VideoMode vm(resolutionWidth, resolutionHeight);

	RenderWindow window(vm, "Bass Cat", Style::Default);

	cat bassCat("gumi");

	Texture textureC;
	textureC.loadFromFile("frames/gumi C.png");
	Sprite spriteC;
	spriteC.setTexture(textureC);
	spriteC.setPosition(0, 0);
	//float scaleC = 0.75;
	float scaleC = 1;
	spriteC.setScale(scaleC, scaleC);

	SoundBuffer bassBuffer;
	bassBuffer.loadFromFile("sound/bass sfx v2.wav");
	Sound bass;
	bass.setBuffer(bassBuffer);

	Music catMusic;
	catMusic.openFromFile("sound/Cowboy Spacecat Compressed.ogg");
	catMusic.play();

	bool F1 = true;
	bool hitThatBass = false;
	int inputTimeOut = 0;
	int hitFrame = 1;
	Sprite current;
	int frameID = 1;
	bool boost = false;

    Clock clock;
    Time dt;
    float timeCount = 0.0;
    float update = 0.10; //4 frames per beat at 150bpm
	float updateTest = update - 0.005; //allow catching the update slightly early
	updateTest = update; //update will always be slightly late

	Clock test;
	Time dtTest;
	
	/*
	while (window.isOpen())
	{

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			current = spriteC;
			window.clear(Color::White);
			window.draw(current);
			window.display();

			window.close();
		}
		if ( (Keyboard::isKeyPressed(Keyboard::Space)) && inputTimeOut==0 && hitFrame == 1)
		{
			hitThatBass = true;
			clock.restart(); //reset timing of animation
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			//inputTimeOut = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			boost = true;
		}
		if (!Keyboard::isKeyPressed(Keyboard::LShift))
		{
			boost = false;
		}
		if (timeCount > update && !hitThatBass)
		{
			F1 = !F1;
			if (F1)
				frameID = 1;
			else
				frameID = 2;

			timeCount -= update;
            if(inputTimeOut > 0){inputTimeOut--;}
		}
		if(hitThatBass && inputTimeOut==0 && timeCount > updateTest && !boost)
		{
            F1 = !F1;
			if (F1)
				frameID = 3;
			else
				frameID = 4;

			if (hitFrame == 1)
            {
                if(bass.getStatus() == bass.Playing)
                    bass.stop();
            	bass.play();
                
                hitFrame++;
            }
            else
            {
				inputTimeOut = 2;
				hitThatBass = false;
				hitFrame = 1;
			}
			timeCount -= update;
		}
		if(hitThatBass && boost && timeCount > updateTest)
		{
			F1 = !F1;
			if(F1)
				frameID = 1;
			else
				frameID = 4;

			timeCount -= update;
		}
		*/
	while (window.isOpen())
	{

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			current = spriteC;
			window.clear(Color::White);
			window.draw(current);
			window.display();

			window.close();
		}
		if ( (Keyboard::isKeyPressed(Keyboard::Space)) && inputTimeOut==0 && hitFrame == 1)
		{
			bassCat.hitThatBass();
			clock.restart(); //reset timing of animation
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			//inputTimeOut = 0;
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			bassCat.setBoost(true);
		}
		if (!Keyboard::isKeyPressed(Keyboard::LShift))
		{
			bassCat.setBoost(false);
		}

		//Sprite *ptr = bassCat.getSprite(frameID);
		if(timeCount > update)
		{
			current = bassCat.getSprite(frameID);
		}
		window.clear(Color::White);
		window.draw(current);
		window.display();

        dt = clock.restart();
        timeCount += dt.asSeconds();
        //if(timeCount > update)
        //{
            //cout << timeCount << endl;
        //}
        
	}

	return 0;
}
