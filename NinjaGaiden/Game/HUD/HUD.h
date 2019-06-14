#pragma once
#include "../Framework/Sprite.h"
#include "../Framework/Constants.h"
class Hud {
private:
	static Hud* _instance;
	Sprite* healthPlayer;
	Sprite*  healthBoss;
	Sprite*	box;
	Sprite* item;
	Sprite* lifePoint;
	Sprite* skill;
public:
	Hud();
	~Hud();
	static Hud* GetInstance() {
		if (_instance == NULL) {
			_instance = new Hud();
		}
		return _instance;
	}
	void Update(float t);
	void Render(int hpBoss = 16);
	void SetSkill(Sprite* skill);
};