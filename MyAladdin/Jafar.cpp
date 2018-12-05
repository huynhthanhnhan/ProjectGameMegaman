#include "Jafar.h"


Jafar::Jafar(int xRegion, int yRegion, int widthRegion, int heightRegion, Global::EDirection direct)
	:Enemy(xRegion, yRegion, widthRegion, heightRegion, W_JAFAR_NORMAL, H_JAFAR_NORMAL, V_JAFAR, direct)
{
	this->_id = Global::JAFAR;
	this->_x = xRegion + widthRegion / 2;
	this->_state = Global::Stand;
	this->updateBody();
	this->LoadResource();
	this->_hp = 30;
	Aladdin::getInstance()->setJafar(true);
}

Jafar::~Jafar()
{
}

bool Jafar::isAttack()
{
	return true;
}

void Jafar::update(float deltaTime)
{
	//if (this->_isDead)
	//	return;

	if (this->_hp == 0)
	{
		this->takeAction(Global::Dead);	
	}

	if (this->GetCurrentFrame(Global::Dead) == 14)
	{
		//Aladdin* _aladdin;
		//_aladdin = Aladdin::getInstance();
		//_aladdin->setVictory2(true);
		Aladdin::getInstance()->setVictory2(true);
	}

	if (this->_hp <= 30 && this->_hp >= 16)
	{
		if (abs(this->_x - this->_aladdinLocation.x) >= D_ATTACK_JAFAR)
		{
			if (time1 < 100)
			{
				this->takeAction(Global::Stand);
				int x = (this->_direct == Global::Left) ? _x - 60 : _x + _width;
				if (time1 % 2 == 0)
					BulletManager::Instance()->addBullet(new JafarBullet(x, _y + _height, _direct, 0, 50));
			}
			if (time1 >= 100 && time1 < 130)
			{
				this->takeAction(Global::Attack);
				if (this->GetCurrentFrame(Global::Attack) == 4)
					this->SetCurrentFrame(Global::Attack, 3);
			}
			if (time1 >= 130)
			{
				if (this->GetCurrentFrame(Global::Attack) == 0)
					time1 = 0;
			}
			time1++;
		}
		else
		{
			this->takeAction(Global::Stand);
			time1 = 0;
		}
	}
	if (this->_hp <= 15 && this->_hp > 0)
	{
		Aladdin::getInstance()->setJafar(false);
		if (time2 < 10)
		{
			this->takeAction(Global::Snake);
			int x = (this->_direct == Global::Left) ? _x - 60 : _x + _width;
			if (this->GetCurrentFrame(Global::Snake) == 8)
				BulletManager::Instance()->addBullet(new SnakeBullet(x - 30 , _y + _height - 100, _direct, 0, 25));
		}
		if (time2 >= 10 && time2 < 14)
		{
			if (this->GetCurrentFrame(Global::Snake) == 3)
				this->SetCurrentFrame(Global::Snake, 2);
		}
		if (time2 == 14)
			time2 = 0;
		time2++;
	}

	//Xác định hướng theo aladdin
	this->_direct = (this->_x > this->_aladdinLocation.x) ? Global::Left : Global::Right;
}

void Jafar::Refresh()
{
}


void Jafar::LoadResource()
{
	//=========================================================
	//Stand
	//=========================================================
	std::vector<Rect*> Stand = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "JafarStand");
	Stand[0]->setCenter(19);
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		Stand);
	//=========================================================
	//Attack
	//=========================================================
	std::vector<Rect*> Attack = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "JafarAttack");
	Attack[0]->setCenter(20);
	Attack[1]->setCenter(19);
	Attack[2]->setCenter(19);
	Attack[3]->setCenter(19);
	Attack[4]->setCenter(18);
	Attack[5]->setCenter(19);
	Attack[6]->setCenter(18);
	Attack[7]->setCenter(18);

	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		Attack);
	//=========================================================
	//Explosing
	//=========================================================
	std::vector<Rect*> explosing = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "jafarExplosing");
	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		explosing);
	//=========================================================
	//Snake
	//=========================================================
	std::vector<Rect*> Snake = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_JAFAR, "Snake");
	Snake[0]->setCenter(42);
	Snake[1]->setCenter(44);
	Snake[2]->setCenter(39);
	Snake[3]->setCenter(39);
	Snake[4]->setCenter(40);
	Snake[5]->setCenter(40);
	Snake[6]->setCenter(38);
	Snake[7]->setCenter(20);
	Snake[8]->setCenter(9);
	Snake[9]->setCenter(15);
	Snake[10]->setCenter(27);
	this->mListSprite[Global::Snake] = new SpriteManager(ResourceImage::Instance()->getJafarTexture(),
		Snake);
}

void Jafar::UpdateRender(Global::EState currentState)
{

}


void Jafar::DetermineDirection(Global::EState state, Global::EDirection direct)
{
	this->mListSprite[state]->FlipVertical(direct == Global::Left);
}
