#include "MapDead.h"



MapDead::MapDead()
{
	//position in World
	this->_position = D3DXVECTOR3(0, 9542, 0);
	LoadResource();
}

MapDead::MapDead(int x, int y, int z)
	:_position(x, y, z)
{
	LoadResource();
}

MapDead::~MapDead()
{
}

void MapDead::SetCamera(Camera * camera)
{
	this->_camera = camera;
}

void MapDead::LoadResource()
{
	this->_rectMapDead.update(0, 0, 7933, 4078, D3DXVECTOR3(0, 0, 0));
	this->_mapDeadTexture = ResourceImage::Instance()->getMapTexture()[5];
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}

void MapDead::Render(MapDead::EMapID mapId)
{
	Application* apps = Application::Instance();
	ViewPort* view = ViewPort::Instance();

	//get Camera Position in View Port
	D3DXVECTOR3 cameraPositionInView = view->getViewPortPosition(this->_camera->getPosition());

	this->_transform._translation = D3DXVECTOR3(-cameraPositionInView.x, -cameraPositionInView.y, 0);

	D3DXVECTOR3 inPosition = view->getViewPortPosition(this->_position);// +this->_transform._translation;

	Graphics* graphics = Graphics::Instance();

	LPDIRECT3DTEXTURE9 map = NULL;

	switch (mapId)
	{
	case MapDead::mapDead: map = this->_mapDeadTexture; break;
	}

	D3DXVECTOR2 translation = D3DXVECTOR2(this->_transform._translation.x, this->_transform._translation.y);

	if (map != NULL)
		graphics->DrawTexture(map, _rectMapDead, inPosition, this->_transform._scale, translation);
}
