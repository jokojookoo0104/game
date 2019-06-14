#include "MapLevel1Scence.h"
#include "../Object/Enemy/SwordMan.h"
#include "../Logging/GameDebugDraw.h"
#include "../HUD/HUD.h"
#include "../Framework/NinjaGaidenScence.h"
#include "../Framework/MCIPlayer.h"
MapLevel1Scence::MapLevel1Scence(): Scence()
{
	this->LoadResource();
}

MapLevel1Scence::~MapLevel1Scence()
{
	delete map;
}

void MapLevel1Scence::LoadResource()
{
	PLAYER->Restart(20, 100.0f);
	name = " STAGE 3-1";
	scenceType = SCENCE::SCENCE_1;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_1, PATH_TEXTURE_MAP_1, ID_TEXTURE_MAP_1);
	CAMERA->setWorldBoundary(2048);
	GRID->ReSetGrid(246, map->GetWidth());
	GRID->LoadGroundAndItem(PATH_POS_GROUND_MAP_1, scenceType);
	GRID->LoadObjects(PATH_POS_ENEMY_MAP_1);
}

void MapLevel1Scence::Update(float deltaTime)
{
	CAMERA->Update();
	GRID->UpdateGrid(PLAYER);
	if (PLAYER->GetAlphaEndPoint() < 255) {
		GRID->UpdatePlayer(deltaTime);
	}
	else {
		GRID->UpdateObject(deltaTime);
	}
	HUD->Update(deltaTime);
	if (time >= 1.0f) {
		this->timer--;
		time = 0;
		PLAYER->MinusFreezeTime();
		if (this->timer <= 0) {
			this->timer = 0;
			PLAYER->SetState(PLAYER_STATE::DIE);
		}
	}
	else {
		time += deltaTime;
	}
	if (PLAYER->GetState() == PLAYER_STATE::DIE) {
		this->timer = 150;
	}
}

void MapLevel1Scence::Render()
{
	HUD->Render();
	Scence::Render();
}