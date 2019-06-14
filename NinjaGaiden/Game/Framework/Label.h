#pragma once
#include <string>
#include "d3d9.h"
class Label
{
public:
	Label()
	{
		text = "";
		color = D3DCOLOR_XRGB(255, 255, 255);
		size = 1;
		xPos = yPos = 0.0f;
		space = false;
	}

	Label(std::string text,
		int size,
		float xPos,
		float yPos,
		D3DCOLOR color,
		bool space
	)
	{
		this->text = text;
		this->size = size;
		this->color = color;
		this->xPos = xPos;
		this->yPos = yPos;
		this->space = space;
	}
	~Label()
	{
		text = "";
		color = D3DCOLOR_XRGB(255, 255, 255);
		size = 0;
		xPos = yPos = 0.0f;
		space = false;
	}

	std::string text;
	int size;
	D3DCOLOR color;
	float xPos;
	float yPos;
	bool space;
};