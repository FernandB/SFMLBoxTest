#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include <image_sfml.h>
#include <iostream>
#include <random>
#include <ctime>
#include "plateform.h"

#define SCALE_SQUARE 30.0f
#define START_POSITION 50.f
#define WIDTH 800.f
#define HEIGHT 600.f
#define SECONDS 60.f
#define VELOCITY_ITERATIONS 8  
#define POSITION_ITERATIONS 3
#define GRAVITY 9.8
#define GRAVITY_SCALE 10
#define SPEED 3
#define IMPULSE 10000
#define PLATEFORM_H 10.f
#define ARRAY_SIZE 5

int getRandomValue()
{
	return rand() % (ARRAY_SIZE - 1);
}

void generatePlateforms(plateform& p1, plateform& p2, plateform& p3,b2PolygonShape plateformb2Shape1, sf::RectangleShape plateformShape1, b2PolygonShape plateformb2Shape2, sf::RectangleShape plateformShape2, b2PolygonShape plateformb2Shape3, sf::RectangleShape plateformShape3)
{
	srand(time(nullptr));
	float heights[ARRAY_SIZE] = { 10.f,30.f,50.f,70.f,90.f };
	float widths[ARRAY_SIZE] = { 100.f,200.f,300.f,400.f,150.f };
	float x_positions[ARRAY_SIZE] = { 100.f,200.f,300.f,400.f,500.f };
	float y_positions[ARRAY_SIZE] = { 100.f,200.f,300.f,400.f,500.f };
	int randomHeight = getRandomValue();
	int randomWidth = getRandomValue();
	int randomXPos = getRandomValue();
	int randomYPos = getRandomValue();

	p1 = plateform(y_positions[randomYPos], x_positions[randomXPos], heights[randomHeight], widths[randomWidth],plateformb2Shape1, plateformShape1);

	randomHeight = getRandomValue();
	randomWidth = getRandomValue();
	randomXPos = getRandomValue();
	randomYPos = getRandomValue();

	p2= plateform(y_positions[randomYPos], x_positions[randomXPos], heights[randomHeight], widths[randomWidth], plateformb2Shape2, plateformShape2);

	randomHeight = getRandomValue();
	randomWidth = getRandomValue();
	randomXPos = getRandomValue();
	randomYPos = getRandomValue();

	p3 = plateform(y_positions[randomYPos], x_positions[randomXPos], heights[randomHeight], widths[randomWidth], plateformb2Shape3, plateformShape3);

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

	sf::RectangleShape plateformShape1;
	sf::RectangleShape plateformShape2;
	sf::RectangleShape plateformShape3;
	b2PolygonShape plateformb2Shape1;
	b2PolygonShape plateformb2Shape2;
	b2PolygonShape plateformb2Shape3;
	
	plateform plateform1;
	plateform plateform2;
	plateform plateform3;

	generatePlateforms(plateform1,plateform2,plateform3, plateformb2Shape1, plateformShape1,plateformb2Shape2, plateformShape2,plateformb2Shape3,plateformShape3);
	
	b2BodyDef plateformBodyDef1 = plateform1.getBodyDef();
	b2Body* staticplateformBody = myWorld->CreateBody(&plateformBodyDef1);
	plateform1.setStaticplateformBody(staticplateformBody);
	b2FixtureDef plateformFixtureDef;
	plateformb2Shape1 = plateform1.getB2Shape();
	plateformFixtureDef.shape = &plateformb2Shape1;
	plateformFixtureDef.friction = 1;
	plateformFixtureDef.restitution = 0;
	b2Fixture* plateformFixture = staticplateformBody->CreateFixture(&plateformFixtureDef);
	
	b2BodyDef plateformBodyDef2 = plateform2.getBodyDef();
	b2Body* staticplateformBody2 = myWorld->CreateBody(&plateformBodyDef2);
	plateform2.setStaticplateformBody(staticplateformBody2);
	b2FixtureDef plateformFixtureDef2;
	plateformb2Shape2 = plateform2.getB2Shape();
	plateformFixtureDef2.shape = &plateformb2Shape2;
	plateformFixtureDef2.friction = 1;
	plateformFixtureDef2.restitution = 0;
	b2Fixture* plateformFixture2 = staticplateformBody2->CreateFixture(&plateformFixtureDef2);

	b2BodyDef plateformBodyDef3 = plateform3.getBodyDef();
	b2Body* staticplateformBody3 = myWorld->CreateBody(&plateformBodyDef3);
	plateform3.setStaticplateformBody(staticplateformBody3);
	b2FixtureDef plateformFixtureDef3;
	plateformb2Shape3 = plateform3.getB2Shape();
	plateformFixtureDef3.shape = &plateformb2Shape3;
	plateformFixtureDef3.friction = 1;
	plateformFixtureDef3.restitution = 0;
	b2Fixture* plateformFixture3 = staticplateformBody3->CreateFixture(&plateformFixtureDef3);

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
		plateformShape1=plateform1.getShape();
		plateformShape2 = plateform2.getShape();
		plateformShape3 = plateform3.getShape();
		plateformShape1.setPosition(staticplateformBody->GetPosition().x, staticplateformBody->GetPosition().y);
		plateformShape1.setFillColor(sf::Color::Magenta);
		plateformShape2.setPosition(staticplateformBody2->GetPosition().x, staticplateformBody2->GetPosition().y);
		plateformShape2.setFillColor(sf::Color::Magenta);
		plateformShape3.setPosition(staticplateformBody3->GetPosition().x, staticplateformBody3->GetPosition().y);
		plateformShape3.setFillColor(sf::Color::Magenta);
		window.draw(borderLeft);
		window.draw(square);
		window.draw(ground);
		window.draw(plateformShape1);
		window.draw(plateformShape2);
		window.draw(plateformShape3);
		window.display();
	}
	delete myWorld;

	system("pause");
	return 0;
}

