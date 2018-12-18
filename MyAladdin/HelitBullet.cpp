#include "HelitBullet.h"


HelitBullet::HelitBullet(int x, int y, Global::EDirection direct)
	:Bullet(x, y, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::HELITBULLET;
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

HelitBullet::~HelitBullet()
{
}

bool HelitBullet::isFinish()
{
	return (this->GetCurrentFrame(Global::Attack) == 14 || this->GetCurrentFrame(Global::Dead) == 9
		||this->_timeLife>=20);
}

Collision::ResultCollision HelitBullet::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

bool HelitBullet::isCanAttack()
{
	return this->GetCurrentFrame(_state) <= 5;
}

void HelitBullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _rotation);
	this->UpdateRender(_state);
}

void HelitBullet::LoadResource()
{
	//======================================================
	//Attack
	//======================================================
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_rocket"));
	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy");

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture1(),
		explosing);
}

void HelitBullet::UpdateRender(Global::EState currentState)
{
	//if (currentState == Global::Dead)
	//	this->setGround();
	//else
	//{
	//	if (!this->_isGround)
	//	{
	//		if (this->GetCurrentFrame(_state) == 6)
	//			this->SetCurrentFrame(_state, 0);
	//	}
	//	else
	//	{
	//		if (this->GetCurrentFrame(_state) == 7)
	//		{

	//		}
	//		if (this->GetCurrentFrame(_state) < 6)
	//			this->SetCurrentFrame(_state, 6);
	//	}
	//}
	this->_timeLife++;
}
