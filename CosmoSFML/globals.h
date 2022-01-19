#ifndef GLOBALS_H
#define GLOBALS_H
#include <SFML/System.hpp>
#define v2f sf::Vector2f
#define NULL_VEC v2f(0.0f, 0.0f);
enum states {
	GAME,
	OPTIONS,
	CREDITS,
	MENU
};

class IMovObject {
public:
	virtual void move(v2f m) {};
	virtual v2f getPosition() = 0;
	virtual void setPosition(v2f n_position) = 0;
	virtual float getRotation() { return rotation; };
	virtual void setRotation(float n_rotation) { rotation = n_rotation; };
	virtual void rotate(float deg) { rotation += deg; };
	float rotation = 0.0f;

};

class IPhysObject : IMovObject {
public:
	v2f gravity_force = NULL_VEC;
	v2f gravity_acceleration = NULL_VEC;
	v2f o_force = NULL_VEC;
	v2f o_acceleration = NULL_VEC;
	float mass = 0.0f;
	v2f movement = NULL_VEC;
	v2f resultant_force = NULL_VEC;
};

class IStaticObject : IMovObject {
	//?
};




#endif GLOBALS_H