#include "Enemy.h"
#include"Aladdin.h"

Enemy::Enemy()
{
}

Enemy::Enemy(int xRegion, int yRegion, int widthRegion, int heightRegion, int width, int height, int v, Global::EDirection direct)
{
	this->_direct = direct;
	this->_region.update(xRegion, yRegion, widthRegion, heightRegion);
	this->_width = width;
	this->_height = height;
	this->_x = this->_region.right - this->_width;
	this->_y = this->_region.bottom;
	this->updateBody();
	this->_vx = v;
	this->_ax = this->_ay = this->_vy = 0;
	this->_type = Global::Enemy;
	this->_state = Global::Stand;
}


Enemy::~Enemy()
{
}

Global::EDirection Enemy::getDirect()
{
	return this->_direct;
}

Global::EState Enemy::getState()
{
	return this->_state;
}

WRect Enemy::getRectBound()
{
	return this->_rectBound;
}

bool Enemy::isCollision()
{
	return (this->_state != Global::Dead && !this->_isDead);
}


void Enemy::takeAction(Global::EState state)
{
	if (state == Global::Hurting)
		this->_hp--;
	if (this->_state == state)
		return;
	this->_start = true;
	this->_isFinishAction = false;
	this->_state = state;
}

void Enemy::render()
{
	if (this->_isDead)
		return;
	this->transform();
	D3DXVECTOR3 position = D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0);
	this->Render(this->_direct, this->_state, position);
}

Collision::ResultCollision Enemy::processCollision(Object * obj)
{
	if (this->_isDead)
		return Collision::ResultCollision();
	if (this->_state == Global::Dead && this->GetCurrentFrame(Global::Dead) == 1 && this->getId() != Global::JAFAR && this->getId() != Global::GUARD3)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_CLOUD_POOF);
	}
	switch (obj->getId())
	{
	case Global::ALADDIN:
	{
		if (!this->isCollision())
			break;

		this->_aladdinLocation = (D3DXVECTOR2)obj->getCurrentLocation();
		if (Collision::Instance()->AABB(obj->getRectBound(), this->_region))
			this->_start = true;

		Aladdin* aladdin = (Aladdin*)obj;
		if (aladdin->IsHit())
		{
			if (Collision::Instance()->AABB(aladdin->getRectSword(), this->_rectBound))
			{
				
				if (this->_id != Global::JAFAR)
				{
					if (this->_id == Global::CIVILIAN3)
						this->_hp--;
					else
						this->takeAction(Global::Hurting);
				}
			}
			if (Collision::Instance()->AABB(aladdin->getRectSword(), this->getRectSword()) && this->isAttack())
			{
				this->_sound = Sound::Instance();
				this->_sound->play(SOUND_SWORD_CHING);
				if (aladdin->getState() == Global::HitClimb)
					aladdin->setState(Global::Climb);
				else
					aladdin->setState(Global::Stand);
				this->setState(Global::Stand);
			}
		}
		break;
	}
	default:
	{
		Bullet* bullet = (Bullet*)obj;

		if (!bullet->isCanAttack())
			break;
		Collision::ResultCollision result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), this->_rectBound, this->_vx, this->_vy);
		if (result.flag)
		{
			if (this->_id == Global::CIVILIAN3 && this->_state != Global::Dead)
			{
				bullet->setGround();
			}
			else
			{
				if (this->_id == Global::JAFAR && this->_state != Global::Dead)
				{
					this->_hp--;
					bullet->setState(Global::Dead);
					this->_sound = Sound::Instance();
					this->_sound->play(SOUND_JAFAR_SNAKE);
				}
				else
				{
					if (this->_state != Global::Dead)
					{
						this->takeAction(Global::Hurting);
						bullet->setGround();
					}
				}
			}
			obj->setCurrentLocation(bullet->getX() + bullet->getVx()*result.collisionTime, bullet->getY() + bullet->getVy()*result.collisionTime);
		}
		else if (Collision::Instance()->AABB(obj->getRectBound(), this->getRectSword()) && this->isAttack())
		{
			bullet->setGround();
		}
	}
	}
	return Collision::ResultCollision();
}

void Enemy::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
	this->UpdateRender(state);
}

void Enemy::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Right);
}

