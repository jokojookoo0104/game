#include "HUD.h"
#include "../Object/Player/Player.h"

Hud* Hud::_instance = NULL;
Hud::Hud() {
	healthPlayer = new Sprite(TEXTURE->Get(HEALTH_ID), L"resource\\HUD\\health.txt", 2, 0.0f, 0.5f);
	healthBoss = new Sprite(TEXTURE->Get(HEALTH_ID), L"resource\\HUD\\health.txt", 2, 0.0f, 0.5f);
	box = new Sprite(TEXTURE->Get(BOX_ID), L"resource\\HUD\\box.txt", 1, 0.0f);
	lifePoint = new Sprite(TEXTURE->Get(POINT_ID), L"resource\\HUD\\point.txt", 2, 0.0f, 0.475f);
}

Hud::~Hud() {
	delete healthBoss;
	delete healthPlayer;
	delete box;
	delete item;
}

void Hud::Update(float t) {
	if(PLAYER->GetState() == PLAYER_STATE::DIE) {
		this->skill = NULL;
	}
}

void Hud::Render(int hpBoss) {
	box->DrawSprite(D3DXVECTOR3(57.0f, 3.0f, 0.0f), false, 0.35f, 0.45f);
	for (int i = 0; i < 16; i++) {
		if (i < PLAYER->GetHp()) {
			healthPlayer->SetIndex(0);
		}
		else {
			healthPlayer->SetIndex(1);
		}
		if (i < hpBoss) {
			healthBoss->SetIndex(0);
		}
		else {
			healthBoss->SetIndex(1);
		}
		float temp = 155 + i * 5;
		healthPlayer->DrawSprite(D3DXVECTOR3(temp, 6.0f, 0.0f), false);
		healthBoss->DrawSprite(D3DXVECTOR3(temp, 16.0f, 0.0f), false);
	}
	lifePoint->DrawSprite(D3DXVECTOR3(57.0f, 16.0f, 0.0f), false);

	if (skill != NULL)
		skill->DrawSprite(D3DXVECTOR3(82.0f, 14.5f, 0.0f), false);
}

void Hud::SetSkill(Sprite* skill) {
	this->skill = skill;
}