#include "MapLevel3Scence.h"
#include "../HUD/HUD.h"
MapLevel3Scence::MapLevel3Scence() : Scence()
{
	this->LoadResource();
}

MapLevel3Scence::~MapLevel3Scence()
{
	delete map;
	delete boss;
}

void MapLevel3Scence::LoadResource()
{
	PLAYER->Restart(125, 130);
	name = " STAGE 3-3";
	scenceType = SCENCE::SCENCE_3;
	timer = 150;
	map->LoadMap(PATH_POS_MAP_3, PATH_TEXTURE_MAP_3, ID_TEXTURE_MAP_3);
	CAMERA->setWorldBoundary(256);
	GRID->ReSetGrid(246, map->GetWidth());
	GRID->LoadGroundAndItem(PATH_POS_GROUND_MAP_3, scenceType);
	boss = new Boss();
	GRID->Add(boss);
	remainTime = 1.0f;
}

void MapLevel3Scence::Update(float deltaTime)
{
	if (boss->GetHp() == 0) {
		remainTime = 0.05f;
	}

	if (PLAYER->GetState() == PLAYER_STATE::DIE
		&& PLAYER->GetLifePoint() < 0) {
		return;
	}
	CAMERA->Update();
	GRID->UpdateGrid(PLAYER);
	GRID->UpdateObject(deltaTime);
	HUD->Update(deltaTime);
	
	if (time >= remainTime) {
		if (boss->GetHp() == 0 && this->timer > 0) {
			PLAYER->AddScore(200);
		}
		this->timer--;
		time = 0;
		if (this->timer <= 0) {
			this->timer = 0;
			PLAYER->SetState(PLAYER_STATE::WIN);
			if (boss->GetHp() > 0) {
				PLAYER->SetState(PLAYER_STATE::DIE);
			}
		}
	}
	else {
		time += deltaTime;
	}
	if (PLAYER->GetState() == PLAYER_STATE::DIE) {
		this->timer = 150;
	}
}

void MapLevel3Scence::Render()
{
	HUD->Render(boss->GetHp());
	Scence::Render();
}