#include <platformer_character.h>
#include <iostream>

PlatformerCharacter::PlatformerCharacter(b2World & world)
{
	//Create the rectangle
	rect.setPosition(center_position - size / 2.f);
	rect.setSize(size);
	rect.setFillColor(sf::Color::Green);
	//Create the body
	b2BodyDef myBodyDef;
	myBodyDef.type = b2_dynamicBody;
	myBodyDef.position = pixel2meter(center_position);
	myBodyDef.fixedRotation = true;
	body = world.CreateBody(&myBodyDef);

	//Create the fixtures
	b2FixtureDef box;
	b2PolygonShape box_shape;
	box_shape.SetAsBox(
		pixel2meter(size.x) / 2.f, pixel2meter(size.y) / 2.f);
	box.shape = &box_shape;
	box.friction = 0.f;

	b2FixtureDef foot;
	b2PolygonShape foot_shape;
	foot.isSensor = true;
	foot_shape.SetAsBox(
		pixel2meter(size.x-4.f) / 2.f, pixel2meter(2.0f) / 2.f,
		b2Vec2(0.f, pixel2meter(size.y)/2), 
		0.f);
	foot.shape = &foot_shape;
	contactData.contactDataType = ContactDataType::PLATFORM_CHARACTER_GROUND;
	contactData.data = this;
	foot.userData = &contactData;

	// TEST IF RIGHT WALL
	b2FixtureDef left_side;
	b2PolygonShape left_side_shape;
	left_side.isSensor = true;
	left_side_shape.SetAsBox(
		pixel2meter(2.f) /2, pixel2meter(size.y-4.f) / 2.f, // Taille)
		b2Vec2(-pixel2meter(size.x) / 2, 0), //Position (A partir du centre)
		0.f); //Angle
	left_side.shape = &left_side_shape;
	contactDataLeftWall.contactDataType = ContactDataType::PLATFORM_CHARACTER_LEFT_WALL;
	contactDataLeftWall.data = this;
	left_side.userData = &contactDataLeftWall;

	b2FixtureDef right_side;
	b2PolygonShape right_side_shape;
	right_side.isSensor = true;
	right_side_shape.SetAsBox(
		pixel2meter(2.f) / 2, pixel2meter(size.y - 4.f) / 2.f, // Taille)
		b2Vec2(pixel2meter(size.x) / 2, 0), //Position (A partir du centre)
		0.f); //Angle
	right_side.shape = &right_side_shape;
	contactDataRightWall.contactDataType = ContactDataType::PLATFORM_CHARACTER_RIGHT_WALL;
	contactDataRightWall.data = this;
	right_side.userData = &contactDataRightWall;

	body->CreateFixture(&box);
	body->CreateFixture(&foot);
	body->CreateFixture(&left_side);
	body->CreateFixture(&right_side);
}

PlatformerCharacter::~PlatformerCharacter()
{
}

void PlatformerCharacter::update(float move_axis, bool jump_button)
{
	//manage movements
	body->SetLinearVelocity(b2Vec2(walk_speed*move_axis, body->GetLinearVelocity().y));
	if (foot > 0 && jump_button)
	{
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, -jump_speed));
	}

	if( wall > 0 && foot == 0 && jump_button)
	{
		if(isTouchingLeftWall)
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x + wall_jump_speed, -jump_speed));
		else
			body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x - wall_jump_speed, -jump_speed));
	}

	center_position = meter2pixel(body->GetPosition());
	rect.setPosition(center_position - size / 2.f);
}

void PlatformerCharacter::draw(sf::RenderWindow& window)
{
	window.draw(rect);
}

void PlatformerCharacter::touch_ground()
{
	foot++;
}

void PlatformerCharacter::leave_ground()
{
	foot--;
}

void PlatformerCharacter::touch_wall(bool isLeftSide)
{
	wall++;
	isLeftSide ? isTouchingLeftWall = true: isTouchingLeftWall = false;
}

void PlatformerCharacter::leave_wall()
{
	wall--;
}


