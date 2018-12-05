#include "Shop.h"



Shop::Shop()
{
	this->LoadResource();
}


Shop::~Shop()
{
}


void Shop::Render(Global::EDirection direct, Global::EState state, D3DXVECTOR3 position, D3DXVECTOR2 scale, D3DXVECTOR2 translation, float rotation, D3DXVECTOR2 rotationCenter)
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

void Shop::Refresh()
{
}

void Shop::LoadResource()
{
	std::vector<Rect*> FIND_MORE_GEM = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "FIND_MORE_GEM");
	FIND_MORE_GEM[0]->setCenter(0);
	this->mListSprite[Global::Gem] = new SpriteManager(ResourceImage::Instance()->getItemTexture1(),
		FIND_MORE_GEM, false);

	std::vector<Rect*> A_DEAL = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "A_DEAL");
	A_DEAL[0]->setCenter(0);
	this->mListSprite[Global::A_Deal] = new SpriteManager(ResourceImage::Instance()->getItemTexture2(),
		A_DEAL, false);

}

void Shop::UpdateRender(Global::EState currentState)
{
	if (currentState == Global::Gem)
	{
		int size0 = this->mListSprite[Global::Gem]->GetListRect().size();
		this->SetCurrentFrame(Global::Gem, (this->GetCurrentFrame(Global::Gem) + 1) % size0);
	}

	if (currentState == Global::A_Deal)
	{
		int size1 = this->mListSprite[Global::A_Deal]->GetListRect().size();
		this->SetCurrentFrame(Global::A_Deal, (this->GetCurrentFrame(Global::A_Deal) + 1) % size1);
	}

}
