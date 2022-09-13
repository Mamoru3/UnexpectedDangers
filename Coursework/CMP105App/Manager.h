#pragma once
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "Boss.h"
#include "Player.h"
#include "Framework/Collision.h"
#include <string>
#include <iostream>
#include "Framework/GameState.h"
#include "Enemy.h"
#include "Framework/SoundObject.h"
#include "Framework/AudioManager.h"
class Manager
{


public:
		Manager();
		~Manager();


		bool bulletFlip;
		
		int bossHealth;
		int playerHealth;
		int enemyPosition;
		int enemyHealth1;
		int enemyHealth2;
		int enemyHealth3;

		void collisionCheck();
		void handleInput(float dt,Input*input,int wX,int wY);
		void update(float dt,Input*input,int wX,int wY, GameState* gameState);
		void render(sf::RenderWindow* window);
		void bulletSpawn();
		void bulletDeathCheck(int wX, int wY);
		void setPositions(int wX,int wY);
		void clockRestarter();

		int getBDamage();
		void setBDamage(int b);

		void bossBulletSpawn();
		void bossHealthDisplay();
		void bossBulletDeathCheck(int wX, int wY);
private:
	
		Player player;
		Boss boss;
		Enemy enemy1,enemy2,enemy3;
		GameObject goal;

		sf::Time time;
		sf::Time time2;
		sf::Texture bText;		//Boss texture
		sf::Texture pText;		//Player texture
		sf::Texture bMTexture;	//Bullet Texture
		sf::Texture eTexture;	//Enemy texture
		sf::Texture bossBullets;
		sf::Texture goalText;
		sf::Vector2f spawnPoint;

		sf::SoundBuffer buffer;
		sf::Sound shoot;
		
		sf::RenderWindow* window;
		std::vector<Bullet> bullets;
		std::vector<Bullet> enemyBullets;
		
		

		sf::Clock clock;
		sf::Clock clock2;
		int bDamage;
};

