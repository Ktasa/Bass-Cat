
//last prototype version
/*
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include "cat.h"
#include "rhythm.h"

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
	textureC.loadFromFile("graphics/gumi C.png");
	Sprite spriteC;
	spriteC.setTexture(textureC);
	spriteC.setPosition(0, 0);
	float scaleC = 0.75;
	//float scaleC = 1;
	spriteC.setScale(scaleC, scaleC);

	Music catMusic;
	catMusic.openFromFile("sound/Cowboy Spacecat Compressed.ogg");
	//catMusic.play();
    //
	Clock clock;
	Time dt;
	//float timeCount = 0.0;
	//float update = 0.10; //4 frames per beat at 150bpm
	//float updateTest = update - 0.005; //allow catching the update slightly early
	//updateTest = update; //update will always be slightly late

	Int64 timeCount = 0;
	Int64 update = 100 * 1000; //microseconds = 0.1s
	Int64 updateTest = update - 5000; 
	updateTest = update; 

	//Clock testClock;
	//Time testDT;
	//int fps = 0;
	//double tCount = 0.0;

	//testClock.restart();
	Sprite current;
	//current = bassCat.getSprite();

	rhythm userInput;
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
		if ( (Keyboard::isKeyPressed(Keyboard::Space)) 
			&& bassCat.getInputTimeOut()==0 && bassCat.getActionFrame() == 1)
		{
			if(userInput.getValidInput() == true)
			{
				userInput.count();
				userInput.setValidInput(false);
			}
			
			bassCat.hitThatBass();
			clock.restart(); //reset timing of animation
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			//inputTimeOut = 0;
			userInput.setValidInput(false);
			userInput.count();
			userInput.setValidInput(true);
		}
		if (Keyboard::isKeyPressed(Keyboard::LShift))
		{
			bassCat.setBoost(true);
		}
		if (!Keyboard::isKeyPressed(Keyboard::LShift))
		{
			bassCat.setBoost(false);
		}

		if(timeCount > updateTest)
		{
			current = bassCat.getSprite(); //this system runs at 6000fps on linux VM
			timeCount -= update;
			window.clear(Color::White);
			window.draw(current);
			window.display();
		}

		 //test fps
		
		//window.clear(Color::White); //260 fps without this
		//window.draw(current); //1130 fps without this - 900 fps faster
		//window.display();

		//testDT = testClock.restart();
		//tCount += testDT.asSeconds();

		//if(tCount < 10.0)
		//	fps++;
		//if(tCount > 10.0 && tCount < 10.01)
		//	cout << fps/10.0 << endl;
		

		dt = clock.restart();
		//timeCount += dt.asSeconds();

		timeCount+= dt.asMicroseconds();
		//cout << dt.asMicroseconds() << endl;
		//if(timeCount > update)
		//	cout << timeCount << endl;
		

	}

	return 0;
}

*/