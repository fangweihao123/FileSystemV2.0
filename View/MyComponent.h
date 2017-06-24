#pragma once
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/System/String.hpp>

class MyFont:public sf::Font
{
	public:
		static sf::Font font;
		static void loadFromFile(const sf::String& str);

};

class MyView:public sf::View
{

};