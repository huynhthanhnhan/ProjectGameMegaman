#include "AppleItem.h"

AppleItem::AppleItem(int x, int y)
	:ItemObject(x, y, APPLE_WIDTH, APPLE_HEIGHT)
{
	this->_id = Global::APPLEITEM;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
}

AppleItem::~AppleItem()
{
}


void AppleItem::LoadResource()
{
	_rect.update(16, 340, 352, 29);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(), std::vector<Rect*>(), false);
}

void AppleItem::getItem()
{
	this->_sound = Sound::Instance();
	this->_sound->play(SOUND_TAKE_APPLE);
	Aladdin::getInstance()->increaseApple();
}

