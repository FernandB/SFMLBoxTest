#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#ifndef PLATEFORM_H
#define PLATEFORM_H
class plateform
{
private:
	b2BodyDef plateformBodyDef;
	b2Body* staticplateformBody;
	b2PolygonShape b2plateform;
	sf::RectangleShape plateformShape;
	float y_position;
	float x_position;
	float height;
	float width;
public:
	plateform(float, float, float, float, b2PolygonShape,sf::RectangleShape);
	plateform();
	b2BodyDef getBodyDef();
	b2PolygonShape getB2Shape();
	sf::RectangleShape getShape();
    void setStaticplateformBody(b2Body*);
	~plateform();
};

#endif