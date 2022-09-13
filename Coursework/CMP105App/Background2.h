#pragma once
#include "Framework/GameObject.h"
#include "Framework/Input.h"
class Background2 : public GameObject
{
public:
	Background2();
	~Background2();



	void update(sf::RenderWindow& window, float dt, sf::View& view, Input* input);

private:
	sf::Texture texture;
};

