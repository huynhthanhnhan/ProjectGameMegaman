#include "AbuItem.h"


AbuItem::AbuItem(int x, int y)
	:ItemObject(x, y, ABU_WIDTH, ABU_HEIGHT)
{
	this->_id = Global::ABUITEM;
	this->_x = x + _width / 2;
	this->_y = y - _height / 2;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}

AbuItem::~AbuItem()
{
}


void AbuItem::LoadResource()
{
	this->_listSourceRect = ResourceFile::Instance()->LoadXML(RESOURCE_RECT_ITEM, "abu");
	for each (auto rect in this->_listSourceRect)
		rect->setCenter(rect->getWidth() / 2, rect->getHeight() / 2, 0);

	for each (auto rect in this->mListSprite[Global::Dead]->GetListRect())
		rect->setCenter(rect->getWidth() / 2, rect->getHeight() / 2, 0);

	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(),
		_listSourceRect, false);

	void* tempPoint = this->mListSprite[Global::Dead];
	delete tempPoint;
	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "abuExplosing"));
}

void AbuItem::UpdateRender(Global::EState currentState)
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

void AbuItem::getItem()
{
	this->_sound = Sound::Instance();
	this->_sound->play(SOUND_TAKE_ABU);
	Aladdin::getInstance()->increaseScore(250);
}