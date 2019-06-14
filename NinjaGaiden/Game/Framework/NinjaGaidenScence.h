#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Object.h"
#include "Texture.h"
#include "Sprite.h"
#include "Game.h"
#include "../Object/Player/Player.h"
#include "Camera.h"
#include "Scence.h"
class NinjaGaidenScence
{
private:
	static NinjaGaidenScence * _instance;
	Scence* scence;
public:
	NinjaGaidenScence();
	~NinjaGaidenScence();
	//Khởi tạo texture, object, map, Player
	void LoadResource();
	void Update(float deltaTime);
	void Render();
	void ReplaceScence(SCENCE scenceType);
	void SetScence(Scence* s);
	SCENCE GetScence();
	static NinjaGaidenScence* GetInstance() {
		if (_instance == NULL) _instance = new NinjaGaidenScence();
		return _instance;
	}
};

