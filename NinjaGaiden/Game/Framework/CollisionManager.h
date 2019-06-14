#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "Texture.h"
#include "Sprite.h"

class CollisionManager
{
private:
	static CollisionManager * _instance;
public:
	static CollisionManager* getInstance() {
		if (_instance == NULL) _instance = new CollisionManager();
		return _instance;
	};
	bool AABB(RECT r1, RECT r2);
	void SweptAABB(
		float ml, float mt, float mr, float mb,
		float dx, float dy,
		float sl, float st, float sr, float sb,
		float &t, float &nx, float &ny);
	CollisionManager();
	~CollisionManager();
};
