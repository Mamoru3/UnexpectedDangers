#pragma once
#include "Framework/GameObject.h"
#include "Framework/Input.h"
class Background : public GameObject
{
public:
	Background();
	~Background();



	void update(sf::RenderWindow& window, float dt, sf::View& view,Input*input);

private:
	sf::Texture texture;
};

