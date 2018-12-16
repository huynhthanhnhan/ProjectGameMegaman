#include "ResourceImage.h"

ResourceImage*				ResourceImage::__instance;

ResourceImage::ResourceImage()
{
	LoadResource();
}


ResourceImage::~ResourceImage()
{
}

ResourceImage * ResourceImage::Instance()
{
	if (!__instance)
		__instance = new ResourceImage();
	return __instance;
}

LPDIRECT3DTEXTURE9 ResourceImage::getPeddlerTexture()
{
	return this->_peddler;
}

LPDIRECT3DTEXTURE9 ResourceImage::getAladdinTexture()
{
	return this->_aladdinAction;
}

LPDIRECT3DTEXTURE9 ResourceImage::getAladdinTexture2()
{
	return this->_aladdinAction2;
}

LPDIRECT3DTEXTURE9 ResourceImage::getAladdinTexture3()
{
	return this->_aladdinAction3;
}

LPDIRECT3DTEXTURE9 ResourceImage::getFireTexture()
{
	return this->_fire;
}

LPDIRECT3DTEXTURE9 ResourceImage::getCamelTexture()
{
	return this->_camel;
}

LPDIRECT3DTEXTURE9 ResourceImage::getGuardsTexture()
{
	return this->_guards;
}

LPDIRECT3DTEXTURE9 ResourceImage::getCivilianTexture()
{
	return this->_civilians;
}

vector<LPDIRECT3DTEXTURE9> ResourceImage::getMapTexture()
{
	return this->_map;
}

LPDIRECT3DTEXTURE9 ResourceImage::getDropGroundTexture()
{
	return this->_dropGround;
}

LPDIRECT3DTEXTURE9 ResourceImage::getExplosingTexture()
{
	return this->_explosing;
}

LPDIRECT3DTEXTURE9 ResourceImage::getExplosingTexture1()
{
	return this->_explosing1;
}

LPDIRECT3DTEXTURE9 ResourceImage::getItemTexture()
{
	return this->_item;
}


LPDIRECT3DTEXTURE9 ResourceImage::getItemTexture1()
{
	return this->_item1;
}

LPDIRECT3DTEXTURE9 ResourceImage::getItemTexture2()
{
	return this->_item2;
}

LPDIRECT3DTEXTURE9 ResourceImage::getJafarTexture()
{
	return this->_jafar;
}

LPDIRECT3DTEXTURE9 ResourceImage::getStick()
{
	return this->_stick;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp0()
{
	return this->_hp0;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp1()
{
	return this->_hp1;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp2()
{
	return this->_hp2;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp3()
{
	return this->_hp3;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp4()
{
	return this->_hp4;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp5()
{
	return this->_hp5;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp6()
{
	return this->_hp6;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp7()
{
	return this->_hp7;
}

LPDIRECT3DTEXTURE9 ResourceImage::getHp8()
{
	return this->_hp8;
}

LPDIRECT3DTEXTURE9 ResourceImage::getStarTexture()
{
	return this->_star;
}

LPDIRECT3DTEXTURE9 ResourceImage::getVictoryTexture()
{
	return this->_victory;
}

LPDIRECT3DTEXTURE9 ResourceImage::getAbuVictoryTexture()
{
	return this->_abuVictory;
}

LPDIRECT3DTEXTURE9 ResourceImage::getAbuDeadTexture()
{
	return this->_abuDead;
}

LPDIRECT3DTEXTURE9 ResourceImage::getMenu()
{
	return this->_menu;
}

LPDIRECT3DTEXTURE9 ResourceImage::getKnifeMenu()
{
	return this->_knife_menu;
}

LPDIRECT3DTEXTURE9 ResourceImage::getMegamanSprite()
{
	return this->_MegamanSprite;
}

LPDIRECT3DTEXTURE9 ResourceImage::getEnemy()
{
	return this->_enemy;
}

void ResourceImage::LoadResource()
{
	Graphics* graphics = Graphics::Instance();
	//================================================================
	//Explosing
	//================================================================
	this->_explosing = graphics->LoadTexture("AnimationSource\\Bullet.png", D3DCOLOR_XRGB(50, 96, 166));
	this->_explosing1 = graphics->LoadTexture("AnimationSource\\explosion1.png");
	//================================================================
	//Map
	//================================================================
	this->_map.push_back(graphics->LoadTexture("Map\\Map.png", D3DCOLOR_XRGB(63, 72, 204)));
	this->_map.push_back(graphics->LoadTexture("Map\\MapLevel1_part2.png", D3DCOLOR_XRGB(63, 72, 204)));
	this->_map.push_back(graphics->LoadTexture("Map\\pillars.png", D3DCOLOR_XRGB(63, 72, 204)));
	this->_map.push_back(graphics->LoadTexture("Map\\palace_back.png", D3DCOLOR_XRGB(63, 72, 204)));
	this->_map.push_back(graphics->LoadTexture("Map\\LevelComplete.png"));
	this->_map.push_back(graphics->LoadTexture("Map\\dead.png", D3DCOLOR_XRGB(63, 72, 204)));
	this->_map.push_back(graphics->LoadTexture("Map\\menu.png"));

	//================================================================
	//Drop Ground
	//================================================================
	this->_dropGround = graphics->LoadTexture("Map\\dropGround.png");
	//================================================================
	//Aladdin Action
	//================================================================
	this->_aladdinAction = graphics->LoadTexture("AnimationSource\\MegamanSprite.png", D3DCOLOR_XRGB(0, 0, 255));
	//================================================================
	//Aladdin Run Attack
	this->_aladdinAction2 = graphics->LoadTexture("AnimationSource\\RunAttack.png", D3DCOLOR_XRGB(106, 148, 189));
	//================================================================
	//Aladdin Run Throw
	this->_aladdinAction3 = graphics->LoadTexture("AnimationSource\\RunThrow.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//Camel
	//================================================================
	this->_camel = graphics->LoadTexture("AnimationSource\\Camel.png", D3DCOLOR_XRGB(248, 0, 248));
	//================================================================
	//Guards
	//================================================================
	this->_guards = graphics->LoadTexture("AnimationSource\\Guards.png", D3DCOLOR_XRGB(120, 193, 152));
	//================================================================
	//Guards
	//================================================================
	this->_civilians = graphics->LoadTexture("AnimationSource\\Civilians.png", D3DCOLOR_XRGB(120, 193, 152));
	//================================================================
	//Stick
	//================================================================
	this->_stick = graphics->LoadTexture("AnimationSource\\Stick.png");
	//================================================================
	//Item
	//================================================================
	this->_item = graphics->LoadTexture("AnimationSource\\Item.png", D3DCOLOR_XRGB(248, 0, 248));
	this->_item1 = graphics->LoadTexture("AnimationSource\\FIND MORE GEMS.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_item2 = graphics->LoadTexture("AnimationSource\\A DEAL.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//HealthPoint
	//================================================================
	this->_hp0 = graphics->LoadTexture("AnimationSource\\0.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp1 = graphics->LoadTexture("AnimationSource\\1.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp2 = graphics->LoadTexture("AnimationSource\\2.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp3 = graphics->LoadTexture("AnimationSource\\3.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp4 = graphics->LoadTexture("AnimationSource\\4.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp5 = graphics->LoadTexture("AnimationSource\\5.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp6 = graphics->LoadTexture("AnimationSource\\6.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp7 = graphics->LoadTexture("AnimationSource\\7.png", D3DCOLOR_XRGB(255, 0, 255));
	this->_hp8 = graphics->LoadTexture("AnimationSource\\8.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//Jafar + Snake 
	//================================================================
	this->_jafar = graphics->LoadTexture("AnimationSource\\Jafar.png", D3DCOLOR_XRGB(186, 254, 202));
	//================================================================
	//Star
	//================================================================
	this->_star = graphics->LoadTexture("AnimationSource\\Star.png");
	//================================================================
	//Peddler
	//================================================================
	this->_peddler = graphics->LoadTexture("AnimationSource\\Peddler.png", D3DCOLOR_XRGB(255, 0, 255));
	//================================================================
	//Fire
	//================================================================
	this->_fire = graphics->LoadTexture("AnimationSource\\fire.png");
	//================================================================
	//Victory
	//================================================================
	this->_victory = graphics->LoadTexture("AnimationSource\\victory.png");
	//================================================================
	//Victory
	//================================================================
	this->_abuVictory = graphics->LoadTexture("AnimationSource\\abu_victory.png");
	//================================================================
	//Abu dead
	//================================================================
	this->_abuDead = graphics->LoadTexture("AnimationSource\\abu_gameover.png");
	//================================================================
	//Knife Menu
	//================================================================
	this->_knife_menu = graphics->LoadTexture("AnimationSource\\menu_select.png");
	//================================================================
	//Intro
	//================================================================
	this->_menu = graphics->LoadTexture("AnimationSource\\intro.png");

	this->_MegamanSprite = graphics->LoadTexture("AnimationSource\\MegamanSprite.png");
	this->_enemy = graphics->LoadTexture("AnimationSource\\Enemy.png", D3DCOLOR_XRGB(50, 96, 166));
}
