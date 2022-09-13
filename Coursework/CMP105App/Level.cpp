#include "Level.h"
Level::Level(sf::RenderWindow* hwnd,Input*in ,GameState*gs)
{
	window = hwnd;
	input = in;
	gameState = gs;
	// initialise game objects
	backTexture.loadFromFile("gfx/Background.jpg");

	background.setTexture(&backTexture);

	background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));

	manager.setPositions(window->getSize().x, window->getSize().y);

}

Level::~Level()
{

}

// handle user input
void Level::handleInput(float dt)
{
	manager.handleInput(dt, input, window->getSize().x, window->getSize().y);
	if (input->isKeyDown(sf::Keyboard::P))
	{
		gameState->setCurrentState(State::PAUSE);
		input->setKeyUp(sf::Keyboard::P);
	}
}

// Update game objects
void Level::update(float dt)
{
	background.update(*window, dt, view, input);
	manager.update(dt, input, window->getSize().x, window->getSize().y,gameState);
}

// Render level
void Level::render()
{
	beginDraw();
	window->draw(background);
	manager.render(window);
	endDraw();
}

// Begins rendering to the back buffer. Background colour set to light blue.
void Level::beginDraw()
{
	window->clear(sf::Color::Black);
}

// Ends rendering to the back buffer, and swaps buffer to the screen.
void Level::endDraw()
{
	window->display();
}