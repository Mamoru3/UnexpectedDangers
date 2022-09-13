#include "Manager.h"
Manager::Manager()
{
	buffer.loadFromFile("sfx/laser9.ogg");	//SHOOTING AUDIO LOADED
	shoot.setBuffer(buffer);

	bText.loadFromFile("gfx/Boss.gif");	//BOSS TEXTURE POSITION AND COLLISION SET
	boss.setSize(sf::Vector2f(350, 350));
	boss.setCollisionBox(sf::FloatRect(0, 0, 350, 350));
	boss.setTexture(&bText);
	boss.setHealth(130);	//BOSS HEALTH SPEED AND BULLET SET
	bossHealth = boss.getHealth();
	boss.setSpeed(60);
	boss.setBulletDamage(50);

	if (!boss.bFont.loadFromFile("font/BossLifefont.ttf"))	//BOSS HEALTH DISPLAY
	{
		std::cout << "NO \n";
	}
	boss.hDisplay.setFont(boss.bFont);
	boss.hDisplay.setCharacterSize(30);
	boss.hDisplay.setFillColor(sf::Color::White);
	

	pText.loadFromFile("gfx/Player.png");	//PLAYER POSITION AND COLLISION SET
	player.setSize(sf::Vector2f(103, 156));
	
	player.setTexture(&pText);
	player.setHealth(100);
	player.setCollisionBox(sf::FloatRect(0, 0, 50, 73));
	playerHealth = player.getHealth(); //CREATION OF A HEALTH VARIABLE

	bMTexture.loadFromFile("gfx/Bullet.png"); // PLAYER BULLET TEXTURE AND SETTINGS
	for (int i = 0; i < 200; i++)
	{
		bullets.push_back(Bullet());
		bullets[i].setAlive(false);
		bullets[i].setTexture(&bMTexture);
		bullets[i].setSize(sf::Vector2f(80, 40));
		bullets[i].setCollisionBox(sf::FloatRect(0, 0, 80, 40));
	}
	setBDamage(5); //SETS BULLETS DAMAGE

	bossBullets.loadFromFile("gfx/bossBullet.png"); //BOSS BULLET TEXTURE AND SETTINGS
	for (int i = 0; i < 200; i++)
	{
		enemyBullets.push_back(Bullet());
		enemyBullets[i].setAlive(false);
		enemyBullets[i].setTexture(&bossBullets);
		enemyBullets[i].setSize(sf::Vector2f(80, 40));
		enemyBullets[i].setCollisionBox(sf::FloatRect(0, 0, 80, 40));
	}

	goalText.loadFromFile("gfx/goal.png"); // GOAL COLLISION AND SPRITE

		goal.setSize(sf::Vector2f(100, 100));
		goal.setTexture(&goalText);
		goal.setCollisionBox(sf::FloatRect(0, 0, 200, 200));



	eTexture.loadFromFile("gfx/Alien.png"); //ENEMIES SET UP
	
		enemy1.setSize(sf::Vector2f(200,200));
		enemy1.setTexture(&eTexture);
		enemy1.setHealth(30);
		enemy1.setCollisionBox(sf::FloatRect(0, 0, 200, 200));
		enemy1.setSpeed(80);
		
		enemy2.setSize(sf::Vector2f(200, 200));
		enemy2.setTexture(&eTexture);
		enemy2.setHealth(30);
		enemy2.setCollisionBox(sf::FloatRect(0, 0, 200, 200));
		enemy2.setSpeed(80);
		
		enemy3.setSize(sf::Vector2f(200, 200));
		enemy3.setTexture(&eTexture);
		enemy3.setHealth(30);
		enemy3.setCollisionBox(sf::FloatRect(0, 0, 200, 200));
		enemy3.setSpeed(80);
		
		enemyHealth1 = enemy1.getHealth();
		enemyHealth2 = enemy2.getHealth();
		enemyHealth3 = enemy3.getHealth();
}


Manager::~Manager()
{

}
void Manager::handleInput(float dt, Input* input,int wX,int wY)
{
	if (input->isKeyDown(sf::Keyboard::J) && time.asSeconds() >= 0.3)		//PLAYER BULLET SPAWN ON INPUT
	{
		shoot.stop();	//SHOOTING SOUND IS STOPPED
		bulletSpawn();
		clock.restart();
		shoot.play();	//SHOOTING SOUND IS STARTS

	}
	if (bossHealth > 70)
	{
		if (time2.asSeconds() >= 1 && bossHealth >= 5)		//BOSS SPAWNS BULLETS FIRST PHASE
		{
			bossBulletSpawn();
			clock2.restart();
		}
	}
	else if (bossHealth > 30)
	{
		if (time2.asSeconds() >= 0.5 && bossHealth >= 5)		//BOSS SPAWNS BULLETS SECOND PHASE
		{
			bossBulletSpawn();
			clock2.restart();
		}
	}
	else if (bossHealth <= 30)
	{
		if (time2.asSeconds() >= 0.3 && bossHealth >= 5)		//BOSS SPAWNS BULLETS THIRD PHASE
		{
			bossBulletSpawn();
			clock2.restart();
		}
	}
	player.handleInput(dt, input);	//PLAYER INPUT 
	time = clock.getElapsedTime();	//PLAYER CLOCK SET
	time2 = clock2.getElapsedTime();//BOSS CLOCK SET

	// call update on all ALIVE balls
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			bullets[i].update(dt);
		}
	}
	bulletDeathCheck(wX, wY); //CHECKS WHETHER THE PLAYER BULLETS ARE OUT OF THE SCREEN
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i].isAlive())
		{
			enemyBullets[i].update(dt);
		}
	}
	bossBulletDeathCheck(wX, wY); //CHECKS WHETHER THE BOSS BULLETS ARE OUT OF THE SCREEN

	if (input->isKeyDown(sf::Keyboard::A))	//CHECKS WHETHER THE PLAYER IS FLIPPED AND SETS A VARIABLE FOR THE BULLET SPAWN LOCATIONS
	{
		bulletFlip = true;
	}
	if (input->isKeyDown(sf::Keyboard::D))
	{
		bulletFlip = false;
	}
	if (bulletFlip == false && !input->isKeyDown(sf::Keyboard::S))	//DIFFERENT PLAYER BULLET SPAWN LOCATIONS
	{
		spawnPoint = sf::Vector2f(player.getPosition().x + 40, player.getPosition().y + 5);
	}
	else	if (bulletFlip == true)
	{
		spawnPoint = sf::Vector2f(player.getPosition().x - 40, player.getPosition().y + 5);
	}
	else	if (input->isKeyDown(sf::Keyboard::S) && bulletFlip == false)
	{
		spawnPoint = sf::Vector2f(player.getPosition().x + 40, player.getPosition().y + 30);
	}
	if (input->isKeyDown(sf::Keyboard::S) && bulletFlip == true)
	{
		spawnPoint = sf::Vector2f(player.getPosition().x - 40, player.getPosition().y + 30);
	}
}

void Manager::render(sf::RenderWindow* window)	//function that renders objects
{
	window->draw(goal);
	window->draw(player);
	window->draw(boss.hDisplay);

	if (bossHealth >= 5)
	{
		window->draw(boss);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			window->draw(bullets[i]);
		}
	}
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i].isAlive())
		{
			window->draw(enemyBullets[i]);
		}
	}
	if (enemyHealth1 > 0)	//if first enemy is alive, it is rendered 
	{
		window->draw(enemy1);
	}
	if (enemyHealth2 > 0)	//if second enemy is alive, it is rendered 
	{
		window->draw(enemy2);
	}
	if (enemyHealth3 > 0)	//if third enemy is alive, it is rendered 
	{
		window->draw(enemy3);
	}
}


void Manager::update(float dt,Input*input,int wX,int wY, GameState* gameState)
{
	
	
	bossHealthDisplay(); //DISPLAYS BOSS AND PLAYER HEALTH AND UPDATES IT
	collisionCheck(); //CHECKS FOR THE DIFFERENT COLLISIONS
	player.update(dt,wX,wY,input);

	if (bossHealth >= 5)
	{
		boss.update(dt,wX,wY);
	}
	if (bossHealth <= 0)
	{
		bossHealth = 0;
	}
	if (playerHealth <= 0)
	{
		playerHealth = 0;
	}

	if (Collision::checkBoundingBox(&goal, &player))	//IF GOAL IS REACHED, THE GAME IS WON 
	{
		gameState->setCurrentState(State::CREDITS);
	}
	else if (playerHealth <= 0)		//IF PLAYER'S HEALTH IS ZERO, THE GAME IS LOSS
	{
		gameState->setCurrentState(State::LOSS);
	}
	if (enemyHealth1>0)	//IF ENEMIES ARE ALIVE, THEY ARE UPDATED
	{
		enemy1.update(dt, wX, wY);
	}
	if (enemyHealth2>0)
	{
		enemy2.update(dt, wX, wY);
	}
	if (enemyHealth3>0)
	{
		enemy3.update(dt, wX, wY);
	}
}

void Manager::bulletSpawn()			//FUNCTION THAT SPAWNS THE BULLETS AND CHECKS WHETHER THE PLAYER IS FLIPPED
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (!bullets[i].isAlive())
		{
			bullets[i].setAlive(true);
			if (bulletFlip == true)
			{
				bullets[i].setVelocity(-1000, 0);
			}
			if (bulletFlip == false)
			{
				bullets[i].setVelocity(1000, 0);
			}
			bullets[i].setPosition(spawnPoint);
			return;
		}
	}
}
void Manager::bossBulletSpawn()			//FUNCTION THAT SPAWNS BOSS BULLETS 
{
		for (int i = 0; i < enemyBullets.size(); i++)
		{
			if (!enemyBullets[i].isAlive())
			{
				enemyBullets[i].setAlive(true);
				enemyBullets[i].setVelocity(-1000, 0);
				boss.bossCounter = boss.bossCounter + 1; //COUNTER TO ALLOW BOSS TO FIRE UP AND DOWN

				if (boss.bossCounter % 2 == 0) //BOSS ALTERNATES FIRE UP AND DOWN
				{
					enemyBullets[i].setPosition(boss.getPosition());
				}
				else if (boss.bossCounter % 2 != 0)
				{
					enemyBullets[i].setPosition(sf::Vector2f(boss.getPosition().x, boss.getPosition().y + 250));
				}
				return;
			}
		}
}

void Manager::bulletDeathCheck(int wX, int wY)		//CHECKS IF THE BULLETS ARE STILL IN THE SCREEN
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())
		{
			if (bullets[i].getPosition().x < -100)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().x > wX)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y < -100)
			{
				bullets[i].setAlive(false);
			}
			if (bullets[i].getPosition().y > wY)
			{
				bullets[i].setAlive(false);
			}
		}
	}
}
void Manager::bossBulletDeathCheck(int wX, int wY)		//CHECKS IF THE ENEMY BULLETS ARE STILL IN THE SCREEN
{
	for (int i = 0; i < enemyBullets.size(); i++)
	{
		if (enemyBullets[i].isAlive())
		{
			if (enemyBullets[i].getPosition().x < -100)
			{
				enemyBullets[i].setAlive(false);
			}
			if (enemyBullets[i].getPosition().x > wX)
			{
				enemyBullets[i].setAlive(false);
			}
			if (enemyBullets[i].getPosition().y < -100)
			{
				enemyBullets[i].setAlive(false);
			}
			if (enemyBullets[i].getPosition().y > wY)
			{
				enemyBullets[i].setAlive(false);
			}
		}
	}
}
void Manager::collisionCheck() //FUNCTION THAT CHECKS ALL THE COLLISIONS
{
	for (int i = 0; i < bullets.size(); i++)
	{
		if (bullets[i].isAlive())	//COLLISION BETWEEN PLAYER BULLETS AND BOSS
		{
			if (Collision::checkBoundingBox(&bullets[i], &boss) && bossHealth >= 5)
			{
				bullets[i].setAlive(false);
				bossHealth -= getBDamage();
			}
		}
	}
	for (int i = 0; i < enemyBullets.size(); i++)	//COLLISION BETWEEN BOSS BULLETS AND PLAYER
	{
		if (enemyBullets[i].isAlive())
		{
			if (Collision::checkBoundingBox(&enemyBullets[i], &player))
			{
				enemyBullets[i].setAlive(false);
				playerHealth -= boss.getBulletDamage();
			}
		}
	}
	if (bossHealth > 0)
	{
		if (Collision::checkBoundingBox(&player, &boss))	//IF BOSS COLLIDES WITH PLAYER, PLAYER'S HEALTH IS SET TO 0
		{
			playerHealth = 0;
		}
	}
	if (enemyHealth1 > 0)
	{
		if (Collision::checkBoundingBox(&enemy1, &player))	//IF ENEMIES COLLIDE WITH PLAYER, PLAYER HEALTH IS SET TO 0
		{
			playerHealth = 0;
		}
	}
	if (enemyHealth2 > 0)
	{
		if (Collision::checkBoundingBox(&enemy2, &player))
		{
			playerHealth = 0;
		}
	}
	if (enemyHealth3 > 0)
	{
		if (Collision::checkBoundingBox(&enemy3, &player))
		{
			playerHealth = 0;
		}
	}
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())	//COLLISION BETWEEN PLAYER BULLETS AND FIRST ENEMY
			{
				if (Collision::checkBoundingBox(&bullets[i], &enemy1) && enemyHealth1 >= 5)
				{
					bullets[i].setAlive(false);
					enemyHealth1 -= getBDamage();
				}
			}
		}
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())	//COLLISION BETWEEN PLAYER BULLETS AND SECOND ENEMY
			{
				if (Collision::checkBoundingBox(&bullets[i], &enemy2) && enemyHealth2 >= 5)
				{
					bullets[i].setAlive(false);
					enemyHealth2 -= getBDamage();
				}
			}
		}
		for (int i = 0; i < bullets.size(); i++)
		{
			if (bullets[i].isAlive())	//COLLISION BETWEEN PLAYER BULLETS AND THIRD ENEMY
			{
				if (Collision::checkBoundingBox(&bullets[i], &enemy3) && enemyHealth3 >= 5)
				{
					bullets[i].setAlive(false);
					enemyHealth3 -= getBDamage();
				}
			}
		}
	
}
int Manager::getBDamage()
{
	return bDamage;
}
void Manager::setBDamage(int b)
{
	bDamage = b;
}
void Manager::bossHealthDisplay() //FUNCTION THAT DISPLAYS BOSS HEALTH AND PLAYER HEALTH
{
	std::string bossHealthDisplay = + "PLAYER'S HEALTH: "+std::to_string(playerHealth)+ "                               ALIEN QUEEN'S HEALTH: " + std::to_string(bossHealth);
	boss.hDisplay.setString(bossHealthDisplay);
}
void Manager::setPositions(int wX,int wY)	//FUNCTION THAT SETS ALL THE POSITIONS 
{
	enemyPosition = (wX/2)+(wX/7);
	boss.setPosition(sf::Vector2f(wX-200, wY/2));
	player.setPosition(sf::Vector2f(wX/7, wY/2));
	enemy1.setPosition(sf::Vector2f(enemyPosition, wY/2));
	enemy2.setPosition(sf::Vector2f(enemyPosition - 50, wY/2));
	enemy3.setPosition(sf::Vector2f(enemyPosition - 100, wY/2));
	boss.hDisplay.setPosition(wX / 4, wY / 4);
	goal.setPosition(wX - goal.getSize().x, wY-goal.getSize().y*2);
}
