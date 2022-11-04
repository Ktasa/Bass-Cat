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

	Texture textureCat;
	textureCat.loadFromFile("frames/gumi A1.png");
	Sprite spriteCat;
	spriteCat.setTexture(textureCat);
	spriteCat.setPosition(0, 0);
	float scale = 0.5;
	spriteCat.setScale(scale, scale);

	while (window.isOpen())
	{

		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			window.close();
		}

		window.clear(Color::White);
		window.draw(spriteCat);
		window.display();

	}

	return 0;
}
