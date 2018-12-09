#include "StaticObject.h"
#include"Aladdin.h"

StaticObject*			StaticObject::__instance;

StaticObject::StaticObject()
{
}

StaticObject::~StaticObject()
{
}

StaticObject * StaticObject::Instance()
{
	if (!__instance)
		__instance = new StaticObject();
	return __instance;
}

void StaticObject::clearGround()
{
	this->_listGround.clear();
}

void StaticObject::clearStair()
{
	this->_listStair.clear();
}

void StaticObject::clearWall()
{
	this->_listWall.clear();
}

void StaticObject::clear()
{
	this->clearGround();
	this->clearStair();
	this->clearWall();
}

void StaticObject::addGround(Ground * ground)
{
	this->_listGround.push_back(ground);
}


void StaticObject::addWall(Wall * wall)
{
	this->_listWall.push_back(wall);
}

void StaticObject::addStair(Stair * stair)
{
	this->_listStair.push_back(stair);
}

Collision::ResultCollision StaticObject::processCollision(Object * obj)
{
	std::vector<D3DXVECTOR2> listLocation;
	int x = -1, y = -1;
	int  dxMin = INT_MAX;
	Collision::ResultCollision result;
	Collision::ResultCollision resultG;
	//=====================================================
	//Ground
	//=====================================================
	resultG = this->groundCollision(obj);
	if (resultG.flag)
		listLocation.push_back(resultG.intersectionPoint);
	//=====================================================
	//Stair
	//=====================================================
	result = this->stairCollision(obj);
	if (result.flag)
		listLocation.push_back(result.intersectionPoint);

	//=====================================================
	//Wall
	//=====================================================
	result = this->wallCollision(obj);
	if (result.flag)
	{
		listLocation.push_back(result.intersectionPoint);
		if (obj->getId() == Global::ALADDIN)
		{
			Aladdin* aladdin = (Aladdin*)obj;
			if(aladdin->getState()==Global::Jump)
				aladdin->In_climb();
		}
		listLocation.push_back(result.intersectionPoint);
	}
	//=====================================================

	for each (auto location in listLocation)
	{
		int dx = abs(location.x - obj->getX());
		int dy = abs(location.y - obj->getY());
		if (dx < dxMin)
		{
			x = location.x;
			dxMin = dx;
		}

		if (location.y > y)
			y = location.y;
	}

	if (x != -1)
	{
		result.intersectionPoint.x = x;
		result.intersectionPoint.y = y;
		result.flag = true;
	}
	else
		result.flag = false;

	return result;
}

Collision::ResultCollision StaticObject::groundCollision(Object * obj)
{
	Collision::ResultCollision result, result2;
	ActionObject* actionObject = (ActionObject*)obj;

	int  dxMin = INT_MAX, dyMin = INT_MAX;

	for each (auto ground in this->_listGround)
	{
		result = ground->processCollision(obj);
		if (result.flag)
		{
			int dx = abs(result.intersectionPoint.x - obj->getX());
			int dy = abs(result.intersectionPoint.y - obj->getY());
			result2.flag = result.flag;
			if (dx < dxMin)
			{
				result2.intersectionPoint.x = result.intersectionPoint.x;
				dxMin = dx;
			}

			if (dy < dyMin)
			{
				result2.intersectionPoint.y = result.intersectionPoint.y;
				dyMin = dy;
			}

			

			if (obj->getId() == Global::ALADDIN)
			{
				Aladdin* aladdin = (Aladdin*)actionObject;
				aladdin->refreshTime();
				if (aladdin->IsJump() && (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT)))
				{
					aladdin->setState(Global::Run);
					aladdin->getAladdinAction()->SetCurrentFrame(Global::Run, 6);
					
				}
				if (!aladdin->isGround())
					aladdin->Stand();
			}

			actionObject->setGround(true);
		}
	}

	return result2;
}

Collision::ResultCollision StaticObject::stairCollision(Object * obj)
{
	ActionObject* actionObject = (ActionObject*)obj;
	Collision::ResultCollision result;
	for each (auto stair in this->_listStair)
	{
		result = stair->processCollision(obj);
		if (result.flag)
			return result;
	}

	return result;
}

Collision::ResultCollision StaticObject::wallCollision(Object * obj)
{
	Collision::ResultCollision result;
	ActionObject* actionObject = (ActionObject*)obj;

	for each (auto wall in this->_listWall)
	{
		result = wall->processCollision(obj);
		if (result.flag)
		{
			if (obj->getId() == Global::ALADDIN)
			{
				Aladdin* aladdin = (Aladdin*)actionObject;
				aladdin->refreshTime();
				aladdin->setState(Global::In_climb);
				aladdin->getAladdinAction()->SetCurrentFrame(Global::In_climb, 2);
			}
			return result;
		}
	}
	return result;
}

Collision::ResultCollision StaticObject::actionGroundCollision(Object * obj)
{
	Collision::ResultCollision result, result2;
	ActionObject* actionObject = (ActionObject*)obj;

	int  dxMin = INT_MAX, dyMin = INT_MAX;

	return result2;
}

void StaticObject::permissionStair(Object * obj)
{
	WRect bound1(4544, 8118, 760, 248);//Hình chữ nhật chứa stair dưới
	WRect bound2(4536, 8278, 624, 208);//Hình chữ nhật chứa stair trên
	std::vector<int> listStair1;
	std::vector<int> listStair2;

	for (int i = 0; i < this->_listStair.size(); i++)
	{
		if (bound1.isContain(_listStair[i]->getRectBound()))
			listStair1.push_back(i);
		else if (bound2.isContain(_listStair[i]->getRectBound()))
			listStair2.push_back(i);
	}

	if (listStair1.size() == 0)
		return;

	Aladdin* aladdin = (Aladdin*)obj;

	WRect landmarkRect1(5216, 8110, 8, 224);
	WRect landmarkRect2(4520, 8294, 8, 200);
	WRect landmarkRect3(5456, 8254, 8, 128);

	//Nếu nhân vật va chạm với điểm mốc
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), landmarkRect1, 0, 0);
	if (result.flag && result.normalx == -1)
	{
		int decide = aladdin->getDecideStair();
		aladdin->setDecideStair(((decide == 0) ? 1 : 0));
	}

	result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), landmarkRect2, 0, 0);
	if (result.flag && result.normalx == 1)
	{
		int decide = aladdin->getDecideStair();

		if (decide == 1)
			aladdin->setDecideStair(2);
		else if (decide == 2)
			aladdin->setDecideStair(1);
	}

	result = Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), landmarkRect3, 0, 0);
	if (result.flag && result.normalx == 1)
	{
		aladdin->setDecideStair(1);
	}

	switch (aladdin->getDecideStair())
	{
	case 0:
	{
		for (auto i = 0; i < this->_listGround.size(); i++)
		{
			if (_listGround[i]->getX() == 4488 && _listGround[i]->getY() == 8094)
				this->_listGround.erase(this->_listGround.begin() + i);
		}
		for each (int indexStair in listStair1)
			this->_listStair[indexStair]->setAllow(false);
		for each (int indexStair in listStair2)
			this->_listStair[indexStair]->setAllow(false);
		break;
	}
	case 1:
	{
		for each (int indexStair in listStair1)
			this->_listStair[indexStair]->setAllow(true);
		for each (int indexStair in listStair2)
			this->_listStair[indexStair]->setAllow(false);
		break;
	}
	case 2:
	{
		for each (int indexStair in listStair1)
			this->_listStair[indexStair]->setAllow(true);
		for each (int indexStair in listStair2)
			this->_listStair[indexStair]->setAllow(true);
		break;
	}
	}
}

int StaticObject::distance(int x, int y)
{
	return x - y;
}

