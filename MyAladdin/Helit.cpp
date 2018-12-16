#include "Helit.h"
#include"Aladdin.h"
#include<time.h>

Helit::Helit()
{
}

Helit::Helit(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_Helit_NORMAL, H_Helit_NORMAL, V_Helit, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::HELIT;
	this->_direct = direct;
	this->_region.update(xRegion, yRegion, widthRegion, heightRegion);
	this->LoadResource();
	this->_width = W_Helit_NORMAL;
	this->_height = H_Helit_NORMAL;
	this->_x = xRegion;
	this->_y = yRegion;
	this->_hp = 1;
	this->_state = Global::Stand;
}


Helit::~Helit()
{
}

void Helit::update(float deltaTime)
{
	if (this->_hp == 0)
		this->takeAction(Global::Dead);

	if (this->_isDead)
		return;

	if (this->_start)
		this->takeAction(Global::Attack);
	else if (this->_isFinishAction)
		this->takeAction(Global::NoneAction);
	if (this->_state == Global::Attack && this->GetCurrentFrame(_state) == 0) /// set Frame ban
		BulletManager::Instance()->addBullet(new HelitBullet(this->_x + this->_width -100, this->_y + this->_height -50, this->_direct));
}

bool Helit::isAttack()
{
	return (!this->_state == Global::Dead || !this->_state == Global::NoneAction);
}

void Helit::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

void Helit::Refresh()
{
}

void Helit::LoadResource()
{
	//=========================================================
	//Attack
	//=========================================================
	std::vector<Rect*> attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_fan");
	this->mListSprite[Global::helit_fan] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_launch_rocket");
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit");
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_rocket");
	this->mListSprite[Global::helit_rocket] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_fragment_1");
	this->mListSprite[Global::helit_fragment_1] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_fragment_2");
	this->mListSprite[Global::helit_fragment_2] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_fragment_3");
	this->mListSprite[Global::helit_fragment_3] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);
	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy");

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture1(),
		explosing);
}

void Helit::UpdateRender(Global::EState currentState)
{
	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;
}

Collision::ResultCollision Helit::processCollision(Object * obj)
{
	//if (this->_isDead)
	//	return Collision::ResultCollision();
	//switch (obj->getId())
	//{
	//case Global::ALADDIN:
	//{
	//	this->_aladdinLocation = (D3DXVECTOR2)obj->getCurrentLocation();
	//	if (Collision::Instance()->AABB(obj->getRectBound(), this->_region))
	//		this->_start = true;
	//	else
	//		this->_start = false;

	//	Aladdin* aladdin = (Aladdin*)obj;
	//	if (aladdin->IsHit())
	//	{
	//		if (Collision::Instance()->AABB(aladdin->getRectSword(), this->_rectBound))
	//			this->takeAction(Global::Dead);
	//	}
	//	break;
	//}
	//}
	return Collision::ResultCollision();
}
