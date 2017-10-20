#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>

#include <Box2D/Box2D.h>
#define SCALE 30.0f

int main()
{

	b2Vec2 gravity(0, 9.8); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");
	window.setFramerateLimit(60.f);
	
	sf::RectangleShape square;
	square.setFillColor(sf::Color::Blue);
	square.setSize(sf::Vector2f(30.f,30.f));
	b2PolygonShape b2square;
	b2square.SetAsBox(30.0f,30.0f);
	b2BodyDef squareBodyDef;
	squareBodyDef.type = b2_dynamicBody; //this will be a dynamic body
	squareBodyDef.position.Set(0.f, 50.f); //set the starting position
	b2Body* squareBody = myWorld->CreateBody(&squareBodyDef);
	b2FixtureDef squareFixtureDef;
	squareFixtureDef.shape = &b2square;
	squareFixtureDef.friction = 0;
	squareFixtureDef.restitution = 0;
	b2Fixture* squareFixture = squareBody->CreateFixture(&squareFixtureDef);
	float32 timeStep = 1 / 60.0;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = 8;   //how strongly to correct velocity
	int32 positionIterations = 3;   //how strongly to correct position
	
	b2PolygonShape b2ground;
	b2ground.SetAsBox(800.0f, 0.f);
	sf::RectangleShape ground;
	ground.setFillColor(sf::Color::Green);
	ground.setSize(sf::Vector2f(800.0f, 50.f));
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody; //this will be a static body
	groundBodyDef.position.Set(0.f, 550.f); //slightly lower position
	b2Body* staticGroundBody = myWorld->CreateBody(&groundBodyDef); //add body to world
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.shape = &b2ground;
	groundFixtureDef.friction = 1;
	groundFixtureDef.restitution = 0;
	b2Fixture* groundFixture = staticGroundBody->CreateFixture(&groundFixtureDef);
	ground.setPosition(staticGroundBody->GetPosition().x, staticGroundBody->GetPosition().y);

	
	
	float speed = 5.0f;
	
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