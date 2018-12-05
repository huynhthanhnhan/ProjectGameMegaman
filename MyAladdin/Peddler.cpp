#include "Peddler.h"



Peddler::Peddler(int x, int y)
	:ItemObject(x, y, 96, 128)
{
	this->_id = Global::PEDDLER;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
	_index2 = 0;
	this->_rectPeddler.setX(x);
	this->_rectPeddler.setY(y);
	this->_rectPeddler.setWidth(5);
	this->_rectPeddler.setHeight(5);
	this->_graphic = Graphics::Instance();
}


Peddler::~Peddler()
{
}

void Peddler::LoadResource()
{
	//this->_rect._update(7904, 9126, 96, 128);

	this->_listSourceRect1 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "PeddlerNone");
	_listSourceRect1[0]->setCenter(35);
	_listSourceRect1[1]->setCenter(36);
	_listSourceRect1[2]->setCenter(37);
	_listSourceRect1[3]->setCenter(37);
	_listSourceRect1[4]->setCenter(37);
	_listSourceRect1[5]->setCenter(37);
	_listSourceRect1[6]->setCenter(37);
	_listSourceRect1[7]->setCenter(37);
	_listSourceRect1[8]->setCenter(37);
	_listSourceRect1[9]->setCenter(37);
	_listSourceRect1[10]->setCenter(37);
	_listSourceRect1[11]->setCenter(37);
	_listSourceRect1[12]->setCenter(37);
	_listSourceRect1[13]->setCenter(37);
	_listSourceRect1[14]->setCenter(36);
	_listSourceRect1[15]->setCenter(35);
	_listSourceRect1[16]->setCenter(35);
	_listSourceRect1[17]->setCenter(35);
	_listSourceRect1[18]->setCenter(35);
	_listSourceRect1[19]->setCenter(35);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
		_listSourceRect1, false);

	this->_listSourceRect2 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "PeddlerStand");
	_listSourceRect2[0]->setCenter(7);
	_listSourceRect2[1]->setCenter(8);
	_listSourceRect2[2]->setCenter(9);
	_listSourceRect2[3]->setCenter(9);
	_listSourceRect2[4]->setCenter(9);
	_listSourceRect2[5]->setCenter(9);
	_listSourceRect2[6]->setCenter(9);
	_listSourceRect2[7]->setCenter(14);
	_listSourceRect2[8]->setCenter(21);
	_listSourceRect2[9]->setCenter(14);
	_listSourceRect2[10]->setCenter(10);
	_listSourceRect2[11]->setCenter(11);
	_listSourceRect2[12]->setCenter(11);
	_listSourceRect2[13]->setCenter(11);
	this->mListSprite[Global::Stand] = new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
		_listSourceRect2, false);

	this->_listSourceRect3 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "PeddlerHit");
	_listSourceRect3[0]->setCenter(63);
	_listSourceRect3[1]->setCenter(68);
	_listSourceRect3[2]->setCenter(68);
	_listSourceRect3[3]->setCenter(92);
	_listSourceRect3[4]->setCenter(94);
	_listSourceRect3[5]->setCenter(96);
	_listSourceRect3[6]->setCenter(97);
	_listSourceRect3[7]->setCenter(75);
	_listSourceRect3[8]->setCenter(75);
	_listSourceRect3[9]->setCenter(73);
	_listSourceRect3[10]->setCenter(72);
	_listSourceRect3[11]->setCenter(76,74);
	_listSourceRect3[12]->setCenter(74);
	_listSourceRect3[13]->setCenter(74);
	_listSourceRect3[14]->setCenter(92,74);
	_listSourceRect3[15]->setCenter(92,73);
	_listSourceRect3[16]->setCenter(99,70);
	_listSourceRect3[17]->setCenter(112,54);
	_listSourceRect3[18]->setCenter(98,55);
	_listSourceRect3[19]->setCenter(76,55);
	_listSourceRect3[20]->setCenter(75,51);
	_listSourceRect3[21]->setCenter(77,47);
	_listSourceRect3[22]->setCenter(88,58);
	_listSourceRect3[23]->setCenter(95,59);
	this->mListSprite[Global::HitStand] = new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
		_listSourceRect3, false);

	this->_listSourceRect4 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "Shop");
	_listSourceRect4[0]->setCenter(84);
	_listSourceRect4[1]->setCenter(104);
	_listSourceRect4[2]->setCenter(100);
	_listSourceRect4[3]->setCenter(95);
	_listSourceRect4[4]->setCenter(94);
	_listSourceRect4[5]->setCenter(94);
	this->mListSprite[Global::Run] = new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
		_listSourceRect4, false);

	this->_listSourceRect5 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "PeddlerNone");
	this->mListSprite[Global::Attack] = new SpriteManager(ResourceImage::Instance()->getPeddlerTexture(),
		_listSourceRect5, false);

	//std::vector<Rect*> FIND_MORE_GEM = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "knife");
	//this->mListSprite[Global::Knife] = new SpriteManager(ResourceImage::Instance()->getKnifeMenu(),
	//	listSourceRect_0, false);
}

void Peddler::getItem()
{

}

void Peddler::UpdateRender(Global::EState currentState)
{
	if (_index == 3 && this->_state == Global::HitStand)
	{
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_TAKE_TEAPOT);
	}
	if (_index == 23 && this->_state == Global::HitStand)
	{
		this->_state = Global::Attack;
		this->_sound = Sound::Instance();
		this->_sound->play(SOUND_PEDDLER_SHOP);
		this->_index = 0;
		return;
	}

	if (_index2 == 5 && this->_state == Global::Attack)
	{
		_index2 = 4;
	}

	if (this->_state == Global::NoneAction)
	{
		this->_index1 = (_index1 + 1) % this->_listSourceRect1.size();
		this->_rect = *this->_listSourceRect1[_index1];
	}

	if (this->_state == Global::HitStand)
	{
		_index = (_index + 1) % this->_listSourceRect3.size();
		this->_rect = *this->_listSourceRect3[_index];
	}

	if (this->_state == Global::Attack)
	{
		_index = (_index + 1) % this->_listSourceRect2.size();
		this->_rect2 = *this->_listSourceRect2[_index];
		_index2 = (_index2 + 1) % this->_listSourceRect4.size();
		this->_rect = *this->_listSourceRect4[_index2];
	}



}

Collision::ResultCollision Peddler::processCollision(Object * obj)
{
	//if (this->_state == Global::Run)
	//	return Collision::ResultCollision();

	if (this->_state == Global::Stand)
		return Collision::ResultCollision();

	if (this->_state == Global::HitStand)
		return Collision::ResultCollision();

	if (_index2 <= 3 && this->_state == Global::Attack)
		return Collision::ResultCollision();
	if (obj->getId() != Global::ALADDIN)
		return Collision::ResultCollision();

	WRect rectBody;
	rectBody = obj->getRectBound();

	WRect _rectPeddler1;
	_rectPeddler1.setX(this->_rectPeddler.getX() - 100);
	_rectPeddler1.setY(this->_rectPeddler.getY());
	_rectPeddler1.setWidth(this->_rectPeddler.getWidth());
	_rectPeddler1.setHeight(this->_rectPeddler.getHeight());

	WRect _rectPeddler2;
	_rectPeddler2.setX(this->_rectPeddler.getX() - 30);
	_rectPeddler2.setY(this->_rectPeddler.getY());
	_rectPeddler2.setWidth(this->_rectPeddler.getWidth());
	_rectPeddler2.setHeight(this->_rectPeddler.getHeight());

	if (_index2 >= 4 && this->_state == Global::Attack)
	{
		if (Collision::Instance()->sweptAABB(rectBody, obj->getVx(), obj->getVy(), _rectPeddler1, 0, 0).flag || Collision::Instance()->AABB(_rectPeddler1, rectBody))
		{
			if (Aladdin::getInstance()->isLookUp() == true)
			{
				if (Aladdin::getInstance()->getNumberOfGem() >= 5)
				{
					Aladdin::getInstance()->setLookUp(false);
					Aladdin::getInstance()->setGem(Aladdin::getInstance()->getNumberOfGem() - 5);
					Aladdin::getInstance()->setLife(Aladdin::getInstance()->getLife() + 1);
					this->_sound = Sound::Instance();
					this->_sound->play(SOUND_A_DEAL);
					Aladdin::getInstance()->setA_Deal(true);
					Aladdin::getInstance()->setGems(false);
				}
				else
				{
					Aladdin::getInstance()->setA_Deal(false);
					Aladdin::getInstance()->setGems(true);
				}

			}
		}
		else if (Collision::Instance()->sweptAABB(rectBody, obj->getVx(), obj->getVy(), _rectPeddler2, 0, 0).flag || Collision::Instance()->AABB(_rectPeddler2, rectBody))
		{
			if (Aladdin::getInstance()->isLookUp() == true)
			{
				if (Aladdin::getInstance()->getNumberOfGem() >= 10)
				{
					Aladdin::getInstance()->setLookUp(false);
					/*Aladdin::getInstance()->setGem(Aladdin::getInstance()->getNumberOfGem() - 10);
					Aladdin::getInstance()->setLife(Aladdin::getInstance()->getLife() + 1);*/
					/*Rect rect3;
					rect3._update(300, 200, 400, 50);
					this->_graphic->DrawText_("IT'S A DEAL", &rect3, this->_graphic->GetSpriteHandler(), D3DCOLOR_XRGB(255, 255, 15));*/
					//this->_sound = Sound::Instance();
					//this->_sound->play(SOUND_A_DEAL);
					//Aladdin::getInstance()->setA_Deal(true);
					//Aladdin::getInstance()->setGems(false);
					//return Collision::ResultCollision();
				}
				else
				{
					Aladdin::getInstance()->setA_Deal(false);
					Aladdin::getInstance()->setGems(true);
				}
			}
		}
		if (!Collision::Instance()->sweptAABB(rectBody, obj->getVx(), obj->getVy(), _rectPeddler1, 0, 0).flag && !Collision::Instance()->AABB(_rectPeddler1, rectBody))
			if (!Collision::Instance()->sweptAABB(rectBody, obj->getVx(), obj->getVy(), _rectPeddler2, 0, 0).flag && !Collision::Instance()->AABB(_rectPeddler2, rectBody))
			{
				Aladdin::getInstance()->setA_Deal(false);
				Aladdin::getInstance()->setGems(false);
			}
	}
	else
	{
		if (Collision::Instance()->sweptAABB(rectBody, obj->getVx(), obj->getVy(), this->_rectBound, 0, 0).flag || Collision::Instance()->AABB(this->_rectBound, rectBody))
		{
			this->_state = Global::HitStand;

		}
	}
	return Collision::ResultCollision();
}
