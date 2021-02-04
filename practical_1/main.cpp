#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

const Keyboard::Key controls[4] = {
	Keyboard::A, //Player 1 up
	Keyboard::Z, //player 1 down
	Keyboard::Up, //player 2 up
	Keyboard::Down, //Player 2 down
};

const Vector2f paddleSize(25.0f, 100.0f);
const float ballRadius = 10.0f;
const int gameWidth = 800;
const int gameHeight = 600;
const float paddleSpeed = 400.0f;
Font font;
Text text;
Vector2f ballVelocity;
bool server = false;
int p1score;
int p2score;
CircleShape ball;
RectangleShape paddles[2];

bool ai = false;

void Reset() {
	server = !server;
	//reset paddle position
	paddles[0].setPosition(10 + paddleSize.x / 2, gameHeight / 2);
	paddles[1].setPosition(gameWidth - 10 - paddleSize.x / 2, gameHeight / 2);
	//reset ball position
	ball.setPosition(gameWidth / 2, gameHeight / 2);
	ballVelocity = { (server ? 100.0f : -100.0f), 60.0f };
	sf::String string = to_string(p2score) + " : " + to_string(p1score);
	text.setString(string);
	text.setPosition((gameWidth * 0.5f) - (text.getLocalBounds().width * 0.5f), 0);

}

void Load() {

	font.loadFromFile("res/RobotoMono-Regular.ttf");
	text.setFont(font);
	text.setCharacterSize(24);

	p1score = 0;
	p2score = 0;

	//Set size and origin of paddles
	for (auto& p : paddles) {
		p.setSize(paddleSize - Vector2f(3, 3));
		p.setOrigin(paddleSize / 2.0f);
	}
	//Set size and origin of ball
	ball.setRadius(ballRadius - 3);
	ball.setOrigin(ballRadius / 2, ballRadius / 2);
	Reset();
}

void Update(RenderWindow& window) {
	//reset clock, recalculate deltatime
	static Clock clock;
	float dt = clock.restart().asSeconds();
	//check and consume events
	Event event;
	while (window.pollEvent(event)) {
		if (event.type == Event::Closed) {
			window.close();
			return;
		}
	}
	const float bx = ball.getPosition().x;
	const float by = ball.getPosition().y;
	if (by > gameHeight) { //bottom wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, -10);

	}
	else if (by < 0) {//top wall
		ballVelocity.x *= 1.1f;
		ballVelocity.y *= -1.1f;
		ball.move(0, 10);
	}
	else if (bx > gameWidth) {//right wall
		p2score++;
		Reset();
	}
	else if (bx < 0) {// left wall
		p1score++;
		Reset();
	}
	else if (bx<paddleSize.x && by > paddles[0].getPosition().y - (paddleSize.y * 0.5) && by < paddles[0].getPosition().y + (paddleSize.y * 0.5)) {//bounce off left baddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(10, 0);
	}

	else if (bx> gameWidth - 10 - paddleSize.x && by> paddles[1].getPosition().y - (paddleSize.y * 0.5) && by <paddles[1].getPosition().y + (paddleSize.y * 0.5)) {//bounce off Right baddle
		ballVelocity.x *= -1.1f;
		ballVelocity.y *= 1.1f;
		ball.move(-10, 0);
	}

	float direction2p = 0.0f;

	if (ai) {
		if (by < paddles[1].getPosition().y && !(paddles[1].getPosition().y - (paddleSize.y * .5f) < 0)) {
			direction2p--;

		}
		else if (by > paddles[1].getPosition().y && !(paddles[1].getPosition().y + (paddleSize.y * .5f) > gameHeight)) {
			direction2p++;

		}
		else {
			//do nothing
		}



	}
	else {
	if (Keyboard::isKeyPressed(controls[2]) && !(paddles[1].getPosition().y - (paddleSize.y * .5f) < 0)) {
		direction2p--;
	}
	if (Keyboard::isKeyPressed(controls[3]) && !(paddles[1].getPosition().y + (paddleSize.y * .5f) > gameHeight)) {
		direction2p++;
	}
	
	}
paddles[1].move(0, direction2p * paddleSpeed * dt);




	//Quit via ESC Key
	if (Keyboard::isKeyPressed(Keyboard::Escape)) {
		window.close();
	}
	float direction = 0.0f;
	if (Keyboard::isKeyPressed(controls[0]) && !(paddles[0].getPosition().y - (paddleSize.y * .5f) < 0)) {
		direction--;
	}
	if (Keyboard::isKeyPressed(controls[1]) && !(paddles[0].getPosition().y + (paddleSize.y * .5f) > gameHeight)) {
		direction++;
	}	

	paddles[0].move(0, direction * paddleSpeed * dt);

	ball.move(ballVelocity * dt);
}

void Render(RenderWindow& window) {
	//Draw Everything
	window.draw(paddles[0]);
	window.draw(paddles[1]);
	window.draw(ball);
	window.draw(text);
}


int main() {
	RenderWindow window(VideoMode(gameWidth, gameHeight), "Pong");

	Load();
	while (window.isOpen()) {
		window.clear();
		Update(window);
		Render(window);
		window.display();
	}
	return 0;
}