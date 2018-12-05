#include "FireBurning.h"
#include "Aladdin.h"
#include "Jafar.h"
#include<time.h>

FireBurning::FireBurning(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_FIRE, H_FIRE, V_FIRE, direct)
{
	this->_id = Global::FIRE;
	this->_state = Global::NoneAction;
	this->_type = Global::Enemy;
	this->LoadResource();
}

FireBurning::~FireBurning()
{
}

void FireBurning::set(bool flag)
{
	this->isSnake = flag;
}

Collision::ResultCollision FireBurning::processCollision(Object * obj)
{
	WRect rect1;
	Aladdin* _aladdin;
	_aladdin = Aladdin::getInstance();
	rect1 = _aladdin->getRectBound();
	WRect rect2 = this->getRectBound();
	float vx1 = _aladdin->getVx();
	float vy1 = _aladdin->getVy();
	float vx2 = 0;
	float vy2 = 0;

	if (!Aladdin::getInstance()->isJafar())
	{
		Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);
		//Chỉ xét hướng va chạm từ trên xuống
		if (result.normaly == -1 || result.normaly == 0 && obj->getId() == Global::ALADDIN)
			result.flag = false;
		if (!result.flag)
			return result;

		this->_start = (result.flag) ? true : _start;

		if (obj->getId() == Global::ALADDIN )
		{
			result.intersectionPoint.x = obj->getX() + obj->getVx();
		}
		else
			result.intersectionPoint.x = obj->getX() + obj->getVx()*result.collisionTime;

		result.intersectionPoint.y = obj->getY() + obj->getVy()*result.collisionTime;

		if (!_aladdin->isReset() && this->GetCurrentFrame(Global::Stand) > 4)
			_aladdin->Hurting();
		return result;
	}
	return Collision::ResultCollision();
}

bool FireBurning::isAttack()
{
	return ((_state == Global::Stand) && (this->GetCurrentFrame(_state) == 0));
}

void FireBurning::update(float deltaTime)
{
	if (this->_state == Global::Stand && this->GetCurrentFrame(this->_state) == 1)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_FIRE_FROM_COAL);
	}
	if (!_start)
	{
		this->_state = Global::NoneAction;
	}
	else
	{
		this->_state = Global::Stand;
	}
	if ((_state == Global::Stand) && (this->GetCurrentFrame(_state) == 8))
	{
		_start = false;
	}
	this->updateBody();
}

void FireBurning::Refresh()
{
}

void FireBurning::LoadResource()
{
	//=================================================================
	//Stand
	//=================================================================
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getFireTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "Fire"));
}

void FireBurning::UpdateRender(Global::EState currentState)
{

}

void FireBurning::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}
