#pragma once
#ifndef _RESOURCE_MANAGER_H__
#define _RESOURCE_MANAGER_H__

#include<vector>
using namespace std;
#include<d3d9.h>
#include<d3dx9.h>
#include"Graphics.h"

class ResourceImage
{
private:
	static ResourceImage*			__instance;
	std::vector<LPDIRECT3DTEXTURE9>	_map;
	LPDIRECT3DTEXTURE9				_dropGround;
	LPDIRECT3DTEXTURE9				_aladdinAction;			//Hành động aladdin
	LPDIRECT3DTEXTURE9				_aladdinAction2;			//Hành động aladdin
	LPDIRECT3DTEXTURE9				_aladdinAction3;			//Hành động aladdin
	LPDIRECT3DTEXTURE9				_camel;					//Con lạc đà
	LPDIRECT3DTEXTURE9				_civilians;		//Kẻ thù dân sự
	LPDIRECT3DTEXTURE9				_genie;					//Thần đèn
	LPDIRECT3DTEXTURE9				_abu;					//Con khỉ
	LPDIRECT3DTEXTURE9				_guards;				//Vệ binh
	LPDIRECT3DTEXTURE9				_jafar;					//Boss Jafar
	LPDIRECT3DTEXTURE9				_peddler;				//Người bán hàng
	LPDIRECT3DTEXTURE9				_explosing;
	LPDIRECT3DTEXTURE9				_explosing1;
	LPDIRECT3DTEXTURE9				_star;
	LPDIRECT3DTEXTURE9				_abuDead;
	LPDIRECT3DTEXTURE9				_victory;
	LPDIRECT3DTEXTURE9				_abuVictory;
	LPDIRECT3DTEXTURE9				_menu;
	LPDIRECT3DTEXTURE9				_knife_menu;
	LPDIRECT3DTEXTURE9				_fire;
	LPDIRECT3DTEXTURE9				_item;
	LPDIRECT3DTEXTURE9				_item1;
	LPDIRECT3DTEXTURE9				_item2;
	LPDIRECT3DTEXTURE9				_hp0;
	LPDIRECT3DTEXTURE9				_hp1;
	LPDIRECT3DTEXTURE9				_hp2;
	LPDIRECT3DTEXTURE9				_hp3;
	LPDIRECT3DTEXTURE9				_hp4;
	LPDIRECT3DTEXTURE9				_hp5;
	LPDIRECT3DTEXTURE9				_hp6;
	LPDIRECT3DTEXTURE9				_hp7;
	LPDIRECT3DTEXTURE9				_hp8;
	LPDIRECT3DTEXTURE9				_stick;
	LPDIRECT3DTEXTURE9				_dead;

	LPDIRECT3DTEXTURE9				_MegamanSprite;
public:
	ResourceImage();
	~ResourceImage();
	static ResourceImage*			Instance();

	LPDIRECT3DTEXTURE9				getPeddlerTexture();
	LPDIRECT3DTEXTURE9				getAladdinTexture();
	LPDIRECT3DTEXTURE9				getAladdinTexture2();
	LPDIRECT3DTEXTURE9				getAladdinTexture3();
	LPDIRECT3DTEXTURE9				getCamelTexture();
	LPDIRECT3DTEXTURE9				getGuardsTexture();
	LPDIRECT3DTEXTURE9				getCivilianTexture();
	std::vector<LPDIRECT3DTEXTURE9>	getMapTexture();
	LPDIRECT3DTEXTURE9				getDropGroundTexture();
	LPDIRECT3DTEXTURE9				getExplosingTexture();
	LPDIRECT3DTEXTURE9				getExplosingTexture1();
	LPDIRECT3DTEXTURE9				getItemTexture();
	LPDIRECT3DTEXTURE9				getItemTexture1();
	LPDIRECT3DTEXTURE9				getItemTexture2();
	LPDIRECT3DTEXTURE9				getAbuDeadTexture();
	LPDIRECT3DTEXTURE9				getJafarTexture();
	LPDIRECT3DTEXTURE9				getStarTexture();
	LPDIRECT3DTEXTURE9				getFireTexture();
	LPDIRECT3DTEXTURE9				getVictoryTexture();
	LPDIRECT3DTEXTURE9				getAbuVictoryTexture();
	LPDIRECT3DTEXTURE9				getHp0();
	LPDIRECT3DTEXTURE9				getMenu();
	LPDIRECT3DTEXTURE9				getKnifeMenu();
	LPDIRECT3DTEXTURE9				getHp1();
	LPDIRECT3DTEXTURE9				getHp2();
	LPDIRECT3DTEXTURE9				getHp3();
	LPDIRECT3DTEXTURE9				getHp4();
	LPDIRECT3DTEXTURE9				getHp5();
	LPDIRECT3DTEXTURE9				getHp6();
	LPDIRECT3DTEXTURE9				getHp7();
	LPDIRECT3DTEXTURE9				getHp8();
	LPDIRECT3DTEXTURE9				getStick();

	LPDIRECT3DTEXTURE9				getMegamanSprite();

private:
	void							LoadResource();
};

#endif _RESOURCE_MANAGER_H__