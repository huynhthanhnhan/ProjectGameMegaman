#include "Aladdin.h"
#include<math.h>
#include"Collision.h"
#include"Ground.h"
#include"Camera.h"
#include"Enemy.h"

Aladdin* Aladdin::_instance;
Aladdin* Aladdin::getInstance()
{
	if (!_instance)
		_instance = new Aladdin();
	return _instance;
}
Aladdin::Aladdin()
{

}

void Aladdin::Init(int x, int y, int number_apple, int hp, int life)
{
	this->_x = x;
	this->_y = y;
	this->_startPosition = D3DXVECTOR2(x, y);
	this->_width = ALADDIN_WIDTH;
	this->_height = ALADDIN_HEIGHT_NORMAL;
	this->updateBody();
	this->_id = Global::ALADDIN;

	this->_state = Global::Stand;
	this->_direct = Global::Right;
	this->loadResource();

	this->_countRun = 0;
	this->_countDash = 0;
	this->_countJump = 0;
	this->_timeAction = 0;
	this->_ay = -ACCELERATION;//Vì chiều dương hướng của trục y hướng xuống(= gia tốc trọng trường)
	this->_decideStair = 0;

	this->_numberOfApple = number_apple;
	this->_hp = hp;
	this->_life = life;
}

Aladdin::~Aladdin()
{
}

void Aladdin::update(float deltaTime)
{
	this->_deltaTime = deltaTime;		//Khoảng thời gian giữa 2 frame liên tiếp

	this->caculateSpeed(deltaTime);

	switch (this->_state)
	{
	case Global::Run:
	{
		break;
	}
	
	}

	StaticObject::Instance()->permissionStair(this);
	this->_isGround;
	//Xét va chạm với các static object
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
	//Update rectangle of object depend on object location
	this->updateBody();
	this->_countDash += (_state == Global::Dash) ? 1 : 0;
	this->_countRun += (_state == Global::Run) ? 1 : 0;
	this->_countJump += (_state == Global::Jump) ? 1 : 0;
}

void Aladdin::render()
{
	this->transform();
	D3DXVECTOR3 position = D3DXVECTOR3(this->_transform._position.x, this->_transform._position.y, 0);
	if (_state == Global::OnTrap)
	{
		_state = Global::Hurting;
	}

	if (this->_isReset)
	{
		if (this->_drawReset)
			this->_aladdinAction->Render(this->_direct, this->_state, position);
		else
		{
			if (this->_state != Global::Climb && !this->IsJump())
				//Ko draw những vẫn tăng index lên để tránh trường hợp ne1m 2 quả táo cùng lúc
			{

				int index = (this->_aladdinAction->GetCurrentFrame(this->_state) + 1) % this->_aladdinAction->GetListSprite().at(this->_state)->GetListRect().size();
				if (index == 0)
					this->_aladdinAction->SetCurrentFrame(this->_state, this->_aladdinAction->GetListSprite().at(this->_state)->GetListRect().size() - 1);
				else
					this->_aladdinAction->SetCurrentFrame(this->_state, index);
			}
		}

		this->_drawReset = (this->_drawReset) ? false : true;
		this->_countReset++;
		if (this->_countReset == 20)
		{
			this->_countReset = 0;
			this->_isReset = false;
		}
	}
	else
		this->_aladdinAction->Render(this->_direct, this->_state, position);// , _tramsfrom._scale, _tramsfrom._translation, _tramsfrom._rotation, _tramsfrom._rotationCenter);

	if (this->_numberOfApple <= 0)
		return;

	//Create Apple
	switch (_state)
	{
	case Global::Stand_shoot:
	{
		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		float d = 20;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;

		BulletManager::Instance()->addBullet(new Apple(appleLocation.x, appleLocation.y, this->_direct));
		//this->_numberOfApple--;
		break;

	}
	}
}

void Aladdin::updateBody()
{
	//Update RectBody
	switch (this->_state)
	{
	case Global::HitClimb:
	case Global::ThrowClimb:
	case Global::Climb:
	default: this->_height = ALADDIN_HEIGHT_NORMAL; break;
	}
	int width = 1;
	//Update RectCollision
	_rectBound.update(_x - _width / 2, _y + this->_height, _width, this->_height);
	_rectBound2.update(_x - width / 2, _y + this->_height, width, this->_height);
	int x = (this->_direct == Global::Right) ? this->_x + this->_width / 2 : this->_x - this->_width / 2 - SWORD_WIDTH;
	int y = this->_y + this->_height + 30;
	width = SWORD_WIDTH;
	int height = this->_height + 30;
	this->_rectSword.update(x, y, width, height);
}

Collision::ResultCollision Aladdin::processCollision(Object * obj)
{
	WRect rectBody, rectBody2;
	int vx, vy, vx2, vy2;
	Bullet* bullet = (Bullet*)obj;
	if (this->_isReset)
		return Collision::ResultCollision();
	bool isAttack;
	if (obj->getId() == Global::SWORDBULLET || obj->getId() == Global::CIVILIANBULLET || obj->getId() == Global::JAFARBULLET || obj->getId() == Global::SNAKEBULLET)
	{
		//Bullet* bullet = (Bullet*)obj;
		if (bullet->isCanAttack())
		{
			//WRect rectBody, rectBody2;
			//int vx, vy, vx2, vy2;
			if (this->IsHit())
			{	
				rectBody = this->_rectSword;
				vx = 0;
				vy = 0;
				if (Collision::Instance()->AABB(rectBody, obj->getRectBound()) || (Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), rectBody, vx, vy).flag))
				{
					if (bullet->getId() == Global::SWORDBULLET)
					{
						bullet->turnBack(this->_direct);
						this->_sound = Sound::Instance();
						this->_sound->play(SOUND_SWORD_CHING);
					}
					else
					{
						if (bullet->getId() == Global::CIVILIANBULLET)
						{
							this->_sound->play(SOUND_CLOUD_POOF);
							bullet->setState(Global::Dead);
						}
						else bullet->setGround();
					}
				}
			}
			else
			{
				rectBody = this->_rectBound;
				vx = this->_vx;
				vy = 0;
				if (Collision::Instance()->AABB(rectBody, obj->getRectBound()) || (Collision::Instance()->sweptAABB(obj->getRectBound(), obj->getVx(), obj->getVy(), rectBody, vx, vy).flag))
				{
					if (bullet->getId() == Global::CIVILIANBULLET)
					{
						this->Hurting();
						//bullet->setGround();
					}
					else
					{
						this->Hurting();
						bullet->setState(Global::NoneAction);
					}
				}
			}
		}
	}
	else
	{
		Enemy* enemy = (Enemy*)obj;
		if (Collision::Instance()->AABB(this->_rectBound, enemy->getRectBound()) && enemy->isCollision() && enemy->getId() != Global::CIVILIAN3)
		{
			this->Hurting();
		}
		if (enemy->isAttack())
		{
			if (Collision::Instance()->AABB(this->_rectBound, enemy->getRectSword()))
			{
				if (enemy->getId() == Global::CIVILIAN3 && this->_state != Global::Hurting)
				{
					if (this->_numberOfApple < 3)
						this->_numberOfApple = 0;
					else
						this->_numberOfApple = this->_numberOfApple - 3;
					this->setState(Global::Hurting);
					this->_sound = Sound::Instance();
					this->_sound->play(SOUND_ALADDIN_HURT);
				}
				else
					this->Hurting();
			}
		}
	}
	return Collision::ResultCollision();
}

void Aladdin::loadResource()
{
	this->_aladdinAction = new AladdinAction();
}


void Aladdin::caculateSpeed(float deltaTime)
{
	deltaTime /= 1000;					//Chuyển từ ms->s
	this->_v0 = DISTANCE / deltaTime;	//Tính vận tốc gốc của nhân vật
	this->_timeAction += deltaTime;		//Thời gian trong một hành động

	float vx = 0, vy = 0, ax = 0, ay = 0;
	float angle = 0;
	bool canMoveX = true, canMoveY = true;
	Global::EDirection directX, directY;
	directX = _direct;
	directY = Global::Up;
	ay = _ay;
	switch (this->_state)
	{
	case Global::Revival:
	{
		canMoveX = false;
		canMoveY = false;
		ay = 0;
		break;
	}
	case Global::StopJump:
	case Global::Hurting:
	case Global::Stand:
	{
		this->_v0 = 0;
		canMoveY = false;
		break;
	}
	case Global::Appearance:
	{
		this->_v0 = 0;
		break;
	}
	case Global::Run:
	{
		angle = 0;
		canMoveY = false;
		break;
	}
	case Global::StopRun:
	{
		angle = 0;
		this->_v0 /= 3;
		break;
	}
	//case Global::JumpClimb:
	//{
	//	this->_v0 *= 0;// 1.8;
	//	angle = 1.1345;
	//	if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
	//		canMoveX = true;
	//	else
	//		canMoveX = false;

	//	ax = 0;

	//	if (this->_isGround)
	//		canMoveY = false;
	//	break;
	//}
	case Global::Fall:
	{
		this->_v0 /= 2;
		angle = 0;
		canMoveY = true;
		if (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT))
		{
			canMoveX = true;
		}
		else
			canMoveX = false;
		break;
	}
	case Global::In_climb:
	{
		ay = 0;
		ax = 0;
		canMoveX = false;
		this->_v0 /= 2;
		angle = 1.571;
		if(!KeyBoard::Instance()->isKeyPress(DIK_LEFT)&&!KeyBoard::Instance()->isKeyPress(DIK_RIGHT))
		{
			//this->_aladdinAction->setDirect(Global::None);
			canMoveY = false;
		}

		break;
	}
	case Global::Jump:
	{
		this->_v0 *=2;
		angle = 1.571;
		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;
		canMoveY = true;
		//if (this->_isGround)
		//	canMoveY = false;
		break;
	}
	case Global::Dash:
	{
		angle = 1.0f;
		this->_vx = 100;
		this->_v0 *= 1;
		canMoveX = true;
		canMoveY = false;
		break;
	}
	case Global::Stand_shoot:
	{
		this->_v0 *= 2.5;
		angle = 0;
		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;
		if (this->_isGround)
			canMoveY = false;
		break;
	}
	case Global::ThrowSwing: break;
	}

	vx = (canMoveX) ? this->_v0 : 0;// *sin(angle) : 0;
	vy = (canMoveY) ? this->_v0 : 0;// *sin(angle) : 0;

	vx *= (directX == Global::Right) ? 1 : -1;
	ax *= (directX == Global::Right) ? 1 : -1;
	vy *= 1;

	float vx_Immediately = vx + ax*(_timeAction - deltaTime);
	float vy_Immediately = vy + ay*(_timeAction - deltaTime);

	this->_vx = vx_Immediately*deltaTime + 0.5*ax*pow(deltaTime, 2);
	this->_vy = vy_Immediately*deltaTime + 0.5*ay*pow(deltaTime, 2);
}
//===================================================
//Base Move action
//===================================================
#pragma region BaseMove
void Aladdin::Stand()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::Stand)
		return;

	if (_state == Global::Run && this->_countRun >= 5 && this->_isGround)
	{
		this->Running();
		this->_countRun = 0;
		return;
	}
	if (_state == Global::Jump && this->_countJump >= 6 && this->_isGround)
	{
		this->Jump();
		this->_countJump = 0;
		return;
	}
	this->_aladdinAction->Refresh();
	this->_countRun = 0;
	this->_countJump = 0;
	this->_state = Global::Stand;
}

void Aladdin::Appearance()
{
	if (_state == Global::Appearance)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::Appearance;
}

void Aladdin::Running()
{
	//this->set(1, 0, 1, 0);
	if (_state == Global::Run)
		return;
	if (_state == Global::Stand && this->_countRun >= 5 && this->_isGround)
	{
		this->Stand();
		this->_countRun = 0;
		return;
	}
	if (_state == Global::Jump && this->_countRun >= 5 && this->_isGround)
	{
		this->Jump();
		this->_countRun = 0;
		return;
	}
	this->_aladdinAction->Refresh();
	this->_state = Global::Run;
}

void Aladdin::Jump()
{
	if (_state == Global::Jump)
		return;
	if (_state == Global::Stand && this->_countJump >= 6 && this->_isGround)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
		this->_countJump = 0;
		return;
	}
	this->_aladdinAction->Refresh();
	this->_state = Global::Jump;
}
#pragma endregion
//===================================================
//PushWall
//===================================================
#pragma region PushWall
//bool Aladdin::IsPushWall()
//{
//	//return _state == Global::PushWall;
//}

void Aladdin::PushWall()
{
	//this->set(1, 0, 1, 0);
	//if (_state == Global::PushWall)
	//	return;
	//this->_aladdinAction->Refresh();
	//this->_state = Global::PushWall;
}
#pragma endregion
//===================================================
//Climb
//===================================================
#pragma region Climb
void Aladdin::Climb()
{
	if (_state == Global::Climb)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::Climb;
}

#pragma endregion
//===================================================
//Swing
//===================================================
#pragma region Swing
void Aladdin::Hurting()
{
	if (this->_state == Global::Hurting)
		return;
	if (this->_state == Global::Climb || this->_state == Global::Jump)
	{
		this->_hp--;
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_ALADDIN_HURT);
		this->setReset();
		return;
	}
	this->_hp--;
	this->setReset();
	this->_sound = Sound::Instance();
	this->_sound->play(SOUND_ALADDIN_HURT);
	this->_aladdinAction->Refresh();
	//this->_state = Global::Hurting;
	this->setState(Global::Hurting);
}
#pragma endregion
//===================================================
//Hit
//===================================================
#pragma region Hit
void Aladdin::HitStand()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::HitStand)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitStand;}

void Aladdin::HitStand2()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::HitStand2)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitStand2;
}

void Aladdin::HitRun()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::HitRun)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitRun;
}

void Aladdin::HitSitDown()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::HitSitDown)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitSitDown;
}

bool Aladdin::IsHit()
{
	if (_state != Global::HitStand && _state != Global::HitStand2 && _state != Global::HitRun && _state != Global::HitSitDown && _state != Global::HitJump && _state != Global::HitClimb && _state != Global::HitSwing)
		return false;

	int x = (this->_direct == Global::Right) ? this->_x + this->_width / 2 : this->_x - this->_width / 2 - SWORD_WIDTH;
	int y = this->_y + this->_height;
	int width = SWORD_WIDTH;
	int height = this->_height;
	this->_rectSword.update(x, y, width, height);

	bool result = ((_state == Global::HitStand && this->_aladdinAction->GetCurrentFrame(_state) == 3) ||
		(_state == Global::HitSitDown&& this->_aladdinAction->GetCurrentFrame(_state) == 3) ||
		(_state == Global::HitJump && this->_aladdinAction->GetCurrentFrame(_state) == 4) ||
		(_state == Global::HitFall && this->_aladdinAction->GetCurrentFrame(_state) == 4) ||
		(_state == Global::HitClimb && (this->_aladdinAction->GetCurrentFrame(_state) == 3 || this->_aladdinAction->GetCurrentFrame(_state) == 5)) ||
		(_state == Global::HitSwing && (this->_aladdinAction->GetCurrentFrame(_state) == 3 || this->_aladdinAction->GetCurrentFrame(_state) == 5)) ||
		(_state == Global::HitRun && (this->_aladdinAction->GetCurrentFrame(_state) == 5)) ||
		(_state == Global::HitStand2 && (this->_aladdinAction->GetCurrentFrame(_state) == 7 || this->_aladdinAction->GetCurrentFrame(_state) == 14)));
	return result;
}
#pragma endregion

//===================================================
//Jump
//===================================================
#pragma region Jump
bool Aladdin::IsJump()
{
	return (_state == Global::Jump);
}


void Aladdin::Fall()
{
	if (_state == Global::Fall)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Fall;
}

void Aladdin::StopJump()
{
	this->_timeAction = 0;
	this->_state = Global::Stand;
}
void Aladdin::Revival()
{
	if (this->_state == Global::Appearance)
		return;
	this->_timeAction = 0;
	this->_countRun = 0;
	if (!this->_startPosition_)
	{
		this->setState(Global::Appearance);
		this->setReset();
		this->_x = this->_startPosition.x;
		this->_y = this->_startPosition.y;
		this->updateBody();
		return;
	}
	this->_state = Global::Appearance;
	this->setReset(false);
	this->_x = this->_startPosition.x;
	this->_y = this->_startPosition.y;
	this->updateBody();
}

void Aladdin::Stand_shoot()
{
	if (_state == Global::Stand_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Stand_shoot;
}
void Aladdin::Run()
{
	if (_state == Global::Run)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Run;
}
void Aladdin::Run_shoot()
{
	if (_state == Global::Run_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Run_shoot;
}

void Aladdin::Jump_shoot()
{
	if (_state == Global::Jump_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Jump_shoot;
}
void Aladdin::In_climb()
{
	if (_state == Global::In_climb)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::In_climb;
}
void Aladdin::Out_climb()
{
	if (_state == Global::Out_climb)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Out_climb;
}
void Aladdin::In_climb_shoot()
{
	if (_state == Global::In_climb_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::In_climb_shoot;
}
void Aladdin::Out_climb_shoot()
{
	if (_state == Global::Out_climb_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Out_climb_shoot;
}
void Aladdin::Climb_ladder()
{
	if (_state == Global::Climb_ladder)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Climb_ladder;
}
void Aladdin::Climb_ladder_shoot()
{
	if (_state == Global::Climb_ladder_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Climb_ladder_shoot;
}
void Aladdin::Dash()
{
	if (_state == Global::Dash)
	{
		if (this->_countDash >= 7 && this->_isGround)
		{
			Aladdin* aladdin = Aladdin::getInstance();
			aladdin->Stand();
			this->_countDash = 0;
			bDash = false;;
			return;
		}
		return;
	}
	
	if (!bDash)
		return;
	if (_state == Global::Stand && this->_countDash >= 4 && this->_isGround)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
		this->_countDash = 0;
		bDash = false;;
		return;
	}
	this->_aladdinAction->Refresh();
	this->_state = Global::Dash;
	
}
void Aladdin::Destroyed()
{
	if (_state == Global::Destroyed)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Destroyed;
}
void Aladdin::Hurt()
{
	if (_state == Global::Hurt)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Hurt;
}
void Aladdin::Defense_hurt()
{
	if (_state == Global::Defense_hurt)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Defense_hurt;
}
void Aladdin::Weak_sit()
{
	if (_state == Global::Weak_sit)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Weak_sit;
}
void Aladdin::Dash_shoot()
{
	if (_state == Global::Dash_shoot)
		return;
	if (_state == Global::Stand )
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
		return;
	}
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Dash_shoot;
}





#pragma endregion
//===================================================
//Stop
//===================================================
#pragma region Stop
void Aladdin::StopRun()
{
	if (_state == Global::StopRun)
		return;
	this->_aladdinAction->Refresh();
	this->_countRun = 0;
	this->_timeAction = 0;
	this->_state = Global::StopRun;
}
#pragma endregion
//===================================================
//get and set properties
//===================================================
#pragma region get and set properties
AladdinAction * Aladdin::getAladdinAction()
{
	return this->_aladdinAction;
}

WRect Aladdin::getRectBound2()
{
	return this->_rectBound2;
}

WRect Aladdin::getRectWithBar()
{
	return this->_rectWithBar;
}
int Aladdin::getDecideStair()
{
	return this->_decideStair;
}
void Aladdin::setDecideStair(int decide)
{
	this->_decideStair = decide;
}
bool Aladdin::isReset()
{
	return this->_isReset;
}
bool Aladdin::isVictory1()
{
	return this->_isVictory1;
}

void Aladdin::setVictory1(bool flag)
{
	this->_isVictory1 = flag;
	this->_startPosition_ = false;
}

bool Aladdin::isVictory2()
{
	return this->_isVictory2;
}

void Aladdin::setVictory2(bool flag)
{
	this->_isVictory2 = flag;
}
void Aladdin::setReset(bool flag)
{
	this->_isReset = flag;
}
void Aladdin::increaseApple()
{
	this->_numberOfApple++;
}
void Aladdin::setHp(int hp)
{
	this->_hp = hp;
	this->_hp = (this->_hp > 8) ? 8 : this->_hp;
}

void Aladdin::setGem(int Gem)
{
	this->_numberOfGem = Gem;
}

void Aladdin::increaseGem()
{
	this->_numberOfGem++;
}
void Aladdin::increaseScore(int score)
{
	this->_score += score;
}
void Aladdin::setStartPosition(int x, int y)
{
	this->_startPosition = D3DXVECTOR2(x, y);
	this->_startPosition_ = true;
}
void Aladdin::setLife(int life)
{
	this->_life = life;
}
int Aladdin::getHp()
{
	return this->_hp;
}
int Aladdin::getNumberOfApple()
{
	return this->_numberOfApple;
}
int Aladdin::getNumberOfGem()
{
	return this->_numberOfGem;
}
int Aladdin::getScore()
{
	return this->_score;
}
int Aladdin::getLife()
{
	return this->_life;
}
#pragma endregion