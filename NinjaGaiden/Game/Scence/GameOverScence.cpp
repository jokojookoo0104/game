#include "GameOverScence.h"
#include "../HUD/Text.h"
#include "../Framework/Label.h"


GameOverScence::GameOverScence() : Scence() {
	label = new Label*[1];
	string score = PLAYER->GetScoreString();
	label[1] = new Label();

	label[1]->text = "SCORE ";
	label[1]->color = D3DCOLOR_XRGB(255, 255, 255);
	label[1]->size = 8;
	label[1]->xPos = 110;
	label[1]->yPos = 150;

	this->LoadResource();
}


void GameOverScence::LoadResource() {
	scenceType = SCENCE::SCENCE_OVER;
	CAMERA->setWorldBoundary(100);
	map->LoadMap(PATH_TEXTURE_MAP_GameOver, ID_TEXTURE_MAP_GameOver);
	PLAYER->ResetState();
}


GameOverScence::~GameOverScence()
{
	delete map;
}

void GameOverScence::Update(float deltaTime) {
}
void GameOverScence::Render() {
	Scence::RenderScene(252, 220);
	string score = PLAYER->GetScoreString();
	TEXT->DrawString(score, 5, 2, 230, 10);
}


