#include "Player.h"

//Initializer functions
void Player::initVariable()
{
}

void Player::initComponents()
{
}

//Constructor / Destructors
Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariable();

	this->setPosition(x, y);
	
	this->createHitboxComponent(this->sprite, 15.f, 11.f, 33.f, 53.f);
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	//this->animationComponent->addAnimation("IDLE", 10.f, 0, 0, 14, 0, 616, 566);
	//this->animationComponent->addAnimation("WALK", 10.f, 0, 1, 14, 1, 616, 566);

	this->animationComponent->addAnimation("IDLE", 70.f, 0, 3, 6, 3, 64, 64);
	this->animationComponent->addAnimation("WALK_UP", 10.f, 0, 10, 8, 10, 64, 64);
	this->animationComponent->addAnimation("WALK_DOWN", 10.f, 0, 8, 8, 8, 64, 64);
	this->animationComponent->addAnimation("WALK_LEFT", 10.f, 0, 9, 8, 9, 64, 64);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0,  11, 8, 11, 64, 64);
	this->sprite.setScale(1.f, 1.f);
}

Player::~Player()
{
}

//Funtions
void Player::update(const float& dt)
{

	this->movementComponent->update(dt);

	if(this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE", dt);
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK_UP", dt);
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK_DOWN", dt);
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		this->animationComponent->play("WALK_RIGHT", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		this->animationComponent->play("WALK_LEFT", dt);
	}

	this->hitboxComponent->update();

}
