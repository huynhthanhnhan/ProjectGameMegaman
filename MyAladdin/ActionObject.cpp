#include "ActionObject.h"



ActionObject::ActionObject()
{
}

ActionObject::ActionObject(int x, int y, int width, int height)
	:Object(x, y, width, height)
{
	this->_isDead = false;
}


ActionObject::~ActionObject()
{
}

void ActionObject::updateBody()
{
	Object::updateBody();
	D3DXVECTOR2 center = this->getCurrentLocation();
	_rectMove.update(center.x - _width / 2, center.y + this->_height, 1, this->_height);
}

bool ActionObject::isDead()
{
	return this->_isDead;
}

bool ActionObject::isGround()
{
	return this->_isGround;
}

bool ActionObject::isLookUp()
{
	return this->_isLookUp;
}

void ActionObject::setLookUp(bool flag)
{
	this->_isLookUp = flag;
}

bool ActionObject::isJafar()
{
	return this->_isJafar;
}

void ActionObject::setJafar(bool flag)
{
	this->_isJafar = flag;
}

bool ActionObject::isGems()
{
	return this->_isGems;
}

void ActionObject::setGems(bool flag)
{
	this->_isGems = flag;
}

bool ActionObject::isA_Deal()
{
	return this->_isA_Deal;
}

void ActionObject::setA_Deal(bool flag)
{
	this->_isA_Deal = flag;
}

int ActionObject::getAx()
{
	return this->_ax;
}

int ActionObject::getAy()
{
	return this->_ay;
}

Global::EState ActionObject::getState()
{
	return this->_state;
}

Global::EDirection ActionObject::getDirect()
{
	return this->_direct;
}

WRect ActionObject::getRectSword()
{
	return this->_rectSword;
}


void ActionObject::setDead(bool dead)
{
	this->_isDead = dead;
}

WRect ActionObject::getRectMove()
{
	return this->_rectMove;
}

void ActionObject::setAx(int ax)
{
	this->_ax = ax;
}

void ActionObject::setAy(int ay)
{
	this->_ay = ay;
}

void ActionObject::setGround(bool flag)
{
	this->_isGround = flag;
}

void ActionObject::setState(Global::EState state)
{
	this->_state = state;
}

void ActionObject::setDirect(Global::EDirection direct)
{
	this->_direct = direct;
}

void ActionObject::setRectSword(WRect sword)
{
	this->_rectSword = sword;
}

void ActionObject::refreshTime()
{
	this->_timeAction = 0;
}
