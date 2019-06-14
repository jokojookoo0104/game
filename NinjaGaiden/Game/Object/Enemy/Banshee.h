#pragma once
#include "../../Framework/Object.h"
#include "../../Framework/Sprite.h"
#include "BansheeSword.h"
#include <map>

#define THROW_DELAY_TIME 1.5
#define SKILL_DELAY_TIME 0.3
#define NUMBER_OF_SWORD 3
#define WITCH_VX 30.0f
class Banshee :public Object {
private:
	vector<int> movingLimit;
	vector<int> activeArea;

	BansheeSword* sword[NUMBER_OF_SWORD];
	map<ENEMY_STATE, Sprite*>* sprite;
	RECT movingArea;
	ENEMY_STATE state;
	DIRECTION direction;
	float timerThrow;
	float timerSkill;
	int countThrow;
	bool isOnGround;
	void InitSpite();
	void HandleDirection();
	void HandleAttack(float t);
public:
	Banshee();
	Banshee(int posX, int posY, vector<int> movingLimit, vector<int> activeArea);
	~Banshee();
	void Update(float t, vector<Object*>* objects);
	void Render();
	void HandleCollision(vector<Object*> *object);
	void ResetState();
	void Dead();
	void GotoStateFollow();
};