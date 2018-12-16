#include "Aladdin.h"
#include<math.h>
#include"Collision.h"
#include"Ground.h"
#include"Rope.h"
#include"Column.h"
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
	this->_timeAction = 0;
	this->_ay = -ACCELERATION;//Vì chiều dương hướng của trục y hướng xuống(= gia tốc trọng trường)
	this->_decideStair = 0;

	this->_numberOfApple = number_apple;
	this->_hp = hp;
	this->_life = life;
	this->bCharge = false;
	this->bulletLv = 0;
	this->_timeCharge = 0;
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
	this->Charge(deltaTime);

	this->_countRun += (_state == Global::Run) ? 1 : 0;
	this->_countDash += (_state == Global::Dash) ? 1 : 0;
	this->_countJump += (_state == Global::Jump) ? 1 : 0;
}

void Aladdin::Charge(float deltaTime)
{
	if (!bCharge)
	{
		this->_timeCharge = 0;
		return;
	}	
	else
	{
		_timeCharge++;
		if (_timeCharge >= 20)
		{
			this->bulletLv = 3;
			return;
		}
		if (_timeCharge >= 10 && _timeCharge < 20)
		{
			this->bulletLv = 2;
			return;
		}
		if (_timeCharge < 10)
		{
			this->bulletLv = 1;
			return;
		}
	}
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
			if (this->_state != Global::Climb && !this->IsJump() && this->_state != Global::LookUp && this->_state != Global::SitDown)
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
	case Global::ThrowClimb:
	case Global::ThrowJump:
	case Global::ThrowSitDown:
	case Global::ThrowStand:
	case Global::ThrowSwing:
	case Global::ThrowFall:
	case Global::ThrowRun:
	{
		if (this->_aladdinAction->GetCurrentFrame(_state) != 3)
			break;

		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		switch (_state)
		{
		case Global::ThrowJump:
		case Global::ThrowStand:
		case Global::ThrowRun:
		case Global::ThrowFall:
		case Global::ThrowSitDown: appleLocation.y = _rectBound.top - 15; break;
		case Global::ThrowClimb:
		case Global::ThrowSwing: appleLocation.y = _rectBound.top - 100; break;
		}
		float d = 20;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;

		BulletManager::Instance()->addBullet(new Apple(appleLocation.x, appleLocation.y, this->_direct));
		this->_numberOfApple--;
		break;

	}
	case Global::Stand_shoot:
	{
		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		float d = 5;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;
		appleLocation.y = _rectBound.top -85 ;
		Apple* apple = new Apple(appleLocation.x, appleLocation.y, this->_direct);
		switch (this->bulletLv)
		{
		case 1:
			apple->setState(Global::Stand);
			break;
		case 2:
			apple->setState(Global::Run);
			break;
		case 3:
			apple->setState(Global::Dash);
			break;
		default:
			break;
		}
		BulletManager::Instance()->addBullet(apple);
		//this->_numberOfApple--;

		break;
	}
	case Global::Jump_shoot:
	{
		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		float d = 5;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;
		appleLocation.y = _rectBound.top - 112;

		Apple* apple = new Apple(appleLocation.x, appleLocation.y, this->_direct);
		switch (this->bulletLv)
		{
		case 1:
			apple->setState(Global::Stand);
			break;
		case 2:
			apple->setState(Global::Run);
			break;
		case 3:
			apple->setState(Global::Dash);
			break;
		default:
			break;
		}
		BulletManager::Instance()->addBullet(apple);
		this->setState(Global::Jump);
		this->setGround(false);
		this->_timeAction = _timeActionTemp;
		//this->_numberOfApple--;

		break;
	}
	case Global::Run_shoot:
	{
		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		float d = 20;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;
		appleLocation.y = _rectBound.top - 85;

		Apple* apple = new Apple(appleLocation.x, appleLocation.y, this->_direct);
		switch (this->bulletLv)
		{
		case 1:
			apple->setState(Global::Stand);
			break;
		case 2:
			apple->setState(Global::Run);
			break;
		case 3:
			apple->setState(Global::Dash);
			break;
		default:
			break;
		}
		BulletManager::Instance()->addBullet(apple);
		//this->_numberOfApple--;

		break;
	}
	case Global::Dash_shoot:
	{
		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		float d = 20;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;
		appleLocation.y = _rectBound.top - 112;

		Apple* apple = new Apple(appleLocation.x, appleLocation.y, this->_direct);
		switch (this->bulletLv)
		{
		case 1:
			apple->setState(Global::Stand);
			break;
		case 2:
			apple->setState(Global::Run);
			break;
		case 3:
			apple->setState(Global::Dash);
			break;
		default:
			break;
		}
		BulletManager::Instance()->addBullet(apple);
		//this->_numberOfApple--;

		break;
	}
	case Global::In_climb_shoot:
	{
		D3DXVECTOR2 appleLocation;	//Apple location to create a apple
		float d = 20;

		appleLocation.x = (_direct == Global::Right) ? this->_x + d : this->_x - d;
		appleLocation.y = _rectBound.top - 112;

		Apple* apple = new Apple(appleLocation.x, appleLocation.y, this->_direct);
		switch (this->bulletLv)
		{
		case 1:
			apple->setState(Global::Stand);
			break;
		case 2:
			apple->setState(Global::Run);
			break;
		case 3:
			apple->setState(Global::Dash);
			break;
		default:
			break;
		}
		BulletManager::Instance()->addBullet(apple);
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
	case Global::Climb_Drop:this->_height = ALADDIN_HEIGHT_CLIMB; break;
	case Global::HitSwing:
	case Global::ThrowSwing:
	case Global::StopSwing:
	case Global::Swing: this->_height = ALADDIN_HEIGHT_SWING; break;
	case Global::HitSitDown:
	case Global::ThrowSitDown:
	case Global::SitDown: this->_height = ALADDIN_HEIGHT_SITDOWN; break;
	default: this->_height = ALADDIN_HEIGHT_NORMAL; break;
	}
	int width = 1;
	//Update RectCollision
	_rectBound.update(_x - _width / 2, _y + this->_height, _width, this->_height);
	_rectBound2.update(_x - width / 2, _y + this->_height, width, this->_height);
	if (this->_state == Global::JumpSwing)
		_rectWithBar.update(0, 0, 0, 0);
	else
		_rectWithBar.update(_x, _y + this->_height + 100, width, 2);


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
	if (obj->getId() == Global::JAFARBULLET && (bullet->isCanAttack()))
	{
		JafarBullet* star = (JafarBullet*)obj;
		rectBody = this->_rectBound;
		vx = this->_vx;
		vy = this->_vy;
		rectBody2 = obj->getRectBound();
		vx2 = obj->getVx();
		vy2 = obj->getVy();
		if (Collision::Instance()->AABB(rectBody, rectBody2) || (Collision::Instance()->sweptAABB(rectBody, vx, vy, rectBody2, vx2, vy2).flag))
		{
			if (abs(star->getX0() - this->_x) > 0 && this->getState() != Global::Hurting && !this->_isReset)
			{
				this->_x += (star->getDirect() == Global::Left) ? 35 : -35;
			}
			star->setFinish();
			star->setState(Global::Hurting);
		}
		return Collision::ResultCollision();
	}
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
			if (obj->getId() == Global::SNAKEBULLET)
			{
				SnakeBullet* fire = (SnakeBullet*)obj;
				rectBody = this->_rectBound;
				vx = this->_vx;
				vy = this->_vy;
				rectBody2 = obj->getRectBound();
				vx2 = obj->getVx();
				vy2 = obj->getVy();
				if (Collision::Instance()->AABB(rectBody, rectBody2) || (Collision::Instance()->sweptAABB(rectBody, vx, vy, rectBody2, vx2, vy2).flag))
				{
					this->Hurting();
				}
				return Collision::ResultCollision();
			}
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
					
					}
					else
					{
						if (bullet->getId() == Global::CIVILIANBULLET)
						{
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
	case Global::OnTrap:
	case Global::HitStand:
	case Global::HitStand2:
	case Global::HitSitDown:
	case Global::ThrowStand:
	case Global::ThrowSitDown:
	case Global::SitDown:
	case Global::StandUp:
	case Global::LookUp:
	case Global::LookDown:
	case Global::Stand:
	{
		this->_v0 = 0;
		break;
	}
	case Global::Run:
	{
		angle = 0;
		break;
	}
	case Global::StopRun:
	{
		angle = 0;
		this->_v0 /= 3;
		break;
	}
	case Global::Jump:
	{
		this->_v0 *= 1.8;
		angle = 1.1345;
		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;

		ax = 0;

		if (this->_isGround)
			canMoveY = false;
		break;
	}
	case Global::ThrowFall:
	case Global::HitFall:
	{
		int i = 0;
	}
	case Global::JumpSwing:
	case Global::Fall:
	{
		this->_v0 /= 2;
		angle = 0;
		canMoveY = false;
		if (KeyBoard::Instance()->isKeyPress(DIK_LEFT) || KeyBoard::Instance()->isKeyPress(DIK_RIGHT))
			canMoveX = true;
		else
			canMoveX = false;
		break;
	}
	case Global::JumpRotate:
	{
		this->_v0 *= 2.5;
		angle = 1.1345;
		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;
		if (this->_isGround)
			canMoveY = false;
		break;
	}
	case Global::HitClimb:
	case Global::ThrowClimb:
	{
		ay = 0;
		canMoveX = false;
		canMoveY = false;
		break;
	}
	case Global::Climb:
	{
		ay = 0;
		canMoveX = false;
		this->_v0 /= 2;
		angle = 1.571;
		int ropeTop = this->_aladdinAction->getRope().top;
		int ropeBottom = this->_aladdinAction->getRope().bottom;
		if (KeyBoard::Instance()->isKeyPress(DIK_UP) &&
			this->_y < ropeTop)
		{
			this->_aladdinAction->setDirect(Global::Up);
			directY = Global::Up;
		}
		else if (KeyBoard::Instance()->isKeyPress(DIK_DOWN))
		{
			if (this->_y > ropeBottom - this->_height)
			{
				this->_aladdinAction->setDirect(Global::Down);
				directY = Global::Down;
			}
			else
				this->Fall();
		}
		else
		{
			this->_aladdinAction->setDirect(Global::None);
			canMoveY = false;
		}

		break;
	}
	case Global::Climb_Drop:
	{
		ay = this->_ay * 8;
		canMoveX = false;
		canMoveY = false;
		int columnBottom = this->_aladdinAction->getColumn().bottom;
		if (this->_y < columnBottom)
			this->Fall();
		break;
	}
	case Global::HitSwing:
	case Global::ThrowSwing:
	case Global::StopSwing:
	{
		canMoveX = false;
		canMoveY = false;
		ay = 0;
		break;
	}
	case Global::Dash:
	{
		angle = 1.0f;
		this->_vx = 10;
		this->_v0 *= 2.5;
		canMoveX = true;
		canMoveY = false;
		break;
	}
	case Global::In_climb:
	{
		canMoveX = false;
		canMoveY = false;
		break;
	}
	case Global::Jump_shoot:
	{
		this->_v0 /= 1.8;
		angle = 1.1345;
		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;
		if (this->_isGround)
			canMoveY = true;
		break;
	}
	case Global::Dash_shoot:
	{
		angle = 1;
		this->_vx = 10;
		canMoveX = true;
		canMoveY = false;
		break;
	}
	case Global::Run_shoot:
	{
		this->_vx = 10;
		angle = 1;

		if (KeyBoard::Instance()->isKeyPress(DIK_RIGHT) || KeyBoard::Instance()->isKeyPress(DIK_LEFT))
			canMoveX = true;
		else
			canMoveX = false;
		//if (this->_isGround)
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
	case Global::In_climb_shoot:
	{
		canMoveX = false;
		canMoveY = false;
		break;
	}
	}

	vx = (canMoveX) ? this->_v0*cos(angle) : 0;
	vy = (canMoveY) ? this->_v0*sin(angle) : 0;

	vx *= (directX == Global::Right) ? 1 : -1;
	ax *= (directX == Global::Right) ? 1 : -1;
	//vy *= (directY == Global::Up) ? 1 : -1;

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

	if (_state == Global::Run && this->_countRun >= 10/* && this->_isGround*/)
	{
		this->StopRun();
		this->_countRun = 0;
		return;
	}
	/*if (_state == Global::Jump  && this->_isGround)
	{
		this->Jump();
		this->_countJump = 0;
		return;
	}*/

	this->_aladdinAction->Refresh();
	this->_countRun = 0;
	this->_state = Global::Stand;
}

void Aladdin::Running()
{
	//this->set(1, 0, 1, 0);
	if (_state == Global::Run)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::Run;
}

void Aladdin::SitDown()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::SitDown)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::SitDown;
}

void Aladdin::StandUp()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::StandUp)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::StandUp;
}

void Aladdin::LookUp()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::LookUp)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::LookUp;
}

void Aladdin::LookDown()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::LookDown)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::LookDown;
}
#pragma endregion
//===================================================
//PushWall
//===================================================
#pragma region PushWall
bool Aladdin::IsPushWall()
{
	return _state == Global::PushWall;
}

void Aladdin::PushWall()
{
	//this->set(1, 0, 1, 0);
	if (_state == Global::PushWall)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::PushWall;
}
#pragma endregion
//===================================================
//Climb
//===================================================
#pragma region Climb
bool Aladdin::IsClimb()
{
	return (_state == Global::In_climb || _state == Global::In_climb_shoot);
}
void Aladdin::Climb()
{
	this->_timeAction = 0;
	this->_state = Global::Climb;
}
void Aladdin::In_climb()
{
	if (this->isGround())
	{
		this->Stand();
		return;
	}
	if (_state == Global::In_climb)
		return;
	/*if (_state == Global::In_climb_shoot)
	{
		this->In_climb_shoot();
		return;
	}*/
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::In_climb;
}
void Aladdin::Stand_shoot()
{
	if (_state == Global::Stand_shoot)
		return;
	if (_state == Global::Jump)
	{
		this->Jump();
		return;
	}
	if (_state == Global::Run_shoot)
	{
		this->Run_shoot();
		return;
	}
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Stand_shoot;
}
void Aladdin::Run_shoot()
{
	if (_state == Global::Run_shoot)
		return;
	if (_state == Global::Dash_shoot)
	{
		this->Dash_shoot();
		return;
	}
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Run_shoot;
}
void Aladdin::Jump()
{
	if (_state == Global::Jump)
		return;
	/*if (_state == Global::Stand && this->_countJump >= 6 && this->_isGround)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
		this->_countJump = 0;
		return;
	}*/
	//if (/*_state == Global::Jump_shoot*/ /*&& this->_countJump >= 6*/  !this->_isGround)
	//{
	//	Aladdin* aladdin = Aladdin::getInstance();
	//	aladdin->Jump_shoot();
	//	//this->_countJump = 0;
	//	return;
	//}
	if (_state == Global::Jump_shoot)
	{
		this->_state = Global::Jump;
	}
	this->_aladdinAction->Refresh();
	this->_isGround = false;
	this->_timeAction = 0;
	this->_state = Global::Jump;
}
void Aladdin::Jump_shoot()
{
	if (_state == Global::Jump_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeActionTemp = this->_timeAction;
	this->_timeAction = 0;
	this->_state = Global::Jump_shoot;
}
void Aladdin::In_climb_shoot()
{
	if (_state == Global::In_climb_shoot)
		return;
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::In_climb_shoot;
}
void Aladdin::Dash_shoot()
{
	if (_state == Global::Dash_shoot)
		return;
	if (_state == Global::Stand)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		aladdin->Stand();
		return;
	}
	this->_aladdinAction->Refresh();
	this->_timeAction = 0;
	this->_state = Global::Dash_shoot;
}
void Aladdin::Climb_Drop()
{
	this->_timeAction = 0;
	this->_state = Global::Climb_Drop;
}
#pragma endregion
//===================================================
//Swing
//===================================================
#pragma region Swing
void Aladdin::Swing()
{
	//this->set(1, 0, 0, 0);
	if (_state == Global::Swing)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::Swing;
}

void Aladdin::StopSwing()
{
	//this->set(0, 0, 0, 0);
	if (_state == Global::StopSwing)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::StopSwing;
}
void Aladdin::Hurting()
{
	if (this->_state == Global::Hurting)
		return;
	if (this->_state == Global::Climb ||this->_state == Global::Jump)
	{
		this->_hp--;
		this->setReset();
		return;
	}
	this->_hp--;
	this->setReset();
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

void Aladdin::HitJump()
{
	//this->set(1, 0, 1, 1.1345);
	if (_state == Global::HitJump)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitJump;
}

void Aladdin::HitClimb()
{
	//this->set(0, 0, 0, 0);
	if (_state == Global::HitClimb)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitClimb;
}

void Aladdin::HitSwing()
{
	if (_state == Global::HitSwing)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitSwing;
}

void Aladdin::HitFall()
{
	if (_state == Global::HitFall)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::HitFall;
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
//Throw
//===================================================
#pragma region Throw
void Aladdin::ThrowStand()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::ThrowStand)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowStand;
}

void Aladdin::ThrowSitDown()
{
	//this->set(0, 0, 1, 0);
	if (_state == Global::ThrowSitDown)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowSitDown;
}

void Aladdin::ThrowJump()
{
	//this->set(1, 0, 1, 1.1345);
	if (_state == Global::ThrowJump)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowJump;
}

void Aladdin::ThrowClimb()
{
	//this->set(0, 0, 0, 0);
	if (_state == Global::ThrowClimb)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowClimb;
}

void Aladdin::ThrowSwing()
{
	if (_state == Global::ThrowSwing)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowSwing;
}
void Aladdin::ThrowFall()
{
	if (_state == Global::ThrowFall)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowFall;
}

void Aladdin::ThrowRun()
{
	if (_state == Global::ThrowRun)
		return;
	this->_aladdinAction->Refresh();
	this->_state = Global::ThrowRun;
}
#pragma endregion
//===================================================
//Jump
//===================================================
#pragma region Jump
bool Aladdin::IsJump()
{
	return (_state == Global::Jump || _state == Global::Jump_shoot);
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
	this->_state = Global::StopJump;
}
void Aladdin::Revival()
{
	if (this->_state == Global::Revival)
		return;
	this->_timeAction = 0;
	this->_countRun = 0;
	if (!this->_startPosition_)
	{
		this->setState(Global::Stand);
		this->setReset();
		this->_x = this->_startPosition.x;
		this->_y = this->_startPosition.y;
		this->updateBody();
		return;
	}
	this->_state = Global::Revival;
	this->setReset(false);
	this->_x = this->_startPosition.x;
	this->_y = this->_startPosition.y;
	this->updateBody();
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
	if (_state == Global::Dash_shoot && this->_countDash >= 4 && this->_isGround)
	{
		Aladdin* aladdin = Aladdin::getInstance();
		//aladdin->Dash_shoot();
		this->_countDash = 0;
		bDash = false;;
		return;
	}
	this->_aladdinAction->Refresh();
	this->_state = Global::Dash;

}
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