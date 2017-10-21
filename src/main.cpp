#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>

#include <Box2D/Box2D.h>
#define SCALE_SQUARE 30.0f
#define START_POSITION 50.f
#define WIDTH 800.f
#define HEIGHT 600.f
#define SECONDS 60.f
#define VELOCITY_ITERATIONS 8  //how strongly to correct velocity
#define POSITION_ITERATIONS 3
#define SPEED 5.f
#define GRAVITY 9.8
int main()
{

	b2Vec2 gravity(0, GRAVITY); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Jumping Square !");
	window.setFramerateLimit(60.f);
	
	//SQUARE shape and Fixture
	sf::RectangleShape square;
	square.setFillColor(sf::Color::Blue);
	square.setSize(sf::Vector2f(SCALE_SQUARE,SCALE_SQUARE));
	b2PolygonShape b2square;
	b2square.SetAsBox(SCALE_SQUARE,SCALE_SQUARE);
	b2BodyDef squareBodyDef;
	squareBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	squareBodyDef.position.Set(0.f, START_POSITION); //set the starting position
	b2Body* squareBody = myWorld->CreateBody(&squareBodyDef);
	b2FixtureDef squareFixtureDef;
	squareFixtureDef.shape = &b2square;
	squareFixtureDef.friction = 0;
	squareFixtureDef.restitution = 0;
	b2Fixture* squareFixture = squareBody->CreateFixture(&squareFixtureDef);
	
	
    //ground shape and Fixture
	b2PolygonShape b2ground;
	b2ground.SetAsBox(WIDTH, 0.f);
	sf::RectangleShape ground;
	ground.setFillColor(sf::Color::Green);
	ground.setSize(sf::Vector2f(WIDTH, START_POSITION));
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody; //this will be a static body
	groundBodyDef.position.Set(0.f, HEIGHT-START_POSITION); //slightly lower position
	b2Body* staticGroundBody = myWorld->CreateBody(&groundBodyDef); //add body to world
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &b2ground;
	groundFixtureDef.friction = 1;
	groundFixtureDef.restitution = 0;
	b2Fixture* groundFixture = staticGroundBody->CreateFixture(&groundFixtureDef);
	ground.setPosition(staticGroundBody->GetPosition().x, staticGroundBody->GetPosition().y);

	
	float32 timeStep = 1 / SECONDS;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = VELOCITY_ITERATIONS;   //how strongly to correct velocity
	int32 positionIterations = POSITION_ITERATIONS;   //how strongly to correct position

	float speed = SPEED;
	
	while (window.isOpen())
	{
		myWorld->Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Space)
				{
					std::cout << "User pressed SPACE\n";
				}
			}
		}
		
	
			square.setPosition(squareBody->GetPosition().x, squareBody->GetPosition().y);

		

		window.clear();

		window.draw(square);
		window.draw(ground);
		window.display();
	}
	delete myWorld;

	system("pause");
	return 0;
}