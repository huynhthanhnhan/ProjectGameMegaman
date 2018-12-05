#include "TeaPotItem.h"
#include"Enemy.h"


TeaPotItem::TeaPotItem(int x, int y)
	:ItemObject(x, y, TEAPOT_WIDTH, TEAPOT_HEIGHT)
{
	this->_id = Global::TEAPOTITEM;
	this->LoadResource();
	this->_state = Global::NoneAction;
	this->_transform._scale = D3DXVECTOR2(2, 2.5);
	this->_region.update(x - REGION_WIDTH / 2, y + REGION_HEIGHT / 2, REGION_WIDTH, REGION_HEIGHT);
	this->_reach = false;
}

TeaPotItem::~TeaPotItem()
{
}

bool TeaPotItem::isReach()
{
	return this->_reach;
}

void TeaPotItem::setReach(bool flag)
{
	this->_reach = flag;
}

void TeaPotItem::clearEnemy(Object * obj)
{
	if (obj->getId() == Global::APPLEITEM || obj->getId() == Global::CAMEL || obj->getTypeObject() == Global::Static || obj->getId() == Global::TEAPOTITEM)
		return;
	if (Collision::Instance()->AABB(this->_region, obj->getRectBound()))
	{
		ActionObject* acObject = (ActionObject*)obj;
		acObject->setState(Global::Dead);
	}
}

void TeaPotItem::getItem()
{
	this->_sound = Sound::Instance();
	this->_sound->play(SOUND_TAKE_TEAPOT);
	this->_reach = true;
}

void TeaPotItem::LoadResource()
{
	this->_rect._update(369, 15, 33, 16);
	this->mListSprite[Global::NoneAction] = new SpriteManager(ResourceImage::Instance()->getItemTexture(),
		std::vector<Rect*>(), false);
	void* tempPoint = this->mListSprite[Global::Dead];
	delete tempPoint;
	this->mListSprite[Global::Dead] = new SpriteManager(ResourceImage::Instance()->getExplosingTexture(),
		ResourceFile::Instance()->LoadXML(RESOURCE_RECT_EXPLOSING, "teapotExplosing"));
}
