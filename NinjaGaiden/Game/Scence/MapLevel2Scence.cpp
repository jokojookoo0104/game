#include "MapLevel2Scence.h"
#include "../HUD/HUD.h"
#include "../Framework/World.h"
MapLevel2Scence::MapLevel2Scence() : Scence()
{
	this->LoadResource();
}

MapLevel2Scence::~MapLevel2Scence()
{
	delete map;
}

void MapLevel2Scence::LoadResource()
{
	PLAYER->Restart(2815, 0);
	name = " STAGE 3-2";
	scenceType = SCENCE::SCENCE_2;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_2, PATH_TEXTURE_MAP_2, ID_TEXTURE_MAP_2);
	CAMERA->setWorldBoundary(3072);
	GRID->ReSetGrid(246, map->GetWidth());
	GRID->LoadGroundAndItem(PATH_POS_GROUND_MAP_2, scenceType);
	GRID->LoadObjects(PATH_POS_ENEMY_MAP_2);
}

void MapLevel2Scence::Update(float deltaTime)
{
	Scence::Update(deltaTime);
}

void MapLevel2Scence::Render()
{
	HUD->Render();
	Scence::Render();
}