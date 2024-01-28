#pragma once
#include <SFML/Graphics.hpp>

enum SwagBallTypes {
	DEFAULT = 0,
	DAMAGING,
	HEALING,
	NROFTYPES
};

class SwagBall {
public:
	SwagBall(const sf::RenderWindow& window, int typeOfSwagBall);
	~SwagBall();

	void update();
	void render(sf::RenderTarget& target);	

	// Accessors
	const sf::CircleShape getShape() const;
	const int& getTypeOfBall() const;
private:
	sf::CircleShape shape;
	int typeOfSwagBall;

	void initShape(const sf::RenderWindow& window);
};

