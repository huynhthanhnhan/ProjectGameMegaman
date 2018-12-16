#include "NotorbangerBullet.h"


NotorbangerBullet::NotorbangerBullet(int x, int y, Global::EDirection direct)
	:Bullet(x, y, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::NOTORBANGERBULLET;
	this->_state = Global::Attack;
	this->_width = 30;
	this->_width = 30;
	this->_vx = 0;
	this->_ay =  -ACCELERATION/2;
	this->_angle = 0;
	this->_rotation = 0;
	this->updateBody();
	this->_timeLife = 0;
	this->_distanceBullet = 10;// DISTANCE_CIVILIANBULLET;
	this->LoadResource();
}

NotorbangerBullet::~NotorbangerBullet()
{
}

bool NotorbangerBullet::isFinish()
{
	return (this->_timeLife>=10);
}

Collision::ResultCollision NotorbangerBullet::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

bool NotorbangerBullet::isCanAttack()
{
	return this->GetCurrentFrame(_state) <= 5;
}

void NotorbangerBullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _rotation);
	this->UpdateRender(_state);
}

void NotorbangerBullet::LoadResource()
{
	//======================================================
	//Attack
	//======================================================
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_bullet"));
	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy");

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture1(),
		explosing);
}

void NotorbangerBullet::UpdateRender(Global::EState currentState)
{
	this->_timeLife++;
}
