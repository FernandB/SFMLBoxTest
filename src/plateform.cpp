#include "plateform.h"



plateform::plateform(float y_position,float x_position,float height,float width, b2PolygonShape b2plateform,sf::RectangleShape plateformShape):y_position(y_position),x_position(x_position),height(height),width(width),b2plateform(b2plateform),plateformShape(plateformShape)
{
	this->b2plateform.SetAsBox(width/2, height/2);
	this->plateformShape.setSize(sf::Vector2f(width, height));
	b2BodyDef plateformBodyDef1;
	//this will be a static body
	plateformBodyDef = plateformBodyDef1;
	plateformBodyDef.type = b2_staticBody;
	this->plateformBodyDef.position.Set(x_position, y_position); //slightly lower position
	 staticplateformBody = nullptr;

}

plateform::plateform() {}
b2PolygonShape plateform::getB2Shape()
{
	return b2plateform;
}

sf::RectangleShape plateform::getShape()
{
	return plateformShape;
}

b2BodyDef plateform::getBodyDef()
{
	return plateformBodyDef;
}

void plateform::setStaticplateformBody(b2Body* body)
{
	staticplateformBody = body;
	

}
plateform::~plateform()
{
}
