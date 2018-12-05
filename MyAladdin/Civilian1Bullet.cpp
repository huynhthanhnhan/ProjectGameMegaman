#include "Civilian1Bullet.h"


Civilian1Bullet::Civilian1Bullet(int x, int y, Global::EDirection direct)
	:Bullet(x, y, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::CIVILIANBULLET;
	this->_state = Global::Attack;
	this->_width = 30;
	this->_width = 30;
	this->_vx = 0;
	this->_ay = -ACCELERATION;
	this->_angle = 0;
	this->_rotation = 0;
	this->updateBody();
	this->_distanceBullet = DISTANCE_CIVILIANBULLET;
	this->LoadResource();
}

Civilian1Bullet::~Civilian1Bullet()
{
}

bool Civilian1Bullet::isFinish()
{
	return (this->GetCurrentFrame(Global::Attack) == 14 || this->GetCurrentFrame(Global::Dead) == 9);
}

Collision::ResultCollision Civilian1Bullet::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

bool Civilian1Bullet::isCanAttack()
{
	return this->GetCurrentFrame(_state) <= 5;
}

void Civilian1Bullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _rotation);
	this->UpdateRender(_state);
}

void Civilian1Bullet::LoadResource()
{
	//======================================================
	//Attack
	//======================================================
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getCivilianTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Civilian1Bullet"));
	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy");

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture1(),
		explosing);
}

void Civilian1Bullet::UpdateRender(Global::EState currentState)
{
	if (currentState == Global::Dead)
		this->setGround();
	else
	{
		if (!this->_isGround)
		{
			if (this->GetCurrentFrame(_state) == 6)
				this->SetCurrentFrame(_state, 0);
		}
		else
		{
			if (this->GetCurrentFrame(_state) == 7)
			{
				this->_sound = Sound::Instance();
				this->_sound->play(SOUND_CLAY_POT);
			}
			if (this->GetCurrentFrame(_state) < 6)
				this->SetCurrentFrame(_state, 6);
		}
	}
}
