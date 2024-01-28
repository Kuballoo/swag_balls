#pragma once
#include <SFML/Graphics.hpp>

#include <ctime>
#include <vector>
#include <iostream>
#include <sstream>

#include "Player.h"
#include "SwagBall.h"

class Game {
public:
	// Constructors and destructors
	Game();
	~Game();

	// Accesors
	const bool running() const;
	const bool& getEndGame() const;

	// Functions
	void update();
	void render();
	void pollEvents();

	// Clock, delta time
	sf::Clock deltaTimeClock;
	sf::Time deltaTime;

private:
	// Window variables
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	sf::Event ev;

	// Objects and their variables
	Player player;
	int points;

	sf::Font font;
	sf::Text guiText;
	sf::Text endGameText;

	std::vector<SwagBall> swagBalls;
	float spawnTimerMax;
	float spawnTimer;
	int maxSwagBalls;

	// Private functions
	void initVariables();
	void initWindow();
	void initFont();
	void initText();

	void updatePlayer();
	void spawnSwagBalls();
	const int randomizeTypeOfBall();
	void collsionCheck();
	void renderGui(sf::RenderTarget* target);
	void updateGui();
};

