#include "Player.h"

Player::Player(float posX, float posY) {
	this->shape.setPosition(posX, posY);

	this->initVariables();
	this->initShape();
}

Player::~Player() {
}

/*
*	Public section
*/

void Player::update(const sf::RenderTarget* target, sf::Time deltaTime) {
	// Updating ours delta time every update was called
	this->deltaTime = deltaTime;
	this->updateInput();

	// Window bounds collison
	this->updateWindowBoundsCollsion(target);
}

void Player::render(sf::RenderTarget* target) {
	target->draw(this->shape);
}

void Player::updateWindowBoundsCollsion(const sf::RenderTarget* target) {
	/*
	*	Window border collsion detection
	*/
	// Left and right 
	if(this->shape.getGlobalBounds().left <= 0.f)
		this->shape.setPosition(0.f, this->shape.getGlobalBounds().top);
	else if(this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->shape.setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	// Top and bottom
	if(this->shape.getGlobalBounds().top <= 0.f)
		this->shape.setPosition(this->shape.getGlobalBounds().left, 0.f);
	else if(this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->shape.setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::takeDamage(const int damage) {
	if(this->hp > 0)
		this->hp -= damage;

	if(this->hp < 0)
		this->hp = 0;
}

void Player::gainHealth(const int health) {
	if(this->hp < this->hpMax)
		this->hp += health;

	if(this->hp > this->hpMax)
		this->hp = this->hpMax;
}

// Accessors
const sf::RectangleShape& Player::getShape() const {
	return this->shape;
}

const int& Player::getHp() const {
	return this->hp;
}

const int& Player::getHpMax() const {
	return this->hpMax;
}


/*
*	Private section
*/

void Player::initVariables() {
	this->movementSpeed = 200.f;
	this->hpMax = 10;
	this->hp = this->hpMax;
}

void Player::initShape() {
	this->shape.setFillColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

void Player::updateInput() {
	// Keyboard input
	float moveOffset = this->movementSpeed * this->deltaTime.asSeconds();
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		this->shape.move(-moveOffset, 0.f);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		this->shape.move(moveOffset, 0.f);
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		this->shape.move(0.f, -moveOffset);
	else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		this->shape.move(0.f, moveOffset);
}