#pragma once
#include "../Framework/Scence.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "../Framework/Object.h"
#include "../Framework/Texture.h"
#include "../Framework/Sprite.h"
#include "../Framework/Game.h"
#include "../Framework/Grid.h"
#include "../Object/Player/Player.h"
#include "../Framework/Constants.h"
#include "../Framework/Map.h"
#include "../Object/Square/Square.h"
class GameWinScence : public Scence {
public:
	Texture* pBackGround;
	GameWinScence();
	~GameWinScence();
	void LoadResource();
	void Render();
	void Update(float deltaTime);
private:
	LPDIRECT3DTEXTURE9 texture;
};

