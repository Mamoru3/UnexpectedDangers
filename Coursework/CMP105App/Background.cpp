#include "Background.h"
Background::Background() 
{

}

Background::~Background()
{

}

void Background::update(sf::RenderWindow& window, float dt, sf::View& view, Input* input)
{
	window.getView();


	if (input->isKeyDown(sf::Keyboard::A))
	{
		move(80 * dt, 0);
		if (getPosition().x > 0)
		{
			float x = 0;
			setPosition(x, getPosition().y);

		}
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		move(-80 * dt, 0);
		if (getPosition().x + getSize().x < window.getSize().x)
		{

			float x = window.getSize().x - getSize().x;

			setPosition(x, getPosition().y);
		}
	}
}