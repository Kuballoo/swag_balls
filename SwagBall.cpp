#include "SwagBall.h"

SwagBall::SwagBall(const sf::RenderWindow& window, int typeOfSwagBall) 
	: typeOfSwagBall(typeOfSwagBall)
{
	this->initShape(window);
}

SwagBall::~SwagBall() {
}

/*
*	Public section
*/

void SwagBall::update() {
}

void SwagBall::render(sf::RenderTarget& target) {
	target.draw(this->shape);
}

const sf::CircleShape SwagBall::getShape() const {
	return this->shape;
}

const int& SwagBall::getTypeOfBall() const {
	return this->typeOfSwagBall;
}

/*
*	Private section
*/

void SwagBall::initShape(const sf::RenderWindow& window) {
	this->shape.setRadius(static_cast<float>(rand() % 10 + 10));
	sf::Color color;
	switch(this->typeOfSwagBall) {
	case DEFAULT:
		color = sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1);
		break;
	case DAMAGING:
		color = sf::Color::Red;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	case HEALING:
		color = sf::Color::Green;
		this->shape.setOutlineColor(sf::Color::White);
		this->shape.setOutlineThickness(2.f);
		break;
	default:
		break;
	}
	
	this->shape.setFillColor(color);
	this->shape.setPosition(sf::Vector2f(
		static_cast<float>(rand() % static_cast<int>(window.getSize().x - this->shape.getGlobalBounds().width)),
		static_cast<float>(rand() % static_cast<int>(window.getSize().y - this->shape.getGlobalBounds().height)))
	);
}
