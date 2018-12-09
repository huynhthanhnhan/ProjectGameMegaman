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
	this->_ay = 0;// -ACCELERATION;
	this->_angle = 0;//0.26;//15 độ
	this->_rotation = 0;
	this->updateBody();
	this->_distanceBullet = 25;//DISTANCE_APPLE;
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

	////=========================================================
	////Explosing Apple
	////=========================================================
	//std::vector<Rect*> explosing_apple = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_BULLET,"Bullet_lv1");
	//this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
	//	explosing_apple);

}

void Apple::UpdateRender(Global::EState currentState)
{
	//switch (currentState)
	//{
	//case Global::Stand:
	//{
	//		
	//	break;
	//}
	//case Global::Run:
	//{
	//	break;
	//}
	//case Global::Dash:
	//{
	//	break;
	//}
	//default:
	//{
	//	this->_ax = this->_ay = this->_v0 = 0;
	//	this->_angle = 0;
	//	this->_rotation = 0;
	//	this->_distanceBullet = 0;
	//	break;
	//}
	//	
	//}
	//
	//{
	//	/*this->_ax = this->_ay = this->_v0 = 0;
	//	this->_angle = 0;
	//	this->_rotation = 0;
	//	this->_distanceBullet = 0;*/
	//}
}

bool Apple::isFinish()
{
	return (this->GetCurrentFrame(Global::Stand) == 5 || this->GetCurrentFrame(Global::Dead) == 9);
}

bool Apple::isCanAttack()
{
	return (this->GetCurrentFrame(Global::Stand) == 0);
}
