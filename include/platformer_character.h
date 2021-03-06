#ifndef PLATFORMER_CHAR_H
#define PLATFORMER_CHAR_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <utility.h>

class PlatformerCharacter
{
public:
	PlatformerCharacter(b2World&);
	~PlatformerCharacter();
	void update(float move_axis, bool jump_button);
	void draw(sf::RenderWindow&);
	void touch_ground();
	void leave_ground();
	void touch_wall(bool isLeftSide);
	void leave_wall();
private:
	int foot = 0;
	int wall = 0;
	bool isTouchingLeftWall = true;
	b2Body* body;
	sf::RectangleShape rect;
	sf::Vector2f center_position = sf::Vector2f(400.f, 300.f);
	sf::Vector2f size = sf::Vector2f(64.f,64.f);
	const float walk_speed = 5.0f;
	const float jump_speed = 10.f;
	const float wall_jump_speed = 25.f;
	ContactData contactData;
	ContactData contactDataLeftWall;
	ContactData contactDataRightWall;
};

#endif // !PLATFORMER_CHAR_H
