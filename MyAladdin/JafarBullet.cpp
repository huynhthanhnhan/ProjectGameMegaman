#include "JafarBullet.h"



JafarBullet::JafarBullet()
{
}

JafarBullet::JafarBullet(int x, int y, Global::EDirection direct, float angle, int distance)
	:Bullet(x, y, direct)
{
	this->_type = Global::Enemy;
	this->_id = Global::JAFARBULLET;
	this->_state = Global::Stand;
	this->_width = 27;
	this->_height = 27;
	this->_ay = -ACCELERATION / 2;
	this->_angle = angle;
	this->updateBody();
	this->_distanceBullet = distance;
	this->LoadResource();
}

JafarBullet::~JafarBullet()
{
}

bool JafarBullet::isFinish()
{
	return (this->_state == Global::Hurting && this->GetCurrentFrame(_state) == 3);
}

Collision::ResultCollision JafarBullet::processCollision(Object * obj)
{

	return Collision::ResultCollision();
}

void JafarBullet::update(float deltaTime)
{
	if (this->_state == Global::Hurting && this->GetCurrentFrame(this->_state) == 3)
	{
		this->_state = Global::NoneAction;
	}
	else

	{
		Aladdin* _aladdin;
		_aladdin = Aladdin::getInstance();
		_nextPos = _aladdin->getCurrentLocation(); //Vị trí aladdin
		_preV = this->getCurrentLocation(); // Vị trí viên đạn
		deltaTime /= 1000;//Đổi đơn vị
		this->_v0 = this->_distanceBullet / deltaTime;
		float vx, vy;
		vx = this->_v0*cos(this->_angle);
		vy = this->_v0*sin(this->_angle);

		if (_preV.y > _nextPos.y + _aladdin->getWidth()) vy = -this->_v0;
		if (_preV.y < _nextPos.y) vy = this->_v0;
		if (_preV.y < _nextPos.y + _aladdin->getWidth() && _preV.y > _nextPos.y) vy = 0;
		if (_preV.x > _nextPos.x) vx = -this->_v0;
		if (_preV.x < _nextPos.x) vx = this->_v0;

		this->_vx = vx*deltaTime;
		this->_vy = vy*deltaTime;

		this->_x += this->_vx;
		this->_y += this->_vy;
	}

	this->updateBody();
}

void JafarBullet::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, _state, position, D3DXVECTOR2(1, 1), D3DXVECTOR2(0, 0), 0);
	this->UpdateRender(_state);
}

void JafarBullet::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}

void JafarBullet::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "JafarStar");

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getStarTexture(),
		listSourceRect, false);

	//=====================================================
	//Explosing
	//=====================================================
	std::vector<Rect*> exposing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "JafarStarExplosive");
	this->mListSprite[Global::Hurting] = new SpriteManager(ResourceImage::Instance()->getStarTexture(),
		exposing);
}

void JafarBullet::UpdateRender(Global::EState currentState)
{
	if (this->_state == Global::Stand)
	{
		int size = this->mListSprite[Global::Stand]->GetListRect().size();
		this->SetCurrentFrame(this->_state, (this->GetCurrentFrame(this->_state) + 1) % size);
	}
	if (this->_state == Global::Hurting)
	{
		int size2 = this->mListSprite[Global::Hurting]->GetListRect().size();
		this->SetCurrentFrame(this->_state, (this->GetCurrentFrame(this->_state) + 1) % size2);
	}
	if (this->_state == Global::NoneAction)
		this->_isFinish = true;
}

bool JafarBullet::isCanAttack()
{
	return (this->GetCurrentFrame(Global::Hurting) == 0);
}

void JafarBullet::setFinish()
{
	this->_isFinish = true;
}