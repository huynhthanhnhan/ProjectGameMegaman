#include "MapMenu.h"



MapMenu::MapMenu()
{
	//position in World
	this->_position = D3DXVECTOR3(0, 9542, 0);
	LoadResource();
}

MapMenu::MapMenu(int x, int y, int z)
	:_position(x, y, z)
{
	LoadResource();
}

MapMenu::~MapMenu()
{
}

void MapMenu::SetCamera(Camera * camera)
{
	this->_camera = camera;
}

void MapMenu::LoadResource()
{
	this->_rectMapMenu.update(0, 0, 800, 600, D3DXVECTOR3(0, 0, 0));
	this->_mapMenuTexture = ResourceImage::Instance()->getMapTexture()[6];
	this->_transform._scale = D3DXVECTOR2(1, 1);
}

void MapMenu::Render(MapMenu::EMapID mapId)
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
	case MapMenu::mapMenu: map = this->_mapMenuTexture; break;
	}

	D3DXVECTOR2 translation = D3DXVECTOR2(this->_transform._translation.x, this->_transform._translation.y);

	if (map != NULL)
		graphics->DrawTexture(map, _rectMapMenu, inPosition, this->_transform._scale, translation);
}
