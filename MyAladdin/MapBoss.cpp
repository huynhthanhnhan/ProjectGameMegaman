#include "MapBoss.h"

MapBoss::MapBoss()
{
	//position in World
	this->_position = D3DXVECTOR3(0, 9542, 0);
	LoadResource();
}

MapBoss::MapBoss(int x, int y, int z)
	:_position(x, y, z)
{
	LoadResource();
}

MapBoss::~MapBoss()
{
}

void MapBoss::SetCamera(Camera * camera)
{
	this->_camera = camera;
}

void MapBoss::LoadResource()
{
	this->_rectMapBoss1.update(0, 0, 2000, 1000, D3DXVECTOR3(0, 0, 0));
	this->_rectMapBoss2.update(0, 0, 1500, 800, D3DXVECTOR3(0, 0, 0));
	this->_mapBossTexturePart1 = ResourceImage::Instance()->getMapTexture()[2];
	this->_mapBossTexturePart2 = ResourceImage::Instance()->getMapTexture()[3];
	this->_transform._scale = D3DXVECTOR2(1.3, 1.3);
}

void MapBoss::Render(MapBoss::EMapID mapId)
{
	Application* apps = Application::Instance();
	ViewPort* view = ViewPort::Instance();

	//get Camera Position in View Port
	D3DXVECTOR3 cameraPositionInView = view->getViewPortPosition(this->_camera->getPosition());

	this->_transform._translation = D3DXVECTOR3(-cameraPositionInView.x, -cameraPositionInView.y +750, 0);

	D3DXVECTOR3 inPosition = view->getViewPortPosition(this->_position);// +this->_transform._translation;

	Graphics* graphics = Graphics::Instance();

	LPDIRECT3DTEXTURE9 map = NULL;

	switch (mapId)
	{
	case MapBoss::MapBoss1: map = this->_mapBossTexturePart1; break;
	case MapBoss::MapBoss2: map = this->_mapBossTexturePart2; break;
	}

	D3DXVECTOR2 translation = D3DXVECTOR2(this->_transform._translation.x, this->_transform._translation.y);

	if (map != NULL)
		graphics->DrawTexture(map, _rectMapBoss1, inPosition, this->_transform._scale, translation);
}
