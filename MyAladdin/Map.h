#pragma once
#ifndef __MAP_H__
#define __MAP_H__
#include"Graphics.h"
#include"ResourceImage.h"
#include"Rect.h"
#include"Camera.h"
#include"Application.h"
#include"ResourceFile.h"
#include"Global.h"
class Map
{
public:
	enum EMapID
	{
		MapLevel1,
		MapLevel2,
		MapBoss1,
		MapBoss2
	};

private: 
	D3DXVECTOR3				_position;
	Rect					_rectMap1, _rectMap2;

	LPDIRECT3DTEXTURE9		_mapTexturePart1, _mapTexturePart2;
	
	Camera*					_camera;
	
	Global::Transform		_transform;
public:
	Map();
	Map(int x, int y, int z);
	~Map();
	void					SetCamera(Camera* camera);
	void					LoadResource();
	void					Render(Map::EMapID mapId);
};

#endif __MAP_H__