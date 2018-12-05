#include "Sword.h"



Sword::Sword()
{
}

Sword::Sword(int x, int y, Global::EDirection direct, float angle, int distance)
	:Bullet(x, y, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::SWORDBULLET;
	this->_state = Global::Stand;
	this->_width = 27;
	this->_height = 27;
	this->_ay = -ACCELERATION / 2;
	this->_angle = angle;
	this->updateBody();
	this->_distanceBullet = distance;
	this->LoadResource();
}

Sword::~Sword()
{
}

bool Sword::isFinish()
{
	return (this->_state == Global::Hurting && this->GetCurrentFrame(_state) == 2);
}

Collision::ResultCollision Sword::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

void Sword::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	if (_isGround)
		this->_state = Global::Hurting;
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _rotation);
	this->UpdateRender(_state);
}

void Sword::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Right);
}

void Sword::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "Sword");
	listSourceRect[0]->setCenter(5, 16);
	listSourceRect[1]->setCenter(16, 11);
	listSourceRect[2]->setCenter(7, 9);
	listSourceRect[3]->setCenter(9, 5);
	listSourceRect[4]->setCenter(9, 15);
	listSourceRect[5]->setCenter(13, 15);
	listSourceRect[6]->setCenter(5, 8);
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getGuardsTexture(),
		listSourceRect, false);
	//=====================================================
	//Explosing
	//=====================================================
	std::vector<Rect*> exposing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveSword");
	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		exposing);
}

void Sword::UpdateRender(Global::EState currentState)
{
	switch (_state)
	{
	case Global::Stand:
	{
		if (this->_time >= 1)
		{
			int size = this->mListSprite[Global::Stand]->GetListRect().size();
			this->SetCurrentFrame(_state, (this->GetCurrentFrame(_state) + 1) % size);
			this->_time = 0;
		}
		else
			this->_time++;
	}
	case Global::Hurting:
	{
		if (this->GetCurrentFrame(Global::Hurting) == 1)
		{
			this->_sound = Sound::Instance();
			this->_sound->play(SOUND_SWORD_CHING);
		}
	}
	}
}

bool Sword::isCanAttack()
{
	return this->_state != Global::Hurting;
}
