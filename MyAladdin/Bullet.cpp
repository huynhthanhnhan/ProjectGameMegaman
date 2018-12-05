#include "Bullet.h"



Bullet::Bullet()
{
}

Bullet::Bullet(int x, int y, Global::EDirection direct)
	:ActionObject(x, y)
{
	this->_direct = direct;
	this->Refresh();
}


Bullet::~Bullet()
{
}

void Bullet::update(float deltaTime)
{
	deltaTime /= 1000;//Đổi đơn vị
	this->_timeAction += deltaTime;
	this->_v0 = this->_distanceBullet / deltaTime;
	if (this->_isGround)
	{
		this->_ax = this->_ay = this->_v0 = 0;
	}

	float vx, vy, ax, ay;
	vx = this->_v0*cos(this->_angle);
	vy = this->_v0*sin(this->_angle);
	ax = 0;
	ay = this->_ay;

	vx *= (this->_direct == Global::Right) ? 1 : -1;
	ax *= (this->_direct == Global::Right) ? 1 : -1;

	float vxNext = vx + ax*(this->_timeAction - deltaTime);
	float vyNext = vy + ay*(this->_timeAction - deltaTime);
	this->_vx = vxNext*deltaTime + 0.5*ax*pow(deltaTime, 2);
	this->_vy = vyNext*deltaTime + 0.5*ay*pow(deltaTime, 2);

	Collision::ResultCollision result = StaticObject::Instance()->processCollision(this);
	if (!result.flag)
	{
		this->_x += this->_vx;
		this->_y += this->_vy;
	}
	else
	{
		this->_x = result.intersectionPoint.x;
		this->_y = result.intersectionPoint.y;
	}
	this->updateBody();
}

void Bullet::render()
{
	this->transform();
	D3DXVECTOR3 position = this->_transform._position;
	this->Render(this->_direct, this->_state, position);
}

void Bullet::turnBack(Global::EDirection direct)
{
	this->_direct = direct;
	this->_angle = 0.78;
	this->_type = Global::AladdinParty;
	this->_distanceBullet *= 1.2f;
	this->_timeAction = 0;
}

void Bullet::updateBody()
{
	D3DXVECTOR2 position = this->getCurrentLocation();
	this->_rectBound.update(position.x - _width / 2, position.y + _height / 2, _width, _height);
}

void Bullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	if(state == Global::Hurting)
		Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), 0);
	else
		Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), _rotation);
	this->UpdateRender(_state);
	this->_rotation += (direct == Global::Right) ? -1 : 1;
}

void Bullet::Refresh()
{
	this->_timeAction = 0;
	for each (auto sprite in this->mListSprite)
		sprite.second->SetCurrentFrame(0);
}

