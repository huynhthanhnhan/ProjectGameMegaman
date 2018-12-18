#include "HeadGunnerBullet.h"


HeadGunnerBullet::HeadGunnerBullet(int x, int y, Global::EDirection direct)
	:Bullet(x, y, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::HEADGUNNERBULLET;
	this->_state = Global::Attack;
	this->_width = 30;
	this->_width = 30;
	this->_vx = 3;
	this->_ay = 0; //-ACCELERATION / 2;
	this->_angle = 0;
	this->_rotation = 0;
	this->updateBody();
	this->_timeLife = 0;
	this->_distanceBullet = 10;// DISTANCE_CIVILIANBULLET;
	this->LoadResource();
}

HeadGunnerBullet::~HeadGunnerBullet()
{
}

bool HeadGunnerBullet::isFinish()
{
	return (this->GetCurrentFrame(Global::Attack) == 14 || this->GetCurrentFrame(Global::Dead) == 9
		|| this->_timeLife >= 20);
}

Collision::ResultCollision HeadGunnerBullet::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

bool HeadGunnerBullet::isCanAttack()
{
	return this->GetCurrentFrame(_state) <= 5;
}

void HeadGunnerBullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _rotation);
	this->UpdateRender(_state);
}

void HeadGunnerBullet::LoadResource()
{
	//======================================================
	//Attack
	//======================================================
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "headgunner_rocket"));
	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy");

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture1(),
		explosing);
}

void HeadGunnerBullet::UpdateRender(Global::EState currentState)
{
	this->_timeLife++;
}
