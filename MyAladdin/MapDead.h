#pragma once
#ifndef __MAPDEAD_H__
#define __MAPDEAD_H__
#include"Graphics.h"
#include"ResourceImage.h"
#include"Rect.h"
#include"Camera.h"
#include"Application.h"
#include"ResourceFile.h"
#include"Global.h"
class MapDead
{
public:
	enum EMapID
	{
		mapDead
	};
private:
	D3DXVECTOR3				_position;
	Rect					_rectMapDead;
	LPDIRECT3DTEXTURE9		_mapDeadTexture;
	Camera*					_camera;
	Global::Transform		_transform;
public:
	MapDead();
	MapDead(int x, int y, int z);
	~MapDead();
	void					SetCamera(Camera* camera);
	void					LoadResource();
	void					Render(MapDead::EMapID mapId);
};

#endif __MAPDEAD_H__