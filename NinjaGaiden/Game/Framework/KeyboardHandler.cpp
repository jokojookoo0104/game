#include "GameTime.h"
#include "MCIPlayer.h"
#include "KeyboardHandler.h"

void KeyboardHandler::KeyState(BYTE * states)
{

}

void KeyboardHandler::OnKeyDown(int KeyCode)
{
	/*DebugOut((wchar_t *)L"[GameAction.cpp][KEYBOARD] KeyDown: %d\n", KeyCode);*/
	if (PLAYER->GetState() != PLAYER_STATE::DIE && PLAYER->GetAlphaEndPoint() == 255) {
		if (PLAYER->GetState() == PLAYER_STATE::JUMP) {
			if (PLAYER->GetIsJumpClimb()) {
				if (PLAYER->GetDirectionClimb() == DIRECTION::LEFT) {
					if (GAME->IsKeyDown(DIK_RIGHT)) {
						PLAYER->SetAcceleratorX(20.0f);
						PLAYER->SetDirection(DIRECTION::RIGHT);
					}
					else {
						if (GAME->IsKeyDown(DIK_LEFT)) {
							PLAYER->SetAcceleratorX(-5.0f);
							PLAYER->SetDirection(DIRECTION::LEFT);
						}
					}
				}
				else {
					if (PLAYER->GetDirectionClimb() == DIRECTION::RIGHT) {
						if (GAME->IsKeyDown(DIK_LEFT)) {
							PLAYER->SetAcceleratorX(-20.0f);
							PLAYER->SetDirection(DIRECTION::LEFT);
						}
						else {
							if (GAME->IsKeyDown(DIK_RIGHT)) {
								PLAYER->SetAcceleratorX(5.0f);
								PLAYER->SetDirection(DIRECTION::RIGHT);
							}
						}
					}
				}
			}
			else {
				if (GAME->IsKeyDown(DIK_LEFT)) {
					PLAYER->SetAcceleratorX(-20.0f);
					PLAYER->SetDirection(DIRECTION::LEFT);
				}
				if (GAME->IsKeyDown(DIK_RIGHT)) {
					PLAYER->SetAcceleratorX(20.0f);
					PLAYER->SetDirection(DIRECTION::RIGHT);
				}
			}

			if (GAME->IsKeyDown(DIK_UP)) {
				if (KeyCode == DIK_Z) {
					PLAYER->SetState(PLAYER_STATE::JUMP_ATK);
					if (PLAYER->GetAcceleratorX() != 0) {
						if (PLAYER->GetDirection() == DIRECTION::RIGHT) {
							PLAYER->SetVx(100.0f);
						}
						else {
							PLAYER->SetVx(-100.0f);
						}
					}
					PLAYER->SetAcceleratorX(0.0f);
					MCIPLAYER->Play(SOUND_ATK);
				}
			}
			else {
				if (KeyCode == DIK_Z) {
					PLAYER->SetState(PLAYER_STATE::STAND_ATK);
					if (PLAYER->GetAcceleratorX() != 0) {
						if (PLAYER->GetDirection() == DIRECTION::RIGHT) {
							PLAYER->SetVx(80.0f);
						}
						else {
							PLAYER->SetVx(-80.0f);
						}
					}
					PLAYER->SetAcceleratorX(0.0f);
					MCIPLAYER->Play(SOUND_ATK);
				}
			}
			if (KeyCode == DIK_C) {
				PLAYER->SetState(PLAYER_STATE::USE_WEAPON);
				PLAYER->UseWeapon();
				PLAYER->SetAcceleratorX(0.0f);
				PLAYER->SetVx(0.0f);
			}
		}

		if (GAME->IsKeyDown(DIK_UP)) {
			if (PLAYER->GetState() == PLAYER_STATE::CLIMB) {
				PLAYER->SetVeclocity(NO_VELOCITY, -50);
				PLAYER->SetClimbMoving(true);
			}
		}

		if (GAME->IsKeyDown(DIK_DOWN)) {
			if (PLAYER->GetState() == PLAYER_STATE::STAND
				&& PLAYER->GetOnGround()) {
				PLAYER->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				PLAYER->SetState(PLAYER_STATE::SIT);
			}
			if (PLAYER->GetState() == PLAYER_STATE::CLIMB) {
				PLAYER->SetVeclocity(NO_VELOCITY, 50);
				PLAYER->SetClimbMoving(true);
			}
		}

		if (PLAYER->GetLastState() == PLAYER_STATE::SIT) {
			if (KeyCode == DIK_Z && GAME->IsKeyDown(DIK_DOWN)) {
				PLAYER->SetState(PLAYER_STATE::SIT_ATK);
				MCIPLAYER->Play(SOUND_ATK);
			}
		}

		if (PLAYER->GetState() == PLAYER_STATE::STAND) {
			if (GAME->IsKeyDown(DIK_LEFT)) {
				PLAYER->SetAcceleratorX(-25.0f);
				PLAYER->SetDirection(DIRECTION::LEFT);
				PLAYER->SetState(PLAYER_STATE::RUN);
			}
			if (GAME->IsKeyDown(DIK_RIGHT)) {
				PLAYER->SetAcceleratorX(25.0f);
				PLAYER->SetDirection(DIRECTION::RIGHT);
				PLAYER->SetState(PLAYER_STATE::RUN);
			}
			if (KeyCode == DIK_Z) {
				PLAYER->SetState(PLAYER_STATE::STAND_ATK);
				MCIPLAYER->Play(SOUND_ATK);
				PLAYER->SetVx(0.0f);
				PLAYER->SetAcceleratorX(0.0f);
			}
			if (KeyCode == DIK_X) {
				if (PLAYER->GetOnGround()) {
					PLAYER->SetState(PLAYER_STATE::JUMP);
					PLAYER->SetVy(-PLAYER_VELOCITY_Y);
					PLAYER->SetOnGround(false);
					MCIPLAYER->Play(SOUND_JUMP);
				}
			}
			if (KeyCode == DIK_C) {
				PLAYER->SetState(PLAYER_STATE::USE_WEAPON);
				PLAYER->UseWeapon();
				PLAYER->SetAcceleratorX(0.0f);
				PLAYER->SetVx(0.0f);
			}
		}

		if (PLAYER->GetState() == PLAYER_STATE::RUN) {
			if (KeyCode == DIK_X) {
				PLAYER->SetState(PLAYER_STATE::JUMP);
				PLAYER->SetVy(-PLAYER_VELOCITY_Y);
				PLAYER->SetOnGround(false);
				MCIPLAYER->Play(SOUND_JUMP);
			}
		}

		if (PLAYER->GetState() == PLAYER_STATE::USE_WEAPON) {
			if (KeyCode == DIK_X) {
				if (PLAYER->GetOnGround()) {
					PLAYER->SetState(PLAYER_STATE::JUMP);
					PLAYER->SetVy(-PLAYER_VELOCITY_Y);
					PLAYER->SetOnGround(false);
					MCIPLAYER->Play(SOUND_JUMP);
				}
			}
		}

		if (PLAYER->GetState() == PLAYER_STATE::CLIMB) {
			if (GAME->IsKeyDown(DIK_LEFT)) {
				if (KeyCode == DIK_X) {
					PLAYER->JumpClimb(DIK_LEFT);
				}
			}
			if (GAME->IsKeyDown(DIK_RIGHT)) {
				if (KeyCode == DIK_X) {
					PLAYER->JumpClimb(DIK_RIGHT);
				}
			}
		}
	}
}

void KeyboardHandler::OnKeyUp(int KeyCode)
{
	if (PLAYER->GetAlphaEndPoint() == 255
		&& PLAYER->GetState() != PLAYER_STATE::DIE
		&& PLAYER->GetState() != PLAYER_STATE::CLIMB) {
		if (KeyCode == DIK_1) {
			WORLD->ReplaceScence(SCENCE::SCENCE_1);
		}
		if (KeyCode == DIK_2) {
			WORLD->ReplaceScence(SCENCE::SCENCE_2);
		}
		if (KeyCode == DIK_3) {
			WORLD->ReplaceScence(SCENCE::SCENCE_3);
		}
	}

	if (WORLD->GetScence() == SCENCE::SCENCE_MENU)
	{
		if (KeyCode == DIK_RETURN) {
			WORLD->ReplaceScence(SCENCE::SCENCE_1);
		}
	}
	if (WORLD->GetScence() == SCENCE::SCENCE_OVER || WORLD->GetScence() == SCENCE::SCENCE_WIN)
	{
		if (KeyCode == DIK_RETURN) {
			WORLD->ReplaceScence(SCENCE::SCENCE_MENU);
		}
	}

	if (PLAYER->GetState() != PLAYER_STATE::DIE &&  PLAYER->GetAlphaEndPoint() == 255) {
		if (KeyCode == DIK_UP) {
			if (PLAYER->GetState() == PLAYER_STATE::CLIMB) {
				PLAYER->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				PLAYER->SetAcceleratorX(0.0f);
				PLAYER->SetClimbMoving(false);
			}
		}

		if (KeyCode == DIK_DOWN) {
			if (PLAYER->GetState() == PLAYER_STATE::CLIMB) {
				PLAYER->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				PLAYER->SetAcceleratorX(0.0f);
				PLAYER->SetClimbMoving(false);
			}
		}

		if (KeyCode == DIK_RIGHT) {
			if (PLAYER->GetState() == PLAYER_STATE::RUN) {
				PLAYER->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				PLAYER->SetAcceleratorX(0.0f);
				PLAYER->SetDirection(DIRECTION::RIGHT);
				PLAYER->SetState(PLAYER_STATE::STAND);
			}
		}

		if (KeyCode == DIK_LEFT) {
			if (PLAYER->GetState() == PLAYER_STATE::RUN) {
				PLAYER->SetVeclocity(NO_VELOCITY, NO_VELOCITY);
				PLAYER->SetAcceleratorX(0.0f);
				PLAYER->SetDirection(DIRECTION::LEFT);
				PLAYER->SetState(PLAYER_STATE::STAND);
			}
		}


		if (PLAYER->GetState() == PLAYER_STATE::SIT || PLAYER->GetState() == PLAYER_STATE::SIT_ATK) {
			if (KeyCode == DIK_DOWN) {
				PLAYER->SetState(PLAYER_STATE::STAND);
			}
		}
	}
}