#include "GemItem.h"


GemItem::GemItem(int x, int y)
	:ItemObject(x, y, GEM_WIDTH, GEM_HEIGHT)
{
	this->_id = Global::GEMITEM;
	this->_x = x;
	this->_y = y;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}

GemItem::~GemItem()
{
	for (size_t i = 0; i < this->_listSourceRect.size(); i++)
		delete this->_listSourceRect[i];

	this->_listSourceRect.clear();

	for (auto i = this->mListSprite.begin(); i != this->mListSprite.end(); i++)
		delete i->second;

	this->mListSprite.clear();
}

void GemItem::LoadResource()
{
	this->_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "gem");
	this->_listSourceRect[0]->setCenter(0, 0);
	this->_listSourceRect[1]->setCenter(0, 0);
	this->_listSourceRect[2]->setCenter(0, 0);
	this->_listSourceRect[3]->setCenter(0, 0);
	this->_listSourceRect[4]->setCenter(0, 1);
	this->_listSourceRect[5]->setCenter(6, 6);
	this->_listSourceRect[6]->setCenter(0, 4);
	this->_listSourceRect[7]->setCenter(0, 0);
	this->_listSourceRect[8]->setCenter(0, 0);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(),
		this->_listSourceRect, false);

	for each (auto rect in this->mListSprite[Global::Dead]->GetListRect())
		rect->setCenter(rect->getWidth(), rect->getHeight() / 2, 0);
}

void GemItem::UpdateRender(Global::EState currentState)
{
	if (this->_state == Global::Dead && this->GetCurrentFrame(_state) == 0)
		this->_taken = true;

	if (this->_state != Global::NoneAction)
		return;

	if (this->_time >= 2)
	{
		_index = (_index + 1) % this->_listSourceRect.size();
		this->_rect = *this->_listSourceRect[_index];
		_time = 0;
	}
	else
		_time++;
}

void GemItem::getItem()
{
	this->_sound = Sound::Instance();
	this->_sound->play(SOUND_TAKE_GEM);
	Aladdin::getInstance()->increaseGem();
	Aladdin::getInstance()->increaseScore(150);
}
