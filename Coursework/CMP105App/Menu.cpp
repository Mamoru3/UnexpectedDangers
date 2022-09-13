#include "Menu.h"
Menu::Menu(sf::RenderWindow* hwnd, GameState* gs, Input* in)
{
	gameState = gs;
	window = hwnd;
	input = in;


	if (!font.loadFromFile("font/BossLifefont.ttf")) //SETS THE GAME NAME IN THE MENU SCREEN
	{
		std::cout << "NO \n";
	}
	gameName.setFont(font);
	gameName.setString("UNEXPECTED DANGERS ");
	gameName.setCharacterSize(70);
	gameName.setFillColor(sf::Color::Red);
	gameName.setPosition(window->getSize().x / 3.3, window->getSize().y / 12);


	if (!font.loadFromFile("font/BossLifefont.ttf"))		//FIRST TEXT IN MENU GAMESTATE
	{
		std::cout << "NO \n";
	}
	startGame.setFont(font);
	startGame.setString("PRESS ENTER TO START GAME");
	startGame.setCharacterSize(60);
	startGame.setFillColor(sf::Color::Green);
	startGame.setPosition(window->getSize().x/3.7, window->getSize().y/4);
	


	if (!font.loadFromFile("font/BossLifefont.ttf"))		//SECOND TEXT IN MENU GAMESTATE
	{
		std::cout << "NO \n";
	}
	controls.setFont(font);
	controls.setString("PRESS SPACE TO VIEW CONTROLS");
	controls.setCharacterSize(60);
	controls.setFillColor(sf::Color::Green);
	controls.setPosition(window->getSize().x / 3.7, window->getSize().y / 2.5);

	if (!font.loadFromFile("font/BossLifefont.ttf"))		//EXIT TEXT IN MENU GAMESTATE
	{
		std::cout << "NO \n";
	}
	endGame.setFont(font);
	endGame.setString("PRESS EXIT TO END THE GAME");
	endGame.setCharacterSize(60);
	endGame.setFillColor(sf::Color::Green);
	endGame.setPosition(window->getSize().x / 3.7, window->getSize().y / 1.8);
	
	if (!font.loadFromFile("font/BossLifefont.ttf"))		//STORY IN STORY GAMESTATE
	{
		std::cout << "NO \n";
	}
	story.setFont(font);
	story.setString("DURING A PROBLEM IN THE SPACESHIP X49L26NZ, \n A BRAVE MARINE GOES OUT ON THE SHIP TO CHECK AND REPAIR THE PROBLEM.\n HE DID NOT KNOW WHAT WOULD HAPPEN.\n HE FINDS HIMSELF IN A CRUCIAL BATTLE TO SAVE THE SHIP AND ALL HIS CREW. ");
	story.setCharacterSize(30);
	story.setFillColor(sf::Color::Yellow);
	story.setPosition(0,0 );

	if (!font.loadFromFile("font/BossLifefont.ttf"))		//ENTER IN STORY GAMESTATE TO START THE GAME
	{
		std::cout << "NO \n";
	}
	enterToContinue.setFont(font);
	enterToContinue.setString("PRESS ENTER TO CONTINUE ");
	enterToContinue.setCharacterSize(30);
	enterToContinue.setFillColor(sf::Color::Red);
	enterToContinue.setPosition(window->getSize().x/6 ,window->getSize().y/2);

	if (!font.loadFromFile("font/BossLifefont.ttf"))		//WIN DISPLAY
	{
		std::cout << "NO \n";
	}
	credits.setFont(font);
	credits.setString("CONGRATULATIONS, YOU SAVED THE CREW, PRESS EXIT TO END THE GAME ");
	credits.setCharacterSize(30);
	credits.setFillColor(sf::Color::Green);
	credits.setPosition(window->getSize().x / 6, window->getSize().y / 2);

	if (!font.loadFromFile("font/BossLifefont.ttf"))		//LOSS DISPLAY
	{
		std::cout << "NO \n";
	}
	loss.setFont(font);
	loss.setString("GAME OVER, YOU HAVE BEEN DEFEATED BY THE MONSTER ");
	loss.setCharacterSize(30);
	loss.setFillColor(sf::Color::Red);
	loss.setPosition(window->getSize().x / 6, window->getSize().y / 2);

	if (!font.loadFromFile("font/BossLifefont.ttf"))		//WIN DISPLAY
	{
		std::cout << "NO \n";
	}
	controlsScreen.setFont(font);
	controlsScreen.setString("THESE ARE THE INSTRUCTIONS \n \n PRESS SPACE TO JUMP AND AVOID THE BOSS ATTACKS \n PRESS J TO SHOOT \n YOU CAN MOVE WITH A,S,D,W,\n PRESS SHIFT TO SPRINT . \n \n PRESS ENTER TO START THE GAME . ");
	controlsScreen.setCharacterSize(30);
	controlsScreen.setFillColor(sf::Color::Green);
	controlsScreen.setPosition(0,0);

	if (!font.loadFromFile("font/BossLifefont.ttf"))		//WIN DISPLAY
	{
		std::cout << "NO \n";
	}
	pause.setFont(font);
	pause.setString("GAME IS PAUSED, PRESS P IF YOU WANT TO RESUME THE GAME ");
	pause.setCharacterSize(30);
	pause.setFillColor(sf::Color::Cyan);
	pause.setPosition(0, 0);

	if (!font.loadFromFile("font/BossLifefont.ttf"))		//WIN DISPLAY
	{
		std::cout << "NO \n";
	}
	author.setFont(font);
	author.setString("A GAME BY: ALESSANDRO LODDO ");
	author.setCharacterSize(30);
	author.setFillColor(sf::Color::Green);
	author.setPosition(0, 0);

	menuMusic.openFromFile("sfx/MenuSoundtrack.wav");	//MENU MUSIC IS SET AND STARTS
	menuMusic.play();
	menuMusic.setVolume(50);
	menuMusic.setLoop(true);

	levelMusic.openFromFile("sfx/LevelMusic.ogg");	//LEVEL MUSIC IS SET

	levelMusic.setVolume(50);
	levelMusic.setLoop(true);
}
void Menu::handleInput(float dt)
{
	
	if (input->isKeyDown(sf::Keyboard::Escape))	//IF EXIT IS PRESSED,THE SCREEN CLOSES
	{
		window->close();
	}
	if (input->isKeyDown(sf::Keyboard::Enter)) //IF ENTER IS PRESSED IN MENU, STORY STARTS
	{
		gameState->setCurrentState(State::STORY);
		input->setKeyUp(sf::Keyboard::Enter);
	}
	if (input->isKeyDown(sf::Keyboard::Space)) //IF SPACE IS PRESSED IN MENU, CONTROLS STARTS
	{
		gameState->setCurrentState(State::CONTROLS);
		input->setKeyUp(sf::Keyboard::Space);
	}
}
void Menu::handleInputStory()
{
	if (input->isKeyDown(sf::Keyboard::Escape))	//IF EXIT IS PRESSED,THE SCREEN CLOSES
	{
		window->close();
	}
	if (input->isKeyDown(sf::Keyboard::Enter))	//IF ENTER IS PRESSED IN STORY SCREEN, GAME STARTS
	{
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::Enter);
		menuMusic.stop();
		levelMusic.play();
	}
}
void Menu::handleInputInstructions()
{
	if (input->isKeyDown(sf::Keyboard::Escape))	//IF EXIT IS PRESSED,THE SCREEN CLOSES
	{
		window->close();
	}
	if (input->isKeyDown(sf::Keyboard::Enter))	//IF ENTER IS PRESSED IN STORY SCREEN, GAME STARTS
	{
		gameState->setCurrentState(State::STORY);
		input->setKeyUp(sf::Keyboard::Enter);

	}
}
void Menu::pauseInput()	//PRESS P DURING THE GAME TO PAUSE THE GAME
{
	if (input->isKeyDown(sf::Keyboard::P))
	{
		gameState->setCurrentState(State::LEVEL);
		input->setKeyUp(sf::Keyboard::P);
	}
}

void Menu::update(float dt)
{

}
void Menu::render()
{
	beginDraw();
	window->draw(startGame);
	window->draw(gameName);
	window->draw(controls);
	window->draw(endGame);
	endDraw();
}
void Menu::renderIntro()	//TEXT RENDERING IN INTRODUCTION SCREEN
{
	beginDraw();
	window->draw(story);
	window->draw(enterToContinue);
	endDraw();
}
void Menu::beginDraw()
{
	window->clear(sf::Color::Black);
}
void Menu::endDraw()
{
	window->display();
}
void Menu::winDisplay()
{
	beginDraw();
	window->draw(credits);
	window->draw(author);
	
	if (input->isKeyDown(sf::Keyboard::Escape))	//IF EXIT IS PRESSED,THE SCREEN CLOSES
	{
		window->close();
	}
	endDraw();
}
void Menu::lossdisplay()
{
	beginDraw();
	window->draw(loss);
	if (input->isKeyDown(sf::Keyboard::Escape))	//IF EXIT IS PRESSED,THE SCREEN CLOSES
	{
		window->close();
	}
	endDraw();
}
void Menu::controlsDisplay()
{
	beginDraw();
	window->draw(controlsScreen);
	if (input->isKeyDown(sf::Keyboard::Escape))	//IF EXIT IS PRESSED,THE SCREEN CLOSES
	{
		window->close();
	}
	endDraw();
}
void Menu::pauseDisplay()
{
	beginDraw();
	window->draw(pause);
	endDraw();
}