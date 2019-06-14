#pragma once
#include "../Framework/Texture.h"
#include "../Framework/Sprite.h"
#include "../Framework/Game.h"
#include "../Framework/Grid.h"
#include "../Object/Player/Player.h"
#include "../Framework/Constants.h"
#include "../Framework/Map.h"
#include "../Object/Square/Square.h"
#include "../Framework/Scence.h"
#include "../Object/Boss/Boss.h"
class MapLevel3Scence : public Scence {
private:
	Boss* boss;
	float remainTime;
public:
	MapLevel3Scence();
	~MapLevel3Scence();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
};