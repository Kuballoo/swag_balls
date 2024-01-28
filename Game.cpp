#include "Game.h"

// Constructors and destructors
Game::Game() {
	this->initVariables();
	this->initWindow();
	this->initFont();
	this->initText();
}

Game::~Game() {
	delete this->window;
}

/*
*	Public section
*/

const bool Game::running() const {
	return this->window->isOpen();
}

const bool& Game::getEndGame() const {
	return this->endGame;
}

void Game::update() {
	// Updating delta time
	this->deltaTime = this->deltaTimeClock.restart();
	this->pollEvents();
	if(this->endGame == false) {
		this->spawnSwagBalls();
		this->collsionCheck();
		this->updateGui();
		this->updatePlayer();
	}
}

void Game::render() {
	this->window->clear();

	// Render stuff
	this->player.render(this->window);

	for(auto ball : this->swagBalls)
		ball.render(*this->window);

	// Render gui
	this->renderGui(this->window);
	if(this->endGame)
		this->window->draw(this->endGameText);
	this->window->display();
}

void Game::pollEvents() {
	while(this->window->pollEvent(this->ev)) {
		switch(this->ev.type) {
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if(this->ev.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		default:
			break;
		}
	}
}

/*
*	Private section
*/

void Game::initVariables() {
	this->endGame = false;
	this->window = nullptr;
	this->spawnTimerMax = 0.25f;
	this->spawnTimer = this->spawnTimerMax;
	this->maxSwagBalls = 10;
	this->points = 0;
	this->endGame = false;
}

void Game::initWindow() {
	this->videoMode = sf::VideoMode(800, 600);
	this->window = new sf::RenderWindow(this->videoMode, "Swag balls", sf::Style::Close | sf::Style::Titlebar);
	this->window->setFramerateLimit(200);
}

void Game::initFont() {
	if(!this->font.loadFromFile("Exo2.ttf")) {
		std::cout << "ERROR::GAME::INITFONT::COULD NOT LOAD Exo2.ttf\n";
	}
}

void Game::initText() {
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::White);
	this->guiText.setCharacterSize(24);
	this->guiText.setString("Test");

	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(60);
	this->endGameText.setPosition(sf::Vector2f(20.f, 300.f));
	this->endGameText.setString("Game Over");
}

void Game::updatePlayer() {
	this->player.update(this->window, this->deltaTime);
	if(this->player.getHp() <= 0)
		this->endGame = true;
}

void Game::spawnSwagBalls() {
	if(this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += this->deltaTime.asSeconds();
	else {
		if(this->swagBalls.size() < this->maxSwagBalls) {
			this->swagBalls.push_back(SwagBall(*this->window, this->randomizeTypeOfBall()));
			this->spawnTimer = 0.f;
		}
	}
}

const int Game::randomizeTypeOfBall() {
	int type = SwagBallTypes::DEFAULT;
	int randVal = rand() % 100+1;
	if(randVal > 60 && randVal <= 85) 
		type = SwagBallTypes::DAMAGING;
	else if(randVal > 85)
		type = SwagBallTypes::HEALING;
	return type;
}

void Game::collsionCheck() {
	// Check the collsion
	for(int i = 0; i < this->swagBalls.size(); i++) {
		if(this->player.getShape().getGlobalBounds().intersects(swagBalls[i].getShape().getGlobalBounds())) {
			switch(this->swagBalls[i].getTypeOfBall()) {
			case SwagBallTypes::DEFAULT:
				break;
			case SwagBallTypes::DAMAGING:
				this->player.takeDamage(2);
				break;
			case SwagBallTypes::HEALING:
				this->player.gainHealth(1);
				break;
			default:
				break;
			}
			this->swagBalls.erase(this->swagBalls.begin() + i);
			this->points++;
		}
	}
}

void Game::renderGui(sf::RenderTarget* target) {
	target->draw(this->guiText);
}

void Game::updateGui() {
	std::stringstream ss;
	ss << "Points: " << this->points << "\n"
		<< "Health: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";
	this->guiText.setString(ss.str());
}
