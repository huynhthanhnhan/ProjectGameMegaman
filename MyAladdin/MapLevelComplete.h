#pragma once
#ifndef __MAPLEVELCOMPLETE_H__
#define __MAPLEVELCOMPLETE_H__
#include"Graphics.h"
#include"ResourceImage.h"
#include"Rect.h"
#include"Camera.h"
#include"Application.h"
#include"ResourceFile.h"
#include"Global.h"
class MapLevelComplete
{
public:
	enum EMapID
	{
		MapComplete
	};
private:
	D3DXVECTOR3				_position;
	Rect					_rectMapComplete;
	LPDIRECT3DTEXTURE9		_mapCompleteTexture;
	Camera*					_camera;
	Global::Transform		_transform;
public:
	MapLevelComplete();
	MapLevelComplete(int x, int y, int z);
	~MapLevelComplete();
	void					SetCamera(Camera* camera);
	void					LoadResource();
	void					Render(MapLevelComplete::EMapID mapId);
};

#endif __MAPLEVELCOMPLETE_H__