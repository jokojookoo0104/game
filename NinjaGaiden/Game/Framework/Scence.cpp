#include "Scence.h"
#include "../Object/Player/Player.h"
#include "../HUD/Text.h"
#include <iomanip> 
#include "../HUD/HUD.h"
Scence::Scence()
{
	this->map = new Map();
	this->timer = 0;
	this->name = "";
}

Scence::~Scence()
{
	delete map;
}

void Scence::Update(float deltaTime)
{
	if (PLAYER->GetState() == PLAYER_STATE::DIE
		&& PLAYER->GetLifePoint() < 0) {
		return;
	}
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

void Scence::RenderText() {
	// Đếm thời gian
	std::stringstream timer;
	timer << std::setw(3) << std::setfill('0') << this->timer;
	//Mạng người chơi
	int temp = PLAYER->GetLifePoint();
	if (temp == -1) temp = 0;
	std::stringstream lifePoint;
	lifePoint << std::setw(2) << std::setfill('0') << temp;
	//Điểm của người chơi
	string score = "SCORE - " + PLAYER->GetScoreString() + " ";
	//Item point
	std::stringstream itemPoint;
	int item = PLAYER->GetItemPoint();
	itemPoint << std::setw(2) << std::setfill('0') << item;
	
	//Vẽ text
	TEXT->DrawString(score+"   "+name, 5, 2, 230, 10);
	TEXT->DrawString("TIMER - " + timer.str(), 5, 12, 150, 10);
	TEXT->DrawString("P-" + lifePoint.str(), 5, 22, 50, 10);
	TEXT->DrawString(itemPoint.str(), 45, 22, 20, 10);
	TEXT->DrawString("Ninja-", 119, 12, 50, 10);
	TEXT->DrawString("Enemy-", 119, 22, 50, 10);
}

void Scence::Render()
{
	RenderText();
	if (map) {
		map->drawMap(PLAYER->GetAlphaEndPoint());
	}
	GRID->RenderObject();
}

void Scence::RenderScene(int w,int h)
{
	if (map) {
		map->drawScence(w,h);
	}
}

SCENCE Scence::GetScenceType() {
	return scenceType;
}
