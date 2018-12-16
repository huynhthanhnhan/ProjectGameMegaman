#include "HeadGunner.h"
#include "Aladdin.h"
#include<time.h>


HeadGunner::HeadGunner()
{
}
HeadGunner::HeadGunner(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_GUNNER_NORMAL, H_GUNNER_NORMAL, V_GUNNER, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::GUNNER;
	this->_region.update(xRegion, yRegion, widthRegion, heightRegion);
	this->LoadResource();
	this->_width = W_GUNNER_NORMAL;
	this->_height = H_GUNNER_NORMAL;
	this->_x = xRegion;
	this->_y = yRegion;
	this->_hp = 5;
	this->_state = Global::Stand;
}

HeadGunner::~HeadGunner()
{
}

void HeadGunner::update(float deltaTime)
{
	if (this->_hp == 0)
		this->takeAction(Global::Dead);

	if (this->_isDead)
		return;
	if (abs(this->_x - this->_aladdinLocation.x) <= D_ATTACK_GUNNER)
	{
		this->takeAction(Global::Attack);
	}
	if (this->_start)
		this->takeAction(Global::Stand);
	else if (this->_isFinishAction)
		this->takeAction(Global::NoneAction);
}

bool HeadGunner::isAttack()
{
	return (!this->_state == Global::Dead || !this->_state == Global::NoneAction);
}

void HeadGunner::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

void HeadGunner::Refresh()
{
}

void HeadGunner::LoadResource()
{
	//=========================================================
	//Attack
	//=========================================================
	std::vector<Rect*> attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "headgunner_launch_rocket_1");
	//for each (auto rect in attackResource)
	//	rect->setCenter(0, 0, 0);
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "headgunner");
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);
}

void HeadGunner::UpdateRender(Global::EState currentState)
{
	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
	this->_isDead = true;

}
