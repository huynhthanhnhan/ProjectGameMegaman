#include "Stick.h"
#include"Aladdin.h"


Stick::Stick(int x, int y, int width, int height)
{
	this->_type = Global::Enemy;
	this->_width = width;
	this->_height = height;
	this->_x = x;
	this->_y = y - _height;
	this->_vx = this->_vy = 0;
	this->LoadResource();
	this->updateBody();
	this->_id = Global::STICKITEM;
}

Stick::~Stick()
{
}

void Stick::update(float deltaTime)
{
	if (this->GetCurrentFrame(Global::JumpRun) == 1 )
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_STICK);
	}
	if (this->_start)
		this->UpdateRender(Global::JumpRun);
}

void Stick::render()
{
	this->transform();
	this->Render(Global::Right, Global::JumpRun, this->_transform._position);
}

Collision::ResultCollision Stick::processCollision(Object * obj)
{
	WRect rect1;
	if (obj->getId() == Global::ALADDIN)
		rect1 = ((Aladdin*)obj)->getRectBound2();
	else
		rect1 = obj->getRectBound();

	WRect rect2 = this->getRectBound();
	float vx1 = obj->getVx();
	float vy1 = obj->getVy();
	float vx2 = this->getVx();
	float vy2 = this->getVy();
	Collision::ResultCollision result = Collision::Instance()->sweptAABB(rect1, vx1, vy1, rect2, vx2, vy2);
	//Chỉ xét hướng va chạm từ trên xuống
	if (result.normaly == -1 || result.normaly == 0)
		result.flag = false;

	this->_start = (result.flag) ? true : _start;

	if (result.flag)
	{
		Aladdin* aladdin = (Aladdin*)obj;
		aladdin->JumpRotate();
		result.intersectionPoint.x = obj->getX() + obj->getVx() * result.collisionTime;
		result.intersectionPoint.y = obj->getY() + obj->getVy() *result.collisionTime;
	}
	return result;
}

void Stick::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	Animation::Render(direct, state, position, scale, translation, rotation, rotationCenter);
}

void Stick::updateBody()
{
	D3DXVECTOR2 position = D3DXVECTOR2(this->getCurrentLocation().x, this->getCurrentLocation().y + this->_height);
	this->_rectBound.update(position.x, position.y, this->_width, this->_height);
}

void Stick::Refresh()
{
	this->mListSprite[Global::JumpRun]->SetCurrentFrame(0);
}

void Stick::LoadResource()
{
	std::vector<Rect*> listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ALADDIN, "stick");
	listSourceRect[0]->setCenter(1, 18);
	listSourceRect[1]->setCenter(1, 5);
	listSourceRect[2]->setCenter(1, 18);
	listSourceRect[3]->setCenter(2, 25);
	listSourceRect[4]->setCenter(1, 18);
	listSourceRect[5]->setCenter(1, 5);
	listSourceRect[6]->setCenter(1, 18);
	listSourceRect[7]->setCenter(2, 25);
	listSourceRect[8]->setCenter(1, 18);
	listSourceRect[9]->setCenter(1, 5);
	listSourceRect[10]->setCenter(1, 18);

	this->mListSprite[Global::JumpRun] = new SpriteManager(ResourceImage::Instance()->getStick(),
		listSourceRect, false);
}

void Stick::UpdateRender(Global::EState currentState)
{
	int size = this->mListSprite[currentState]->GetListRect().size();
	int index = (this->GetCurrentFrame(currentState) + 1) % size;
	this->SetCurrentFrame(currentState, index);
	this->_start = (index == 0) ? false : this->_start;
}
