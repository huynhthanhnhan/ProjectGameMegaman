#include "Notorbanger.h"
#include"Aladdin.h"
#include<time.h>

Notorbanger::Notorbanger()
{
}

Notorbanger::Notorbanger(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_Notorbanger_NORMAL, H_Notorbanger_NORMAL, V_Notorbanger, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::NOTORBANGER;
	this->_direct = direct;
	this->_region.update(xRegion, yRegion, widthRegion, heightRegion);
	this->LoadResource();
	this->_width = W_Notorbanger_NORMAL;
	this->_height = H_Notorbanger_NORMAL;
	this->_x = xRegion;
	this->_y = yRegion;
	this->_ay = -ACCELERATION;
	this->_hp = 1;
	this->_timeAttack = 0;
	this->_state = Global::Stand;
	_timeDelay = 10;
}


Notorbanger::~Notorbanger()
{
}

void Notorbanger::update(float deltaTime)
{
	if (this->_hp == 0)
		this->takeAction(Global::Dead);

	if (this->_isDead)
		return;

	this->_direct = (this->_x >= this->_aladdinLocation.x) ? Global::Left : Global::Right;
	if (abs(this->_x - this->_aladdinLocation.x) <= D_ATTACK_NOTORBANGER)
	{
		if (this->_start)
			this->takeAction(Global::Attack);
		else if (this->_isFinishAction)
			this->takeAction(Global::NoneAction);
		if (this->_state == Global::Attack)
			_timeDelayCount--;
		if (this->_state == Global::Attack && this->GetCurrentFrame(_state) == 2 && _time > 0 && _timeDelayCount < 0)
		{
			BulletManager::Instance()->addBullet(new NotorbangerBullet(this->_x - 30*((this->_direct == Global::Left) ? 1 : -1) + this->_width - 20, this->_y + this->_height + 40, this->_direct));
			_time--;
			_timeDelayCount = _timeDelay;
		}
		else
		{
			_time = 3;
		}
		this->caculateSpeed(deltaTime);

		if (!bJump)
		{
			this->takeAction(Global::Attack);
		}
		else
		{
			this->takeAction(Global::notorbanger_jump);
		}

		Collision::ResultCollision result = StaticObject::Instance()->processCollision(this);
		if (!result.flag)
		{
			//Update new location
			this->_isGround = false;
			this->_x += this->_vx;
			this->_y += this->_vy;
		}
		else
		{
			this->_x = result.intersectionPoint.x;
			this->_y = result.intersectionPoint.y;
		}
		bJump;

		_rectBound.update(_x - _width / 2, _y + this->_height, this->_width, this->_height);
		//_rectBound2.update(_x - width / 2, _y + this->_height, width, this->_height);
		_timeAttack++;
	}
}

void Notorbanger::caculateSpeed(float deltaTime)
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
	if (bJump)
	{
		this->_v0 *= 3.0;
		angle = 2.356;
		canMoveX = true;
		if (this->_isGround)
			canMoveY = true;
	}
	else
	{
		canMoveX = false;
		canMoveY = false;
		ax = 0;
		ay = 0;
	}
	vx = (canMoveX) ? this->_v0*cos(angle) : 0;
	vy = (canMoveY) ? this->_v0*sin(angle) : 0;

	vx *= (directX == Global::Left) ? 1 : -1;
	ax *= (directX == Global::Left) ? 1 : -1;

	float vx_Immediately = vx + ax*(_timeAction - deltaTime);
	float vy_Immediately = vy + ay*(_timeAction - deltaTime);

	this->_vx = vx_Immediately*deltaTime + 0.5*ax*pow(deltaTime, 2);
	this->_vy = vy_Immediately*deltaTime + 0.5*ay*pow(deltaTime, 2);

	//this->_x = (this->_direct == Global::Right) ? this->_x + this->_vx : this->_x - this->_vx;
	//this->_y = this->_y + this->_vy/5;
}

bool Notorbanger::isAttack()
{
	return (!this->_state == Global::Dead || !this->_state == Global::NoneAction);
}

void Notorbanger::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Right);
}

void Notorbanger::Refresh()
{
}

void Notorbanger::LoadResource()
{
	//=========================================================
	//Attack
	//=========================================================
	std::vector<Rect*> attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_jump");
	this->mListSprite[Global::notorbanger_jump] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_attack_1");
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_after_attack_1");
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_attack_2");
	this->mListSprite[Global::notorbanger_attack_2] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_after_attack_2");
	this->mListSprite[Global::notorbanger_after_attack_2] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_fragment_1");
	this->mListSprite[Global::notorbanger_fragment_1] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_fragment_2");
	this->mListSprite[Global::notorbanger_fragment_2] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_fragment_3");
	this->mListSprite[Global::notorbanger_fragment_3] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);

	attackResource = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ENEMY, "notorbanger_fragment_4");
	this->mListSprite[Global::notorbanger_fragment_4] = new SpriteManager(ResourceImage::Instance()->getEnemy(),
		attackResource);
	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "explosiveEnemy");

	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture1(),
		explosing);
}

void Notorbanger::UpdateRender(Global::EState currentState)
{
	if (_timeAttack < 25 && this->_state == Global::Attack&&!bJump)
	{
		if(this->GetCurrentFrame(currentState)>=1)
			this->SetCurrentFrame(currentState, this->GetCurrentFrame(currentState)-1);
	}
	else
	{
		_timeAttack = 0;
	}
	if ((this->GetCurrentFrame(currentState) == 0 || this->GetCurrentFrame(currentState) == 1)&&this->_state ==Global::Attack&&!bJump)
		_timeAttack += 2;
	if (this->_state == Global::Attack&&this->GetCurrentFrame(currentState) == 3&&!bJump)
	{
		bJump = true;
		this->refreshTime();
		this->takeAction(Global::notorbanger_jump);
	}

	this->_isFinishAction = (this->GetCurrentFrame(currentState) == 0) ? true : false;
	if (this->_state == Global::Dead && this->GetCurrentFrame(this->_state) == 0)
		this->_isDead = true;
}

