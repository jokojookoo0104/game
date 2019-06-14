﻿#pragma once
#include "../Framework/Scence.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../Framework/Object.h"
#include "../Framework/Texture.h"
#include "../Framework/Sprite.h"
#include "../Framework/Game.h"
#include "../Framework/Grid.h"
#include "../Object/Player/Player.h"
#include "../Framework/Constants.h"
#include "../Framework/Map.h"
#include "../Object/Square/Square.h"
class MapLevel1Scence : public Scence {
public:
	MapLevel1Scence();
	~MapLevel1Scence();
	void LoadResource();
	void Update(float deltaTime);
	void Render();
};