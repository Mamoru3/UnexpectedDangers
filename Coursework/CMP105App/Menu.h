#pragma once
#include"Framework\GameObject.h"
#include "Framework/GameObject.h"
#include"Framework\GameState.h"
#include<iostream>
#include "Framework/MusicObject.h"
class Menu : public GameObject
{
public:

	Menu(sf::RenderWindow* hwnd,GameState*gs, Input* in);

	void handleInput(float dt);
	void update(float dt);
	void render();
	void beginDraw();
	void endDraw();
	int selectedItem;
	void renderIntro();
	void handleInputStory();
	void winDisplay();
	void lossdisplay();
	void controlsDisplay();
	void handleInputInstructions();
	void pauseDisplay();
	void pauseInput();



	sf::RenderWindow* window;

	sf::Font font;

	sf::Text gameName;
	sf::Text startGame;
	sf::Text endGame;
	sf::Text controls;
	sf::Text story;
	sf::Text enterToContinue;
	sf::Text credits;
	sf::Text loss;
	sf::Text controlsScreen;
	sf::Text pause;
	sf::Text author;

	sf::Music menuMusic;
	sf::Music levelMusic;

	Input* input;
	GameState* gameState;



};

