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

	// Pointer to the only class instance
	static TextureHolder* m_s_Instance;

public:
	TextureHolder();
	static sf::Texture& GetTexture(std::string const& filename);

};

#endif
