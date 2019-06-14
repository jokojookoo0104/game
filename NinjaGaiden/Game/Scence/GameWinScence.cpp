#include "GameWinScene.h"
#include "../HUD/Text.h"


GameWinScence::GameWinScence() : Scence() {
	this->LoadResource();
}


void GameWinScence::LoadResource() {
	scenceType = SCENCE::SCENCE_WIN;
	CAMERA->setWorldBoundary(100);
	map->LoadMap(PATH_TEXTURE_MAP_GAMEWIN, ID_TEXTURE_MAP_GAMEWIN);
	PLAYER->ResetState();
}


GameWinScence::~GameWinScence()
{
	delete map;
}

void GameWinScence::Update(float deltaTime) {

}
void GameWinScence::Render() {
	Scence::RenderScene(252, 220);
}


