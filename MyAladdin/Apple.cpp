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
	this->_ay = -ACCELERATION;
	this->_angle = 0.26;//15 độ
	this->_rotation = 0;
	this->updateBody();
	this->_distanceBullet = DISTANCE_APPLE;
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
	vector<Rect*>	_listRectSource;
	float top = 10, bottom = 42;
	_listRectSource.push_back(new Rect(top, 369, 385, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 390, 406, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 411, 436, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 439, 476, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 479, 519, bottom, D3DXVECTOR3(-1, 21, 0)));
	_listRectSource.push_back(new Rect(top, 525, 565, bottom, D3DXVECTOR3(-1, 21, 0)));

	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getAladdinTexture(),
		_listRectSource);

	//=========================================================
	//Explosing Apple
	//=========================================================
	std::vector<Rect*> explosing_apple = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "abuExplosing");
	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		explosing_apple);

}

void Apple::UpdateRender(Global::EState currentState)
{
	if (currentState == Global::Stand)
	{
		if (!this->isGround())
			this->SetCurrentFrame(currentState, 0);//Chỉ hiện thị hình ảnh quả táo
		else
		{
			if (this->GetCurrentFrame(_state) == 2)
			{
				this->_sound = Sound::Instance();
				this->_sound->play(SOUND_REACH_APPLE);
			}
		}
	}
	else
	{
		this->_ax = this->_ay = this->_v0 = 0;
		this->_angle = 0;
		this->_rotation = 0;
		this->_distanceBullet = 0;
	}
}

bool Apple::isFinish()
{
	return (this->GetCurrentFrame(Global::Stand) == 5 || this->GetCurrentFrame(Global::Dead) == 9);
}

bool Apple::isCanAttack()
{
	return (this->GetCurrentFrame(Global::Stand) == 0);
}
