#include <SFML/Graphics.hpp>
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

//temporary count/modulus system determines when animation updates
int count = 1;
int frameRateTemp = 25;
bool F1 = true;
bool hitThatBass = false;
bool inputTimeOut = false;
int hitFrame = 1;
	while (window.isOpen())
	{

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}
		if ( (Keyboard::isKeyPressed(Keyboard::Space)) && !inputTimeOut)
		{
			hitThatBass = true;
		}
		if (!Keyboard::isKeyPressed(Keyboard::Space))
		{
			inputTimeOut = false;
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
		}
		if(hitThatBass && !inputTimeOut && count%frameRateTemp == 0)
		{
			if (hitFrame == 1)
			{
				//cout << "A3\n";
				current = spriteA3;
			}
			else
			{
				//cout << "A4\n";
				current = spriteA4;
			}
			//cout << "Frame: " << hitFrame << endl;
			hitFrame++;
			if(hitFrame>2)
			{
				inputTimeOut = true;
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
