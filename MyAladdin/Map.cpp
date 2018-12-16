#include "Map.h"



Map::Map()
{
	//position in World
	this->_position = D3DXVECTOR3(0, WORLD_Y, 0);
	LoadResource();
}

Map::Map(int x, int y, int z)
	:_position(x, y, z)
{
	LoadResource();
}

Map::~Map()
{
}

void Map::SetCamera(Camera * camera)
{
	this->_camera = camera;
}

void Map::LoadResource()
{
	this->_rectMap1.update(0, 0, 7933, 4078, D3DXVECTOR3(0, 0, 0));
	this->_rectMap2.update(0, 0, 4771, 688, D3DXVECTOR3(0, 0, 0));
	this->_mapTexturePart1 = ResourceImage::Instance()->getMapTexture()[0];
	this->_mapTexturePart2 = ResourceImage::Instance()->getMapTexture()[1];
	this->_transform._scale = D3DXVECTOR2(2, 2);
}

void Map::Render(Map::EMapID mapId)
{
	Application* apps = Application::Instance();
	ViewPort* view = ViewPort::Instance();

	//get Camera Position in View Port
	D3DXVECTOR3 cameraPositionInView = view->getViewPortPosition(this->_camera->getPosition());

	this->_transform._translation = D3DXVECTOR3(-cameraPositionInView.x, -cameraPositionInView.y-330, 0);

	D3DXVECTOR3 inPosition = view->getViewPortPosition(this->_position);// +this->_transform._translation;

	Graphics* graphics = Graphics::Instance();

	LPDIRECT3DTEXTURE9 map = NULL;

	switch (mapId)
	{
	case Map::MapLevel1: map = this->_mapTexturePart1; break;
	case Map::MapLevel2: map = this->_mapTexturePart2; break;
	}


	D3DXVECTOR2 translation = D3DXVECTOR2(this->_transform._translation.x, this->_transform._translation.y);

	if(map!= NULL)
		graphics->DrawTexture(map, _rectMap1, inPosition, this->_transform._scale, translation);
}
