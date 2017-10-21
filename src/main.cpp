#include <SFML/Graphics.hpp>
#include <image_sfml.h>
#include <iostream>
#include <Box2D/Box2D.h>
#include <random>
#include <ctime>
#define SCALE_SQUARE 30.0f
#define START_POSITION 50.f
#define WIDTH 800.f
#define HEIGHT 600.f
#define SECONDS 60.f
#define VELOCITY_ITERATIONS 8  //how strongly to correct velocity
#define POSITION_ITERATIONS 3
#define GRAVITY 9.8
#define GRAVITY_SCALE 5
#define SPEED 3
#define IMPULSE 100000.f

void generatePlateform()
{
	const float MAX_HEIGHT = 600.f;
	const float MIN_HEIGHT = 600.f;
	std::srand(std::time(nullptr));

}

int main()
{

	b2Vec2 gravity(0, GRAVITY); //normal earth gravity, 9.8 m/s/s straight down!

	b2World* myWorld = new b2World(gravity);

	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Jumping Square !");
	window.setFramerateLimit(SECONDS);
	
	//square shape and Fixture
	sf::RectangleShape square;
	square.setFillColor(sf::Color::Blue);
	square.setSize(sf::Vector2f(SCALE_SQUARE,SCALE_SQUARE));
	b2PolygonShape b2square;
	b2square.SetAsBox(SCALE_SQUARE,SCALE_SQUARE);
	b2BodyDef squareBodyDef;
	squareBodyDef.gravityScale = GRAVITY_SCALE;
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
	b2ground.SetAsBox(WIDTH-4, 0.f);
	sf::RectangleShape ground;
	ground.setFillColor(sf::Color::Green);
	ground.setSize(sf::Vector2f(WIDTH, START_POSITION));
	b2BodyDef groundBodyDef;
	groundBodyDef.type = b2_staticBody; //this will be a static body
	groundBodyDef.position.Set(0.f, HEIGHT-START_POSITION); //slightly lower position
	b2Body* staticGroundBody = myWorld->CreateBody(&groundBodyDef); //add body to world
	b2FixtureDef groundFixtureDef;
	groundFixtureDef.userData=(void*)3;
	groundFixtureDef.shape = &b2ground;
	groundFixtureDef.friction = 1;
	groundFixtureDef.restitution = 0;
	b2Fixture* groundFixture = staticGroundBody->CreateFixture(&groundFixtureDef);
	ground.setPosition(staticGroundBody->GetPosition().x, staticGroundBody->GetPosition().y);

	sf::RectangleShape borderLeft;
	borderLeft.setFillColor(sf::Color::Red);
	borderLeft.setSize(sf::Vector2f(1, HEIGHT));
	borderLeft.setPosition(0.f, 0.f);


	float32 timeStep = 1 / SECONDS;      //the length of time passed to simulate (seconds)
	int32 velocityIterations = VELOCITY_ITERATIONS;   //how strongly to correct velocity
	int32 positionIterations = POSITION_ITERATIONS;   //how strongly to correct position

	
	
	while (window.isOpen())
	{
		myWorld->Step(timeStep, velocityIterations, positionIterations);
		sf::Event event;
		sf::Vector2f delta_move;
		while (window.pollEvent(event))
		{

			//Manage inputs
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				{
					if(squareBody->GetLinearVelocity().y<=0.3)
					delta_move.y -= IMPULSE;
				}
				
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				{
						if(square.getPosition().x>borderLeft.getPosition().x)
						delta_move.x -= 1;

				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				{
					
						delta_move.x += 1;
					
				}
			
			}
			
		}

		if(delta_move.y<0)
		squareBody->ApplyForce(b2Vec2::b2Vec2(0.f, delta_move.y), squareBody->GetWorldCenter(), true);

		square.setPosition(square.getPosition().x+SPEED*delta_move.x, squareBody->GetPosition().y);
	
		window.clear();

		window.draw(borderLeft);
		window.draw(square);
		window.draw(ground);
		window.display();
	}
	delete myWorld;

	system("pause");
	return 0;
}

