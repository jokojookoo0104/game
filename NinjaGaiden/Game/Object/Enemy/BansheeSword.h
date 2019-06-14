#pragma once
#include "../../Framework/Object.h"
#include "../../Framework/Sprite.h"
#include <map>

#define WITCH_SWORD_VY 300.0f
class BansheeSword :public Object {
private:
	map<ENEMY_STATE, Sprite*>* sprite;
	ENEMY_STATE state;
	DIRECTION direction;
	D3DXVECTOR3 witchPosition;
	int countThrow;
public:
	BansheeSword(int positionX, int positionY, DIRECTION direction);
	~BansheeSword();
	void Update(float t, vector<Object*>* objects);
	void UpdateWitchPosition(D3DXVECTOR3 witchPosition);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void Fly(int vX, DIRECTION direction);
	void Dead();
	void SetState(ENEMY_STATE state);
};