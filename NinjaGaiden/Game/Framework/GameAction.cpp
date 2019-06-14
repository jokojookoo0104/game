#include "GameAction.h"
#include "GameTime.h"
#include "MCIPlayer.h"
#define MAX_FRAME_RATE 170
GameAction *GameAction::_instance = NULL;

GameAction::GameAction(HINSTANCE hInstance, int nShowCmd)
{
	Graphic *graphic = Graphic::GetInstance(hInstance, nShowCmd, GAME_TITLE, GAME_SCREEN_320_240);
	Game *game = GAME;
	game->Init(graphic->GetHWnd());
	this->keyHandler = new KeyboardHandler();
	game->InitKeyboard(this->keyHandler);
	World *world = WORLD;
	world->LoadResource();
	GameTime* gameTime = GAMETIME;
}

int GameAction::GameRun()
{
	MSG msg;
	int done = 0;
	float tickPerFrame = 1.0f / MAX_FRAME_RATE, delta = 0;

	while (!done) {
		GAMETIME->StartCounter();
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		delta += GAMETIME->GetCouter();
		if (delta >= tickPerFrame)
		{
			GAME->ProcessKeyboard();
			this->Update(delta);
			this->Render();
			delta = 0;
		}
		else {
			Sleep(tickPerFrame - delta);
			delta = tickPerFrame;
		}
	}
	return 1;
}

void GameAction::Update(float dt)
{
	WORLD->Update(dt);
}

void GameAction::Render()
{
	LPDIRECT3DDEVICE9 d3ddv = GAME->GetDirect3DDevice();
	if (d3ddv->BeginScene()) {
		d3ddv->ColorFill(GAME->GetBackBuffer(), NULL, D3DCOLOR_XRGB(0, 0, 0));
		GAME->GetSpriteHandler()->Begin(D3DXSPRITE_ALPHABLEND);
		WORLD->Render();
		GAME->GetSpriteHandler()->End();
		d3ddv->EndScene();
	}
	d3ddv->Present(NULL, NULL, NULL, NULL);
}