#include "SnakeBullet.h"

SnakeBullet::SnakeBullet()
{
}

SnakeBullet::SnakeBullet(int x, int y, Global::EDirection direct, float angle, int distance)
	:Bullet(x, y, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::SNAKEBULLET;
	this->_state = Global::Stand;
	this->updateBody();
	this->_distanceBullet = distance;
	this->LoadResource();
}

SnakeBullet::~SnakeBullet()
{
}

void SnakeBullet::update(float deltaTime)
{
	deltaTime /= 1000;//Đổi đơn vị
	this->_v0 = this->_distanceBullet / deltaTime;
	float vx, vy;
	vx = this->_v0*cos(this->_angle);
	vy = this->_v0*sin(this->_angle);
	if (this->_direct == Global::Right)
	{
		vx = this->_v0;
		vy = -_v0*2;
		this->_vx = vx*deltaTime;
		this->_vy = vy*deltaTime;
	}
	else
	{
		vx = -this->_v0;
		vy = -_v0*2;
		this->_vx = vx*deltaTime;
		this->_vy = vy*deltaTime;
	}

	Collision::ResultCollision result = StaticObject::Instance()->groundCollision(this);
	Collision::ResultCollision result2 = StaticObject::Instance()->wallCollision(this);
	if (!result.flag && !result2.flag)
	{
		this->_x += this->_vx;
		this->_y += this->_vy;
	}
	else
	{
		this->_x += this->_vx;
		this->_y = result.intersectionPoint.y;
		if (result2.flag)
			_isFinish = true; //vien dan bien mat
	}

	this->updateBody();
}

bool SnakeBullet::isFinish()
{
	return _isFinish;
}

Collision::ResultCollision SnakeBullet::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

void SnakeBullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _rotation);
	this->UpdateRender(_state);
}

void SnakeBullet::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

void SnakeBullet::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "FireSnake");
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		listSourceRect, false);
}

void SnakeBullet::UpdateRender(Global::EState currentState)
{
	int size = this->mListSprite[Global::Stand]->GetListRect().size();
	this->SetCurrentFrame(_state, (this->GetCurrentFrame(_state) + 1) % size);
}

bool SnakeBullet::isCanAttack()
{
	return true;
}

void SnakeBullet::setFinish()
{
	_isFinish = true;
}

