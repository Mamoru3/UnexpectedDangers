#pragma once

#include <SFML/Graphics.hpp>
#include "Framework/Input.h"
#include "Framework/AudioManager.h"
#include "Framework/GameState.h"
#include "Framework/Collision.h"
#include "Framework/GameObject.h"
#include "Background.h"
#include "Background2.h"
#include <string>
#include <iostream>
#include "Manager.h"

class Level{
public:
	Level(sf::RenderWindow* hwnd,Input*in ,GameState*gs);
	~Level();

	void handleInput(float dt);
	void update(float dt);
	void render();


	sf::Vector2f bulletPosition;
	float bulletSpawn1;
	float bulletSpawn2;
private:
	// Default functions for rendering to the screen.
	void beginDraw();
	void endDraw();

	// Default variables for level class.
	
	sf::RenderWindow* window;
	Input* input;
	GameState* gameState;
	AudioManager* audio;
	Manager manager;


	Background	background;
	Background2	background2;

	sf::Texture backTexture;
	sf::View view;
	
};