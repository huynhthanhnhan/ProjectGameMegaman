#include "HealthPoint.h"



HealthPoint::HealthPoint()
{
	this->LoadResource();
}


HealthPoint::~HealthPoint()
{
}


void HealthPoint::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
{
	if (mListSprite.find(state) == mListSprite.end())
		return;
	/*D3DXVECTOR2 inScale = this->mListSprite[state]->GetScale();
	this->mListSprite[state]->SetScale(D3DXVECTOR2(inScale.x*scale.x, inScale.y*scale.y));
	*/
	this->mListSprite[state]->SetPosition(position);
	this->mListSprite[state]->SetTranslation(translation);
	this->mListSprite[state]->SetRotaion(rotation);
	this->mListSprite[state]->SetRotationCenter(rotationCenter);
	this->DetermineDirection(state, direct);
	this->mListSprite[state]->Draw();
}

void HealthPoint::Refresh()
{
}

void HealthPoint::LoadResource()
{
	std::vector<Rect*> listSourceRect_0 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "0");
	listSourceRect_0[0]->setCenter(0);
	this->mListSprite[Global::Hp0] = new SpriteManager(ResourceImage::Instance()->getHp0(),
		listSourceRect_0, false);
	std::vector<Rect*> listSourceRect_1 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "1");
	listSourceRect_1[0]->setCenter(0);
	listSourceRect_1[1]->setCenter(0);
	listSourceRect_1[2]->setCenter(0);
	listSourceRect_1[3]->setCenter(0);
	this->mListSprite[Global::Hp1] = new SpriteManager(ResourceImage::Instance()->getHp1(),
		listSourceRect_1, false);

	std::vector<Rect*> listSourceRect_2 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "2");
	listSourceRect_2[0]->setCenter(0);
	listSourceRect_2[1]->setCenter(0);
	listSourceRect_2[2]->setCenter(0);
	listSourceRect_2[3]->setCenter(0);
	this->mListSprite[Global::Hp2] = new SpriteManager(ResourceImage::Instance()->getHp2(),
		listSourceRect_2, false);

	std::vector<Rect*> listSourceRect_3 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "3");
	listSourceRect_3[0]->setCenter(0);
	listSourceRect_3[1]->setCenter(0);
	listSourceRect_3[2]->setCenter(0);
	listSourceRect_3[3]->setCenter(0);
	this->mListSprite[Global::Hp3] = new SpriteManager(ResourceImage::Instance()->getHp3(),
		listSourceRect_3, false);

	std::vector<Rect*> listSourceRect_4 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "4");
	listSourceRect_4[0]->setCenter(0);
	listSourceRect_4[1]->setCenter(0);
	listSourceRect_4[2]->setCenter(0);
	listSourceRect_4[3]->setCenter(0);
	this->mListSprite[Global::Hp4] = new SpriteManager(ResourceImage::Instance()->getHp4(),
		listSourceRect_4, false);

	std::vector<Rect*> listSourceRect_5 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "5");
	listSourceRect_5[0]->setCenter(0);
	listSourceRect_5[1]->setCenter(0);
	listSourceRect_5[2]->setCenter(0);
	listSourceRect_5[3]->setCenter(0);
	this->mListSprite[Global::Hp5] = new SpriteManager(ResourceImage::Instance()->getHp5(),
		listSourceRect_5, false);

	std::vector<Rect*> listSourceRect_6 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "6");
	listSourceRect_6[0]->setCenter(0);
	listSourceRect_6[1]->setCenter(0);
	listSourceRect_6[2]->setCenter(0);
	listSourceRect_6[3]->setCenter(0);
	this->mListSprite[Global::Hp6]= new SpriteManager(ResourceImage::Instance()->getHp6(),
		listSourceRect_6, false);

	std::vector<Rect*> listSourceRect_7 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "7");
	listSourceRect_7[0]->setCenter(0);
	listSourceRect_7[1]->setCenter(0);
	listSourceRect_7[2]->setCenter(0);
	listSourceRect_7[3]->setCenter(0);
	this->mListSprite[Global::Hp7] = new SpriteManager(ResourceImage::Instance()->getHp7(),
		listSourceRect_7, false);

	std::vector<Rect*> listSourceRect_8 = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "8");
	listSourceRect_8[0]->setCenter(0);
	listSourceRect_8[1]->setCenter(0);
	listSourceRect_8[2]->setCenter(0);
	listSourceRect_8[3]->setCenter(0);
	this->mListSprite[Global::Hp8] = new SpriteManager(ResourceImage::Instance()->getHp8(),
		listSourceRect_8, false);
}

void HealthPoint::UpdateRender(Global::EState currentState)
{
	if (currentState == Global::Hp0)
	{
		int size0 = this->mListSprite[Global::Hp0]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp0, (this->GetCurrentFrame(Global::Hp0) + 1) % size0);
	}
	if (currentState == Global::Hp1)
	{
		int size1 = this->mListSprite[Global::Hp1]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp1, (this->GetCurrentFrame(Global::Hp1) + 1) % size1);
	}
	if (currentState == Global::Hp2)
	{
		int size2 = this->mListSprite[Global::Hp2]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp2, (this->GetCurrentFrame(Global::Hp2) + 1) % size2);
	}
	if (currentState == Global::Hp3)
	{
		int size3 = this->mListSprite[Global::Hp3]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp3, (this->GetCurrentFrame(Global::Hp3) + 1) % size3);
	}
	if (currentState == Global::Hp4)
	{
		int size4 = this->mListSprite[Global::Hp4]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp4, (this->GetCurrentFrame(Global::Hp4) + 1) % size4);
	}
	if (currentState == Global::Hp5)
	{
		int size5 = this->mListSprite[Global::Hp5]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp5, (this->GetCurrentFrame(Global::Hp5) + 1) % size5);
	}
	if (currentState == Global::Hp6)
	{
		int size6 = this->mListSprite[Global::Hp6]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp6, (this->GetCurrentFrame(Global::Hp6) + 1) % size6);
	}
	if (currentState == Global::Hp7)
	{
		int size7 = this->mListSprite[Global::Hp7]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp7, (this->GetCurrentFrame(Global::Hp7) + 1) % size7);
	}
	if (currentState == Global::Hp8)
	{
		int size8 = this->mListSprite[Global::Hp8]->GetListRect().size();
		this->SetCurrentFrame(Global::Hp8, (this->GetCurrentFrame(Global::Hp8) + 1) % size8);
	}
}
