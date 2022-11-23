#pragma once
#ifndef TEXTURE_HOLDER_H
#define TEXTURE_HOLDER_H

#include <SFML/Graphics.hpp>
#include <map>
using namespace std;
using namespace sf;

class TextureHolder
{
private:
	// map holds pairs of String and Texture
	map<string, Texture> m_Textures;

	// A pointer of the same type as the class itself
	// the one and only instance
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename);

};

#endif
