#pragma once
#include "Object.h"
class CollisionHandler
{
public:

	CollisionHandler(float collisionTime, float nx, float ny, Object* obj = NULL) {
		this->collisionTime = collisionTime;
		this->nx = nx;
		this->ny = ny;
		this->object = obj;
	}

	static bool Compare(CollisionHandler* a, CollisionHandler *b) {
		return a->collisionTime < b->collisionTime;
	}
private:
	Object* object;
	float collisionTime, nx, ny;

};
