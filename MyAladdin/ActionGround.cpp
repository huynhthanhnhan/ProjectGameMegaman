#include "ActionGround.h"
#include"Aladdin.h"


ActionGround::ActionGround()
{
}

ActionGround::ActionGround(int x, int y, int width, int height)
{
	this->_width = width;
	this->_height = height;
	this->_x0 = this->_x = x + width/2;
	this->_y0 = this->_y = y - height;
	this->_rectBound.update(x, y, width, height);
	this->_vx = 0;
	this->_vy = 0;
	this->_id = Global::GROUND_DROP;
	this->_drop = false;
	this->LoadResource();
}


ActionGround::~ActionGround()
{
}

void ActionGround::update(float deltaTime)
{
	StaticObject::Instance()->addActionGround(this);

	this->_ax = 0;
	this->_vx = this->_vy = 0;
	if (!_drop)
	{
		this->_timeAction = 0;
		this->_ay = 0;
		this->_x = this->_x0;
		this->_y = this->_y0;
	}
	else
	{
		deltaTime /= 1000;
		this->_timeAction += deltaTime;
		this->_ay = -ACCELERATION;
		float preTime = this->_timeAction - deltaTime;
		//Update new location
		float y0 = _y - (_vy*preTime + 0.5*_ay*pow(preTime, 2));
		this->_y = y0 + (_vy*_timeAction + 0.5*_ay*pow(_timeAction, 2));
	}
	this->updateBody();
	if (this->_y <= 7894)
		this->_drop = false;
}

void ActionGround::render()
{
	this->transform();
	//this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->Render(Global::Right, Global::Fall, D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0), this->_transform._scale);
}

Collision::ResultCollision ActionGround::processCollision(Object * obj)
{
	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();

	WRect rect1 = ((Aladdin*)obj)->getRectBound2();
	WRect rect2 = this->getRectBound();
	float vx1 = obj->getVx();
	float vy1 = obj->getVy();
	float vx2 = this->getVx();
	float vy2 = this->getVy();
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);
	//Chỉ xét hướng va chạm từ trên xuống
	if (result.normaly == -1 || result.normaly == 0)
		result.flag = false;

	this->_drop = (result.flag) ? true : _drop;

	if (obj->getId() == Global::ALADDIN)
		result.intersectionPoint.x = obj->getX() + obj->getVx();
	else
		result.intersectionPoint.x = obj->getX() + obj->getVx()*result.collisionTime;

	result.intersectionPoint.y = obj->getY() + obj->getVy()*result.collisionTime;

	return result;
}

void ActionGround::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
}

void ActionGround::Refresh()
{
}

void ActionGround::LoadResource()
{
	std::vector<Rect*> listSourceRect;
	listSourceRect.push_back(new Rect(274, 1587, 1588 + _width/2.5, 274+_height/2));
	this->mListSprite[Global::Fall] = new SpriteManager(ResourceImage::Instance()->getMapTexture()[0],
		listSourceRect, false);
}

void ActionGround::UpdateRender(Global::EState currentState)
{
}
