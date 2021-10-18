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
	
	this->createMovementComponent(300.f, 15.f, 5.f);
	this->createAnimationComponent(texture_sheet);

	this->animationComponent->addAnimation("IDLE_LEFT", 10.f, 0, 0, 14, 0, 616, 566);
	this->animationComponent->addAnimation("WALK_RIGHT", 10.f, 0, 1, 14, 1, 616, 566);
	
}

Player::~Player()
{
}

//Funtions
void Player::update(const float& dt)
{

	this->movementComponent->update(dt);

	if(this->movementComponent->getState(IDLE))
		this->animationComponent->play("IDLE_LEFT", dt);
	else if(this->movementComponent->getState(MOVING_RIGHT))
		this->animationComponent->play("WALK_RIGHT", dt);
}
