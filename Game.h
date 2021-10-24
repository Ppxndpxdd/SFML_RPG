#ifndef GAME_H
#define GAME_H

#include"MainMenuState.h"

class Game
{
private:
	//Variables
	GraphicsSettings gfxSettings;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtclock;
	float dt;

	std::stack<State*> states;

	std::map<std::string, int> supportedKeys;

	//Initialization
	void initVariable();
	void initGraphicSettings();
	void initwindow();
	void initKeys();
	void initStates();

public:
	//Constructor/Destructors
	Game();
	virtual ~Game();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDt();
	void updateSFMLEvents();
	void update();

	//Render
	void render();
	//Core
	void run();
};

#endif // !GAME_H