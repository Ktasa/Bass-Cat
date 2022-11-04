#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace sf;
using namespace std;

int main()
{
	int resolutionWidth = VideoMode::getDesktopMode().width;
    int resolutionHeight = VideoMode::getDesktopMode().height;
    //double aspectRatio = resolutionHeight * 1.0 / resolutionWidth;

    VideoMode vm(resolutionWidth, resolutionHeight);

	RenderWindow window(vm, "Bass Cat", Style::Default);

	Texture textureA1;
	textureA1.loadFromFile("frames/gumi A1.png");
	Sprite spriteA1;
	spriteA1.setTexture(textureA1);
	spriteA1.setPosition(0, 0);

	Texture textureA2;
	textureA2.loadFromFile("frames/gumi A2.png");
	Sprite spriteA2;
	spriteA2.setTexture(textureA2);
	spriteA2.setPosition(0, 0);

	Texture textureA3;
	textureA3.loadFromFile("frames/gumi A3.png");
	Sprite spriteA3;
	spriteA3.setTexture(textureA3);
	spriteA3.setPosition(0, 0);

	Texture textureA4;
	textureA4.loadFromFile("frames/gumi A4.png");
	Sprite spriteA4;
	spriteA4.setTexture(textureA4);
	spriteA4.setPosition(0, 0);

	float scale = 0.5;
	spriteA1.setScale(scale, scale);
	spriteA2.setScale(scale, scale);
	spriteA3.setScale(scale, scale);
	spriteA4.setScale(scale, scale);

	Sprite current = spriteA1;

	SoundBuffer bassBuffer;
	bassBuffer.loadFromFile("sound/bass sfx v2.wav");
	Sound bass;
	bass.setBuffer(bassBuffer);

	Music catMusic;
	catMusic.openFromFile("sound/Cowboy Spacecat Compressed.ogg");
	catMusic.play();

//temporary count/modulus system determines when animation updates
int count = 1;
int frameRateTemp = 20;
bool F1 = true;
bool hitThatBass = false;
int inputTimeOut = 0;
int hitFrame = 1;
	while (window.isOpen())
	{

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if ( (Keyboard::isKeyPressed(Keyboard::Space)) && inputTimeOut==0)
		{
			hitThatBass = true;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			inputTimeOut = 0;
		}
		if (count%frameRateTemp == 0 && !hitThatBass)
		{
			F1 = !F1;
			if (F1)
				current = spriteA1;
			else
				current = spriteA2;
			if (count > frameRateTemp)
			{
				count %= frameRateTemp;
				//if(frameRateTemp > 20) //gradually vibrates faster
				//	frameRateTemp-=1;
			}
			//if(inputTimeOut!=0) //automated strumming when holding space
			//	inputTimeOut--;
		}
		if(hitThatBass && inputTimeOut==0 && count%frameRateTemp == 0)
		{
			if (hitFrame == 1)
			{
				current = spriteA3;
				bass.play();
			}
			else
				current = spriteA4;
			
			hitFrame++;
			if(hitFrame>2)
			{
				inputTimeOut = 2;
				hitThatBass = false;
				hitFrame = 1;
			}
			if (count > frameRateTemp)
				count %= frameRateTemp;
		}
		count++;

		window.clear(Color::White);
		window.draw(current);
		window.display();
	}

	return 0;
}