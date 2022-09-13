#pragma once
#include "Framework/GameObject.h"
#include "Framework/Animation.h"
#include<string>
#include <iostream>
class Boss : public GameObject
{
private:
	int bHealth;
	int bSpeed;
	int bulletDamage;

public:
	Boss();
	~Boss();

	void setSpeed(int a);
	int getSpeed();
	void setHealth(int a);
	int getHealth();
	int getBulletDamage();
	void setBulletDamage(int a);

	int bossCounter;
	void update(float dt,int wX,int wY);

	
	float bossScale = 200.f;
	float bossAcceleration = 200.f;



	sf::Vector2f  bossGravity, bossVelocity;

	Animation bWalk;
	Animation bIdle;
	Animation* getCurrentAnimation;
	sf::Clock bClock;
	sf::Time bTime1;
	sf::Text hDisplay;
	sf::Font bFont;
};

