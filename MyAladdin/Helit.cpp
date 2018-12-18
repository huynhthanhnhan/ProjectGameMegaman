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
	this->_timeMove = 1;
	this->_isMove = true;
	this->bDown = true;
	this->_ay = -ACCELERATION/10;
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

	this->_direct = (this->_x >= this->_aladdinLocation.x) ? Global::Left : Global::Right;

	this->caculateSpeed(deltaTime);
	

	if (abs(this->_x - this->_aladdinLocation.x) <= D_ATTACK_HELIT)
	{
		this->_y += this->_vy;
		if (this->_isMove)
		{
			_rectBound.update(this->_x, _y + this->_height, this->_width, this->_height);
		}
		if (this->_y <= this->_aladdinLocation.y && this->bDown)
		{
			this->_y = this->_aladdinLocation.y+10;
			this->_isMove = false;
			if (this->_start)
				this->takeAction(Global::helit_Shoot);
			else if (this->_isFinishAction)
				this->takeAction(Global::NoneAction);
			if (this->_state == Global::helit_Shoot && this->GetCurrentFrame(_state) == 4 && this->_timeAttack >= 10)
			{
				BulletManager::Instance()->addBullet(new HelitBullet(this->_x, this->_y + this->_height - 60, this->_direct));
				this->_timeAttack = 0;
				this->bDown = false;
				this->_isMove = true;
				this->_timeMove--;
			}
		}
		if (this->_y - this->_aladdinLocation.y >= 250 && this->_timeMove>=0)
			this->bDown = true;
	}
	this->_timeAttack++;
	
}
void Helit::caculateSpeed(float deltaTime)
{
	deltaTime /= 1000;					//Chuyển từ ms->s
	this->_v0 = DISTANCE / deltaTime;	//Tính vận tốc gốc của nhân vật
	this->_timeAction += deltaTime;		//Thời gian trong một hành động
	float vx = 0, vy = 0, ax = 0, ay = 0;
	float angle = 0;
	bool canMoveX = true, canMoveY = true;
	Global::EDirection directX, directY;
	directX = this->_direct;
	directY = Global::Up;
	ay = _ay;


	if (this->_isMove)
	{
		this->_v0 *= 0.000000001;
		angle = 0.1;
		canMoveY = true;
	}
	else
	{
		this->_v0 = 0;
		canMoveY = false;
	}
	vy = (canMoveY) ? this->_v0*sin(angle) : 0;

	vy *= (bDown) ? 1 : -1;
	ay *= (bDown) ? 1 : -1;

	float vy_Immediately = vy + ay*(_timeAction - deltaTime);

	this->_vy = vy_Immediately*deltaTime + 0.5*ay*pow(deltaTime, 2);
}

bool Helit::isAttack()
{
	return (!this->_state == Global::Dead || !this->_state == Global::NoneAction);
}

void Helit::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Right);
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

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_Stand");
	this->mListSprite[Global::helit_Stand] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "helit_Shoot");
	this->mListSprite[Global::helit_Shoot] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
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

//Collision::ResultCollision Helit::processCollision(Object * obj)
//{
//	//if (this->_isDead)
//	//	return Collision::ResultCollision();
//	//switch (obj->getId())
//	//{
//	//case Global::ALADDIN:
//	//{
//	//	this->_aladdinLocation = (D3DXVECTOR2)obj->getCurrentLocation();
//	//	if (Collision::Instance()->AABB(obj->getRectBound(), this->_region))
//	//		this->_start = true;
//	//	else
//	//		this->_start = false;
//
//	//	Aladdin* aladdin = (Aladdin*)obj;
//	//	if (aladdin->IsHit())
//	//	{
//	//		if (Collision::Instance()->AABB(aladdin->getRectSword(), this->_rectBound))
//	//			this->takeAction(Global::Dead);
//	//	}
//	//	break;
//	//}
//	//}
//	return Collision::ResultCollision();
//}
