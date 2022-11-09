
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
	float scaleC = 0.75;
	//float scaleC = 1;
	spriteC.setScale(scaleC, scaleC);

	Music catMusic;
	catMusic.openFromFile("sound/Cowboy Spacecat Compressed.ogg");
	//catMusic.play();
    
	Clock clock;
	Time dt;
	float timeCount = 0.0;
	float update = 0.10; //4 frames per beat at 150bpm
	float updateTest = update - 0.005; //allow catching the update slightly early
	updateTest = update; //update will always be slightly late

	Clock testClock;
	Time testDT;
	int fps = 0;
	double tCount = 0.0;

	Sprite current;
	while (window.isOpen())
	{
		testClock.restart();
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			current = spriteC;
			window.clear(Color::White);
			window.draw(current);
			window.display();

			window.close();
		}
		if ( (Keyboard::isKeyPressed(Keyboard::Space)) 
			&& bassCat.getInputTimeOut()==0 && bassCat.getActionFrame() == 1)
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

		if(timeCount > update)
		{
			current = bassCat.getSprite();
			timeCount -= update;
			window.clear(Color::White);
			window.draw(current);
			window.display();
		}
		//fps++;
		testDT = testClock.restart();
		tCount += testDT.asSeconds();
		//cout << testDT.asSeconds() << endl;
		if(tCount < 3.0)
			fps++;
		if(tCount > 3.0 && tCount < 3.01)
			cout << fps/3.0 << endl;
		//my tests say this loop is running at over 6000 fps

		dt = clock.restart();
		timeCount += dt.asSeconds();
		/*
		if(timeCount > update)
			cout << timeCount << endl;
		*/

	}

	return 0;
}
