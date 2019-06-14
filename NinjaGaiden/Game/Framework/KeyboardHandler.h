#pragma once
#include "Game.h"
#include "World.h"
#include "Graphic.h"
#include "../Object/Player/Player.h"
#include "Camera.h"
class KeyboardHandler : public InputDevice {
public:
	virtual void KeyState(BYTE *states);
	virtual void OnKeyDown(int KeyCode);
	virtual void OnKeyUp(int KeyCode);
};
