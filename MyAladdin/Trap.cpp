#include "Trap.h"
#include"ActionObject.h"
#include"Aladdin.h"
#include"StaticObject.h"

Trap::Trap()
{
}

Trap::Trap(int x, int y, int width, int height)
	:Object(x, y, width, height)
{
	this->_type = Global::Enemy;
	this->_vx = this->_vy = this->_v0 = 0;
	this->_rectBound.update(x, y, width, height);
	this->_id = Global::TRAP;
}


Trap::~Trap()
{
}

Collision::ResultCollision Trap::processCollision(Object * obj)
{
	ActionObject* acObject = (ActionObject*)obj;
	Collision::ResultCollision result;
	if (obj->getId() == Global::APPLEITEM)
		return result;
	WRect objectRect;
	if (obj->getId() == Global::ALADDIN)
	{
		return  result;
		//Aladdin* aladdin = (Aladdin*)obj;
		//objectRect = aladdin->getRectBound2();
	}
	else
		objectRect = acObject->getRectMove();

	if (Collision::Instance()->AABB(objectRect, this->_rectBound))
	{
		//if (obj->getId() == Global::ALADDIN)
		//{
		//	Aladdin* aladdin = (Aladdin*)obj;
		//	if (!aladdin->isReset())
		//		aladdin->Hurting();
		//}
		//else
			acObject->setState(Global::OnTrap);
		result.flag = true;
	}

	return result;
}

void Trap::update(float detalTime)
{
	StaticObject::Instance()->addTrap(this);
}
