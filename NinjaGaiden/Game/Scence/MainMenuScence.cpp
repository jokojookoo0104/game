#include "MainMenuScence.h"
#include "../HUD/Text.h"


MainMenuScence::MainMenuScence() : Scence() {
	this->LoadResource();
}


void MainMenuScence::LoadResource() {
	scenceType = SCENCE::SCENCE_MENU;
	CAMERA->setWorldBoundary(100);
	map->LoadMap(PATH_TEXTURE_MAP_MENU, ID_TEXTURE_MAP_MENU);
	//img.Add(114, PATH_TEXTURE_BUTTON);
	//this->texture = img.Get(114);
	/*TEXTURE->Add(ID_TEXTURE_MAP_MENU, PATH_TEXTURE_MAP_MENU);
	this->texture = TEXTURE->Get(ID_TEXTURE_MAP_MENU);*/
	PLAYER->ResetState();
}


MainMenuScence::~MainMenuScence()
{
	delete map;
}

void MainMenuScence::Update(float deltaTime) {

}
void MainMenuScence::Render() {
	Scence::RenderScene(252,220);
	//GAME->Draw(120, 80, texture, 0, 0, 120, 80, D3DCOLOR_XRGB(255, 255, 255));

}


