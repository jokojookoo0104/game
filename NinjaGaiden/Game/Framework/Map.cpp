#include "Map.h"
#include "Camera.h"
Map::Map()
{

}

Map::Map(int tileWidth, int tileHeight, int numOfColumn, int numOfRow) {
	this->tileWidth = tileWidth;
	this->tileHeight = tileHeight;
	this->numOfColumn = numOfColumn;
	this->numOfRow = numOfRow;
}

void Map::LoadMap(LPCWSTR filePath, int ID_MAP)
{
	this->list = new vector<vector<int>*>();
	TEXTURE->Add(ID_MAP, filePath);
	this->texture = TEXTURE->Get(ID_MAP);
}

void Map::LoadMap(LPCWSTR filePath, LPCWSTR tileset, int ID_MAP)
{
	fstream fs(filePath);
	fs >> numOfColumnTileSet >> numOfRowTileSet >> numOfRow >> numOfColumn >> tileWidth >> tileHeight;

	this->list = new vector<vector<int>*>();

	for (int i = 0; i < numOfRow; i++) {
		vector<int>* temp = new vector<int>();
		for (int j = 0; j < numOfColumn; j++) {
			int tempNumber;
			fs >> tempNumber;
			temp->push_back(tempNumber);
			if (i == 0) {
				this->width += tileWidth;
			}
		}
		this->list->push_back(temp);
		this->height += tileHeight;
	}
	DebugOut((wchar_t *)L"[Map.cpp] Width X Height map: %d %d\n", width, height);
	fs.close();

	TEXTURE->Add(ID_MAP, tileset);
	this->texture = TEXTURE->Get(ID_MAP);
}

Map::~Map()
{
	
	for (int i = 0; i < this->list->size(); i++) {
			delete this->list->at(i);
	}
	this->list->clear();
	delete this->list;
}

void Map::drawMap(int alpha)
{
	D3DXVECTOR2 camposition = CAMERA->getPosition();
	
		int top, left, right, bottom;
		for (int i = 0; i < 208 / tileHeight; i++) {
			for (int j = 0; j < 256 / tileWidth; j++) {
				int number = this->list->at(i)->at(j);
				if (number != 0) {
					int a = i + camposition.y / tileWidth;
					int b = j + camposition.x / tileHeight;
					left = ((list->at(a)->at(b) - 1) % numOfColumnTileSet)*tileWidth;
					top = ((list->at(a)->at(b) - 1) / numOfColumnTileSet)*tileHeight;
					right = left + tileWidth;
					bottom = top + tileHeight;
					GAME->Draw(
						j*tileWidth - (int)camposition.x % tileWidth, i*tileHeight - (int)camposition.y % tileHeight,
						texture,
						left, top, right, bottom, alpha);
				}
			}
		}
}

void Map::drawScence(int w, int h) {
	GAME->Draw(
		0, 0,
		texture, 10, 0, w, h, D3DCOLOR_XRGB(255, 255, 255));
}