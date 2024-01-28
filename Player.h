#pragma once
#include <SFML/Graphics.hpp>
class Player {
public:
	Player(float posX=0.f, float posY=0.f);
	virtual ~Player();

	void update(const sf::RenderTarget* target, sf::Time deltaTime);
	void render(sf::RenderTarget* target);
	void updateWindowBoundsCollsion(const sf::RenderTarget* target);

	void takeDamage(const int damage);
	void gainHealth(const int health);

	// Accessors
	const sf::RectangleShape& getShape() const;
	const int& getHp() const;
	const int& getHpMax() const;
private:
	// Player obj variables
	sf::RectangleShape shape;
	float movementSpeed;
	int hp;
	int hpMax;

	sf::Time deltaTime;

	

	void initVariables();
	void initShape();
	void updateInput();
};
