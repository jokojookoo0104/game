#include "Camera.h"
#include "Graphic.h"
#include "../Logging/Debug.h"
#include "../Object/Player/Player.h"
Camera* Camera::_instance = NULL;

Camera::Camera()
{
	cameraPosition = { 0,0 };
	RECTPosition = { 0, 0 };
	worldBoundary = 0;
}

Camera::~Camera()
{

}

Camera* CAMERA {
	if (_instance == NULL) _instance = new Camera();
	return _instance;
}

int Camera::GetworldBoundary() {
	return this->worldBoundary;
}

D3DXVECTOR3 Camera::transformObjectPosition(D3DXVECTOR3 objectPosition)
{
	D3DXMATRIX mt;
	D3DXMatrixIdentity(&mt);
	mt._22 = 1.0;
	mt._41 = -this->cameraPosition.x;
	mt._42 = -this->cameraPosition.y;
	D3DXVECTOR4 vp_pos;
	D3DXVec3Transform(&vp_pos, &objectPosition, &mt);
	return D3DXVECTOR3(vp_pos.x, vp_pos.y, 0);
}

void Camera::Update()
{
	cameraPosition = { PLAYER->GetPosition().x - GRAPHIC->GetWidth() / 2 + 20, cameraPosition.y };
	RECTPosition = { PLAYER->GetPosition().x, PLAYER->GetPosition().y };
	
	if (cameraPosition.x < 0) {
		cameraPosition = { 0 ,cameraPosition.y };
	}

	if (cameraPosition.x + GRAPHIC->GetWidth() > worldBoundary) {
		cameraPosition = { worldBoundary - GRAPHIC->GetWidth() ,cameraPosition.y };
	}
}

RECT Camera::GetRECT() {
	RECT r;
	int width = 330;
	int height = GRAPHIC->GetHeight();
	SetRect(&r, cameraPosition.x, cameraPosition.y, cameraPosition.x + width, cameraPosition.y + height);
	return r;
}

RECT Camera::GetRECTx() {
	RECT r;
	int width = GRAPHIC->GetWidth();
	int height = GRAPHIC->GetHeight();
	SetRect(&r, cameraPosition.x, cameraPosition.y, cameraPosition.x + width, cameraPosition.y + height);
	return r;
}