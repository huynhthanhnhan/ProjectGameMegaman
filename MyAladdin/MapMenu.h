#pragma once
#ifndef __MAPMENU_H__
#define __MAPMENU_H__
#include"Graphics.h"
#include"ResourceImage.h"
#include"Rect.h"
#include"Camera.h"
#include"Application.h"
#include"ResourceFile.h"
#include"Global.h"
class MapMenu
{
public:
	enum EMapID
	{
		mapMenu
	};
private:
	D3DXVECTOR3				_position;
	Rect					_rectMapMenu;
	LPDIRECT3DTEXTURE9		_mapMenuTexture;
	Camera*					_camera;
	Global::Transform		_transform;
public:
	MapMenu();
	MapMenu(int x, int y, int z);
	~MapMenu();
	void					SetCamera(Camera* camera);
	void					LoadResource();
	void					Render(MapMenu::EMapID mapId);
};

#endif __MAPMENU_H__