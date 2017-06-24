#include"MyComponent.h"

sf::Font MyFont::font;

void MyFont::loadFromFile(const sf::String& str)
{
	font.loadFromFile(str);
}