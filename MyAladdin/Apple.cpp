#include "Apple.h"
#include"Ground.h"
#include"Camera.h"


Apple::Apple(int x, int y, Global::EDirection direct)
	:Bullet(x, y, direct)
{
	this->_type = Global::AladdinParty;
	this->_id = Global::APPLEBULLET;
	this->_state = Global::Stand;
	this->_width = 10;
	this->_height = 10;
	this->_ay = 0;
	this->_angle = 0;
	this->_rotation = 0;
	this->updateBody();
	this->_distanceBullet = DISTANCE_APPLE;
	this->_timeLife = 0;
	this->LoadResource();
}

Apple::~Apple()
{
}

Collision::ResultCollision Apple::processCollision(Object * obj)
{
	return Collision::ResultCollision();
}

void Apple::LoadResource()
{
	std::vector<Rect*>	_listRectSource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_BULLET, "Bullet_lv1");

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		_listRectSource);

	_listRectSource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_BULLET, "Bullet_lv2");

	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		_listRectSource);

	_listRectSource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_BULLET, "Bullet_lv3");

	this->mListSprite[Global::Dash] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		_listRectSource);

	//=========================================================
	//Explosing Apple
	//=========================================================
	std::vector<Rect*> explosing_apple = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_BULLET, "Bullet_lv3");
	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		explosing_apple);

}

void Apple::UpdateRender(Global::EState currentState)
{
	//if (currentState == Global::Stand)
	//{
	//	if (!this->isGround())
	//		this->SetCurrentFrame(currentState, 0);//Chỉ hiện thị hình ảnh quả táo
	//	else
	//	{
	//		if (this->GetCurrentFrame(_state) == 2)
	//		{
	//			
	//		}
	//	}
	//}
	/*else
	{
		this->_ax = this->_ay = this->_v0 = 0;
		this->_angle = 0;
		this->_rotation = 0;
		this->_distanceBullet = 0;
	}*/
	this->_timeLife++;
}

bool Apple::isFinish()
{
	return (this->GetCurrentFrame(Global::Stand) == 5 || this->GetCurrentFrame(Global::Dead) == 9||this->_timeLife>=15);
}

bool Apple::isCanAttack()
{
	return (this->GetCurrentFrame(Global::Stand) == 0);
}
