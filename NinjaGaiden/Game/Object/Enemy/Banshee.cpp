#include "Banshee.h"
#include "BansheeSword.h"
#include "../Square/Square.h"
#include "../Player/Player.h"
#include "../../Logging/GameDebugDraw.h"
#include "../../Framework/MCIPlayer.h"
Banshee::Banshee() {

}

Banshee::~Banshee() {
	if (this->sprite != NULL) {
		for (auto i = this->sprite->begin(); i != this->sprite->end(); i++) {
			delete i->second;
			this->sprite->erase(i);
		}
		delete this->sprite;
	}
	delete[]sword;
}

Banshee::Banshee(int posX, int posY, vector<int> movingLimit, vector<int> activeArea) {
	this->movingLimit = movingLimit;
	this->activeArea = activeArea;
	for (int i = 0; i < NUMBER_OF_SWORD; i++) {
		sword[i] = new BansheeSword(posX, posY, direction);
	}

	SetObjectType(OBJECT_TYPE::BANSHEE);
	direction = direction;
	SetPosition((float)posX, (float)posY);
	isOnGround = false;
	timerSkill = 0;
	timerThrow = 0;
	countThrow = 0;
	GotoStateFollow();
	this->score = 300;
	InitSpite();
}

void Banshee::InitSpite() {
	sprite = new  map<ENEMY_STATE, Sprite*>();
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::FOLLOW,
		new Sprite(TEXTURE->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_BANSHEE_FOLLOW, 2, 0.09f)));
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::ATK,
		new Sprite(TEXTURE->Get(ID_TEXTURE_MAP_1_ENEMY), PATH_TEXTURE_MAP_1_ENEMY_BANSHEE_ATK, 2, 0.09f)));
	sprite->insert(pair<ENEMY_STATE, Sprite*>(ENEMY_STATE::DEAD,
		new Sprite(TEXTURE->Get(ID_TEXTURE_MAP_1_ENEMY_DIE_FIRE), PATH_TEXTURE_MAP_1_ENEMY_ENEMY_DIE, 3, 0.03f)));
}
void Banshee::Update(float t, vector<Object*>* objects) {
	if (PLAYER->isFreezeTime()) {
		SetVeclocity(0, 0);
		Object::Update(t);
		isActive = false;
		//HandleCollision(objects);
		return;
	}
	if (isActive) {
		Object::Update(t);
		RECT rect = sprite->at(state)->GetBoudingBoxFromCurrentSprite();
		Object::updateBoundingBox(rect);
		sprite->at(state)->NextSprite(t);
		if (state == ENEMY_STATE::DEAD) {
			if (sprite->at(state)->GetIsComplete()) {
				sprite->at(state)->Reset();
				sprite->at(this->state)->SetScale(1.0f);
				isActive = false;
				for (int i = 0; i < NUMBER_OF_SWORD; i++) {
					sword[i]->SetState(ENEMY_STATE::INVISIBLE);
				}
			}
		}
		else {
			HandleCollision(objects);
			HandleDirection();
			HandleAttack(t);

			if (!isOnGround) {
				veclocity.y += GRAVITY * t;
			}
			else {
				SetVy(0);
			}
			PlusPosition(deltaX, deltaY);
			PLAYER->KillEnemy(this);
		}
	}

	if (!PLAYER->isFreezeTime()) {
		for (int i = 0; i < NUMBER_OF_SWORD; i++) {
			sword[i]->Update(t, objects);
			sword[i]->UpdateWitchPosition(position);
		}
	}
}

void Banshee::HandleCollision(vector<Object*> *objects) {
	vector<CollisionHandler*>* coEvents = new vector<CollisionHandler*>();
	vector<CollisionHandler*>* coEventsResult = new vector<CollisionHandler*>();
	coEvents->clear();
	if (isActive) {
		Object::CalcPotentialCollisions(objects, coEvents);
	}
	if (coEvents->size() == 0) {
		Object::PlusPosition(this->deltaX, this->deltaY);
	}
	else {
		if (coEvents->size() != 0) {
			float min_tx, min_ty, nx = 0, ny;
			FilterCollision(coEvents, coEventsResult, min_tx, min_ty, nx, ny);
			for (UINT i = 0; i < coEventsResult->size(); i++) {
				CollisionHandler* e = coEventsResult->at(i);
				if (e->object->GetObjectType() == OBJECT_TYPE::SQUARE) {
					if (e->ny < 0) {
						isOnGround = true;
					}
				}
				else if (e->object->GetObjectType() == OBJECT_TYPE::MAIN_CHARACTER) {
					if (!PLAYER->GetWounded()) {
						if (PLAYER->GetState() == JUMP_ATK) {
							state = ENEMY_STATE::DEAD;
							MCIPLAYER->Play(SOUND_ENEMY_DIE);
							PLAYER->AddScore(score);
						}
						else {
							PLAYER->Wounded(e->nx, e->ny, this, direction);
						}
					}
				}
			}
		}
	}
	for (UINT i = 0; i < coEvents->size(); i++) {
		delete coEvents->at(i);
	}
	coEventsResult->clear();
	coEvents->clear();
	delete coEvents;
	delete coEventsResult;
}

void Banshee::HandleDirection(){
	float boxWidth = GetBoundingBox().right - GetBoundingBox().left;

	if (position.x <= movingLimit.at(0)) {
		SetVx(WITCH_VX);
	}

	if (position.x + boxWidth >= movingLimit.at(1)) {
		SetVx(-WITCH_VX);
	}

	if (state != ENEMY_STATE::ATK) {
		if (PLAYER->GetPosition().x >= activeArea.at(0)
			&& PLAYER->GetPosition().x <= activeArea.at(1)) {
			if (PLAYER->GetPosition().x <= position.x) {
				direction = DIRECTION::LEFT;
			}
			else {
				direction = DIRECTION::RIGHT;
			}
		}
	}
}

void Banshee::HandleAttack(float t) {
	if (state != ATK) {
		if (countThrow < 3) {
			if (timerThrow >= THROW_DELAY_TIME) {
				state = ENEMY_STATE::ATK;
				veclocity.x = 0;
				switch (countThrow)
				{
				case 0:
					sword[0]->Fly(70, direction);
					countThrow++;
					break;
				case 1:
					sword[1]->Fly(100, direction);
					countThrow++;
					break;
				case 2:
					sword[2]->Fly(-10, direction);
					countThrow++;
					break;
				default:
					break;
				}
				timerThrow = 0;
			}
			else {
				timerThrow += t;
			}
		}
		else {
			if (timerThrow >= THROW_DELAY_TIME) {
				if (timerSkill >= SKILL_DELAY_TIME) {
					state = ENEMY_STATE::ATK;
					veclocity.x = 0;
					switch (countThrow)
					{
					case 3:
						sword[0]->Fly(70, direction);
						countThrow++;
						break;
					case 4:
						sword[1]->Fly(100, direction);
						countThrow++;
						break;
					case 5:
						sword[2]->Fly(-10, direction);
						countThrow = 0;
						timerThrow = 0;
						break;
					default:
						break;
					}
					timerSkill = 0;
				}
				else {
					timerSkill += t;
				}
			}
			else {
				timerThrow += t;
			}
		}
	}
	else {
		if (sprite->at(state)->GetIsComplete()) {
			sprite->at(state)->Reset();
			this->GotoStateFollow();
		}
	}
}

void Banshee::Dead() {
	MCIPLAYER->Play(SOUND_ENEMY_DIE);
	state = ENEMY_STATE::DEAD;
	SetVeclocity(0.0f, 0.0f);
	//Object::PlusPosition(0, -3.0f);
}

void Banshee::GotoStateFollow() {
	state = ENEMY_STATE::FOLLOW;
	if (direction == DIRECTION::LEFT) {
		SetVeclocity(-WITCH_VX, 0);
	}
	else {
		SetVeclocity(WITCH_VX, 0);
	}
}

void Banshee::Render() {
	if (isActive && !PLAYER->isFreezeTime()) {
		switch (direction) {
		case RIGHT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(this->state)->SetScale(sprite->at(this->state)->GetScale() + 0.015f);
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true, -9, 0);
			}
			else {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), true);
			}
			break;
		case LEFT:
			if (state == ENEMY_STATE::DEAD) {
				sprite->at(this->state)->SetScale(sprite->at(this->state)->GetScale() + 0.015f);
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false, -9, 0);
			}
			else {
				sprite->at(this->state)->DrawSprite(Object::GetTransformObjectPositionByCamera(), false);
			}
			break;
		default:
			break;
		}
	}
	if (!PLAYER->isFreezeTime()) {
		for (int i = 0; i < NUMBER_OF_SWORD; i++) {
			sword[i]->Render();
		}
	}
}

void Banshee::ResetState() {
	isActive = true;
	isOnGround = false;
	if (state == ENEMY_STATE::DEAD) {
		sprite->at(ENEMY_STATE::DEAD)->Reset();
		sprite->at(this->state)->SetScale(1.0f);
	}
	GotoStateFollow();
	SetPosition(lastPos.x, lastPos.y);
	for (int i = 0; i < NUMBER_OF_SWORD; i++) {
		sword[i]->SetState(ENEMY_STATE::INVISIBLE);
	}
}