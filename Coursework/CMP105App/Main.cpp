// Main
// Entry point of the application.
// Handles window creation and window events.
// Contains the game loop, updates input class and contains the level objects.
// @author Paul Robertson

#include <iostream>
#include "Level.h"
#include "Menu.h"
#include "Manager.h"
int main()
{
	sf::VideoMode DesktopMode = sf::VideoMode::getDesktopMode();
	//Create the window
	sf::RenderWindow window(sf::VideoMode(DesktopMode), "Unexpected Dangers", sf::Style::Fullscreen);

	// Initialise input and level objects.
	Input input;
	
	GameState gameState;
	gameState.setCurrentState(State::MENU);
	// Initialise objects for delta time
	sf::Clock clock;
	float deltaTime;
	Level level(&window, &input, &gameState);
	Menu menu(&window, &gameState, &input);
	
	// Game Loop
	while (window.isOpen())
	{
		// Handle window events.
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::Resized:
				window.setView(sf::View(sf::FloatRect(0.f, 0.f, (float)event.size.width, (float)event.size.height)));
				break;
			case sf::Event::KeyPressed:
				// update input class
				input.setKeyDown(event.key.code);
				break;
			case sf::Event::KeyReleased:
				//update input class
				input.setKeyUp(event.key.code);
				break;
			case sf::Event::MouseMoved:
				//update input class
				input.setMousePosition(event.mouseMove.x, event.mouseMove.y);
				break;
			case sf::Event::MouseButtonPressed:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(true);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(true);
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (event.mouseButton.button == sf::Mouse::Left)
				{
					//update input class
					input.setMouseLDown(false);
				}
				else if (event.mouseButton.button == sf::Mouse::Right)
				{
					input.setMouseRDown(false);
				}
				break;
			default:
				// don't handle other events
				break;
			}
		}

		// Calculate delta time. How much time has passed 
		// since it was last calculated (in seconds) and restart the clock.
		deltaTime = clock.restart().asSeconds();


		// Call standard game loop functions (input, update and render)
		enum class GameState { MENU, LEVEL, STORY };


		switch (gameState.getCurrentState())	//DIFFERENT GAME STATES
		{
		case(State::MENU):
			menu.handleInput(deltaTime);
			menu.update(deltaTime);
			menu.render();
			break;
		case(State::LEVEL):
		
			level.handleInput(deltaTime);
			level.update(deltaTime);
			level.render();
			break;
		case(State::STORY):
		{
			menu.renderIntro();
			menu.handleInputStory();
			break;
		}
		case(State::CREDITS):
		{
			menu.winDisplay();
			break;
		}
		case(State::LOSS):
		{
			menu.lossdisplay();
			break;
		}
		case(State::CONTROLS):
		{
			menu.controlsDisplay();
			menu.handleInputInstructions();
			break;
		}
		case(State::PAUSE):
		{
			menu.pauseInput();
			menu.pauseDisplay();
			break;
		}
		}
	}

}