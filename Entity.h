#ifndef ENTITY_H
#define ENTITY_H

#include<iostream>
#include<ctime>
#include<cstdlib>
#include<fstream>
#include<sstream>
#include<vector>
#include<stack>
#include<map>

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/audio.hpp>
#include <SFML/Network.hpp>

class Entity
{
private:

protected:
	sf::RectangleShape shape;
	float movementSpeed;

public:
	Entity();
	virtual ~Entity();

	//Funtions
	virtual void move(const float& dt, const float x, const float y);

	virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
};

#endif //ENTITY_H